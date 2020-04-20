#pragma once
#include <QtTest/QtTest>
#include <QProcess>
#include "version.h"
#include "IpFilter.h"

class TestMain: public QObject
{
    Q_OBJECT
    private slots:
    void TestVersion();
    void TestStrToInt();
    void TestValidBytes();
    void TestIpFilter();
};

QTEST_MAIN(TestMain)
