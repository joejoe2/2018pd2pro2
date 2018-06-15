#ifndef BOX_H
#define BOX_H
#include<QLabel>
#include <QObject>
class box:public QLabel
{
    Q_OBJECT
public:
    box();
    void mousePressEvent(QMouseEvent *event);
    bool isfix;
    int index;
    int value;
signals:
    void clicked();
};

#endif // BOX_H
