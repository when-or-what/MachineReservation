#ifndef _SRV_TEACHER_H_
#define _SRV_TEACHER_H_

#include "dao/Reserv.h"
#include "dao/Teacher.h"
#include "ent/Teacher.h"

namespace srv {
class Teacher {
   private:
    // 老师实体
    ent::Teacher* tea;
    dao::Reserv* r;
    dao::Teacher* t;

    // 菜单
    static const std::unordered_map<char, const char*> MENU;

    /**
     * @brief 审核预约
     *
     * @param id 预约ID
     * @param newstat 审核状态：通过/不通过
     * @return true 审核成功
     * @return false 审核失败
     */
    bool audit_reservations(uint32_t id, uint32_t newstat);
    /**
     * @brief 查看自己管理的机房的所有预约
     *
     */
    void view_reservations();
    /**
     * @brief 显示老师菜单
     *
     */
    void show_ui();

   public:
    Teacher();
    Teacher(ent::Teacher* tea, dao::Reserv* r, dao::Teacher* t);
    ~Teacher();
    /**
     * @brief 校验信息是否匹配
     *
     * @param tname 姓名
     * @param plain_pswd 密码明文
     * @return true 信息匹配
     * @return false 信息不匹配
     */
    bool check_info(const char* tname, const char* plain_pswd);

    /**
     * @brief 提供给上层调用的接口
     *
     */
    void ui();
};

}  // namespace srv

#endif /* _SRV_TEACHER_H_ */