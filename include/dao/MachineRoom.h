#ifndef _DAO_MACHINE_ROOM_H_
#define _DAO_MACHINE_ROOM_H_

#include "../Global.h"
#include "ent/MachineRoom.h"

/**
 * @brief 数据持久层封装
 */
namespace dao {
/**
 * @brief 机房信息文件读写封装
 * @note
 * 数据格式：机房号 机房名 最大容量
 */
class MachineRoom {
   public:
    MachineRoom();
    ~MachineRoom();

    /**
     * @brief 根据传入的机房实体指针向机房数据文件中写入一行文本
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 机房实体的指针
     */
    void insert(ent::MachineRoom *newdata);
    /**
     * @brief 根据机房号（机房唯一ID）来查询机房信息
     * @note
     * 本函数会返回`nullptr`或者一个指向堆上内存的指针，内存的释放由调用者负责
     *
     * @param mid 唯一机房ID
     * @return `ent::MachineRoom*`
     * 返回的机房实体指针，包含查询所得的机房信息，如果没查到，则为`nullptr`
     */
    ent::MachineRoom *select(uint32_t mid);
    /**
     * @brief 查询所有的机房信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::MachineRoom*`指针的`std::vector`，每一个`ent::MachineRoom*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @return `std::vector<ent::MachineRoom *>`
     * 返回一个空`std::vector`或者一个装有一个或多个`ent::MachineRoom
     * *`指针的`std::vector`
     */
    std::vector<ent::MachineRoom *> select();
    /**
     * @brief 根据机房唯一ID更新机房信息
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 新数据的指针
     */
    void update(ent::MachineRoom *newdata);
    /**
     * @brief 根据机房唯一ID删除机房信息
     *
     * @param mid 机房唯一ID
     */
    void delet(uint32_t mid);
    /**
     * @brief 删除所有机房信息（清空数据文件）
     *
     */
    void delet();
};

}  // namespace dao

#endif /* _DAO_MACHINE_ROOM_H_ */