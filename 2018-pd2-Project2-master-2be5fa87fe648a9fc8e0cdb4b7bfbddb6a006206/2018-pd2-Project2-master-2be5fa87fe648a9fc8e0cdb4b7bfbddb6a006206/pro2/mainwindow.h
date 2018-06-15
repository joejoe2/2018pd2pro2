#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVBoxLayout>
#include<QWidget>
#include <QApplication>
#include<QPushButton>
#include <QObject>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QSettings>
#include"solve.h"
#include"play.h"
class MainWindow :public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *o;
    explicit MainWindow();
    void paintEvent(QPaintEvent *event);
    QMediaPlayer *media;
    QMediaPlaylist *l;
    QLabel *record;
public slots:
    void toplay();
    void tosolve();
    void modify();
};
#endif // MAINWINDOW_H
