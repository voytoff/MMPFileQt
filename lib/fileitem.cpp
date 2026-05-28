#include "fileitem.h"

FileItem::FileItem(QObject *parent) : QObject{parent} {}

FileItem::FileItem(MChannelArray *channelBlockArray, bool deferred, QObject *parent)
  : QObject{parent}
  , channelBlockArray(channelBlockArray)
  , deferred(deferred) {}

FileItem::FileItem(QString fileName, int index, MChannelArray* channelBlockArray, bool deferred, QObject *parent)
  : QObject{parent}
  , channelBlockArray(channelBlockArray)
  , deferred(deferred)
  , fileName(fileName)
  , index(index) {}

File *FileItem::file() {
  if (_file == nullptr)
    _file = new File(fileName);
  return _file;
}

void FileItem::loadData() {
  // 1. 64 байта заголовок
  blockHeader = file()->get<QString>(64);
  blockLength = file()->get<int>(4);
  frequency = file()->get<int>(4);
  if (deferred) filePosition = file()->pos();
  else payload = file()->readAll();
} // loadData

