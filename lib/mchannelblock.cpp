#include "mchannelblock.h"
#include "lib.h"

MChannelBlock::MChannelBlock(QObject *parent)
  : QObject{parent}
  //, dataBlockArray(new QList<DataBlock*>())
{}

QList<Parameter *> MChannelBlock::data() {
  auto buffer = fileItem->data();
  if (_data.length() == 0 && buffer.length() > 0) {
    int pos = 0;
    double index = 0;
    int persecond = fileItem->frequency;
    int blockLength = fileItem->blockSize * 4;
    int allLength = buffer.length() / (blockLength + 8/*дата*/);
    while (pos < buffer.length()) {
      auto time = lib::toOleTime(buffer.mid(pos, 8)); pos += 8;
      auto n = pos + blockID * 4;
      auto value = lib::toFloat(buffer.mid(n, 4));
      pos += blockLength;
      Parameter *p = new Parameter(lib::increment(persecond, index), time, value);
      _data.append(p);
      if (std::fmod(index, 100) == 0)
        emit fileItem->progress((int)index, allLength);
    }
    emit dataReceived(index * persecond);
  }
  return _data;
}

DataBlockArray *MChannelBlock::array(int persecond) {
  DataBlockArray* result = nullptr;
  if (finalData.contains(persecond))
    return finalData.value(persecond);
  if (frequencies.contains(persecond)) {
    QVector<Parameter*> array = data();
    if (array.length() == 0) return result;
    double frequency = fileItem->frequency;
    result = new DataBlockArray(this->name, frequency, persecond, unit);
    double temp = frequency / persecond;      // Ищем ближайший делитель
    int mod = (int)std::round(temp);  // он же шаг в буфере даных
    if (mod == 0) mod = 1;            // несущая частота меньше запрошенной
    auto repeat = (int)(1 / temp);    // число повторов значения, если частота меньше запрошенной
    if (repeat == 0) repeat = 1;
    auto deltaTime = 1000 / std::min((int)frequency, persecond); // шаг времени
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

