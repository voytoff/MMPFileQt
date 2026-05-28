#ifndef MLIB_H
#define MLIB_H

#include "mfileitem.h"
#include <QStringList>
#include <QString>
#include <QList>

namespace mlib {
int indexOf(QList<MFileItem*> list, QString fileName);
};

#endif // MLIB_H
