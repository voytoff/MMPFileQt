#include "mfileitem.h"

MFileItem::MFileItem(QObject *parent) : QObject{parent} {}

MFileItem::MFileItem(MChannelArray *channelBlockArray, bool deferred, QObject *parent)
  : QObject{parent}
  , channelBlockArray(channelBlockArray)
  , deferred(deferred) {}

MFileItem::MFileItem(QString fileName, int index, MChannelArray* channelBlockArray, bool deferred, QObject *parent)
  : QObject{parent}
  , channelBlockArray(channelBlockArray)
  , deferred(deferred)
  , fileName(fileName)
  , index(index) {}

File *MFileItem::file() {
  if (_file == nullptr)
    _file = new File(fileName);
  return _file;
}

void MFileItem::loadData() {
  // 1. 64 байта заголовок
  blockHeader = file()->get<QString>(64);
  blockSize = file()->get<int>(4);
  frequency = file()->get<int>(4);
  if (deferred) filePosition = file()->pos();
  else payload = file()->readAll();
}

QByteArray MFileItem::data() {
  if (payload.length() == 0) {
    file()->seek(filePosition);
    payload = file()->readAll();
  }
  return payload;
}

