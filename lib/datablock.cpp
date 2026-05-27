#include "datablock.h"

DataBlock::DataBlock(QObject *parent) : QObject{parent} {}

QList<double> DataBlock::data() {
  return {};
}

