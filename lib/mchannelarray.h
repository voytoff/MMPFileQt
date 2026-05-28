#ifndef MCHANNELARRAY_H
#define MCHANNELARRAY_H

#include "MMPFile_global.h"
#include "mchannelblock.h"
#include <QHash>
#include <QList>

class MMPFILE_EXPORT MChannelArray: public QHash<int, MChannelBlock*>
{
public:
  MChannelArray();

  qsizetype count();

  /**
   * Возвращает канальный блок по указанному фильтру
   * @brief get
   * @param predicate
   * @return
   */
  MChannelBlock* get(std::function<bool(const MChannelBlock&)> &predicate);

  /**
   * Возвращает канальный блок по указанному имени
   * @brief operator []
   * @param name
   * @return
   */
  MChannelBlock* operator[](QString name);

  MChannelBlock *addChannel(MChannelBlock *channel);

};

#endif // MCHANNELARRAY_H
