#include "scrollarea.h"
#include <QDebug>
#include "scrollarea.h"
#include <QMouseEvent>
#include <QScrollBar>
#include "imagelabel.h"
#include <QWheelEvent>
ScrollArea::ScrollArea(QWidget *parent)
    :QScrollArea(parent)     //基类
    ,mMoveStart(false)
    ,mContinuousMove(false)
    ,mMousePoint(QPoint(0,0))
{
    installEventFilter(this);
    scaler=1;
    setCursor(Qt::OpenHandCursor);
}

ScrollArea::~ScrollArea()
{
}

bool ScrollArea::eventFilter(QObject *obj, QEvent *evt)
{
    if(evt->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = (QMouseEvent*) evt;
        if(me->buttons() & Qt::LeftButton)
        {
            setCursor(Qt::ClosedHandCursor);
            if(!mMoveStart)
            {
                mMoveStart = true;
                mContinuousMove = false;
                mMousePoint = me->globalPos();

            }
            else
            {
                QScrollBar *scrollBarx = horizontalScrollBar();
                QScrollBar *scrollBary = verticalScrollBar();

                QPoint p = me->globalPos();
                int offsetx = p.x() - mMousePoint.x();
                int offsety = p.y() - mMousePoint.y();
                if(!mContinuousMove && (offsetx > -10 && offsetx < 10) && (offsety > -10 && offsety < 10))
                    return false;

                mContinuousMove = true;

                scrollBarx->setValue(scrollBarx->value() - offsetx);
                scrollBary->setValue(scrollBary->value() - offsety);
                mMousePoint = p;
            }
            return true;
        }
    }
    else if(evt->type() == QEvent::MouseButtonRelease)
    {
        setCursor(Qt::OpenHandCursor);
        mMoveStart = false;
    }
    else if(evt->type() == QEvent::Wheel)
    {
        QWheelEvent *me = (QWheelEvent*) evt;
        if(me->delta()>0)
        {
            if(scaler<=1.9)
            {
                scaler+=0.005;
            }
        }else
        {
            if(scaler>=0.1)
            {
                scaler-=0.01;
            }
        }
        emit scaleradio(scaler);
        return true;
    }

    return QObject::eventFilter(obj,evt);
}

void ScrollArea::setdefaultscaler(float radio)
{
    scaler=radio;
}
