#include "mmpobject.h"
#include "datablock.h"
#include "lib.h"

#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <qregularexpression.h>

MMPObject::MMPObject(QObject *parent) :
  QObject{parent}
  , channels(new ChannelArray())
  , files(new QList<FileItem*>()) { }

MMPObject::MMPObject(QStringList fileNames, QObject *parent) : MMPObject(parent) {
  if (fileNames.length() == 0) return;
  // 1. Пытаемся найти файл prm и плясать от него
  // Корневой каталог
  parentDir = QFileInfo(fileNames.first()).absolutePath();
  // Есть prm в списке ?
  auto pattern = QString("%1%2").arg(Ext_info, "$");
  QStringList results = fileNames.filter(QRegularExpression(pattern));
  if (results.length() >= 0)
    infoFileName = results.first();
  else {
    // В списке не нашли, ищем в каталоге
    QDir directory(parentDir);
    QStringList filter(Pattern_info);
    QStringList files = directory.entryList(filter, QDir::Files);
    if (files.length() == 0) return;
    infoFileName = files.first();
  }

  pattern = QString("%1%2").arg(Ext, "$");
  QStringList mmps = fileNames.filter(QRegularExpression(pattern));
  if (mmps.length() == 0) {
    QDir directory(parentDir);
    QStringList filter(Pattern);
    mmps = directory.entryList(filter, QDir::Files);
    if (mmps.length() == 0) return;
  }

  loadCore(mmps);
}

void MMPObject::loadCore(QStringList mmpFiles) {
  QStringList lines;
  QFile file(infoFileName);
  // 122
  // ДПБГ1,2,кгс/см^2,кр1_MR-227_сл1.mmp,0
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in.setEncoding(QStringConverter::System);
    QString line = in.readLine();
    int channelCount = line.toInt();
    int index = 0;
    while (!in.atEnd()) {
      auto parts = in.readLine().split(",");
      if (parts.length() != 5) continue;
      auto channelName = parts.at(0);
      auto unit = parts.at(2);
      auto fileName = parts.at(3);
      auto blockID = parts.at(4).toInt();
      auto n = lib::endsWith(mmpFiles, fileName);
      if (n < 0) continue;
      fileName = mmpFiles.at(n);
      auto channelBlock = new ChannelBlock();
      channelBlock->channelID = index++;
      channelBlock->name = channelName;
      channelBlock->unit = unit;
      channelBlock->blockID = blockID;
      channelBlock->fileItem = appendFile(fileName);
      channels->addChannel(channelBlock);
    }
    file.close();
    assert(channels->count() <= channelCount);
  }
}

FileItem *MMPObject::appendFile(QString fileName) {
  auto index = lib::indexOf(*files, fileName);
  if (index > -1) return files->at(index);
  FileItem *file = new FileItem(fileName, files->length(), channels, true);
  files->append(file);
  connect(file, &FileItem::channelBlockRead, this, [this](QString fileName, int channelID, QString name) {
    emit channelBlockRead(fileName, channelID, name);
  });
  connect(file, &FileItem::dataBlockRead, this, [this](QString fileName, int channelID, int blockID, int size) {
    emit dataBlockRead(fileName, channelID, blockID, size);
  });
  connect(file, &FileItem::fileLoaded, this, [this](int index, QString fileName) {
    emit fileLoaded(index, fileName);
  });
  return file;
}

void MMPObject::load() {
  for (FileItem *file : *files) {
    file->loadData();
  }
}

void MMPObject::close() {
  for (FileItem *file : *files) {
    file->file()->close();
  }
  foreach (ChannelBlock* channel, *channels) {
    foreach (DataBlock* dataBlock, *channel->dataBlockArray) {
      //dataBlock->payload.clear();
      //dataBlock->data().clear();
    }
  }
  channels->clear();
}
