#include <QtTest/QtTest>
#include <qxfixpoint.h>

using namespace cutex;

const double VALUE_1 = 16.43;
const double VALUE_2 = 3.57;

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

    fp = VALUE_1;
    fp += VALUE_2;
    QVERIFY(fp == VALUE_1 + VALUE_2);

    fp = VALUE_1 + VALUE_2;
    QVERIFY(fp == VALUE_1 + VALUE_2);

    fp = VALUE_1;
    fp -= VALUE_2;
    QVERIFY(fp == VALUE_1 - VALUE_2);

    fp = VALUE_1 - VALUE_2;
    QVERIFY(fp == VALUE_1 - VALUE_2);
}

void FixPoint::stream()
{
    QBuffer buffer;
    QDataStream stream(&buffer);
    QxFixPoint fp = VALUE_1;

    buffer.open(QIODevice::ReadWrite);
    stream << fp;
    buffer.seek(0);
    stream >> fp;
    QVERIFY(fp == VALUE_1);
}

QTEST_MAIN(FixPoint)
#include "fixpoint.moc"
