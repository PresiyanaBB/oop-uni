#pragma once
#include "MyString/MyString.h"

class EC 
{
	static const short CHARACTERS_COUNT = 26;

	class BI {
		bool variables[CHARACTERS_COUNT] { false };
	public:
		bool getValue(char ch) const;
		void setValue(char ch, bool value);

		static BI create(size_t number, const bool variables[CHARACTERS_COUNT]);
	};
	class Ex {
	public:
		bool variables[CHARACTERS_COUNT] { false };
		short variablesCount = 0;

		virtual bool eval(const BI& interpretation) const = 0;
		virtual Ex* clone() const = 0;
		virtual ~Ex() = default;
	};
	class Var : public Ex {
		char ch;
	public:
		Var(char ch);
		bool eval(const BI& interpretation) const override;
		Ex* clone() const override;
	};
	class UE : public Ex {
		char operand;
		Ex* expression;
	public:
		UE(char operand, Ex* expression);
		bool eval(const BI& interpretation) const override;
		Ex* clone() const override;
		~UE();
	};
	class BE : public Ex {
		char operand;
		Ex* left;
		Ex* right;
	public:
		BE(char operand, Ex* left, Ex* right);
		bool eval(const BI& interpretation) const override;
		Ex* clone() const override;
		~BE();
	};

	Ex* expression = nullptr;
	Ex* parse(const MyString& str);

	void copyFrom(const EC& other);
	void moveFrom(EC&& other);
	void free();
public:
	EC(const MyString& str);
	EC(const EC& other);
	EC(EC&& other) noexcept;
	EC& operator=(const EC& other);
	EC& operator=(EC&& other) noexcept;
	~EC();

	bool isTautology() const;
};