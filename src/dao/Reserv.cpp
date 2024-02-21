#include "dao/Reserv.h"

namespace dao {

Reserv::Reserv() {}

Reserv::~Reserv() {}

void Reserv::insert(ent::Reserv *data) {
    if (!data) {
        ERR("Data is invalid");
        exit(EXIT_FAILURE);
    }
    // 打开文件以追加的方式写入内容
    // 文件不存在，则先创建文件再写入
    FILE *fp = fopen(gv::Global::RESERV_PATH, "a+");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 确定该条数据的id，即当前文件记录中最大id+1
    uint32_t id = 0, i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;
    while (fscanf(fp, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t) != EOF) {
        if (i > id) id = i;
    }
    id++;
    // 将数据以空格分隔的文件格式写入文本数据文件
    fprintf(fp, "%u %lu %u %u %u\n", id, data->get_date(), data->get_sid(),
            data->get_mid(), data->get_reserv_stat());
    // 关闭文件流
    fclose(fp);
}

ent::Reserv *Reserv::select_one(uint32_t id) {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    ent::Reserv *res = nullptr;
    // 定义存储文件内容的临时变量
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    while (fscanf(fp, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t) != EOF) {
        if (i == id) {
            // 定义结果变量
            res = new ent::Reserv(i, dd, sid, mid, t);
            MEM_ALLOC_FAILED(res)
            break;
        }
    }
    // 关闭文件流
    fclose(fp);
    return res;
}

std::vector<ent::Reserv *> Reserv::select_by_sid(uint32_t id) {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储记录的数组变量
    // 由于不知道长度，所以使用动态数组
    std::vector<ent::Reserv *> resv;
    // 定义存储文件内容的临时变量
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    // 读取文件内容，把sid符合筛选条件的每一行记录都装入结果数组
    while (fscanf(fp, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t) != EOF) {
        if (sid == id) {
            // 定义结果变量
            auto res = new ent::Reserv(i, dd, sid, mid, t);
            MEM_ALLOC_FAILED(res)
            // 装入内容
            resv.emplace_back(res);
        }
    }
    // 关闭文件流
    fclose(fp);
    return resv;
}

std::vector<ent::Reserv *> Reserv::select_by_mid(uint32_t id) {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储记录的数组变量
    // 由于不知道长度，所以使用动态数组
    std::vector<ent::Reserv *> resv;
    // 定义存储文件内容的临时变量
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    // 读取文件内容，把sid符合筛选条件的每一行记录都装入结果数组
    while (fscanf(fp, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t) != EOF) {
        if (mid == id) {
            // 定义结果变量
            auto res = new ent::Reserv(i, dd, sid, mid, t);
            MEM_ALLOC_FAILED(res)
            // 装入内容
            resv.emplace_back(res);
        }
    }
    // 关闭文件流
    fclose(fp);
    return resv;
}

std::vector<ent::Reserv *> Reserv::select() {
    // 首先获取文件流
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储记录的数组变量
    // 由于不知道长度，所以使用动态数组
    std::vector<ent::Reserv *> resv;
    // 定义存储文件内容的临时变量
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    // 读取文件内容，把每一行记录都装入结果数组
    while (fscanf(fp, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t) != EOF) {
        // 定义结果变量
        auto res = new ent::Reserv(i, dd, sid, mid, t);
        MEM_ALLOC_FAILED(res)
        // 装入内容
        resv.emplace_back(res);
    }
    // 关闭文件流
    fclose(fp);
    return resv;
}

void Reserv::update(ent::Reserv *data) {
    // 判断给定的参数是否合法
    if (!data) {
        ERR("Args pointer newdata is empty");
        exit(EXIT_FAILURE);
    }
    // 要替换文件内容的话，就要使用 r+ 模式打开文件
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r+");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 取出更新数据里的id，这个值是不会被改变的
    // 以此来找到要更新的那条记录
    uint32_t id = data->get_id();
    // 定义存储文件内容的临时变量
    char *buf = (char *)malloc(gv::Global::LINE_LEN);
    MEM_ALLOC_FAILED(buf)
    char *tmp = (char *)malloc(gv::Global::LINE_LEN);
    MEM_ALLOC_FAILED(tmp)
    // 临时变量
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    // 读取文件内容，寻找id为id的那一行记录
    while (!feof(fp)) {
        memset(buf, 0, gv::Global::LINE_LEN);
        fgets(buf, gv::Global::LINE_LEN, fp);
        sscanf(buf, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t);
        if (i == id) {
            // 临时变量
            long pos1 = 0, pos2 = 0, pos = 0;
            size_t len = 0, new_len = 0, diff = 0, i = 0;
            char c = 0;
            // 找到要修改的行
            len = strlen(buf);
            // 记录要修改的行的下一行的行首位置
            pos1 = ftell(fp);
            // 记录要修改的行的行首位置
            pos2 = pos1 - len;
            // 将新数据转化为字符串文本
            memset(tmp, 0, gv::Global::LINE_LEN);
            sprintf(tmp, "%u %lu %u %u %u\n", data->get_id(), data->get_date(),
                    data->get_sid(), data->get_mid(), data->get_reserv_stat());
            // 记录新字符串的长度
            new_len = strlen(tmp);
            // 比较新旧字符串长度的大小
            if (new_len == len) {
                // 两个字符串长度相等，直接输出即可
                fseek(fp, pos2, SEEK_SET);
                fputs(tmp, fp);
            } else if (new_len > len) {
                // 新字符串比较长，则先在整个文件最后输出多出的字符
                diff = new_len - len, i = 0;
                fseek(fp, 0, SEEK_END);
                // 记录下原文件的最后一个字符的位置（不是文件末尾）
                pos = ftell(fp) - 1;
                for (i = 0; i < diff; i++) {
                    fputc(i + 'A', fp);
                }
                // 再将后面的字符全部向后移动
                // 定位到原本文件的最后一个字符（换行符）
                while (pos >= pos1) {
                    fseek(fp, pos, SEEK_SET);
                    c = fgetc(fp);
                    fseek(fp, diff - 1, SEEK_CUR);
                    fputc(c, fp);
                    pos--;
                }
                // 再直接在该输入的位置输入字符串即可
                fseek(fp, pos2, SEEK_SET);
                fputs(tmp, fp);
            } else {
                // 新字符比较短，则先将新字符串填充
                fseek(fp, pos2, SEEK_SET);
                fputs(tmp, fp);
                // 记录下需要被覆盖的第一个字符位置
                pos = ftell(fp);
                // 再将后面的字符向前移动，并截断
                diff = len - new_len;
                fseek(fp, pos1, SEEK_SET);
                while ((c = fgetc(fp)) != EOF) {
                    fseek(fp, pos, SEEK_SET);
                    fputc(c, fp);
                    pos++;
                    pos1++;
                    fseek(fp, pos1, SEEK_SET);
                }
                // 截断文件
                ftruncate(fileno(fp), pos);
            }
            break;
        }
    }
    // 关闭文件流并释放空间
    fclose(fp);
    FREE(buf)
    FREE(tmp)
}

void Reserv::delet(uint32_t id) {
    // 要替换文件内容的话，就要使用 r+ 模式打开文件
    FILE *fp = fopen(gv::Global::RESERV_PATH, "r+");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 定义存储文件内容的临时变量
    char *buf = (char *)malloc(gv::Global::LINE_LEN);
    MEM_ALLOC_FAILED(buf)
    // 临时变量：数据相关
    uint32_t i = 0, sid = 0, mid = 0, t = 0;
    uint64_t dd = 0;

    // 临时变量：辅助操作文件
    long pos1 = 0, pos2 = 0;
    size_t len = 0;
    // 读取文件内容，寻找id为id的那一行记录
    while (!feof(fp)) {
        memset(buf, 0, gv::Global::LINE_LEN);
        // 读取文件的每一行
        fgets(buf, gv::Global::LINE_LEN, fp);
        // 解析每一行的结果
        sscanf(buf, "%u %lu %u %u %u\n", &i, &dd, &sid, &mid, &t);
        if (i == id) {
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
}

void Reserv::delet() {
    // 以写入的方式打开文件即可
    FILE *fp = fopen(gv::Global::RESERV_PATH, "w");
    if (!fp) {
        ERR("Open reserv data file failed");
        exit(EXIT_FAILURE);
    }
    // 关闭文件流
    fclose(fp);
}

}  // namespace dao
