#include "Global.h"

#define INIT_PATH(p, f)                         \
    do {                                        \
        p = (char*)malloc(len + strlen(f) + 1); \
        MEM_ALLOC_FAILED(p)                     \
        strcpy(path + len, f);                  \
        strcpy(p, path);                        \
    } while (0)

namespace gv {
/* 系统内部使用常量*/
// 开辟缓冲区空间的大小
const size_t Global::NAME_LEN = 100;  // 姓名（变量名）
const size_t Global::VAL_LEN = 512;   // 变量值
const size_t Global::PSWD_LEN = 70;   // 密码（包括密文）
const size_t Global::CMD_LEN = 10;    // 输入命令（菜单选项）
const size_t Global::PATH_LEN = 512;  // 文件路径
const size_t Global::LINE_LEN = 256;  // 数据文件每一行
// 数据字典常量
const size_t Global::SID_LEN = 6;  // 学号长度
const size_t Global::TID_LEN = 5;  // 职工号长度
const size_t Global::PSW_LEN = 6;  // 管理员初始密码长度
// 数据文件的文件名
const char* Global::MRRS_HOME = "/.mrrs";           // 项目所在目录名
const char* Global::LOG_FILE = "/mrrs.log";         // 日志文件名
const char* Global::STUDENT_FILE = "/student.dat";  // 学生信息
const char* Global::TEACHER_FILE = "/teacher.dat";  // 老师信息
const char* Global::RESERV_FILE = "/reserv.dat";    // 预约信息
const char* Global::MACHINE_ROOM_FILE = "/machine_room.dat";  // 机房信息
const char* Global::CONFIG_FILE = "/mrrs.conf";               // 配置文件

// 文件绝对路径
char* Global::USER_HOME = NULL;          // 用户家目录
char* Global::STUDENT_PATH = NULL;       // 学生信息
char* Global::TEACHER_PATH = NULL;       // 老师信息
char* Global::RESERV_PATH = NULL;        // 预约信息
char* Global::MACHINE_ROOM_PATH = NULL;  // 机房信息
char* Global::CONFIG_PATH = NULL;        // 配置文件
char* Global::LOG_PATH = NULL;           // 日志文件

FILE* Global::LOG_FILE_FP = NULL;  // 日志文件指针

// 配置文件变量名
const char* Global::ADMIN_PSWD = "PASSWORD";  // 管理员密码
const char* Global::INIT_FLAG = "INIT";       // 管理员密码是否初始化
const char* Global::N_INIT = "N";  // 管理员密码未初始化状态
const char* Global::INITED = "Y";  // 管理员密码已经初始化状态

Global::Global() {}
Global::~Global() {}

void Global::sys_init() {
    // 获取用户家目录
    char path[PATH_LEN];
    char* home = getenv("HOME");
    if (!home) exit(EXIT_FAILURE);
    memset(path, 0, sizeof(path));
    // 获取到当前用户家目录路径到path中
    strcpy(path, home);
    OUT("%s\n", path);
    size_t len = strlen(path);
    // 初始化日志文件路径
    LOG_PATH = (char*)malloc(len + strlen(LOG_FILE) + 1);
    if (!LOG_PATH) exit(EXIT_FAILURE);
    strcpy(path + len, LOG_FILE);
    strcpy(LOG_PATH, path);
    // 初始化日志文件指针，初次打开日志文件需要清空之前的（之前的没用）
    LOG_FILE_FP = fopen(LOG_PATH, "w");
    if (!LOG_FILE_FP) exit(EXIT_FAILURE);
    // 从这里开始使用 INFO、WARN、ERR的话都可以记录到日志文件中了
    // 初始化家目录
    USER_HOME = (char*)malloc(len + 1);
    MEM_ALLOC_FAILED(USER_HOME)
    strcpy(USER_HOME, home);
    // 输出日志
    INFO("Initialized log file pointer successfully.");
    INFO("LOG_PATH: %s", LOG_PATH);
    INFO("USER_HOME: %s", USER_HOME);
    // 判断项目的目录是否存在
    INFO("Determines whether the project directory exists...");
    strcpy(path + len, MRRS_HOME);
    INFO("Project directory path: %s", path);
    // 重新给路径长度赋值
    len = strlen(path);  // path = "~/.mrrs"
    if (!access(path, F_OK)) {
        INFO("Project directory path already exists.");
    } else {
        INFO("Project directory path does not find, try to create...");
        // 如果不存在，则新建
        if (mkdir(path, 0755)) {
            // 创建失败
            ERR("Project directory path create failed.");
            exit(EXIT_FAILURE);
        }
        // 创建成功
        INFO("Project directory created successfully.");
    }
    // 到这里就已经将~/.mrrs目录创建好了
    // 下面进一步判断~/.mrrs目录下的数据文件是否存在，不存在则创建
    // 初始化数据文件的路径
    // 初始化配置文件
    INIT_PATH(CONFIG_PATH, CONFIG_FILE);
    INFO("CONFIG_PATH: %s", CONFIG_PATH);
    // 初始化学生信息文件
    INIT_PATH(STUDENT_PATH, STUDENT_FILE);
    INFO("STUDENT_PATH: %s", STUDENT_PATH);
    // 初始化老师信息文件
    INIT_PATH(TEACHER_PATH, TEACHER_FILE);
    INFO("TEACHER_PATH: %s", TEACHER_PATH);
    // 初始化预约信息文件
    INIT_PATH(RESERV_PATH, RESERV_FILE);
    INFO("RESERV_PATH: %s", RESERV_PATH);
    // 初始化机房信息文件
    INIT_PATH(MACHINE_ROOM_PATH, MACHINE_ROOM_FILE);
    INFO("MACHINE_ROOM_PATH: %s", MACHINE_ROOM_PATH);

    const char* paths[] = {CONFIG_PATH, STUDENT_PATH, TEACHER_PATH, RESERV_PATH,
                           MACHINE_ROOM_PATH};
    int sz = sizeof(paths) / sizeof(const char*);
    FILE* fp = NULL;
    for (int i = 0; i < sz; i++) {
        INFO("Check data file: %s", paths[i]);
        fp = fopen(paths[i], "r");
        if (!fp) {
            // 如果文件不存在，则创建
            fp = fopen(paths[i], "w");
            if (!fp) {
                ERR("Data file %s create failed.", paths[i]);
                exit(EXIT_FAILURE);
            }
            INFO("Data file %s create successfully.", paths[i]);
        } else {
            INFO("Data file %s does already exists.", paths[i]);
        }
        fclose(fp);
    }
}

void Global::sys_restore() {
    FREE(LOG_PATH)
    FREE(USER_HOME)
    FREE(CONFIG_PATH)
    FREE(STUDENT_PATH)
    FREE(TEACHER_PATH)
    FREE(RESERV_PATH)
    FREE(MACHINE_ROOM_PATH)
    fclose(LOG_FILE_FP);
}

void Global::sha256(const char* text, char* pswd) {
    std::string str(text), res;
    picosha2::hash256_hex_string(str, res);
    strcpy(pswd, res.c_str());
}

size_t Global::get_uint_len(uint32_t u) {
    size_t res = 0;
    while (u) {
        res++;
        u /= 10;
    }
    return res;
}

char* Global::rand_string(size_t len) {
    char* res = (char*)malloc(len + 1);
    MEM_ALLOC_FAILED(res)
    memset(res, 0, len + 1);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < len; i++) {
        *(res + i) = rand() % 94 + 33;
    }
    return res;
}

}  // namespace gv
