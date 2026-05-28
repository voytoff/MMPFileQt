#include "mlib.h"
#include <algorithm>

namespace mlib {

int indexOf(QList<MFileItem *> list, QString fileName) {
  auto it = std::find_if(list.begin(), list.end(), [=](const MFileItem *f) { return f->fileName == fileName; });
  return (it != list.end()) ? std::distance(list.begin(), it) : -1;
}

}
