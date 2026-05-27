#include "file.h"
#include <QTimeZone>
#include <qendian.h>

File::File(const QString &name) : QFile(name) {
  if (exists() && open(QIODevice::ReadOnly)) {
  } else throw new std::exception();
}

bool File::seekNext(qint64 offset) {
  return seek(pos() + offset);
}

QByteArray File::readExt(const qint64 position, const qint64 count) {
  seek(position);
  return read(count);
} // readExt

QString File::read_string(const qint64 count) {
  QByteArray data = read(count);
  QString text = decoder(data);
  return text.trimmed().remove(QChar('\0'));
} // read_string

QDateTime File::read_date(const qint64 count) {
  QByteArray data = read(count);
  qint64 fileTimeTicks = qFromLittleEndian<qint64>(reinterpret_cast<const uchar*>(data.data()));
  qint64 msecsSinceEpoch = (fileTimeTicks - 116444736000000000LL) / 10000LL;
  return QDateTime::fromMSecsSinceEpoch(msecsSinceEpoch, QTimeZone::systemTimeZone());
} // read_date

double File::read_double(const qint64 count) {
  QByteArray data = read(count);
  double result;
  std::memcpy(&result, data.constData(), 8);
  return result;
} // read_float

int File::read_int(const qint64 count) {
  QByteArray data = read(count);
  int result;
  std::memcpy(&result, data.constData(), sizeof(int));
  return result;
} // read_int

ulong File::read_ulong(const qint64 count) {
  QByteArray data = read(count);
  ulong result;
  std::memcpy(&result, data.constData(), sizeof(unsigned long));
  return result;
} // read_ulong

short File::read_short(const qint64 count) {
  QByteArray data = read(count);
  ulong result;
  memcpy(&result, data.constData(), sizeof(short));
  return result;
} // read_short
