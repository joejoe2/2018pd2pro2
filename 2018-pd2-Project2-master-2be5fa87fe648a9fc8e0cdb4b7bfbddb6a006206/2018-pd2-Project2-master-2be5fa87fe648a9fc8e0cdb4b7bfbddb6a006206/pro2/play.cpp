#include "play.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include<QPainter>
#include"mainwindow.h"
using namespace std;
play::play(){
    l=new QMediaPlaylist();
    l->addMedia(QUrl("qrc:/img/bgm2.mp3"));
    l->setPlaybackMode(QMediaPlaylist::Loop);
    media=new QMediaPlayer(this,QMediaPlayer::LowLatency);
    media->setPlaylist(l);
    media->setVolume(100);
    media->play();

isend=false;
isfin=false;
correct.setText("correct:");
error.setText("error:");
er=0;co=0;
    target=81;
    for(int i=0;i<9;i++)
    {

        trylist[i]=i+1;
        for(int j=0;j<9;j++){
            base[i][j].index=i*9+j;
            map[i][j]=0;
            connect(&base[i][j],SIGNAL(clicked()),this,SLOT(click()));
            qg.addWidget(&base[i][j],i,j,5,5);
        }
        map[0][i]=i+1;
    }
    QPushButton *b1=new QPushButton("answer");
    QPushButton *b2=new QPushButton("reset");
    QPushButton *b3=new QPushButton("back to title");
    b1->setFixedSize(50,50);
    b2->setFixedSize(50,50);
    b3->setFixedSize(85,50);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(startsolve()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(back()));
    qh.addLayout(&qg);
    qv.addWidget(b1);
    qv.addWidget(b2);
    qv.addWidget(b3);
    correct.setFixedSize(90,50);
    error.setFixedSize(90,25);
    qv.addWidget(&correct);
    qv.addWidget(&error);
    qh.addLayout(&qv);
    setLayout(&qh);
    setFixedSize(500,500);
    setWindowTitle("solve");
    srand(time(NULL));
    random_shuffle(&map[0][0],&map[0][9]);
    random_shuffle(&trylist[0],&trylist[9]);
    tryset(0);
    show();

}
void play::keyPressEvent(QKeyEvent *event){
  if(target==81)return;
  int r=target/9;
  int c=target%9;int area;

  if(base[r][c].isfix!=true)
  {
      if(event->key()==Qt::Key_1){base[r][c].setText("1");map[r][c]=1;}
      else if(event->key()==Qt::Key_2){base[r][c].setText("2");map[r][c]=2;}
      else if(event->key()==Qt::Key_3){base[r][c].setText("3");map[r][c]=3;}
      else if(event->key()==Qt::Key_4){base[r][c].setText("4");map[r][c]=4;}
      else if(event->key()==Qt::Key_5){base[r][c].setText("5");map[r][c]=5;}
      else if(event->key()==Qt::Key_6){base[r][c].setText("6");map[r][c]=6;}
      else if(event->key()==Qt::Key_7){base[r][c].setText("7");map[r][c]=7;}
      else if(event->key()==Qt::Key_8){base[r][c].setText("8");map[r][c]=8;}
      else if(event->key()==Qt::Key_9){base[r][c].setText("9");map[r][c]=9;}
      if(event->key()==Qt::Key_0)
      {base[r][c].setText(" ");

          map[r][c]=0;}
  }

}
void play::click(){
   int r=target/9;
   int c=target%9;
   if(target!=81&&!isfin){
         if(base[r][c].isfix)base[r][c].setStyleSheet("border:0.5px solid gray;");
         else if(!base[r][c].isfix)base[r][c].setStyleSheet("color:blue");
   }
   target=qobject_cast<box*>(sender())->index;
   r=target/9;
   c=target%9;
   if(target!=81&&!isfin){base[r][c].setStyleSheet("background-color:gray;border:0.5px solid gray;");}
}
void play::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,4));
    painter.drawLine(101,80,101,425);
    painter.drawLine(198,80,198,425);
    painter.drawLine(0,203,300,203);
    painter.drawLine(0,316,300,316);
    painter.drawLine(2,80,2,425);
    painter.drawLine(300,80,300,425);
    painter.drawLine(0,80,300,80);
    painter.drawLine(0,425,300,425);
}
bool play:: check(int index){
    int row = index / 9;
    int col = index % 9;
    for(int j = 0; j < 9; ++j){
        if(map[j][col] == map[row][col] && j != row){
            return false;
        }
    }
    for(int j = 0; j < 9; ++j){
        if(map[row][j] == map[row][col] && j != col){
            return false;
        }
    }
    int temprow = row / 3 * 3;
    int tempcol = col / 3 * 3;
    for(int j = temprow; j < temprow + 3;++j){
        for(int k = tempcol; k < tempcol + 3; ++k){
            if(map[j][k] == map[row][col] && j != row && k != col){
                return false;
            }
        }
    }
return true; }
void play::tryset(int index){
    if(index == 81){
        for(int i = 0; i < 9; ++i){
            for(int j =  0; j < 9; ++j){
                answer[i][j]=map[i][j];
                base[i][j].value=map[i][j];
                if(rand()%3==0){
                    base[i][j].isfix=false;
                    base[i][j].setStyleSheet("color:blue");
                    map[i][j]=0;base[i][j].setText(" ");}
                else{
                    base[i][j].isfix=true;
                base[i][j].setText(QString::number(map[i][j]));}
            }
        }
        isend=true;
        return;
    }
    int row = index / 9;
    int col = index % 9;
    if(map[row][col] == 0){
        for(int i =0; i < 9; ++i){
            map[row][col] = trylist[i];
            if(check(index)){
                tryset(index+1);
                if(isend)return;
            }
        }

        map[row][col] = 0;
    }else{
        tryset(index+1);
    }
}
void play::startsolve(){
    if(isfin)return;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++){


            if(map[i][j]!=answer[i][j]){
                base[i][j].setStyleSheet("background-color:red;border:0.5px solid gray;");
                base[i][j].setText(QString::number(answer[i][j]));
                er=er+1;
            }
            else if(map[i][j]==answer[i][j]&&!base[i][j].isfix)
            {base[i][j].setStyleSheet("background-color:green;border:0.5px solid gray;");
            co=co+1;
            }
            else{base[i][j].setStyleSheet("border:0.5px solid gray;");}
            base[i][j].isfix=true;
        }
    }
    isfin=true;
    int recp;
    recp=co*100/(er+co);
    correct.setWordWrap(true);
    correct.setText("correct:"+QString::number(co)+"/"+QString::number(er+co)+" "+"("+QString::number(recp)+"%)");
    error.setText("error:"+QString::number(er));

    QSettings *set=new QSettings();

    if(recp>set->value("rec").toInt()){
    set->setValue("rec",recp);
    set->sync();}
}
void play::reset(){
    if(isend){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                base[i][j].value=0;
                base[i][j].setText("0");
                base[i][j].isfix=false;
                map[i][j]=0;
                base[i][j].setStyleSheet("border:0.5px solid gray");
            }
            map[0][i]=1+i;
        }
        isend=false;
        isfin=false;
        random_shuffle(&map[0][0],&map[0][9]);
        random_shuffle(&trylist[0],&trylist[9]);
        tryset(0);
        correct.setText("correct:");
        error.setText("error:");
        er=co=0;
    }
}
void play::back(){
    MainWindow *w=new MainWindow();
    w->show();
    media->stop();
    delete media;
    close();

}
