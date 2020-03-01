#include <QtTest>


// add necessary includes here

class testCaseControl : public QObject
{
    Q_OBJECT

public:
    testCaseControl();
    ~testCaseControl();

private slots:
    void test_case1();

};

testCaseControl::testCaseControl()
{

}

testCaseControl::~testCaseControl()
{

}

void testCaseControl::test_case1()
{

}

QTEST_APPLESS_MAIN(testCaseControl)

#include "tst_testcasecontrol.moc"
