#ifndef _DAO_CONFIG_H_
#define _DAO_CONFIG_H_

#include "../Global.h"
#include "ent/Config.h"

/**
 * @brief 数据持久层封装
 */
namespace dao {
/**
 * @brief 配置文件读写封装
 * @note
 * 数据格式：变量名 变量值
 */
class Config {
   public:
    Config();
    ~Config();

    /**
     * @brief 根据传入的配置项实体指针向配置项数据文件中写入一行文本
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 配置项实体的指针
     */
    void insert(ent::Config *newdata);
    /**
     * @brief 根据键来查询配置项信息
     * @note
     * 本函数会返回`nullptr`或者一个指向堆上内存的指针，内存的释放由调用者负责
     *
     * @param key 键
     * @return `ent::Config*`
     * 返回的配置项实体指针，包含查询所得的配置项信息，如果没查到，则为`nullptr`
     */
    ent::Config *select(const char *key);
    /**
     * @brief 查询所有的配置项信息
     * @note
     * 本函数会返回空`std::vector`或者一个装有一个或多个`ent::Config*`指针的`std::vector`，每一个`ent::Config*`指针都指向一个堆上的内存，内存的释放由调用者负责
     *
     * @return `std::vector<ent::Config *>`
     * 返回一个空`std::vector`或者一个装有一个或多个`ent::Config
     * *`指针的`std::vector`
     */
    std::vector<ent::Config *> select();
    /**
     * @brief 根据配置项键更新配置项信息
     * @note
     * 本函数只是使用指针所指的数据而不释放指针所指内存，内存的释放由调用者负责
     *
     * @param newdata 新数据的指针
     */
    void update(ent::Config *newdata);
    /**
     * @brief 根据配置项键删除配置项信息
     *
     * @param key 配置项键
     */
    void delet(const char *key);
};

}  // namespace dao

#endif /* _DAO_CONFIG_H_ */