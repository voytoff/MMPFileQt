#ifndef CHANNELBLOCK_H
#define CHANNELBLOCK_H

#include "MMPFile_global.h"
#include "datablock.h"
#include "parameter.h"
#include <QObject>

class MMPFILE_EXPORT ChannelBlock : public QObject
{
  Q_OBJECT
public:
  ChannelBlock(QObject *parent = nullptr);

  bool operator==(const ChannelBlock &other) const {
    return channelID == other.channelID && name == other.name;
  }
  bool operator<(const ChannelBlock &other) const {
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
   * Массив считанных блоков данных, соответствующих этому каналу
   * @brief dataBlockArray
   */
  QList<DataBlock*>* dataBlockArray;

  /**
   * Массив с данными этого канала. Формируется из данных всех блоков
   * @brief data
   * @return
   */
  QList<Parameter*> data();

signals:
};

#endif // CHANNELBLOCK_H
