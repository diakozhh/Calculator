#include "../../../operations/description_operator.h"
#include "../../plugins_loader.h"
/**
* @bried Cos operator constructor
*/
class cosin : public description_operator {
public:
  /**
  * Default cos operator constructor
  */
  cosin() {
    prior = 6;
    operatorId = 'b';
    operatorName = "cos";

    isUnary = true;
  }
  /**
  * Function operator "cos"
  * @param value1 is first value for binary operator
  * @param value2 is second value for binary operator
  * @param returnedErr is error if operator takes invalid values
  * @return result of operator
  */
  virtual double operation(double value1, double value2, error& returnedErr) {
    return cos(value1);
  }
};

description_operator* descOper() {
  return new cosin();
}
