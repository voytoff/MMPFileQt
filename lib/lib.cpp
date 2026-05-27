#include "lib.h"
#include <algorithm>

namespace lib {

int endsWith(QStringList list, QString value) {
  auto it = std::find_if(list.begin(), list.end(), [=](const QString &s) { return s.endsWith(value); });
  return (it != list.end()) ? std::distance(list.begin(), it) : -1;
}

int indexOf(QList<FileItem *> list, QString fileName) {
  auto it = std::find_if(list.begin(), list.end(), [=](const FileItem *f) { return f->fileName == fileName; });
  return (it != list.end()) ? std::distance(list.begin(), it) : -1;
}

}
