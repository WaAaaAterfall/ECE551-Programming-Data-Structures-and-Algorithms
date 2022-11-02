#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression() {}
  NumExpression(long number) : num(number) {}
  virtual std::string toString() const {
    std::stringstream res;
    res << num;
    return res.str();
  }
  virtual long evaluate() const { return num; }
  virtual ~NumExpression() {}
};

class OperationExpression : public Expression {
 protected:
  Expression * lhs;
  Expression * rhs;
  const char * operation;

 public:
  OperationExpression() {}
  OperationExpression(Expression * lhs, Expression * rhs, const char * op) :
      lhs(lhs), rhs(rhs), operation(op) {}
  virtual std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << *operation << rhs->toString() << ")";
    return res.str();
  }

  virtual ~OperationExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OperationExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) :
      OperationExpression(lhs, rhs, "+") {}

  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public OperationExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) :
      OperationExpression(lhs, rhs, "-") {}

  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public OperationExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) :
      OperationExpression(lhs, rhs, "*") {}

  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public OperationExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) :
      OperationExpression(lhs, rhs, "/") {}
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};
