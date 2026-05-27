#include "fileitem.h"

FileItem::FileItem(QObject *parent) : QObject{parent} {}

FileItem::FileItem(ChannelArray *channelBlockArray, bool deferred, QObject *parent)
  : QObject{parent}
  , channelBlockArray(channelBlockArray)
  , deferred(deferred) {}

FileItem::FileItem(QString fileName, int index, ChannelArray* channelBlockArray, bool deferred, QObject *parent)
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

void FileItem::loadInfo() {
} // loadInfo

void FileItem::loadData() {
} // loadData

