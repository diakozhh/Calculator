#include "../../operations/description_operator.h"
#include "../plugins_loader.h"
/**
* @brief Logarithm function
*/
class ln : public description_operator {
public:
  /**
  * Default logarithm operator constructor
  */
  ln() {
    prior = 6;
    operatorId = 'g';
    operatorName = "ln";

    isUnary = true;
  }
  /**
  * Function operator "ln"
  * @warning logarithm of zero or a negative value
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) { 
    if (value1 <= 0) {
      returnedErr.updateError(error::errorId_t::INVALID_OPERATION, "ERROR: negative or zero argument in ln");
      return -1;
    }
    return log(value1);
  }
};

description_operator* descOper() {
  return new ln();
}
