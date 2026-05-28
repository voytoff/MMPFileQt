#ifndef MMPFILE_GLOBAL_H
#define MMPFILE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>

#if defined(MMPFILE_LIBRARY)
#define MMPFILE_EXPORT Q_DECL_EXPORT
#else
#define MMPFILE_EXPORT Q_DECL_IMPORT
#endif

const QString ext_mmp = ".mmp";
const QString pattern_mmp = "*.mmp";
const QString ext_prm = ".prm";
const QString pattern_prm = "*.prm";

#endif // MMPFILE_GLOBAL_H
