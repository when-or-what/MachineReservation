#ifndef _DAO_STUDENT_H_
#define _DAO_STUDENT_H_

#include "../Global.h"
#include "ent/Student.h"

/**
 * @brief 数据持久层封装
 */
namespace dao {
/**
 * @brief 学生信息文件读写封装
 * @note
 * 数据格式：学号 姓名 密码密文
 */
class Student {
   public:
    Student();
    ~Student();

    /**
     * @brief 根据传入的学生实体指针向学生数据文件中写入一行文本
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 学生实体的指针
     */
    void insert(ent::Student *newdata);
    /**
     * @brief 根据学号（学生唯一ID）来查询学生信息
     * @note
     * 本函数会返回`nullptr`或者一个指向堆上内存的指针，内存的释放由调用者负责
     *
     * @param sid 唯一学生ID
     * @return `ent::Student*`
     * 返回的学生实体指针，包含查询所得的学生信息，如果没查到，则为`nullptr`
     */
    ent::Student *select(uint32_t sid);
    /**
     * @brief 查询所有的学生信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Student*`指针的`std::vector`，每一个`ent::Student*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @return `std::vector<ent::Student *>`
     * 返回一个空`std::vector`或者一个装有一个或多个`ent::Student
     * *`指针的`std::vector`
     */
    std::vector<ent::Student *> select();
    /**
     * @brief 根据学生唯一ID更新学生信息
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 新数据的指针
     */
    void update(ent::Student *newdata);
    /**
     * @brief 根据学生唯一ID删除学生信息
     *
     * @param sid 学生唯一ID
     */
    void delet(uint32_t sid);
    /**
     * @brief 删除所有学生信息（清空数据文件）
     *
     */
    void delet();
};

}  // namespace dao

#endif /* _DAO_STUDENT_H_ */