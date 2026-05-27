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
};

#endif // CHANNELARRAY_H
