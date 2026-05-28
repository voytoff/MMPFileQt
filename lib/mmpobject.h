#ifndef MMPOBJECT_H
#define MMPOBJECT_H

#include "MMPFile_global.h"
#include "mchannelarray.h"
#include "fileitem.h"

#include <QObject>
#include <QList>
#include <QString>

class MMPFILE_EXPORT MMPObject : public QObject {
  Q_OBJECT

public:
  explicit MMPObject(QObject *parent = nullptr);
  explicit MMPObject(QStringList fileNames, QObject *parent = nullptr);

  QString parentDir;
  QString infoFileName;

  /**
   * Массив файлов обработки acd2
   * @brief files
   */
  QList<FileItem*>* files;

  /**
   * Массив блоков информации по каналам.
   * Передается последовательно в конструкторы обработчиков файлов
   * и в них формируется. Пока все происходит синхронно
   * @brief channels
   */
  MChannelArray* channels;

  /**
   * Возвращает канал по его имени
   * @brief operator []
   * @param name
   * @return
   */
  MChannelBlock* operator[](QString name);

  /**
   * Проверяет наличие канала с именем name
   * @brief containsChannel
   * @param name
   * @return
   */
  bool containsChannel (QString name);

public slots:
  void loadCore(QStringList mmpFiles);
  FileItem *appendFile(QString fileName);
  void load();
  void close();

signals:
  /**
   * Сигнализирует о прочтении очередного блока канала
   * @brief channelBlockRead
   */
  void channelBlockRead(QString fileName, int channelID, QString name);
  /**
   * Сигнализирует о прочтении очередного блока данных
   * @brief dataBlockRead
   */
  void dataBlockRead(QString fileName, int channelID, int blockID, int size);
  /**
   * Сигнализирует об окончании операции загрузки данных
   * @brief fileLoaded
   */
  void fileLoaded(int index, QString fileName); // Загружен очередной файл
};

#endif // MMPOBJECT_H
