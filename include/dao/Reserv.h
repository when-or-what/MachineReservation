#ifndef _DAO_RESERV_H_
#define _DAO_RESERV_H_

#include "../Global.h"
#include "ent/Reserv.h"

/**
 * @brief 数据持久层封装
 */
namespace dao {
/**
 * @brief 机房预约文件读写封装
 * @note"%u %lu %u %u %u\n"
 * 数据格式：ID 时间 学号 机房号 状态
 */
class Reserv {
   public:
    Reserv();
    ~Reserv();

    /**
     * @brief 根据传入的机房预约实体指针向机房预约数据文件中写入一行文本
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 机房预约实体的指针
     */
    void insert(ent::Reserv *newdata);
    /**
     * @brief 根据机房预约唯一ID来查询机房预约信息
     * @note
     * 本函数会返回`nullptr`或者一个指向堆上内存的指针，内存的释放由调用者负责
     *
     * @param mid 唯一机房预约ID
     * @return `ent::Reserv*`
     * 返回的机房预约实体指针，包含查询所得的机房预约信息，如果没查到，则为`nullptr`
     */
    ent::Reserv *select_one(uint32_t id);
    /**
     * @brief 根据学号查询机房预约信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`，每一个
     *`ent::Reserv*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @param sid 学生学号
     * @return `std::vector<ent::Reserv *>`
     * 返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`
     */
    std::vector<ent::Reserv *> select_by_sid(uint32_t sid);
    /**
     * @brief 根据机房号查询机房预约信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`，每一个
     *`ent::Reserv*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @param mid 机房唯一ID
     * @return `std::vector<ent::Reserv *>`
     * 返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`
     */
    std::vector<ent::Reserv *> select_by_mid(uint32_t mid);
    /**
     * @brief 查询所有机房预约信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`，每一个
     *`ent::Reserv*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @return `std::vector<ent::Reserv *>`
     * 返回空`std::vector`或者一个装有一个或多个`ent::Reserv*`指针的`std::vector`
     */
    std::vector<ent::Reserv *> select();
    /**
     * @brief
     * 根据机房预约唯一ID更新机房预约信息（主要是学生取消预约和老师审核预约）
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 新数据的指针
     */
    void update(ent::Reserv *newdata);
    /**
     * @brief 根据机房预约唯一ID删除机房预约信息
     *
     * @param id 机房预约唯一ID
     */
    void delet(uint32_t id);
    /**
     * @brief 删除所有机房预约信息（清空机房预约数据文件）
     *
     */
    void delet();
};

}  // namespace dao

#endif /* _DAO_RESERV_H_ */