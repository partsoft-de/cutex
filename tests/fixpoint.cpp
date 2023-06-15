#include <QtTest/QtTest>
#include <qxfixpoint.h>

using namespace cutex;

class FixPoint : public QObject
{
    Q_OBJECT

private slots:
    void operands();
    void stream();
};

void FixPoint::operands()
{
    QxFixPoint fp;

    fp = 16.43;
    fp += 3.57;
    QVERIFY(QString::number(fp) == "20");

    fp = 16.43 + 3.57;
    QVERIFY(QString::number(fp) == "20");

    fp = 16.43;
    fp -= 3.57;
    QVERIFY(QString::number(fp) == "12.86");

    fp = 16.43 - 3.57;
    QVERIFY(QString::number(fp) == "12.86");
}

void FixPoint::stream()
{
    QBuffer buffer;
    QDataStream stream(&buffer);
    QxFixPoint fp = 16.43;

    buffer.open(QIODevice::ReadWrite);
    stream << fp;
    buffer.seek(0);
    stream >> fp;
    QVERIFY(QString::number(fp) == "16.43");
}

QTEST_MAIN(FixPoint)
#include "fixpoint.moc"
