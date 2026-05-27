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
  explicit ChannelBlock(QObject *parent = nullptr);

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
