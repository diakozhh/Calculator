#include "../../../operations/description_operator.h"
#include "../../plugins_loader.h"
/**
* @bried Sin operator constructor
*/
class sinus : public description_operator {
public:
  /**
  * Default sin operator constructor
  */
  sinus() {
    prior = 6;
    operatorId = 'a';
    operatorName = "sin";

    isUnary = true;
  }
  /**
  * Function operator "sin"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) {
    return sin(value1);
  }
};

description_operator* descOper() {
  return new sinus();
}
