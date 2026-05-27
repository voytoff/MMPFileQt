#include "mmpobject.h"
#include "datablock.h"

MMPObject::MMPObject(QObject *parent) :
  QObject{parent}
  , channels(new ChannelArray())
  , files(new QList<FileItem*>()) { }

MMPObject::MMPObject(QStringList fileNames, QObject *parent) : MMPObject(parent) {
  int n = 0;
  for (const QString &fileName : fileNames) {
    FileItem *file = new FileItem(fileName, n++, channels, true);
    connect(file, &FileItem::channelBlockRead, this, [this](QString fileName, int channelID, QString name) {
      emit channelBlockRead(fileName, channelID, name);
    });
    connect(file, &FileItem::dataBlockRead, this, [this](QString fileName, int channelID, int blockID, int size) {
      emit dataBlockRead(fileName, channelID, blockID, size);
    });
    connect(file, &FileItem::fileLoaded, this, [this](int index, QString fileName) {
      emit fileLoaded(index, fileName);
    });
    files->append(file);
  }
}

void MMPObject::load() {
  for (FileItem *file : *files) {
    file->loadInfo();
    file->loadData();
  }
}

void MMPObject::close() {
  for (FileItem *file : *files) {
    file->file()->close();
  }
  foreach (ChannelBlock* channel, *channels) {
    foreach (DataBlock* dataBlock, *channel->dataBlockArray) {
      dataBlock->payload.clear();
      dataBlock->data().clear();
    }
  }
  channels->clear();
}
