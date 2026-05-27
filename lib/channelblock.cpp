#include "channelblock.h"

ChannelBlock::ChannelBlock(QObject *parent)
  : QObject{parent}
  , dataBlockArray(new QList<DataBlock*>()) {}

QList<Parameter *> ChannelBlock::data() {
  return {};
}

