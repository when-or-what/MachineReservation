#ifndef _MACHINE_RESERVATION_H_
#define _MACHINE_RESERVATION_H_

#include "srv/Admin.h"
#include "srv/Student.h"
#include "srv/Teacher.h"

class MachineReservation {
   private:
    // 管理员密码
    char* password;
    // 系统管理员密码初始化状态
    bool is_init;
    // 机房管理
    dao::MachineRoom* mr;
    // 机房预约管理（清空预约）
    dao::Reserv* reserv;
    // 学生管理
    dao::Student* stu;
    // 老师管理
    dao::Teacher* tea;
    // 配置文件管理
    dao::Config* conf;

    // 私有函数
    void init();
    void show_ui();

   public:
    /* 构造函数和析构函数 */
    MachineReservation();
    ~MachineReservation();
    /* 类方法 */
    // 上层接口
    void start();
};

#endif /* _MACHINE_RESERVATION_H_ */