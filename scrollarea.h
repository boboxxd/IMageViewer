#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>

class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    ScrollArea(QWidget* parent = NULL);
    ~ScrollArea();
    void setdefaultscaler(float radio);
signals:
    float scaleradio(float radio);
protected:
    bool eventFilter(QObject *obj,QEvent *evt);

private:
    bool mMoveStart;
    bool mContinuousMove;
    QPoint mMousePoint; //抓动时
    float scaler;
};



#endif // SCROLLAREA_H
