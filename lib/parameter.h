#ifndef PARAMETER_H
#define PARAMETER_H

#include <QDateTime>

class Parameter
{
public:
  Parameter();

  bool operator<(const Parameter &other) const {
    return time < other.time;
  }

  Parameter(double index, QDateTime time, double value);
  QDateTime time;
  double index;
  double value;
};

#endif // PARAMETER_H
