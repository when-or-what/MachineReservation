#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "picosha2.h"

/* Contrl the output text color for Linux */
/*
 \033[0m 关闭所有属性
\033[1m 高亮
\033[2m 亮度减半
\033[3m 斜体
\033[4m 下划线
\033[5m 闪烁
\033[6m 快闪
\033[7m 反显
\033[8m 消隐
\033[9m 中间一道横线
10-19 关于字体的
21-29 基本与1-9正好相反
30-37 设置前景色
40-47 设置背景色

# 字颜色:30--37
30:黑
31:红
32:绿
33:黄
34:蓝色
35:紫色
36:深绿
37:白色
38 打开下划线,设置默认前景色
39 关闭下划线,设置默认前景色

# 字背景颜色范围:40--49
40 黑色背景
41 红色背景
42 绿色背景
43 棕色背景
44 蓝色背景
45 品红背景
46 孔雀蓝背景
47 白色背景
48 不知道什么东西
49 设置默认背景色
*/
#define NONE_COLOR "\033[0m"
#define BLACK "\033[0;30m"
#define DARK_GRAY "\033[1;30m"
#define RED "\033[0;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define LIGHT_BLUE "\033[1;34m"
#define I_LIGHT_BLUE "\033[1;3;34m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

#define UNUSED(a) ((void)(a))

#define LOG_FP                        \
    (fclose(gv::Global::LOG_FILE_FP), \
     gv::Global::LOG_FILE_FP = fopen(gv::Global::LOG_PATH, "a+"))

#define TIME                                                       \
    time_t __tIJAGYuyshq__ushd = time(NULL);                       \
    struct tm* __tmLLAK__kmskKA = localtime(&__tIJAGYuyshq__ushd); \
    char __tlkJ_soIKxime_str[20];                                  \
    strftime(__tlkJ_soIKxime_str, sizeof(__tlkJ_soIKxime_str),     \
             "%Y-%m-%d %H:%M:%S", __tmLLAK__kmskKA);

#define ERR(msg, ...)                                                     \
    do {                                                                  \
        TIME fprintf(LOG_FP, LIGHT_RED "[%s ERROR] " msg NONE_COLOR "\n", \
                     __tlkJ_soIKxime_str, ##__VA_ARGS__);                 \
    } while (0)

#define INFO(msg, ...)                                                     \
    do {                                                                   \
        TIME fprintf(LOG_FP, LIGHT_GREEN "[%s INFO] " msg NONE_COLOR "\n", \
                     __tlkJ_soIKxime_str, ##__VA_ARGS__);                  \
    } while (0)

#define WARN(msg, ...)                                                \
    do {                                                              \
        TIME fprintf(LOG_FP, YELLOW "[%s WARN] " msg NONE_COLOR "\n", \
                     __tlkJ_soIKxime_str, ##__VA_ARGS__);             \
    } while (0)

#define OUT(msg, ...) printf(LIGHT_CYAN "[MSG] " msg NONE_COLOR, ##__VA_ARGS__)

#define SHOW_CMD_TIP(msg, ...) \
    printf(I_LIGHT_BLUE msg NONE_COLOR, ##__VA_ARGS__)

#define MEM_ALLOC_FAILED(ptr)     \
    if (!ptr) {                   \
        ERR("Mem alloc failed."); \
        exit(EXIT_FAILURE);       \
    }

#define FREE(ptr) \
    free(ptr);    \
    ptr = NULL;

#define DELETE(ptr) \
    delete ptr;     \
    ptr = nullptr;

namespace gv {
class Global {
   public:
    // 系统内部使用常量
    // 开辟缓冲区空间的大小
    static const size_t NAME_LEN;  // 姓名（变量名）
    static const size_t VAL_LEN;   // 变量值
    static const size_t PSWD_LEN;  // 密码（包括密文）
    static const size_t CMD_LEN;   // 输入命令（菜单选项）
    static const size_t SID_LEN;   // 学号长度
    static const size_t TID_LEN;   // 教师职工号长度
    static const size_t PATH_LEN;  // 文件路径
    static const size_t LINE_LEN;  // 数据文件每一行
    static const size_t PSW_LEN;   // 管理员初始密码长度
    // 文件名
    static const char* LOG_FILE;           // 日志文件名
    static const char* MRRS_HOME;          // 项目所在目录名
    static const char* STUDENT_FILE;       // 学生信息
    static const char* TEACHER_FILE;       // 老师信息
    static const char* RESERV_FILE;        // 预约信息
    static const char* MACHINE_ROOM_FILE;  // 机房信息
    static const char* CONFIG_FILE;        // 配置文件

    // 文件绝对路径
    static char* USER_HOME;          // 用户家目录
    static char* STUDENT_PATH;       // 学生信息
    static char* TEACHER_PATH;       // 老师信息
    static char* RESERV_PATH;        // 预约信息
    static char* MACHINE_ROOM_PATH;  // 机房信息
    static char* CONFIG_PATH;        // 配置文件
    static char* LOG_PATH;           // 日志文件

    static FILE* LOG_FILE_FP;  // 日志文件指针

    // 配置文件变量名
    static const char* ADMIN_PSWD;  // 管理员密码
    static const char* INIT_FLAG;   // 管理员密码是否初始化
    static const char* N_INIT;      // 管理员密码未初始化状态
    static const char* INITED;      // 管理员密码已经初始化状态

    Global();
    ~Global();

    /**
     * @brief 系统初始化，主要检查数据文件以及配置文件是否存在，不存在则创建
     */
    static void sys_init();

    /**
     * @brief 系统还原，主要将 `sys_init()` 函数中申请的资源全部释放
     */
    static void sys_restore();

    /**
     * @brief 密码加密
     * @note
     * 本函数没有返回值，参数`pswd`是传入传出参数，由调用者提供并且加密后的密文放在其中
     *
     * @param text 密码明文
     * @param pswd 密码密文
     */
    static void sha256(const char* text, char* pswd);
    /**
     * @brief 获取无符号数的长度
     *
     * @param u 一个`uint32_t`的无符号32位整数
     * @return `size_t` 传入参数的长度，如99则返回2; 123则返回3
     */
    static size_t get_uint_len(uint32_t u);

    /**
     * @brief 获取一个长度为`len`的随机字符串
     * @note
     * 本函数只负责生成随机字符串，并返回一个指向堆内存的指针，内存的释放由调用者负责
     *
     * @param len 随机字符串的长度
     * @return `char*` 随机字符串
     */
    static char* rand_string(size_t len);
};

}  // namespace gv

#endif /* _GLOBAL_H_ */