#include "mchannelarray.h"
#include "mchannelarray.h"

MChannelArray::MChannelArray() {}

qsizetype MChannelArray::count() {
  return QHash::count();
}

MChannelBlock *MChannelArray::get(std::function<bool (const MChannelBlock &)> &predicate) {
  auto it = std::find_if(this->begin(), this->end(), predicate);
  return it.value();
}

MChannelBlock *MChannelArray::operator[](QString name) {
  std::function<bool(const MChannelBlock&)> func = [name](const MChannelBlock& item) {return item.name == name;};
  auto it = get(func);
  return it;
}

MChannelBlock* MChannelArray::addChannel(MChannelBlock *channel) {
  if (!contains(channel->channelID)) this->insert(channel->channelID, channel);
  return channel;
} // addChannel
