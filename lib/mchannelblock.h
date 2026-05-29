#ifndef MCHANNELBLOCK_H
#define MCHANNELBLOCK_H

#include "MMPFile_global.h"
#include "mfileitem.h"
#include "datablockarray.h"
#include "parameter.h"
#include <QObject>
#include <QHash>
#include <QList>

class MMPFILE_EXPORT MChannelBlock : public QObject {
  Q_OBJECT
public:
  MChannelBlock(QObject *parent = nullptr);

  bool operator==(const MChannelBlock &other) const {
    return channelID == other.channelID && name == other.name;
  }
  bool operator<(const MChannelBlock &other) const {
    return channelID < other.channelID;
  }

  /**
   * Числовой идентификатор канала в файле, должен быть уникальным для каждого канала.
   * @brief channelID
   */
  int channelID;

  /**
   * Номер канала в блоке данных
   * @brief blockID
   */
  int blockID;

  /**
   * Имя канала
   * @brief name
   */
  QString name;

  /**
   * Единица измерения
   * @brief unit
   */
  QString unit;

  /**
   * Файл, связанный с этим каналом
   * @brief fileItem
   */
  MFileItem *fileItem;

  /**
   * Массив с данными этого канала. Формируется из данных всех блоков
   * @brief data
   * @return
   */
  QList<Parameter*> data();
  DataBlockArray* array(int persecond);

private:
  QList<Parameter*> _data;
  QHash<int, DataBlockArray*> finalData;

signals:
  void progress(int pos, int max);
  void dataReceived(int count);
};

#endif // MCHANNELBLOCK_H
