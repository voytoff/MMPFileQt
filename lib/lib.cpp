#include "lib.h"
#include <algorithm>

namespace lib {

bool endsWith(QStringList list, QString value) {
  return std::any_of(list.begin(), list.end(), [=](const QString &s) { return s.endsWith(value); });
}

int indexOf(QList<FileItem *> list, QString fileName) {
  return std::any_of(list.begin(), list.end(), [=](const FileItem *f) { return f->fileName == fileName; });
}

}
