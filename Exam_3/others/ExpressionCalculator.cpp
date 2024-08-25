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
EC::BI EC::BI::create(size_t number, const bool variables[CHARACTERS_COUNT])
{
	BI result;

	for (size_t i = 0; i < CHARACTERS_COUNT; i++)
		if (variables[i]) {
			if((number % 2) != 0) 
				result.setValue('A' + i, true);

			number /= 2;
		}

	return result;
}
bool EC::BI::getValue(char ch) const 
{
	return variables[ch - 'A'];
}
void EC::BI::setValue(char ch, bool value) 
{
	variables[ch - 'A'] = value;
}





///  Variable
EC::Var::Var(char ch) : ch(ch) {
	variables[ch - 'A'] = true;
	variablesCount = 1;
}
bool EC::Var::eval(const BI& interpretation) const {
	return interpretation.getValue(ch);
}
EC::Ex* EC::Var::clone() const {
	return new Var(*this);
}





/// Unary Expression
EC::UE::UE(char operand, Ex* expression)
	: operand(operand), expression(expression)
{
	for (size_t i = 0; i < CHARACTERS_COUNT; i++)
		variables[i] = expression->variables[i];

	variablesCount = expression->variablesCount;
}
bool EC::UE::eval(const BI& interpretation) const
{
	return !expression->eval(interpretation);
}
EC::Ex* EC::UE::clone() const 
{
	return new UE(operand, expression->clone());
}
EC::UE::~UE() {
	delete expression;
}




/// Binary Expression
EC::BE::BE(char operand, Ex* left, Ex* right)
	: operand(operand), left(left), right(right)
{
	for (size_t i = 0; i < CHARACTERS_COUNT; i++) {
		variables[i] = left->variables[i] || right->variables[i];

		if (variables[i])
			variablesCount++;
	}
}
bool EC::BE::eval(const BI& interpretation) const {
	switch (operand) {
	case OR: return  left->eval(interpretation) || right->eval(interpretation);
	case AND: return left->eval(interpretation) && right->eval(interpretation);
	default: return false;
	}
}
EC::Ex* EC::BE::clone() const {
	return new BE(operand, left->clone(), right->clone());
}
EC::BE::~BE() {
	delete left;
	delete right;
}



/// ExpressionCalculator
EC::Ex* EC::parse(const MyString& str) {
	if (str.length() == 0)
		return nullptr;

	if (str.length() == 1)
		return new Var(str[0]);

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
				return new UE(NEG, parse(swb.substr(i + 1, length - i - 1)));

			else
				return new BE(swb[i], parse(swb.substr(0, i)), parse(swb.substr(i + 1, length - i - 1)));
		}
	}

	return nullptr;
}
bool EC::isTautology() const {
	size_t variationsCount = 1 << expression->variablesCount; //za vsqka bukva imam 2 opcii => 2 na stepen count na bukvite deto sa true

	for (size_t i = 0; i < variationsCount; i++)
		if (!expression->eval(BI::create(i, expression->variables)))
			return false;

	return true;
}













/// cF,mF,free
void EC::copyFrom(const EC& other) {
	expression = other.expression->clone();
}
void EC::moveFrom(EC&& other) {
	expression = other.expression;
	other.expression = nullptr;
}
void EC::free() {
	delete expression;
}
///Big 6
EC::EC(const MyString& str) : expression(parse(str)) { }
EC::EC(const EC& other) {
	copyFrom(other);
}
EC::EC(EC&& other) noexcept {
	moveFrom(std::move(other));
}
EC& EC::operator=(const EC& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}
EC& EC::operator=(EC&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}
EC::~EC() {
	free();
}