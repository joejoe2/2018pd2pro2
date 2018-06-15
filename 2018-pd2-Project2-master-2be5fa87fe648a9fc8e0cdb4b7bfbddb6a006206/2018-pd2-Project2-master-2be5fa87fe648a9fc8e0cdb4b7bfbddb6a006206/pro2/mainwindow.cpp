#include "mainwindow.h"
#include<QPainter>
#include<QTimer>
MainWindow::MainWindow()
{
    l=new QMediaPlaylist();
    l->addMedia(QUrl("qrc:/img/bgm1.mp3"));
   // l->setPlaybackMode(QMediaPlaylist::Loop);
    media=new QMediaPlayer(this,QMediaPlayer::LowLatency);
    media->setPlaylist(l);
    media->setVolume(80);
    media->play();
    QTimer *timer=new QTimer();
    timer->setInterval(140*1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(modify()));
    timer->start();

    QSettings *set=new QSettings();
    record=new QLabel();
    record->setText("best:"+QString::number(set->value("rec").toInt())+"% correct");
    record->setStyleSheet("background-color:black;color:white;font-size:25px;");
    record->setFixedSize(220,50);
    record->setAlignment(Qt::AlignCenter);

   o=new QVBoxLayout;
    QPushButton *b1=new QPushButton("play");
    QPushButton *b2=new QPushButton("input your sudoku");
   b1->setStyleSheet("background-color:blue;color:white");
   b2->setStyleSheet("background-color:blue;color:white");
   o->addWidget(b1);
   o->addWidget(b2);
   o->addWidget(record);
   o->setAlignment(record,Qt::AlignHCenter);
    setWindowTitle("sudoku");
    setLayout(o);
    setFixedSize(500,500) ;

    connect(b1,SIGNAL(clicked(bool)),this,SLOT(toplay()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(tosolve()));
}
void MainWindow::tosolve(){
    solve *sol=new solve();
    media->stop();
    delete media;
    close();
}
void MainWindow::toplay(){
    play *ply=new play();
    media->stop();
    delete media;
    close();
    //disconnect()
    this->~MainWindow();
}
void MainWindow::paintEvent(QPaintEvent *event){
 QPainter pen(this);
 QPixmap m(":/img/bg.jpg");
 pen.drawPixmap(0,0,500,500,m);
}
void MainWindow::modify(){
        l=new QMediaPlaylist();
        l->addMedia(QUrl("qrc:/img/bgm1.mp3"));
        //l->setPlaybackMode(QMediaPlaylist::Loop);
        media->stop();
        delete media;
        media=new QMediaPlayer(this,QMediaPlayer::LowLatency);
        media->setPlaylist(l);
        media->setVolume(80);
        media->play();
}

