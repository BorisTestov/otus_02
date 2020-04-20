#include "main_test.h"
#include "moc_main_test.cpp"

void TestMain::TestVersion()
{
    QCOMPARE((int)version().find("0.0."),0);
}

void TestMain::TestStrToInt()
{
    IpFilter ipFilter;
    std::vector<int> resulted_vector = ipFilter.ip_str_to_int(std::vector<std::string>{"255","144","12","0"});
    std::vector<int> expected_vector {255,144,12,0};
    QCOMPARE(std::equal(resulted_vector.begin(),resulted_vector.end(),expected_vector.begin()),true);
}

void TestMain::TestValidBytes()
{
    IpFilter ipFilter;
    bool isValid = ipFilter.is_valid_byte("256");
    QCOMPARE(isValid,false);
    isValid = ipFilter.is_valid_byte("-1");
    QCOMPARE(isValid,false);
    isValid = ipFilter.is_valid_byte("s");
    QCOMPARE(isValid,false);
    isValid = ipFilter.is_valid_byte("255");
    QCOMPARE(isValid,true);
    isValid = ipFilter.is_valid_byte("0");
    QCOMPARE(isValid,true);
}

void TestMain::TestIpFilter()
{
    QString resultedMD5;
    QString expectedMD5 = "24e7a7b2270daee89c64d3ca5fb3da1a  -\n";

    QProcess cat;
    QProcess filter;
    QProcess md5;
    
    cat.setProcessChannelMode(QProcess::MergedChannels);
    filter.setProcessChannelMode(QProcess::MergedChannels);

    cat.setStandardOutputProcess(&filter);
    filter.setStandardOutputProcess(&md5);
    
    QObject::connect(&md5,&QProcess::readyRead,this,
            [&md5,&resultedMD5]()
    {
       resultedMD5 = QString(md5.readAll());
    });

    cat.start("cat ../ip_filter.tsv");
    filter.start("./ipfilter_main");
    md5.start("md5sum");

    cat.waitForFinished();
    filter.waitForFinished();
    md5.waitForFinished();

    QCOMPARE(resultedMD5,expectedMD5);
}
