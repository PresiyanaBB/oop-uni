#include "ExpressionCalculator.h"

namespace {
	const char AND = '^';
	const char OR = 'v';
	const char NEG = '!';

	bool isOperator(char ch) {
		return ch == AND || ch == OR || ch == NEG;
	}
}

/// BooleanInterpretation
ExpressionCalculator::BooleanInterpretation ExpressionCalculator::BooleanInterpretation::create(size_t number, const bool variables[CHARACTERS_COUNT])
{
	BooleanInterpretation result;

	for (size_t i = 0; i < CHARACTERS_COUNT; i++)
		if (variables[i]) {
			if((number % 2) != 0) 
				result.setValue('A' + i, true);

			number /= 2;
		}

	return result;
}
bool ExpressionCalculator::BooleanInterpretation::getValue(char ch) const 
{
	return variables[ch - 'A'];
}
void ExpressionCalculator::BooleanInterpretation::setValue(char ch, bool value) 
{
	variables[ch - 'A'] = value;
}
///  Variable
ExpressionCalculator::Variable::Variable(char ch) : ch(ch) {
	variables[ch - 'A'] = true;
	variablesCount = 1;
}
bool ExpressionCalculator::Variable::eval(const BooleanInterpretation& interpretation) const {
	return interpretation.getValue(ch);
}
ExpressionCalculator::Expression* ExpressionCalculator::Variable::clone() const {
	return new Variable(*this);
}
/// Unary Expression
ExpressionCalculator::UnaryExpression::UnaryExpression(char operand, Expression* expression)
	: operand(operand), expression(expression)
{
	for (size_t i = 0; i < CHARACTERS_COUNT; i++)
		variables[i] = expression->variables[i];

	variablesCount = expression->variablesCount;
}
bool ExpressionCalculator::UnaryExpression::eval(const BooleanInterpretation& interpretation) const
{
	return !expression->eval(interpretation);
}
ExpressionCalculator::Expression* ExpressionCalculator::UnaryExpression::clone() const 
{
	return new UnaryExpression(operand, expression->clone());
}
ExpressionCalculator::UnaryExpression::~UnaryExpression() {
	delete expression;
}
/// Binary Expression
ExpressionCalculator::BinaryExpression::BinaryExpression(char operand, Expression* left, Expression* right)
	: operand(operand), left(left), right(right)
{
	for (size_t i = 0; i < CHARACTERS_COUNT; i++) {
		variables[i] = left->variables[i] || right->variables[i];

		if (variables[i])
			variablesCount++;
	}
}
bool ExpressionCalculator::BinaryExpression::eval(const BooleanInterpretation& interpretation) const {
	switch (operand) {
	case OR: return  left->eval(interpretation) || right->eval(interpretation);
	case AND: return left->eval(interpretation) && right->eval(interpretation);
	default: return false;
	}
}
ExpressionCalculator::Expression* ExpressionCalculator::BinaryExpression::clone() const {
	return new BinaryExpression(operand, left->clone(), right->clone());
}
ExpressionCalculator::BinaryExpression::~BinaryExpression() {
	delete left;
	delete right;
}
/// ExpressionCalculator
ExpressionCalculator::Expression* ExpressionCalculator::parse(const MyString& str) {
	if (str.length() == 0)
		return nullptr;

	if (str.length() == 1)
		return new Variable(str[0]);

	MyString swb = str.substr(1, str.length() - 2); //str without brackets
	size_t brCount = 0;

	size_t length = swb.length();
	for (size_t i = 0; i < length; i++) 
	{
		if (swb[i] == '(')
			brCount++;
		
		else if (swb[i] == ')')
			brCount--;
		
		else if (isOperator(swb[i]) && brCount == 0)
		{
			if (swb[i] == NEG)
				return new UnaryExpression(NEG, parse(swb.substr(i + 1, length - i - 1)));

			else
				return new BinaryExpression(swb[i], parse(swb.substr(0, i)), parse(swb.substr(i + 1, length - i - 1)));
		}
	}

	return nullptr;
}
bool ExpressionCalculator::isTautology() const {
	size_t variationsCount = 1 << expression->variablesCount; //za vsqka bukva imam 2 opcii => 2 na stepen count na bukvite deto sa true

	for (size_t i = 0; i < variationsCount; i++)
		if (!expression->eval(BooleanInterpretation::create(i, expression->variables)))
			return false;

	return true;
}




/// cF,mF,free
void ExpressionCalculator::copyFrom(const ExpressionCalculator& other) {
	expression = other.expression->clone();
}
void ExpressionCalculator::moveFrom(ExpressionCalculator&& other) {
	expression = other.expression;
	other.expression = nullptr;
}
void ExpressionCalculator::free() {
	delete expression;
}
///Big 6
ExpressionCalculator::ExpressionCalculator(const MyString& str) : expression(parse(str)) { }
ExpressionCalculator::ExpressionCalculator(const ExpressionCalculator& other) {
	copyFrom(other);
}
ExpressionCalculator::ExpressionCalculator(ExpressionCalculator&& other) noexcept {
	moveFrom(std::move(other));
}
ExpressionCalculator& ExpressionCalculator::operator=(const ExpressionCalculator& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}
ExpressionCalculator& ExpressionCalculator::operator=(ExpressionCalculator&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}
ExpressionCalculator::~ExpressionCalculator() {
	free();
}