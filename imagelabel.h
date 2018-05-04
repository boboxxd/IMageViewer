#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include "scrollarea.h"
class IMageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IMageLabel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);

signals:
    void imageshift(int sx,int sy);

public slots:
    void RecieveImage(const QString&);
    void RecieveScale(float radio);
private:
    QImage image;
    QPixmap pix;
    QImage normalimage;
    QPoint startpos;
    float radio;

    bool reloadflag=false;//重新载入标志，确保画完框后，重新载入图片
    void reload();
};

#endif // IMAGELABEL_H
