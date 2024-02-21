#ifndef _SRV_ADMIN_H_
#define _SRV_ADMIN_H_

#include "dao/Config.h"
#include "dao/MachineRoom.h"
#include "dao/Reserv.h"
#include "dao/Student.h"
#include "dao/Teacher.h"
#include "ent/Admin.h"

namespace srv {
class Admin {
   private:
    // 管理员实体
    ent::Admin* admin;
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

    // 菜单项
    static const std::unordered_map<char, const char*> MENU;

    // 学生的增删查改
    /**
     * @brief 添加学生
     *
     * @param sid 学号
     * @param sname 姓名
     * @param pswd 密码密文
     */
    void add_stu(uint32_t sid, const char* sname, const char* pswd);
    /**
     * @brief 查看所有学生信息
     *
     */
    void view_stu();
    /**
     * @brief 修改学生信息
     *
     * @param sid 学号
     * @param sname 姓名
     * @param pswd 密码密文
     */
    void mod_stu(uint32_t sid, const char* sname, const char* pswd);
    /**
     * @brief 根据学号删除学生
     *
     * @param sid 学号
     */
    void rmv_stu(uint32_t sid);
    // 老师的增删查改
    /**
     * @brief 添加老师
     *
     * @param tid 职工号
     * @param tname 姓名
     * @param pswd 密码密文
     * @param mid 管理的机房号
     */
    void add_tea(uint32_t tid, const char* tname, const char* pswd,
                 uint32_t mid);
    /**
     * @brief 查看老师信息
     *
     */
    void view_tea();
    /**
     * @brief 修改老师信息
     *
     * @param tid 职工号
     * @param tname 姓名
     * @param pswd 密码密文
     * @param mid 管理的机房号
     */
    void mod_tea(uint32_t tid, const char* tname, const char* pswd,
                 uint32_t mid);
    /**
     * @brief 根据职工号删除老师信息
     *
     * @param tid 职工号
     */
    void rmv_tea(uint32_t tid);
    // 机房的增删查改
    /**
     * @brief 添加机房
     *
     * @param mid 机房号
     * @param mname 机房名
     * @param maxsize 最大容量
     */
    void add_mach(uint32_t mid, const char* mname, uint32_t maxsize);
    /**
     * @brief 查看所有机房信息
     *
     */
    void view_mach();
    /**
     * @brief 修改机房信息
     *
     * @param mid 机房号
     * @param mname 机房名
     * @param maxsize 最大容量
     */
    void mod_mach(uint32_t mid, const char* mname, uint32_t maxsize);
    /**
     * @brief 根据机房号删除机房信息
     *
     * @param mid 机房号
     */
    void rmv_mach(uint32_t mid);
    /**
     * @brief 清空预约
     *
     */
    void clear_reserv();
    /**
     * @brief 修改管理员密码
     *
     * @param pswd 新密码密文
     */
    void modi_pswd(const char* pswd);
    /**
     * @brief 显示管理员菜单
     *
     */
    void show_ui();

   public:
    Admin();
    Admin(ent::Admin* admin, dao::Config* conf, dao::MachineRoom* mr,
          dao::Reserv* reserv, dao::Student* stu, dao::Teacher* tea);
    ~Admin();

    /**
     * @brief 校验管理员密码是否正确
     *
     * @param pswd 密码明文
     */
    bool check_info(const char* pswd);

    /**
     * @brief 提供给上层调用的接口
     *
     */
    void ui();
};

}  // namespace srv

#endif /* _SRV_ADMIN_H_ */