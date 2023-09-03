#pragma once
#include "MyString/MyString.h"

class ExpressionCalculator 
{
	static const short CHARACTERS_COUNT = 26;

	class BooleanInterpretation {
		bool variables[CHARACTERS_COUNT] { false };
	public:
		bool getValue(char ch) const;
		void setValue(char ch, bool value);

		static BooleanInterpretation create(size_t number, const bool variables[CHARACTERS_COUNT]);
	};
	class Expression {
	public:
		bool variables[CHARACTERS_COUNT] { false };
		short variablesCount = 0;

		virtual bool eval(const BooleanInterpretation& interpretation) const = 0;
		virtual Expression* clone() const = 0;
		virtual ~Expression() = default;
	};
	class Variable : public Expression {
		char ch;
	public:
		Variable(char ch);
		bool eval(const BooleanInterpretation& interpretation) const override;
		Expression* clone() const override;
	};
	class UnaryExpression : public Expression {
		char operand;
		Expression* expression;
	public:
		UnaryExpression(char operand, Expression* expression);
		bool eval(const BooleanInterpretation& interpretation) const override;
		Expression* clone() const override;
		~UnaryExpression();
	};
	class BinaryExpression : public Expression {
		char operand;
		Expression* left;
		Expression* right;
	public:
		BinaryExpression(char operand, Expression* left, Expression* right);
		bool eval(const BooleanInterpretation& interpretation) const override;
		Expression* clone() const override;
		~BinaryExpression();
	};

	Expression* expression = nullptr;
	Expression* parse(const MyString& str);

	void copyFrom(const ExpressionCalculator& other);
	void moveFrom(ExpressionCalculator&& other);
	void free();
public:
	ExpressionCalculator(const MyString& str);
	ExpressionCalculator(const ExpressionCalculator& other);
	ExpressionCalculator(ExpressionCalculator&& other) noexcept;
	ExpressionCalculator& operator=(const ExpressionCalculator& other);
	ExpressionCalculator& operator=(ExpressionCalculator&& other) noexcept;
	~ExpressionCalculator();

	bool isTautology() const;
};