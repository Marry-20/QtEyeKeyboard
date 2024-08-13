

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QPieSeries>
#include <QTextToSpeech>
#include <QElapsedTimer>
#include <mygaze.h>
#include <QProcess>
#include <QLabel>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void cppSignal(const QVariant& sentMsg) const;
public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void explodeSlice(bool exploded);
    void remove_words();
    void insert_words();
    void timing(bool wexploded);
    void read();
    void write(QString tx);
    void nlpprocess();
    bool event(QEvent *event);

private:
    int pred_num;
    QStringList list,word;
    QString tx,chr;
    QString txt,lbl_txt,str;
    QList<QPieSeries *> m_donuts;
    QPieSeries *donut;
    QColor s_c;
    QPieSlice *newslice;
    QPieSlice *wrd_slice;
    QPieSlice *slice;
    QPieSlice *wslice1;
    QPieSlice *wslice2;
    QPieSlice *wslice3;
    QTimer *updateTimer;
    QTimer *updateTimer1;
    QTimer *updateTimer2;
    QTimer *updateTimer3;
    QElapsedTimer timer;
    MyGaze *elm;


    bool flg;int cnt;bool wrd;  int lbl;
    QProcess *p = new QProcess(this);
    QLabel *label = new QLabel;
    QTextToSpeech *speech = new QTextToSpeech();

};

#endif // WIDGET_H
