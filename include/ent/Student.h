#ifndef _ENT_STUDENT_H_
#define _ENT_STUDENT_H_

#include "../Global.h"

namespace ent {
/**
 * @brief 学生实体类
 *
 */
class Student {
   private:
    uint32_t id;    // 自增主键
    uint32_t s_id;  // 学生账号
    char* s_name;   // 学生姓名
    char* pswd;     // 学生密码密文

   public:
    /* 构造函数和析构函数 */
    Student();
    Student(uint32_t id, uint32_t s_id, const char* s_name, const char* pswd);
    ~Student();
    /* getter setter */
    uint32_t get_id();
    void set_id(uint32_t id);

    char* get_sname();
    void set_sname(const char* sname);

    uint32_t get_sid();
    void set_sid(uint32_t sid);

    char* get_pswd();
    void set_pswd(const char* pswd);
    /* to string */
    void show();
};

}  // namespace ent

#endif /* _ENT_STUDENT_H_ */