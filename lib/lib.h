#ifndef LIB_H
#define LIB_H

#include "fileitem.h"
#include <QStringList>
#include <QString>
#include <QList>

namespace lib {
int endsWith(QStringList list, QString value);
int indexOf(QList<FileItem*> list, QString fileName);
};

#endif // LIB_H
