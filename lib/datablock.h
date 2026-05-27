#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "MMPFile_global.h"
#include <QObject>

class MMPFILE_EXPORT DataBlock : public QObject
{
  Q_OBJECT
public:
  explicit DataBlock(QObject *parent = nullptr);

  /**
   * Данные как есть в файле без преобразований
   * @brief payload
   */
  QByteArray payload;

  /**
   * Массив с данными этого блока
   * @brief data
   * @return
   */
  QList<double> data();

signals:
};

#endif // DATABLOCK_H
