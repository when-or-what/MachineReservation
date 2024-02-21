#ifndef _ENT_ADMIN_H_
#define _ENT_ADMIN_H_

#include "../Global.h"

namespace ent {
/**
 * @brief 管理员实体类
 *
 */
class Admin {
   private:
    uint32_t no;  // 管理员账号
    char* pswd;   // 管理员密码密文
   public:
    /* 构造函数和析构函数 */
    Admin();
    Admin(uint32_t no, const char* p);
    ~Admin();
    /* getter setter */
    uint32_t get_no();
    void set_no(uint32_t no);

    char* get_pswd();
    void set_pswd(const char* pswd);
    /* to string */
    void show();
};

}  // namespace ent

#endif /* _ENT_ADMIN_H_ */