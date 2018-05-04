#include "imagelabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

IMageLabel::IMageLabel(QWidget *parent) : QLabel(parent)
{

}

void IMageLabel::RecieveImage(const QString& pixname)
{
    this->image=QImage(pixname);
    ScrollArea *scrollarea=qobject_cast<ScrollArea*>(this->parentWidget()->parentWidget()->parentWidget());
    normalimage=image.scaled(scrollarea->width(),scrollarea->height(),Qt::KeepAspectRatio);
    scrollarea->setdefaultscaler(qMin((float)scrollarea->width()/image.width(),(float)scrollarea->height()/image.height()));
    pix=QPixmap::fromImage(normalimage);
    setAlignment(Qt::AlignCenter);
    setPixmap(pix);
}

void IMageLabel::RecieveScale(float radio)
{
    if(!image.isNull())
    {
        this->radio=radio;
        pix=QPixmap::fromImage( image.scaled(image.width()*radio,image.height()*radio,Qt::KeepAspectRatio));
        setAlignment(Qt::AlignCenter);
        setPixmap(pix);
    }
}

void IMageLabel::reload()
{
    ScrollArea *scrollarea=qobject_cast<ScrollArea*>(this->parentWidget()->parentWidget()->parentWidget());
    normalimage=image.scaled(scrollarea->width(),scrollarea->height(),Qt::KeepAspectRatio);
    scrollarea->setdefaultscaler(qMin((float)scrollarea->width()/image.width(),(float)scrollarea->height()/image.height()));
    pix=QPixmap::fromImage(normalimage);
    setAlignment(Qt::AlignCenter);
    setPixmap(pix);
    reloadflag=true;
}

void IMageLabel::paintEvent(QPaintEvent *e)
{

    if(!image.isNull())
    {
        QPainter painter;
        painter.begin(&image);
        QPen pen(Qt::green, 7);
        painter.setPen(pen);
        painter.drawRect(QRect(100,100,300,300));
        painter.end();
        if(!reloadflag)
            reload();
    }

    return QLabel::paintEvent(e);
}
