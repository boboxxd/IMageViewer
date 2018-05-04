#ifndef ALARMHANDLE_H
#define ALARMHANDLE_H

#include <QObject>
#include "HHClient.hpp"
using namespace hhclient;

namespace Alarm {

class AlarmHandle : public QObject,public HHlientCallback
{
    Q_OBJECT
public:
    AlarmHandle();
    void onAlarm(const HHAlarm &alarm);
signals:

public slots:
};

class AlarmAPI: public QObject
{
    Q_OBJECT
public:
    AlarmAPI(QString ip,int port);
    void DestroyAPI();
    ~AlarmAPI();
private:
    HHClientAPI *client;
    AlarmHandle *callback;
};

}
#endif // ALARMHANDLE_H
