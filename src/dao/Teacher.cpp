#include "dao/Teacher.h"

namespace dao {

Teacher::Teacher() {}

Teacher::~Teacher() {}

void Teacher::insert(ent::Teacher *data) {
    if (!data) {
        ERR("Data is invalid");
        exit(EXIT_FAILURE);
    }
    // 打开文件以追加的方式写入内容
    // 文件不存在，则先创建文件再写入
    FILE *fp = fopen(gv::Global::TEACHER_PATH, "a+");
    if (!fp) {
        ERR("Open teacher data file failed");
        exit(EXIT_FAILURE);
    }
    // 将数据以空格分隔的文件格式写入文本数据文件
    fprintf(fp, "%u %s %s %u\n", data->get_tid(), data->get_tname(),
            data->get_pswd(), data->get_mid());
    // 关闭文件流
    fclose(fp);
}

ent::Teacher *Teacher::select(uint32_t id) {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::TEACHER_PATH, "r");
    if (!fp) {
        ERR("Open teacher data file failed");
        exit(EXIT_FAILURE);
    }
    // 只声明变量但不开辟空间
    ent::Teacher *res = nullptr;
    // 临时变量
    uint32_t tid = 0, mid = 0;
    char *tname = (char *)malloc(gv::Global::NAME_LEN);
    MEM_ALLOC_FAILED(tname)
    char *pswd = (char *)malloc(gv::Global::PSWD_LEN);
    MEM_ALLOC_FAILED(pswd)
    memset(tname, 0, gv::Global::NAME_LEN);
    memset(pswd, 0, gv::Global::PSWD_LEN);
    // 读取文件内容，寻找tid为id的那一行记录
    while (fscanf(fp, "%u %s %s %u\n", &tid, tname, pswd, &mid) != EOF) {
        if (tid == id) {
            // 寻找到了期望id的记录，才开辟空间存储结果
            res = new ent::Teacher(0, tid, mid, tname, pswd);
            MEM_ALLOC_FAILED(res)
            // 退出循环
            break;
        }
        memset(tname, 0, gv::Global::NAME_LEN);
        memset(pswd, 0, gv::Global::PSWD_LEN);
    }
    // 关闭文件流
    fclose(fp);
    // 将分配的辅助内存释放掉
    FREE(tname)
    FREE(pswd)
    return res;
}

std::vector<ent::Teacher *> Teacher::select() {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::TEACHER_PATH, "a+");
    if (!fp) {
        ERR("Open teacher data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储记录的数组变量
    // 由于不知道长度，所以使用动态数组
    std::vector<ent::Teacher *> resv;
    // 定义存储文件内容的临时变量
    uint32_t tid = 0, mid = 0;
    char *tname = (char *)malloc(gv::Global::NAME_LEN);
    MEM_ALLOC_FAILED(tname)
    char *pswd = (char *)malloc(gv::Global::PSWD_LEN);
    MEM_ALLOC_FAILED(pswd)
    memset(tname, 0, gv::Global::NAME_LEN);
    memset(pswd, 0, gv::Global::PSWD_LEN);
    // 读取文件内容，把每一行记录都装入结果数组
    while (fscanf(fp, "%u %s %s %u\n", &tid, tname, pswd, &mid) != EOF) {
        // 定义结果变量
        auto res = new ent::Teacher(0, tid, mid, tname, pswd);
        MEM_ALLOC_FAILED(res)
        // 装入内容
        resv.emplace_back(res);
        memset(tname, 0, gv::Global::NAME_LEN);
        memset(pswd, 0, gv::Global::PSWD_LEN);
    }
    // 关闭文件流
    fclose(fp);
    // 将分配的辅助内存释放掉
    FREE(tname)
    FREE(pswd)
    return resv;
}

void Teacher::update(ent::Teacher *data) {
    // 判断给定的参数是否合法
    if (!data) {
        ERR("Args pointer newdata is empty");
        exit(EXIT_FAILURE);
    }
    // 取出更新数据里的tid，这个值是不会被改变的
    // 以此来找到要更新的那条记录
    uint32_t id = data->get_tid();
    // 删除掉这条数据，然后再重新添加即可
    this->delet(id);
    // 重新添加
    this->insert(data);
}

void Teacher::delet(uint32_t id) {
    // 要替换文件内容的话，就要使用 r+ 模式打开文件
    FILE *fp = fopen(gv::Global::TEACHER_PATH, "r+");
    if (!fp) {
        ERR("Open teacher data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储文件内容的临时变量
    char *buf = (char *)malloc(gv::Global::LINE_LEN);
    // 临时变量：数据相关
    uint32_t tid = 0, mid = 0;
    char *tname = (char *)malloc(gv::Global::NAME_LEN);
    MEM_ALLOC_FAILED(tname)
    char *pswd = (char *)malloc(gv::Global::PSWD_LEN);
    MEM_ALLOC_FAILED(pswd)
    // 临时变量：辅助操作文件
    long pos1 = 0, pos2 = 0;
    size_t len = 0;
    // 读取文件内容，寻找tid为id的那一行记录
    while (!feof(fp)) {
        memset(buf, 0, gv::Global::LINE_LEN);
        memset(tname, 0, gv::Global::NAME_LEN);
        memset(pswd, 0, gv::Global::PSWD_LEN);
        // 读取文件的每一行
        fgets(buf, gv::Global::LINE_LEN, fp);
        // 解析每一行的结果
        sscanf(buf, "%u %s %s %u\n", &tid, tname, pswd, &mid);
        if (tid == id) {
            // 找到了要删除的行
            // 记录要删除的行的下一行行首的指针位置
            pos1 = ftell(fp);
            // 记录要删除的行的行首指针位置
            pos2 = pos1 - strlen(buf);
            while (true) {
                // 将文件流指针放到下一行
                fseek(fp, pos1, SEEK_SET);
                // 复制整行
                memset(buf, 0, gv::Global::LINE_LEN);
                if (!fgets(buf, gv::Global::LINE_LEN, fp)) {
                    break;
                }
                len = strlen(buf);
                // 指针位置更新到下一行
                pos1 += len;
                // 将文件指针指向上一行首
                fseek(fp, pos2, SEEK_SET);
                // 将缓冲区中的数据输出到文件中
                fputs(buf, fp);
                // 指针位置更新到下一行的位置
                pos2 += len;
            }
            // 截断文件，去除垃圾数据
            // pos2一直代表被删除的行的起始位置，所以到最后的时候
            // pos2就代表文件末尾
            // ftruncate函数需要包含unistd.h头文件，与Unix操作系统耦合
            ftruncate(fileno(fp), pos2);
            break;
        }
    }
    // 关闭文件流
    fclose(fp);
    // 释放空间
    FREE(buf)
    FREE(tname)
    FREE(pswd)
}

void Teacher::delet() {
    // 以写入的方式打开文件即可
    FILE *fp = fopen(gv::Global::TEACHER_PATH, "w");
    if (!fp) {
        ERR("Open teacher data file failed");
        exit(EXIT_FAILURE);
    }
    // 关闭文件流
    fclose(fp);
}

}  // namespace dao
