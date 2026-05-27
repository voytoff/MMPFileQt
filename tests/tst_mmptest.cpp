#include <QTest>
#include <QDirIterator>
#include "mmpobject.h"
#include "parameter.h"

class MMPTest : public QObject {
  Q_OBJECT

  public:
  MMPTest();
  ~MMPTest() override;

private:
  QString path = "D:/Телеметрия/Files";
  QVector<QString> getFiles(const QString &path);

  private slots:
  void test_case1();
};

MMPTest::MMPTest() {}

MMPTest::~MMPTest() = default;

void MMPTest::test_case1() {
  QList<QString> temp(this->getFiles(path));
  QList<QString> files;

  files.append(temp.first());

  MMPObject *acdo = new MMPObject(files, this);
  connect(acdo, &MMPObject::fileLoaded, this, [=](int index, QString fileName) { qDebug() << index << fileName; });
  acdo->load();
  qDebug() << acdo->channels->count() << "каналов";
  foreach (auto channel, *acdo->channels) {
    //for (DataBlock* db : *channel->dataBlockArray) { qDebug() << db->channel->name << db->blockID; }
    //std::sort(channel->data().begin(), channel->data().end());
    foreach (Parameter *p, channel->data()) {
      qDebug() << p->index << p->time.toString("dd.MM.yyyy HH:mm:ss.zzz") << p->value;
    }
  }
  acdo->close();
}

QVector<QString> MMPTest::getFiles(const QString &path) {
  QVector<QString> result;
  QDirIterator it(path, QStringList() << "*.acd", QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext())
    result.append(it.next());
  return result;
} // getFiles

QTEST_MAIN(MMPTest)
//QTEST_APPLESS_MAIN(MMPTest)

#include "tst_mmptest.moc"
