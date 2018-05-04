//
//  HHClient.hpp
//

#ifndef HHClient_hpp
#define HHClient_hpp

#include <string>
#include <vector>

namespace hhclient
{
    enum HHResult                       //接口返回值
    {
        OK = 0,                         //OK
        LOGIN_DUPLICATE = 1,            //重复登录
        NET_ERROR      = 2,             //网络错误
        NOT_LOGIN      = 3,             //未登录
    };

    enum HHCarType{
        NONE = 0,
        TRUCK_CRANE = 1,                //吊车
        EXCAVATOR = 2,                  //挖掘机
        CEMENT_PUMP_TRUCK = 3,          //水泥泵车
        BULLDOZER = 4,                  //推土机
        TRUCK_CRANE_WORKING_ARM = 5,    //扬臂吊车
        TOWER_CRANE_ARM = 6,            //塔吊
    };
    
    struct HHAlarm
    {
        int id;
        HHCarType car_type;         //报警类型
        long timestamp;             //报警时间
        int coordinate[4];           //x,y,with,heihgt
        long start_timestamp;        //报警开始时间
        long end_timestamp;          //报警结束时间  
        float credibility;           //得分        
        long alarm_pic_size;        
        char* alarm_pic;            //报警图片
        long alarm_vid_size;        
        char* alarm_vid;            //报警视频
        long src_image_size;        
        char* src_image;            //原图
        int image_id;               //图片序号
        int image_width;            //图片宽
        int image_height;           //图片高
    };
    
    class HHlientCallback
    {
    public:
        //第三步: 实现onAarm函数获得报警信息
        virtual void onAlarm(const HHAlarm &alarm) {}
    };
    
    class HHClientAPI
    {
    public:
        // 第二步: 登录到服务器
        virtual HHResult Login(std::string ip, int port) = 0;
    };
    
    // 第一步: 创建HHClientAPI
    HHClientAPI* HHClientAPI_Create(HHlientCallback *);
    
    //第四步: 销毁实例，断开于服务链接
    void HHClient_Destroy(HHClientAPI*);
}

#endif
