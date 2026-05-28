#include "mchannelblock.h"
#include "lib.h"

MChannelBlock::MChannelBlock(QObject *parent)
  : QObject{parent}
  , dataBlockArray(new QList<DataBlock*>()) {}

QList<Parameter *> MChannelBlock::data() {
  return {};
}

DataBlockArray *MChannelBlock::array(int persecond) {
  DataBlockArray* result = nullptr;
  if (finalData.contains(persecond))
    return finalData.value(persecond);
  if (frequencies.contains(persecond)) {
    QVector<Parameter*> array = data();
    double f = frequency;
    result = new DataBlockArray(this->name, f, persecond);
    double temp = f / persecond;      // Ищем ближайший делитель
    int mod = (int)std::round(temp);  // он же шаг в буфере даных
    if (mod == 0) mod = 1;            // несущая частота меньше запрошенной
    auto repeat = (int)(1 / temp);    // число повторов значения, если частота меньше запрошенной
    if (repeat == 0) repeat = 1;
    auto deltaTime = 1000 / std::min((int)f, persecond); // шаг времени
    double index = 0;
    int position = 0;
    for (int n = 0; n < array.length(); n += mod) {
      auto parameter = array.at(n);
      auto value = mod == 1 ? parameter->value : lib::avg(array.mid(n, mod));
      for (int i = 0; i < repeat; i++) {
        auto time = parameter->time.addMSecs(deltaTime*i);
        Parameter p = Parameter(lib::increment(persecond, index), time, value);
        result->append(p);
      }
    }
    finalData[persecond] = result;
  }
  return result;
}

