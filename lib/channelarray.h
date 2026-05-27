#ifndef CHANNELARRAY_H
#define CHANNELARRAY_H

#include "MMPFile_global.h"
#include "channelblock.h"
#include <QHash>
#include <QList>

class MMPFILE_EXPORT ChannelArray: public QHash<int, ChannelBlock*>
{
public:
  ChannelArray();

  qsizetype count();

  /**
   * Возвращает канальный блок по указанному фильтру
   * @brief get
   * @param predicate
   * @return
   */
  ChannelBlock* get(std::function<bool(const ChannelBlock&)> &predicate);

  /**
   * Возвращает канальный блок по указанному имени
   * @brief operator []
   * @param name
   * @return
   */
  ChannelBlock* operator[](QString name);

  ChannelBlock *addChannel(ChannelBlock *channel);

};

#endif // CHANNELARRAY_H
