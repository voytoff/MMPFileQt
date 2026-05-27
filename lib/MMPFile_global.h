#ifndef MMPFILE_GLOBAL_H
#define MMPFILE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>

#if defined(MMPFILE_LIBRARY)
#define MMPFILE_EXPORT Q_DECL_EXPORT
#else
#define MMPFILE_EXPORT Q_DECL_IMPORT
#endif

const QString Ext = ".mmp";
const QString Pattern = "*.mmp";
const QString Ext_info = ".prm";
const QString Pattern_info = "*.prm";

#endif // MMPFILE_GLOBAL_H
