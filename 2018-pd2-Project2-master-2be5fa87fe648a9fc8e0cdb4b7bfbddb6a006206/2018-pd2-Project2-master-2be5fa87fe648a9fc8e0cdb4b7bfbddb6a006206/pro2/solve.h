#ifndef SOLVE_H
#define SOLVE_H
#include <QVBoxLayout>
#include<QWidget>
#include<QPushButton>
#include"box.h"
#include<QKeyEvent>
#include<QGridLayout>
#include<QMediaPlayer>
#include<QMediaPlaylist>
class solve:public QWidget
{
Q_OBJECT
public :
    solve();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    bool check(int index);
    void tryset(int index);
    int answer[9][9];
    int map[9][9];
    box base[9][9];
    int target;
    bool isend;
    QPushButton s;
    QGridLayout qg;
    QHBoxLayout qh;
    QVBoxLayout qv;
    QMediaPlayer *media;
    QMediaPlaylist *l;
public slots:
    void click();
void startsolve();
void reset();
void back();
};
#endif // SOLVE_H
