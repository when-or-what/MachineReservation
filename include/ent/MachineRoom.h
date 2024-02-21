#ifndef _ENT_MACHINE_H_
#define _ENT_MACHINE_H_

#include "../Global.h"

namespace ent {
/**
 * @brief 机房实体类
 */
class MachineRoom {
   private:
    uint32_t id;       // 自增主键
    uint32_t m_id;     // 机房号
    char* m_name;      // 机房名（位置）
    uint32_t maxsize;  // 机房最大容量

   public:
    MachineRoom();
    MachineRoom(uint32_t id, uint32_t mid, const char* name, uint32_t sz);
    ~MachineRoom();
    /* getter setter */
    uint32_t get_id();
    void set_id(uint32_t id);

    uint32_t get_mid();
    void set_mid(uint32_t mid);

    char* get_mname();
    void set_mname(const char* mname);

    uint32_t get_maxsize();
    void set_maxsize(uint32_t maxsize);
    /* to string */
    void show();
};

}  // namespace ent

#endif /* _ENT_MACHINE_H_ */