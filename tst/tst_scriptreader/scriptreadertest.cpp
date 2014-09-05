#include <QString>
#include <QtTest>

class ScriptReaderTest : public QObject
{
    Q_OBJECT

public:
    ScriptReaderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

ScriptReaderTest::ScriptReaderTest()
{
}

void ScriptReaderTest::initTestCase()
{
}

void ScriptReaderTest::cleanupTestCase()
{
}

void ScriptReaderTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
//    QVERIFY2(false, "Failure");
}

void ScriptReaderTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(ScriptReaderTest)

#include "scriptreadertest.moc"
