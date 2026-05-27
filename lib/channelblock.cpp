#include "channelblock.h"

ChannelBlock::ChannelBlock(QObject *parent) : QObject{parent} {}

QList<Parameter *> ChannelBlock::data() {
  return {};
}

