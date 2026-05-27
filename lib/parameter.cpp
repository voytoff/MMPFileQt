#include "parameter.h"

Parameter::Parameter() {}

Parameter::Parameter(double index, QDateTime time, double value)
  : index(index)
  , time(time)
  , value(value) {}
