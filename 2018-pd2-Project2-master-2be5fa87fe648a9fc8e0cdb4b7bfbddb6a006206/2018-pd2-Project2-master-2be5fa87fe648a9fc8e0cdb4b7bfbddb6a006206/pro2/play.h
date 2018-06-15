#ifndef PLAY_H
#define PLAY_H
#include <QVBoxLayout>
#include<QWidget>
#include<QPushButton>
#include"box.h"
#include<QKeyEvent>
#include<QGridLayout>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QSettings>
class play:public QWidget
{
Q_OBJECT
public :
    play();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    bool check(int index);
    void tryset(int index);
    int answer[9][9];
    int map[9][9];
    int trylist[9];
    box base[9][9];
    int target;
    int co,er;
    bool isend;
    bool isfin;
    QPushButton s;
    QGridLayout qg;
    QHBoxLayout qh;
    QVBoxLayout qv;
    QLabel correct,error;
    QMediaPlayer *media;
    QMediaPlaylist *l;
public slots:
    void click();
void startsolve();
void reset();
void back();
};
#endif // PLAY_H
