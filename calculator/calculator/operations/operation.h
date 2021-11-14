#include "description_operator.h"

#pragma once
/**
* @brief Addition operator
*/
class addition : public description_operator {
public:
  /**
  * Default addition operator constructor
  */
  addition() {
    prior = 2;
    operatorId = '+';
    operatorName = "+";

    isUnary = false;
  }
  /**
  * Function operator "+"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) { return value1 + value2; }
};
/**
* @brief Subtraction operator
*/
class subtraction : public description_operator {
public:
  /**
   * Default subtraction operator constructor
  */
  subtraction() {
    prior = 2;
    operatorId = '-';
    operatorName = "-";

    isUnary = false;
  }
  /**
  * Function operator "-"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) { return value1 - value2; }
};
/**
* @brief Multiplication operator
*/
class multiplication : public description_operator {
public:
  /**
  * Default multiplication operator constructor
  */
  multiplication() {
    prior = 3;
    operatorId = '*';
    operatorName = "*";

    isUnary = false;
  }
 /**
 * Function operator "*"
 * @param value1 is first value for binary operator
 * @param value2 is second value for binary operator
 * @param returnedErr is error if operator takes invalid values
 * @return result of operator
 */
  virtual double operation(double value1, double value2, error& returnedErr) {return value1 * value2; }
};
/**
* @brief Division operator
*/
class division : public description_operator {
public:
  /**
  * Default division operator constructor
  */
  division() {
    prior = 3;
    operatorId = '/';
    operatorName = "/";

    isUnary = false;
  }
/**
* Function operator "/"
* @warning division by zero
* @param value1 is first value for binary operator
* @param value2 is second value for binary operator
* @param returnedErr is error if operator takes invalid values
* @return result of operator
*/
  virtual double operation(double value1, double value2, error& returnedErr) {
    if (value2 == 0) {
      returnedErr.updateError(error::errorId_t::INVALID_OPERATION, "ERROR: division by zero");
      return -1;
    }
    return value1 / value2;
  }
};
/**
* @brief Unary minus operator
*/
class unary_minus : public description_operator {
public:
  /**
  * Default unary minus operator constructor
  */
  unary_minus() {
    prior = 4;
    operatorId = '!';
    operatorName = "-";

    isUnary = true;
  }
  /**
  * Function operator "-"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErrr) {
    return (-1.0) * value1;
  }
};
/**
* @brief Opening bracket operator
*/
class opening_bracket : public description_operator {
public:
  /**
  * Default opening bracket operator constructor
  */
  opening_bracket() {
    prior = 0;
    operatorId = '(';
    operatorName = "(";

    isUnary = false;
  }
  /**
  * Function operator "("
  * @details '(' is not operator
  * @warning unpair brackets
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return none
  */
  virtual double operation(double value1, double value2, error& returnedErr) {
    returnedErr.updateError(error::errorId_t::INVALID_EVAL, "ERROR: unpaired opening bracket");
    return -1;
  }
};
/**
* @brief Closing bracket operator
*/
class closing_bracket : public description_operator {
public:
  /**
  * Default closing bracket operator constructor
  */
  closing_bracket() {
    prior = 1;
    operatorId = ')';
    operatorName = ")";

    isUnary = false;
  }
  /**
    * Function operator ")"
    * @details ')' is not operator
    * @warning unpair brackets
    * @param value1 is first value for binary operator
    * @param value2 is second value for binary operator
    * @param returnedErr is error if operator takes invalid values
    * @return none
  */
  virtual double operation(double value1, double value2, error& returnedErr) {
    returnedErr.updateError(error::errorId_t::INVALID_EVAL, "ERROR: unpaired closing bracket");
    return -1;
  }
};
