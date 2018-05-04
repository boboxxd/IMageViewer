#include "alarmhandle.h"
#include <QDebug>
#include <fstream>
#include <string>
namespace Alarm {

AlarmHandle::AlarmHandle()
{

}

void AlarmHandle::onAlarm(const HHAlarm &alarm)
{
//    qDebug() << "-----------------onAlarm----------------------- " << endl;

//    qDebug() << "id " << alarm.id;
//    qDebug() << "car_type " << alarm.car_type;
//    qDebug() << "timestamp " << alarm.timestamp;
//    qDebug() << "x " << alarm.coordinate[0];
//    qDebug() << "y " << alarm.coordinate[1];
//    qDebug() << "width " << alarm.coordinate[2];
//    qDebug() << "height " << alarm.coordinate[3];
//    qDebug() << "start " << alarm.start_timestamp;
//    qDebug() << "end " << alarm.end_timestamp;
//    qDebug() << "credibility " << alarm.credibility;

//    //save alarm image
//    if(alarm.alarm_pic_size > 1){
//        char buffer_alarm[256];
//        sprintf(buffer_alarm, "./output/alarm_%d.jpg", alarm.id);
//        std::ofstream os_alarm(buffer_alarm,std::ios::binary);
//        os_alarm.write(alarm.alarm_pic, alarm.alarm_pic_size);
//        os_alarm.close();
//    }
}

AlarmAPI::AlarmAPI(QString ip,int port)
{
//    callback=new AlarmHandle();
//    client=HHClientAPI_Create(callback);
//    HHResult ret=client->Login(ip.toStdString(),port);
//    if(ret !=OK){
//        qDebug()<<"login error!";
//    }
}

void AlarmAPI::DestroyAPI()
{
//    HHClient_Destroy(client);
}

AlarmAPI::~AlarmAPI()
{
    if(client)
    {
       // HHClient_Destroy(client);
    }
}

}
