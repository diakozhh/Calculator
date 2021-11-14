#include <string>
#include "../error.h"

#pragma once

class description_operator {
protected:
  unsigned int prior;
  char operatorId;
  std::string operatorName;

  bool isUnary;
public:
  description_operator() {};
  unsigned int getPrior() const {return prior; }
  char getId() const { return operatorId; }
  const std::string& getOperatorName() const {return operatorName; }

  bool checkUnary() const {return isUnary;}

  virtual double operation(double value1, double value2, error& returnedErr) = 0;
};