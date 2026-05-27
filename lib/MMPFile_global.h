#ifndef MMPFILE_GLOBAL_H
#define MMPFILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MMPFILE_LIBRARY)
#define MMPFILE_EXPORT Q_DECL_EXPORT
#else
#define MMPFILE_EXPORT Q_DECL_IMPORT
#endif

#endif // MMPFILE_GLOBAL_H
