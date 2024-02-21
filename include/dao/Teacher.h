#ifndef _DAO_TEACHER_H_
#define _DAO_TEACHER_H_

#include "../Global.h"
#include "ent/Teacher.h"

/**
 * @brief 数据持久层封装
 */
namespace dao {
/**
 * @brief 教师信息文件读写封装
 * @note
 * 数据格式：职工号 姓名 密码密文 管理的机房号
 */
class Teacher {
   public:
    Teacher();
    ~Teacher();

    /**
     * @brief 根据传入的教师实体指针向教师数据文件中写入一行文本
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 教师实体的指针
     */
    void insert(ent::Teacher *newdata);
    /**
     * @brief 根据教师号（教师唯一ID）来查询教师信息
     * @note
     * 本函数会返回`nullptr`或者一个指向堆上内存的指针，内存的释放由调用者负责
     *
     * @param tid 唯一教师ID
     * @return `ent::Teacher*`
     * 返回的教师实体指针，包含查询所得的教师信息，如果没查到，则为`nullptr`
     */
    ent::Teacher *select(uint32_t tid);
    /**
     * @brief 查询所有的教师信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Teacher*`指针的`std::vector`，每一个`ent::Teacher*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @return `std::vector<ent::Teacher *>`
     * 返回一个空`std::vector`或者一个装有一个或多个`ent::Teacher
     * *`指针的`std::vector`
     */
    std::vector<ent::Teacher *> select();
    /**
     * @brief 根据教师唯一ID更新教师信息
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 新数据的指针
     */
    void update(ent::Teacher *newdata);
    /**
     * @brief 根据教师唯一ID删除教师信息
     *
     * @param tid 教师唯一ID
     */
    void delet(uint32_t tid);
    /**
     * @brief 删除所有教师信息（清空数据文件）
     *
     */
    void delet();
};

}  // namespace dao

#endif /* _DAO_TEACHER_H_ */