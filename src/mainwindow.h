#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include <QStackedLayout>
#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE
class MainWindow;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
//signals:
   //void cppSignal(const QVariant& sentMsg) const;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool event(QEvent *event);

    //Widget keyboard;
private:
   QGridLayout *layout;



};
#endif // MAINWINDOW_H
