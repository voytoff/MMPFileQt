#include "channelarray.h"
#include "channelarray.h"

ChannelArray::ChannelArray() {}

qsizetype ChannelArray::count() {
  return QHash::count();
}

ChannelBlock *ChannelArray::get(std::function<bool (const ChannelBlock &)> &predicate) {
  auto it = std::find_if(this->begin(), this->end(), predicate);
  return it.value();
}

ChannelBlock *ChannelArray::operator[](QString name) {
  std::function<bool(const ChannelBlock&)> func = [name](const ChannelBlock& item) {return item.name == name;};
  auto it = get(func);
  return it;
}

ChannelBlock* ChannelArray::addChannel(ChannelBlock *channel) {
  if (!contains(channel->channelID)) this->insert(channel->channelID, channel);
  return channel;
} // addChannel
