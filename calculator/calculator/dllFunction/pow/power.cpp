#include "../../operations/description_operator.h"
#include "../plugins_loader.h"
/**
* @bried Power function
*/
class power : public description_operator {
public:
  /**
  * Default power operator constructor
  */
  power() {
    prior = 6;
    operatorId = 'e';
    operatorName = "^";

    isUnary = false;
  }
  /**
  * Function operator "^"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) {
    return pow(value1, value2);
  }
};

description_operator* descOper() {
  return new power();
}
