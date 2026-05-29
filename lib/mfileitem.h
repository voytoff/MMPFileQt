#ifndef MFILEITEM_H
#define MFILEITEM_H

#include "MMPFile_global.h"
#include "file.h"
#include <QObject>

class MChannelArray;
class MMPFILE_EXPORT MFileItem : public QObject {
  Q_OBJECT
public:
  explicit MFileItem(QObject *parent = nullptr);
  explicit MFileItem(MChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);
  explicit MFileItem(QString fileName, int index, MChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);

  QString blockHeader;

  /**
   * Количество параметров в блоке файла
   * @brief blockSize
   */
  int blockSize;

  /**
   * Частота дискретизации данных в блоке Гц
   * @brief frequency
   */
  double frequency;

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
   * Указатель на данные в файле
   * @brief filePosition
   */
  long filePosition;

  /**
   * Данные как есть в файле без преобразований
   * @brief payload
   */
  QByteArray payload;

  /**
   * Массив блоков информации по каналам. Пробрасывается в FileItem для загрузки данных из файлов
   * @brief channelBlockArray
   */
  MChannelArray* channelBlockArray;

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
   * Загружает данные файла
   * @brief loadData
   */
  void loadData();

  QByteArray data();

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

  void progress(int pos, int max);
  void dataReceived(int count);
};

#endif // MFILEITEM_H
