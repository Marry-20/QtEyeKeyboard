#include "readwrite.h"
#include "mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QApplication>
#include <QFile>
#include <QProcess>
readwrite::readwrite(QString str)
{
    QFile f("F:/NLP/google_corpus/scrape_python/qt/cpy2/tmp.json");
    f.resize(0);
    QString str = "how are you do";
    f.open(QIODevice::ReadWrite);
    QJsonArray disk_array = QJsonArray::fromStringList(str.split(' '));
    QJsonDocumentjsonDoc;
    jsonDoc.setArray(disk_array);
    f.write(jsonDoc.toJson());
    f.close();

    QProcess p;
    QStringList params;
    params << "F:/NLP/google_corpus/scrape_python/qt/tmp/server.py";
    p.start("C:/Users/A/anaconda3/pkgs/python-3.8.3-he1778fa_2/python.exe", params);
    qDebug() << "finished";

    QFile file("F:/NLP/google_corpus/scrape_python/qt/cpy2/ans.json");
    file.open(QIODevice::ReadWrite);
    file.readAll();
    file.close();
}
