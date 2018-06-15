#include "box.h"

box::box()
{
setText("0");
value=0;
isfix=false;
setFixedSize(20,20);
setFrameShape(QFrame::Box);
setStyleSheet("border:0.5px solid gray");
}
void box::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

