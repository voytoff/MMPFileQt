#include "mmpobject.h"
#include "datablock.h"
#include "lib.h"
#include "mlib.h"

#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QRegularExpression>

MMPObject::MMPObject(QObject *parent) :
  QObject{parent}
  , channels(new MChannelArray())
  , files(new QList<MFileItem*>()) { }

MMPObject::MMPObject(QStringList fileNames, QObject *parent) : MMPObject(parent) {
  if (fileNames.length() == 0) return;
  // 1. Пытаемся найти файл prm и плясать от него
  // Корневой каталог
  parentDir = QFileInfo(fileNames.first()).absolutePath();
  // Есть prm в списке ?
  auto pattern = QString("%1%2").arg(ext_prm, "$");
  QStringList results = fileNames.filter(QRegularExpression(pattern));
  if (results.length() >= 0)
    infoFileName = results.first();
  else {
    // В списке не нашли, ищем в каталоге
    QDir directory(parentDir);
    QStringList filter(pattern_prm);
    QStringList files = directory.entryList(filter, QDir::Files);
    if (files.length() == 0) return;
    infoFileName = files.first();
  }

  pattern = QString("%1%2").arg(ext_mmp, "$");
  QStringList mmps = fileNames.filter(QRegularExpression(pattern));
  if (mmps.length() == 0) {
    QDir directory(parentDir);
    QStringList filter(pattern_mmp);
    mmps = directory.entryList(filter, QDir::Files);
    if (mmps.length() == 0) return;
    mmps.replaceInStrings(QRegularExpression("^"), directory.absolutePath() + "/");
  }

  loadCore(mmps);
}

void MMPObject::loadCore(QStringList mmpFiles) {
  //QStringList lines;
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
      auto channelBlock = new MChannelBlock();
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

MFileItem *MMPObject::appendFile(QString fileName) {
  auto index = mlib::indexOf(*files, fileName);
  if (index > -1) return files->at(index);
  MFileItem *file = new MFileItem(fileName, files->length(), channels, true);
  files->append(file);
  connect(file, &MFileItem::channelBlockRead, this, [this](QString fileName, int channelID, QString name) {
    emit channelBlockRead(fileName, channelID, name);
  });
  connect(file, &MFileItem::dataBlockRead, this, [this](QString fileName, int channelID, int blockID, int size) {
    emit dataBlockRead(fileName, channelID, blockID, size);
  });
  connect(file, &MFileItem::fileLoaded, this, [this](int index, QString fileName) {
    emit fileLoaded(index, fileName);
  });
  return file;
}

void MMPObject::load() {
  for (MFileItem *file : *files) {
    file->loadData();
  }
}

void MMPObject::close() {
  for (MFileItem *file : *files) {
    file->file()->close();
  }
  foreach (MChannelBlock* channel, *channels) {
    foreach (MFileItem* fileItem, *files) {
      fileItem->payload.clear();
      fileItem->payload = nullptr;
    }

  }
  channels->clear();
}
