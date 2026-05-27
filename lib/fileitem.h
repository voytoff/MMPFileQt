#ifndef FILEITEM_H
#define FILEITEM_H

#include "channelarray.h"
#include "file.h"
#include <QObject>

class FileItem : public QObject
{
  Q_OBJECT
public:
  explicit FileItem(QObject *parent = nullptr);
  explicit FileItem(ChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);
  explicit FileItem(QString fileName, int index, ChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);

  /**
   * Номер файла в списке
   * @brief index
   */
  int index;

  /**
   * Флаг отложенной загрузки буфера данных. Если установлен,
   * сохраняется указатель на начало блока в DataBlock.FilePosition,
   * который используется в момент востребованности данных
   * @brief deferred
   */
  bool deferred;

  /**
   * Массив блоков информации по каналам. Пробрасывается в FileItem для загрузки данных из файлов
   * @brief channelBlockArray
   */
  ChannelArray* channelBlockArray;

  /**
   * Имя файла данных acd2
   * @brief fileName
   */
  QString fileName;

  /**
   * Файл
   * @brief file
   * @return
   */
  File* file();

private:

  File* _file = nullptr;

public slots:
  /**
   * Загружает заголовки файла
   * @brief loadInfo
   */
  void loadInfo();

  /**
   * Загружает данные файла
   * @brief loadData
   */
  void loadData();

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
  void fileLoaded(int index, QString fileName); // Signal declaration
};

#endif // FILEITEM_H
