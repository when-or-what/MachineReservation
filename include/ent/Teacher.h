#ifndef _ENT_TEACHER_H_
#define _ENT_TEACHER_H_

#include "../Global.h"

namespace ent {
/**
 * @brief 老师实体类
 *
 */
class Teacher {
   private:
    uint32_t id;    // 自增主键
    uint32_t t_id;  // 老师账号
    char* t_name;   // 老师姓名
    char* pswd;     // 老师密码密文
    uint32_t m_id;  // 老师负责的机房号
   public:
    /* 构造函数和析构函数 */
    Teacher();
    Teacher(uint32_t id, uint32_t t_id, uint32_t m_id, const char* t_name,
            const char* pswd);
    ~Teacher();
    /* getter setter */
    uint32_t get_id();
    void set_id(uint32_t id);

    char* get_tname();
    void set_tname(const char* tname);

    uint32_t get_tid();
    void set_tid(uint32_t tid);

    char* get_pswd();
    void set_pswd(const char* pswd);

    uint32_t get_mid();
    void set_mid(uint32_t mid);
    /* to string */
    void show();
};

}  // namespace ent

#endif /* _ENT_TEACHER_H_ */