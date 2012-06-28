#pragma once

#include "config.h"

#include <memory>
#include <string>

#include "Kinds.h"

namespace trench {

class Expression {
	TRENCH_CLASS_WITH_KINDS(Expression, kind)

	public:

	enum Kind {
		CONSTANT,
		REGISTER,
		UNARY,
		BINARY,
		NOT_BLOCKED,
	};

	public:

	Expression(Kind kind): kind_(kind) {}
};

typedef int Domain;

class Constant: public Expression {
	Domain value_;

	public:

	Constant(Domain value): Expression(CONSTANT), value_(value) {}

	Domain value() const { return value_; }
};

class Register: public Expression {
	std::string name_;

	public:

	Register(const std::string &name):
		Expression(REGISTER), name_(name)
	{}

	const std::string &name() const { return name_; }
};

class UnaryOperator: public Expression {
	std::shared_ptr<Expression> operand_;

	public:

	UnaryOperator(const std::shared_ptr<Expression> &operand):
		Expression(UNARY), operand_(operand)
	{}

	const std::shared_ptr<Expression> &operand() const { return operand_; }
};

class BinaryOperator: public Expression {
	public:

	enum Kind {
		EQ,
		NEQ,
		LT,
		LEQ,
		GT,
		GEQ,
		AND,
		OR,
		ADD,
		SUB
	};

	private:

	Kind kind_;
	std::shared_ptr<Expression> left_;
	std::shared_ptr<Expression> right_;

	public:

	BinaryOperator(Kind kind, const std::shared_ptr<Expression> &left, const std::shared_ptr<Expression> &right):
		Expression(BINARY), kind_(kind), left_(left), right_(right)
	{}

	Kind kind() const { return kind_; }
	const std::shared_ptr<Expression> &left() const { return left_; }
	const std::shared_ptr<Expression> &right() const { return right_; }
};

class NotBlocked: public Expression {
	public:

	NotBlocked():
		Expression(NOT_BLOCKED)
	{}
};

} // namespace trench

TRENCH_REGISTER_CLASS_KIND(Expression, Constant, Expression::CONSTANT)
TRENCH_REGISTER_CLASS_KIND(Expression, Register, Expression::REGISTER)
TRENCH_REGISTER_CLASS_KIND(Expression, UnaryOperator, Expression::UNARY)
TRENCH_REGISTER_CLASS_KIND(Expression, BinaryOperator, Expression::BINARY)
TRENCH_REGISTER_CLASS_KIND(Expression, NotBlocked, Expression::NOT_BLOCKED)
