#ifndef _SRV_STUDENT_H_
#define _SRV_STUDENT_H_

#include "dao/MachineRoom.h"
#include "dao/Reserv.h"
#include "dao/Student.h"
#include "ent/Student.h"

namespace srv {
class Student {
   private:
    // 学生实体
    ent::Student* stu;
    // 数据操作
    dao::Reserv* r;
    dao::Student* s;
    dao::MachineRoom* m;
    // 菜单
    static const std::unordered_map<char, const char*> MENU;

    /**
     * @brief 预约机房
     *
     * @param mid 机房号
     * @param date 时间（16位数字，格式为yyyyMMDDhhmmhhmm）
     */
    void reserv(uint32_t mid, uint64_t date);
    /**
     * @brief 查看所有预约信息
     *
     */
    void view_reservations();
    /**
     * @brief 查看自己的预约信息
     *
     */
    void view_my_reservations();
    /**
     * @brief 取消自己的预约
     *
     * @param id 预约ID
     * @return true 成功取消预约
     * @return false 预约不存在或者输入错误的ID
     */
    bool cancel(uint32_t id);
    /**
     * @brief 显示学生菜单
     *
     */
    void show_ui();

   public:
    Student();
    Student(ent::Student* stu, dao::Reserv* r, dao::Student* s,
            dao::MachineRoom* m);
    ~Student();
    // 上层接口
    /**
     * @brief 校验信息是否匹配
     *
     * @param sname 姓名
     * @param plain_pswd 密码明文
     * @return true 信息匹配
     * @return false 信息不匹配
     */
    bool check_info(const char* sname, const char* plain_pswd);

    /**
     * @brief 提供给上层调用的接口
     *
     */
    void ui();
};

}  // namespace srv

#endif /* _SRV_STUDENT_H_ */