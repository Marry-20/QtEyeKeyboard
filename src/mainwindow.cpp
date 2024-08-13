#include "mainwindow.h"
#include <QFrame>
#include "widget.h"
#include <QQuickWidget>
#include <QGridLayout>
#include <QQmlContext>
#include <QGuiApplication>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>
#include <QMessageBox>
#include <QToolTip>
#include "sqlcontactmodel.h"
#include "sqlconversationmodel.h"

static void connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    // Ensure that we have a writable location on all devices.
    const QString fileName = writeDir.absolutePath() + "/chat-database.sqlite3";
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);

    qmlRegisterType<SqlContactModel>("io.qt.examples.chattutorial", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("io.qt.examples.chattutorial", 1, 0, "SqlConversationModel");
    connectToDatabase();

    QFrame *central = new QFrame;
    //central->setFixedSize(1200,1200);
    this->setCentralWidget(central);
    auto cppObj = new Widget(central);
    auto quickWidget = new QQuickWidget(central);
    auto contact = new QQuickWidget(central);

    quickWidget->rootContext()->setContextProperty("cppObj", cppObj);
    quickWidget->setSource(QUrl("qrc:/main.qml"));
    contact->rootContext()->setContextProperty("cppObj", cppObj);
    contact->setSource(QUrl("qrc:/main.qml"));
    this->layout = new QGridLayout(central);
    this->layout->addWidget(quickWidget, 0, 2);
    this->layout->addWidget(contact, 0, 0);

    this->layout->addWidget(cppObj, 0, 1);


   }

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
           int index = itemAt(helpEvent->pos());
           if (index != -1) {
               QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
           } else {
               QToolTip::hideText();
               event->ignore();
           }

           return true;
       }
       return QWidget::event(event);

}


MainWindow::~MainWindow()
{
}

