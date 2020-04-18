#pragma once
#include <QtTest/QtTest>
#include "version.h"
#include <QProcess>

class TestMain: public QObject
{
    Q_OBJECT
    private slots:
    void TestVersion();
    void TestIpFilter();
};

QTEST_MAIN(TestMain)
