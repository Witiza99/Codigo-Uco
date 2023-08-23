/*!
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <list>
#include <limits>

// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

//
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"

#include "../table/stringVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType()
{
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::print()
{
  std::cout << "VariableNode: " << this->_id << std::endl;
  std::cout << "Type: " << this->getType() << std::endl;
}


double lp::VariableNode::evaluateNumber()
{
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the variable is not numeric",
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the variable is not boolean",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

std::string lp::VariableNode::evaluateString()
{
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::StringVariable *var = (lp::StringVariable *) table.getSymbol(this->_id);

		// Copy the value of the StringVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateString(): the variable is not string",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::print()
{
  std::cout << "ConstantNode: " << this->_id << std::endl;
  std::cout << "Type: " << this->getType() << std::endl;
}

int lp::ConstantNode::getType()
{
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber()
{
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the constant is not numeric",
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the constant is not boolean",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::print()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber()
{
    return this->_number;
}

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::StringNode::getType()
{
	return STRING;
}


void lp::StringNode::print()
{
  std::cout << "StringNode: " << this->_string << std::endl;
}

std::string lp::StringNode::evaluateString()
{
    return this->_string;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Numeric Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Logical Unary Operator");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = NUMBER;
	else
		warning("Runtime error: incompatible types for", "Numeric Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = STRING;
	else
		warning("Runtime error: incompatible types for", "String Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;

	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = BOOL;
	else if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
		result = BOOL;
	else if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = BOOL;
	else
		warning("Runtime error: incompatible types for", "Relational Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;

	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		//
		result = BOOL;
	}
	else
		warning("Runtime error: incompatible types for", "Logical Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print()
{
  std::cout << "UnaryMinusNode: "  << std::endl;
  std::cout << "-";
  this->_exp->print();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "UnaryMinus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print()
{
  std::cout << "UnaryPlusNode: "  << std::endl;
  this->_exp->print();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ","UnaryPlus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print()
{
  std::cout << "PlusNode: "  << std::endl;
  this->_left->print();
  std::cout << " + ";
  this->_right->print();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Plus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print()
{
  std::cout << "MinusNode: "  << std::endl;
  this->_left->print();
  std::cout << " - ";
  this->_right->print();
}

double lp::MinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Minus");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print()
{
	std::cout << "MultiplicationNode: "  << std::endl;
	this->_left->print();
	std::cout << " * ";
	this->_right->print();
}

double lp::MultiplicationNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ","Multiplication");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
  std::cout << "DivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::DivisionNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Runtime error", "Division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Division");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::QuotientNode::print()
{
  std::cout << "QuotientNode: " << std::endl;
  this->_left->print();
  std::cout << " quotient ";
  this->_right->print();
}

double lp::QuotientNode::evaluateNumber()
{
	int result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Runtime error", "Division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Division");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
  std::cout << "ModuloNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::ModuloNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

    	if(std::abs(rightNumber) > ERROR_BOUND)
				result = (int) leftNumber % (int) rightNumber;
		else
			warning("Runtime error", "Division by zero");
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Modulo");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print()
{
	std::cout << "PowerNode: "  << std::endl;
	this->_left->print();
	std::cout << " ^ ";
	this->_right->print();
}

double lp::PowerNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Power");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatNode::print()
{
	std::cout << "ConcatNode: "  << std::endl;
	this->_left->print();
	std::cout << " || ";
	this->_right->print();
}

std::string lp::ConcatNode::evaluateString()
{
	std::string result = "";

	// Ckeck the types of the expressions
	if (this->getType() == STRING)
	{
		result = this->_left->evaluateString() + this->_right->evaluateString() ;
	}
	else
	{
		warning("Runtime error: the expressions are not string for", "concatenation");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::print()
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluateNumber()
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;

	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		warning("Runtime error: incompatible type for", "BuiltinFunctionNode_1");

	return	result;
}

void lp::BuiltinFunctionNode_1::print()
{
	std::cout << "BuiltinFunctionNode_1: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_1::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible type of parameter for ", this->_id);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;

	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		warning("Runtime error: incompatible types for", "BuiltinFunctionNode_2");

	return	result;
}


void lp::BuiltinFunctionNode_2::print()
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", this->_id);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
  std::cout << "GreaterThanNode: " << std::endl;
  this->_left->print();
  std::cout << " > ";
  this->_right->print();
}

bool lp::GreaterThanNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		if(this->_left->getType() == NUMBER and this->_right->getType() == NUMBER){
			double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber > rightNumber);
		}else if(this->_left->getType() == STRING and this->_right->getType() == STRING){
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();

			for (unsigned i = 0; i < leftString.size(); i++) {
				leftString[i] = tolower(leftString[i]);
			}
			for (unsigned i = 0; i < rightString.size(); i++) {
				rightString[i] = tolower(rightString[i]);
			}

			int cmp = strcmp(leftString.c_str(), rightString.c_str());

			if (cmp > 0) {
				result = true;
			}else{
				result = false;
			}
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
  std::cout << "GreaterOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " >= ";
  this->_right->print();
}

bool lp::GreaterOrEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		if(this->_left->getType() == NUMBER and this->_right->getType() == NUMBER){
			double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber >= rightNumber);
		}else if(this->_left->getType() == STRING and this->_right->getType() == STRING){
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();

			for (unsigned i = 0; i < leftString.size(); i++) {
				leftString[i] = tolower(leftString[i]);
			}
			for (unsigned i = 0; i < rightString.size(); i++) {
				rightString[i] = tolower(rightString[i]);
			}

			int cmp = strcmp(leftString.c_str(), rightString.c_str());

			if (cmp >= 0) {
				result = true;
			}else{
				result = false;
			}
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
  std::cout << "LessThanNode: " << std::endl;
  this->_left->print();
  std::cout << " < ";
  this->_right->print();
}

bool lp::LessThanNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		if (this->_left->getType() == NUMBER and this->_right->getType() == NUMBER) {
			double leftNumber, rightNumber;
			leftNumber = this->_left->evaluateNumber();
			rightNumber = this->_right->evaluateNumber();

			result = (leftNumber < rightNumber);
		}else if(this->_left->getType() == STRING and this->_right->getType() == STRING){
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();

			for (unsigned i = 0; i < leftString.size(); i++) {
				leftString[i] = tolower(leftString[i]);
			}
			for (unsigned i = 0; i < rightString.size(); i++) {
				rightString[i] = tolower(rightString[i]);
			}

			int cmp = strcmp(leftString.c_str(), rightString.c_str());

			if (cmp < 0) {
				result = true;
			}else{
				result = false;
			}
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
  std::cout << "LessOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " <= ";
  this->_right->print();
}

bool lp::LessOrEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		if(this->_left->getType() == NUMBER and this->_right->getType() == NUMBER){
			double leftNumber, rightNumber;
			leftNumber = this->_left->evaluateNumber();
			rightNumber = this->_right->evaluateNumber();

			result = (leftNumber <= rightNumber);
		}else if(this->_left->getType() == STRING and this->_right->getType() == STRING){
			std::string leftString, rightString;
			leftString = this->_left->evaluateString();
			rightString = this->_right->evaluateString();

			for (unsigned i = 0; i < leftString.size(); i++) {
				leftString[i] = tolower(leftString[i]);
			}
			for (unsigned i = 0; i < rightString.size(); i++) {
				rightString[i] = tolower(rightString[i]);
			}

			int cmp = strcmp(leftString.c_str(), rightString.c_str());

			if (cmp <= 0) {
				result = true;
			}else{
				result = false;
			}
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
  std::cout << "EqualNode: " << std::endl;
  this->_left->print();
  std::cout << " = ";
  this->_right->print();
}

bool lp::EqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) < ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				//
				result = (leftBoolean == rightBoolean);
				break;
			case STRING:
			{
				std::string leftString, rightString;
				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				for (unsigned i = 0; i < leftString.size(); i++) {
					leftString[i] = tolower(leftString[i]);
				}
				for (unsigned i = 0; i < rightString.size(); i++) {
					rightString[i] = tolower(rightString[i]);
				}

				int cmp = strcmp(leftString.c_str(), rightString.c_str());

				if (cmp == 0) {
					result = true;
				}else{
					result = false;
				}
				break;
			}
		  default:
				warning("Runtime error: incompatible types of parameters for ",
								"Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ",
						"Equal operator");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
  std::cout << "NotEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " != ";
  this->_right->print();
}

bool lp::NotEqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) >= ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				//
				result = (leftBoolean != rightBoolean);
				break;
			case STRING:
			{
				std::string leftString, rightString;
				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				for (unsigned i = 0; i < leftString.size(); i++) {
					leftString[i] = tolower(leftString[i]);
				}
				for (unsigned i = 0; i < rightString.size(); i++) {
					rightString[i] = tolower(rightString[i]);
				}

				int cmp = strcmp(leftString.c_str(), rightString.c_str());

				if (cmp != 0) {
					result = true;
				}else{
					result = false;
				}
				break;
			}
		  default:
				warning("Runtime error: incompatible types of parameters for ",
								"Not Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "Not Equal operator");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: " << std::endl;
  this->_left->print();
  std::cout << " && ";
  this->_right->print();
}

bool lp::AndNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator And");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: " << std::endl;
  this->_left->print();
  std::cout << " || ";
  this->_right->print();
}

bool lp::OrNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Or");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
  std::cout << "NotNode: " << std::endl;
  std::cout << " ! ";
  this->_exp->print();
}

bool lp::NotNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Not");
	}

	return result;
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print()
{
  std::cout << "assignment_node: "  << std::endl;
  std::cout << this->_id << " = ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate()
{
	/* Get the identifier in the table of symbols as Variable */
	/*
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;

			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable
					// with the type BOOL and the value
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;
			case STRING:
			{
				std::string value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateString();

				if (firstVar->getType() == STRING)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::StringVariable *v = (lp::StringVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable
					// with the type BOOL and the value
					lp::StringVariable *v = new lp::StringVariable(this->_id,
											VARIABLE,STRING,value);
					table.installSymbol(v);
				}
			}
			break;

			default:
				warning("Runtime error: incompatible type of expression for ", "Assigment");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value of the previous variable
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not BOOL
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type BOOL and the value of the previous variable
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;
			case STRING:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::StringVariable *secondVar = (lp::StringVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == STRING)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::StringVariable *firstVar = (lp::StringVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable
					// with the type NUMBER and the value of the previous variable
					lp::StringVariable *firstVar = new lp::StringVariable(this->_id,
											VARIABLE,STRING,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			default:
				warning("Runtime error: incompatible type of expression for ", "Assigment");
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WriteStmt::print()
{
  std::cout << "WriteStmt: "  << std::endl;
  std::cout << " write ";
  this->_exp->print();
  std::cout << std::endl;
}


void lp::WriteStmt::evaluate()
{

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber();
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "true";
			else
				std::cout << "false";

			break;

		default:
			warning("Runtime error: incompatible type for ", "write");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print()
{
  std::cout << "ReadStmt: "  << std::endl;
  std::cout << " read (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate()
{
	std::string stringAux;
	double value;
	fflush(stdin);
	std::cin >> stringAux;
	std::cin.ignore();

	value = atof(stringAux.c_str());

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable
		// with the type NUMBER and the read value
		lp::NumericVariable *n = new lp::NumericVariable(this->_id,
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WriteStringStmt::print()
{
  std::cout << "WriteStringStmt: "  << std::endl;
  std::cout << " writeString ";
  this->_exp->print();
  std::cout << std::endl;
}


void lp::WriteStringStmt::evaluate()
{


	if (this->_exp->getType() == STRING) {
		std::string aux = this->_exp->evaluateString();
		for (unsigned i = 0; i < aux.size(); i++) {
			if (aux[i] != '\\') {
				std::cout << aux[i];
			}else{
				i++;
				switch (aux[i]) {
					case 't':
						std::cout << "\t";
						break;
					case 'n':
						std::cout << "\n";
						break;
					case '\'':
						std::cout << "'";
						break;
					default:
						std::cout << "\\" <<aux[i];
				}
			}
		}
	}else{
		warning("Runtime error: incompatible type for ", "writeString");
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::ReadStringStmt::print()
{
  std::cout << "ReadStringStmt: "  << std::endl;
  std::cout << " readstring (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStringStmt::evaluate()
{
	fflush(stdin);
	char stringAux[100];
	std::cin.getline(stringAux, 100);
	fflush(stdin);
	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == STRING)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::StringVariable *n = (lp::StringVariable *) table.getSymbol(this->_id);

		/* Assignment the read value to the identifier */
		n->setValue(stringAux);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable
		// with the type NUMBER and the read value
		lp::StringVariable *n = new lp::StringVariable(this->_id,
									  VARIABLE,STRING,stringAux);

		table.installSymbol(n);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ClearStmt::print()
{
  std::cout << "ClearStmt: "  << std::endl;
}


void lp::ClearStmt::evaluate()
{
	std::cout << CLEAR_SCREEN;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlaceStmt::print()
{
  std::cout << "PlaceStmt: "  << std::endl;
	this->_left->print();
	this->_right->print();
}


void lp::PlaceStmt::evaluate()
{
	PLACE((int) this->_left->evaluateNumber(),(int) this->_right->evaluateNumber());
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print()
{
  std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate()
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print()
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Consequent
	std::list<Statement*>::iterator i=this->_stmt1->begin();
	while(i!=_stmt1->end()) {
		(*i)->print();
		i++;
	}

	 // The alternative is printed if exists
	i=this->_stmt2->begin();
 	while(i!=_stmt2->end()) {
 		(*i)->print();
		i++;
 	}

  std::cout << std::endl;
}


void lp::IfStmt::evaluate()
{

	//check if the condition is boolean
	if (this->_cond->getType() != BOOL) {
		warning("Runtime error: incompatible types for", "if condition");
	}else{
		// If the condition is true,
		if (this->_cond->evaluateBool() == true ){
			// the consequent is run
			std::list<Statement*>::iterator i=this->_stmt1->begin();

			while(i!=_stmt1->end()) {
				(*i)->evaluate();
				i++;
			}
		}
	    // Otherwise, the alternative is run if exists
		else if (this->_stmt2 != NULL){
			std::list<Statement*>::iterator i=this->_stmt2->begin();
			while(i!=_stmt2->end()) {
				(*i)->evaluate();
				i++;
			}
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print()
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
	std::list<Statement*>::iterator i=this->_stmt->begin();
	while(i!=_stmt->end()) {
		(*i)->print();
		i++;
	}

  std::cout << std::endl;
}


void lp::WhileStmt::evaluate()
{
	  // While the condition is true. the body is run
	  while (this->_cond->evaluateBool() == true)
	  {
			std::list<Statement*>::iterator i=this->_stmt->begin();
			while(i!=_stmt->end()) {
				(*i)->evaluate();
				i++;
			}
	  }

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in final work

void lp::RepeatStmt::print()
{
  std::cout << "RepeatStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
	std::list<Statement*>::iterator i=this->_stmt->begin();
	while(i!=_stmt->end()) {
		(*i)->print();
		i++;
	}

  std::cout << std::endl;
}


void lp::RepeatStmt::evaluate()
{
	  // While the condition is true. the body is run
	  do
	  {
			std::list<Statement*>::iterator i=this->_stmt->begin();
			while(i!=_stmt->end()) {
				(*i)->evaluate();
				i++;
			}
	  }while(this->_cond->evaluateBool() == false);
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in final work

void lp::ForStmt::print()
{
  std::cout << "ForStmt: "  << std::endl;
  // identifier
  std::cout << this->_identifier;
	// exp1
  this->_exp1->print();
	// exp2
  this->_exp2->print();
	// identifier
	if (this->_stepExp != NULL) {
	  this->_stepExp->print();
	}

  // Body of the for loop
	std::list<Statement*>::iterator i=this->_stmt->begin();
	while(i!=_stmt->end()) {
		(*i)->print();
		i++;
	}

  std::cout << std::endl;
}


void lp::ForStmt::evaluate()
{
	//check if condition is boolean
	if (this->_exp1->getType() != NUMBER) {
		warning("Runtime error: incompatible types for", "first for expresion");
	}else if(this->_exp2->getType() != NUMBER){
		warning("Runtime error: incompatible types for", "second for expresion");
	}else{
		lp::Variable *var = (lp::Variable *) table.getSymbol(this->_identifier);

		//check if _identifier is a number
		if (var->getType() != NUMBER)
		{
			table.eraseSymbol(this->_identifier);

			// Insert the variable in the table of symbols as NumericVariable
			// with the type NUMBER and the value
			lp::NumericVariable *v = new lp::NumericVariable(this->_identifier, VARIABLE, NUMBER, 0);
			table.installSymbol(v);
		}

		int step;
		//check if step is NULL
		if (this->_stepExp != NULL) {
			step = this->_stepExp->evaluateNumber();
		}else{
			//if step doesn't exists, put the default value of one
			step = 1;
		}

		if (step == 0) {
			warning("Infinte loop in for: ", "step equals zero");
		}else
		if ((this->_exp1->evaluateNumber() > this->_exp2->evaluateNumber()) and step > 0 ) {
			warning("Infinte loop in for: ", "'from' greater than 'to' and step is positive");
		}else
		if ((this->_exp1->evaluateNumber() < this->_exp2->evaluateNumber()) and step < 0 ) {
			warning("Infinte loop in for: ", "'to' greater than 'from' and step is negative");
		}else{
			//Numeric variable to modify the identifier
			lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_identifier);
			//for loop
			//from _exp1 to _exp2 with step "step"
			for (int a = this->_exp1->evaluateNumber(); a <= this->_exp2->evaluateNumber(); a = a + step) {
				//modify the identifier in every step
				v->setValue(a);
				std::list<Statement*>::iterator i=this->_stmt->begin();
				//execute the list of statements
				while(i!=_stmt->end()) {
					(*i)->evaluate();
					i++;
				}
			}
		}
	}


}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::BlockStmt::print()
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
  {
     (*stmtIter)->print();
  }
}


void lp::BlockStmt::evaluate()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
  {
    (*stmtIter)->evaluate();
  }
}





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++)
  {
     (*stmtIter)->print();
  }
}



void lp::AST::evaluate()
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++)
  {
    (*stmtIter)->evaluate();
  }
}
