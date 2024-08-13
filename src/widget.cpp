#include "widget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>
#include <chrono>
#include <QEventLoop>
#include <QCoreApplication>
#include<QFont>
#include <QJsonArray>
#include <QJsonDocument>
#include <QApplication>
#include <QFile>
#include <QProcess>
#include <QJsonObject>
#include <QLabel>
#include <QtDebug>
#include <QTextToSpeech>
#include <gazeapi.h>
#include <QToolTip>
#include<QPoint>
#include <QCursor>
#include <QMouseEvent>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer.start();
    MyGaze *elm = new MyGaze;
    elm;
    setMinimumSize(QSize(800,1050 ));
    //setMaximumSize();
    //nlpprocess();
    setToolTip	(	"gtfy");
    //! [1]
    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = chartView->chart();
    chart->legend()->setVisible(false);

    //chart->setTitle();
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [1]
    //! [2]
    qreal minSize = 0.0;
    qreal maxSize = 1;
    int donutCount = 4;
    flg=false;        wrd = false;
    updateTimer = new QTimer(this);
    updateTimer1 = new QTimer(this);

    const char *donut1[4] = { "e", "t","i","h"};
    const char *donut2[9] = { "a","b","c","d","l","o","m","n","u"};
    const char *donut3[13] = { "r","g", "p","f","q","z","j","x","k","v","y","w","s"};
    //! [2]
    //! [3]

    donut = new QPieSeries;
    int sliceCount = 4; int i=0;
    qreal value = 360/(sliceCount);

    QPieSlice *slice = new QPieSlice("Space", value);
    slice->setLabelVisible(true);
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideTangential);

    connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);

    QFont *font = new QFont("bold Helvetica",12,12,true);
    slice->setLabelFont(*font);
    donut->append(slice);

    slice = new QPieSlice("?", value/2);
    slice->setLabelVisible(true);
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideTangential);
    slice->setLabelFont(*font);
    connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
    donut->append(slice);

    slice = new QPieSlice(".", value/2);
    slice->setLabelVisible(true);
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideTangential);
    slice->setLabelFont(*font);
    connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
    donut->append(slice);
    donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
    donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);

    slice = new QPieSlice("Backspace", value);
    slice->setLabelVisible(true);
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideTangential);
    slice->setLabelFont(*font);
    connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
    donut->append(slice);

    slice = new QPieSlice("Word Erase", value);
    slice->setLabelVisible(true);
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideTangential);
    slice->setLabelFont(*font);
    connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
    donut->append(slice);




    m_donuts.append(donut);
    chartView->chart()->addSeries(donut);

    //! [3]
    //! [3]
    donut = new QPieSeries;
    sliceCount = 4; i=1;

    for ( int j = 0; j < sliceCount; j++) {
        qreal value = 360/(sliceCount);
        QPieSlice *slice = new QPieSlice(donut1[j], value);

        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        //slice->setColor(QColor( qrand() % 256, qrand() % 256, qrand() % 256 ) );
        slice->setColor(QColor((i+1)*15,(i+1)*30,(i+1)*45));

        QFont *font = new QFont("bold Helvetica",25,25,true);
        slice->setLabelFont(*font);
        //connect(slice, &QPieSlice::hovered, this,  &Widget::write);

        connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
        donut->append(slice);
        donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
        donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
    }


    m_donuts.append(donut);
    chartView->chart()->addSeries(donut);




    donut = new QPieSeries;
    sliceCount = 9; i = 2;

    for ( int j = 0; j < sliceCount; j++) {
        qreal value = 360/(sliceCount);
        QPieSlice *slice = new QPieSlice(donut2[j], value);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        //slice->setColor(QColor( qrand() % 256, qrand() % 256, qrand() % 256 ) );
        slice->setColor(QColor((i+1)*15,(i+1)*30,(i+1)*45));
        QFont *font = new QFont("bold Helvetica",25,25,true);
        slice->setLabelFont(*font);
        connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
        //connect(slice, &QPieSlice::hovered, this,  &Widget::write);
        donut->append(slice);
        donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
        donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
    }
    m_donuts.append(donut);
    chartView->chart()->addSeries(donut);



    donut = new QPieSeries;
    sliceCount = 13; i=3;

    for ( int j = 0; j < sliceCount; j++) {

        qreal value = 360/(sliceCount);
        QPieSlice *slice = new QPieSlice(donut3[j], value);

        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::white);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        slice->setColor(QColor((i+1)*15,(i+1)*30,(i+1)*45));

        QFont *font = new QFont("bold Helvetica",25,25,true);
        slice->setLabelFont(*font);
        //connect(slice, &QPieSlice::hovered, this,  &Widget::write);

        connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
        donut->append(slice);
        donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
        donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
    }
    m_donuts.append(donut);
    chartView->chart()->addSeries(donut);

    // create main layout
    //! [4]
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->addWidget(label,0,1);
    label->setAlignment(Qt::AlignCenter);


    QFont fo = label->font();
    fo.setPointSize(25);
    fo.setBold(true);
    label->setFont(fo);
    //label->setGeometry(0, 1, 2, 2);

    setLayout(mainLayout);
    //! [4]
    /*
    QHBoxLayout *a_layout = new QHBoxLayout;
    Widget::setLayout(a_layout);
    a_layout->setMargin(0);
    a_layout->addWidget(a_widget);
    */
}

Widget::~Widget()
{
    p->close();
}




//! [7]
void Widget::explodeSlice(bool exploded)
{


    if (exploded){
        slice = qobject_cast<QPieSlice *>(sender());
        if (flg){remove_words();}
        donut = slice->series();
        chr = slice->label();
        cnt = donut->count();

        if (cnt != 5){
            if (wrd){tx = txt +" "+chr;write(tx);}

            else{ tx = txt +chr; write(tx);}
            if (updateTimer3){updateTimer3->stop();}
            updateTimer3 = new QTimer(this);
            connect(updateTimer3, &QTimer::timeout, this,[=] {
                /*slice->setLabelColor(Qt::red);*/read();                   // QString wrd_label = "";

                if (word[2] != ""){
                    // for (int i=0;i<3;i++){wrd_label.append(word[i]);}
                    slice->setLabel(word[2]+"\n"+word[1]+"\n"+word[0]);
                    QFont *font1 = new QFont("Thin",10,10,true);
                    slice->setLabelFont(*font1);

                    slice->setLabelColor(Qt::white);

                    slice->setLabelFont(*font1);
                }else if (word[1] != ""){
                    slice->setLabel(word[1]+"\n"+word[0]);
                    QFont *font1 = new QFont("Thin",15,15,true);
                    slice->setLabelFont(*font1);
                    slice->setLabelColor(Qt::white);

                    //for (int i=0;i<2;i++){wrd_label.append(word[i]);}
                }else if (word[0] != ""){
                    slice->setLabel(word[0]);
                    QFont *font1 = new QFont("Thin",20,20,true);
                    slice->setLabelFont(*font1);
                    slice->setLabelColor(Qt::white);

                    //for (int i=0;i<1;i++){wrd_label.append(word[i]);}
                }
                //slice->setLabelColor(Qt::darkGray);
                // slice->setLabelFont(*font1);
                // if (wrd_label!=""){    qDebug()<<"wrd_lbl: "<< wrd_label;            slice->setLabel(wrd_label);}
                //wrd_slice->setExploded(true);
                if (updateTimer){updateTimer->stop();}
                updateTimer = new QTimer(this);
                connect(updateTimer, &QTimer::timeout, this,[=] {
                    slice->setLabelColor("red");
                    if (updateTimer2){updateTimer2->stop();}
                    updateTimer2 = new QTimer(this);
                    connect(updateTimer2, SIGNAL(timeout()), this, SLOT(insert_words()));
                    updateTimer2->setSingleShot(true);
                    updateTimer2->start(100);});
            updateTimer->setSingleShot(true);
            updateTimer->start(600);});



            updateTimer3->setSingleShot(true);
            updateTimer3->start(100);}
        else{if (updateTimer){updateTimer->stop();}
            updateTimer = new QTimer(this);
            connect(updateTimer, SIGNAL(timeout()), this, SLOT(insert_words()));
            updateTimer->setSingleShot(true);
            updateTimer->start(400);}


    }
    if (!exploded){
        slice->setLabel(chr);
        QFont *font = new QFont("bold Helvetica",25,25,true);

        slice->setLabelFont(*font);
        if (updateTimer3){updateTimer3->stop();}
        if (updateTimer2){updateTimer2->stop();}
        if (updateTimer){updateTimer->stop();}
        slice->setLabelColor(Qt::white);}//slice->setExploded(exploded);
}


void Widget::insert_words(){


    //QColor clr = slice->color();
    slice->setLabel(chr);
    QFont *font = new QFont("bold Helvetica",25,25,true);

    slice->setLabelFont(*font);


    //QToolTip::showText(QCursor::pos(),"hghf");
    //qDebug()<< "tooltip "<<QToolTip::isVisible();
    lbl_txt = chr;
    slice->setLabelColor("red");
    if (cnt==5){

        if (lbl_txt ==  "Backspace"){txt.chop(1);}
        else if (lbl_txt ==  "Space"){ txt=txt + " ";}
        else if (lbl_txt ==  "?"){ txt=txt + "? ";}
        else if (lbl_txt ==  "."){ txt=txt + ". ";}
        //else if (lbl_txt ==  ","){ txt=txt + ", ";}
        else if (lbl_txt ==  "Word Erase"){
            if (txt.lastIndexOf(QChar(' '))==-1 || txt == txt.left(txt.lastIndexOf(QChar(' ')))){txt="";}
            else if(txt.lastIndexOf(QChar(' '))==(txt.length()-1) || txt.lastIndexOf(QChar(' '))==(txt.length()))
            {txt = txt.left(txt.lastIndexOf(QChar(' '),-1));}
            else{txt = txt.left(txt.lastIndexOf(QChar(' ')));if (wrd==false){txt =txt+" ";}}}
        emit cppSignal(txt);
        label->setText(txt.right(30));

    }else{ read();

        //if (wrd){txt=txt+" ";}
        if (wrd){txt = txt +" "+lbl_txt;}
        else{txt = txt +lbl_txt;}
        emit cppSignal(txt);
        label->setText(txt.right(30));
        speech->say(lbl_txt);
        wrd = false;

        qreal sliceStartAngle = slice->startAngle();
        lbl = int(sliceStartAngle*cnt/360);
        QFont *font = new QFont("bold Helvetica",15,15,true);

        if (word[0] != ""){
            wslice1 = new QPieSlice(QString(word[0]), 360/(cnt*pred_num));
            wslice1->setLabelVisible(true);
            wslice1->setLabelColor(Qt::white);
            wslice1->setLabelFont(*font);
            wslice1->setColor(QColor(5,10,15));

            connect(wslice1, &QPieSlice::hovered, this, &Widget::timing);
            wslice1->setLabelPosition(QPieSlice::LabelInsideNormal);
            donut->insert(lbl+1, wslice1);
        }
        if (word[1] != ""){
            wslice2 = new QPieSlice(QString(word[1]), 360/(cnt*pred_num));
            wslice2->setLabelVisible(true);
            wslice2->setLabelColor(Qt::white);
            wslice2->setLabelFont(*font);
            wslice2->setColor(QColor(15,30,45));

            connect(wslice2, &QPieSlice::hovered, this, &Widget::timing);
            wslice2->setLabelPosition(QPieSlice::LabelInsideNormal);
            donut->insert(lbl+2, wslice2);
        }

        if (word[2] != ""){
            wslice3 = new QPieSlice(QString(word[2]), 360/(cnt*pred_num));
            wslice3->setLabelVisible(true);
            wslice3->setLabelColor(Qt::white);
            wslice3->setLabelFont(*font);
            wslice3->setColor(QColor(30,60,90));

            connect(wslice3, &QPieSlice::hovered, this, &Widget::timing);
            wslice3->setLabelPosition(QPieSlice::LabelInsideNormal);
            donut->insert(lbl+3, wslice3);
        }




        if (word[0] != ""){
            s_c= slice->color();
            donut->remove(slice);
            flg =true;}
    }
}

void Widget::remove_words(){
    newslice = new QPieSlice(lbl_txt,360/(cnt));
    newslice->setLabelVisible(true);
    newslice->setLabelColor(Qt::white);
    newslice->setColor(s_c);

    QFont *font = new QFont("bold Helvetica",25,25,true);
    newslice->setLabelFont(*font);
    newslice->setLabelPosition(QPieSlice::LabelInsideHorizontal);

    donut->remove(wslice1);
    donut->remove(wslice2);
    donut->remove(wslice3);
    donut->insert(lbl,newslice);
    connect(newslice, &QPieSlice::hovered, this, &Widget::explodeSlice);
    flg = false;

}


void Widget::timing(bool wexploded){
    if (wexploded){
        wrd_slice = qobject_cast<QPieSlice *>(sender());
        donut = wrd_slice->series();


        write(txt);
        if (updateTimer1){updateTimer1->stop();}
        updateTimer1 = new QTimer(this);
        connect(updateTimer1, &QTimer::timeout, this,[=] {wrd_slice->setLabelColor(Qt::red);//wrd_slice->setExploded(true);

            if( txt == txt.left(txt.lastIndexOf(QChar(' ')))){txt =  wrd_slice->label();
            }
            else{txt = txt.left(txt.lastIndexOf(QChar(' ')));
                txt = txt +" "+ wrd_slice->label();}
            speech->say(wrd_slice->label());
            qDebug()<< "hi";
            qDebug()<<txt.left(txt.lastIndexOf(QChar(' ')));

            emit cppSignal(txt);
            label->setText(txt.right(30));

            wrd = true;});
        updateTimer1->setSingleShot(true);
        updateTimer1->start(300);


    }else{if (!wexploded){updateTimer1->stop();}wrd_slice->setLabelColor(Qt::white);}//wrd_slice->setExploded(false);}
}



void Widget::write(QString tx){

    QFile f("C:/Users/mirbagherim/Downloads/data/tmp.json");
    f.resize(0);
    qDebug() << "write";
    f.open(QIODevice::ReadWrite);

    tx = tx.mid(tx.lastIndexOf(QChar('.'))+1);
    //tx = tx.right(tx.lastIndexOf(QChar(',')));
    tx = tx.mid(tx.lastIndexOf(QChar('?'))+1);

    qDebug() << "tx:" << tx;
    QJsonArray disk_array = QJsonArray::fromStringList(tx.split(' '));
    QJsonDocument jsonDoc;
    jsonDoc.setArray(disk_array);
    f.write(jsonDoc.toJson());
    f.close();




}
void Widget::read(){
    QFile file("C:/Users/mirbagherim/Downloads/data/ans.json");
    file.open(QIODevice::ReadWrite);
    QString str = file.readAll();
    QJsonDocument sd = QJsonDocument::fromJson(str.toUtf8());
    qWarning() << sd.isNull(); // <- print false :)
    QJsonObject sett2 = sd.object();
    QJsonArray jsonArray = sett2["Words"].toArray();
    qDebug() << jsonArray;

    //QString pred_wrds = jsonArray.toString();


    pred_num = sett2.value("Predicted_num").toInt();   // <- print my title
    /*for (int i = 0; i< pred_num; i++) {
        word.append (jsonArray.at(i).toString());
    }*/
    word.clear();
    word << jsonArray.at(0).toString() << jsonArray.at(1).toString() << jsonArray.at(2).toString();
    qDebug() << word;

    file.resize(0);
    file.close();

    QFile fp("C:/Users/mirbagherim/Downloads/data/anlys.txt");
    fp.open(QIODevice::Text | QIODevice::Append);
    QTextStream s(&fp);

    s << "\n"<< txt<< "\n"<< word[0] << "\t"<< word[1] << "\t"<< word[2];
    s << "\n"<< timer.elapsed() << "milliseconds"<<"\n";

    fp.close();


}
void Widget::nlpprocess(){
    //QProcess *p = new QProcess(this);
    QStringList params;
    params << "C:/Users/mirbagherim/Downloads/wgtqml/someFunction.py";
    p->start("C:/Users/mirbagherim/anaconda3/python.exe", params);

    QString p_stdout = p->readAll();
    qDebug() << p_stdout;
    QString p_stderr = p->readAllStandardError();
    if(!p_stderr.isEmpty())
        qDebug()<<"Python error:"<<p_stderr;
    qDebug() << "Hello World" << p->error();
    connect(p, &QProcess::errorOccurred, [=](QProcess::ProcessError error)
    {
        qDebug() << "error enum val = " << error;
        return exit;
    });

}

//! [7]

void Widget::mouseReleaseEvent(QMouseEvent* event)
{
    if (UnderMouse(event->globalPos()) == true) // Check if LineEdit is under cursor
    {
        QLineEdit::mouseReleaseEvent(event);
        return;
    }

    if (hasAcceptableInput() == false)
    {
        FixInput(); // Helper method to call validator()->fixup(copiedText) (trigger will show the tooltip)
        return;
    }
    else
    {
        releaseMouse();
        clearFocus();
        return;
    }
}
