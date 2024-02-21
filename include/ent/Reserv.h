#ifndef _ENT_RESERV_H_
#define _ENT_RESERV_H_

#include "../Global.h"

namespace ent {
/**
 * @brief 机房预约实体类
 */
class Reserv {
   private:
    uint32_t id;           // 自增主键
    uint64_t date;         // 预约的日期 时间段
    uint32_t s_id;         // 学号
    uint32_t m_id;         // 机房号
    uint32_t reserv_stat;  // 预约状态
   public:
    // 预约状态
    static const uint32_t PENDING;  // 审核中
    static const uint32_t SUCC;     // 预约成功
    static const uint32_t FAIL;     // 预约失败
    static const uint32_t CANCEL;   // 已取消
    static const char* MAPPING[];   // 预约状态与英文的映射

    /**
     * @brief 从64位无符号整数中得出预约日期及时间段
     * @note
     * 返回值是指向日期字符串和时间段字符串的指针，内存的释放由调用者负责
     *
     * @param d 格式为yyyyMMddhhmmhhmm的包含日期和24小时制时间段的64位无符号整数
     *
     * @return `std::pair<char*, char*>` <日期，时间段>
     * 字符串，前者格式为`yyyy-MM-dd`，后者格式为`hh:mm~hh:mm`
     */
    static std::pair<char*, char*> get_time_str(uint64_t d);

    Reserv();
    Reserv(uint32_t id, uint64_t date, uint32_t s_id, uint32_t m_id,
           uint32_t reserv_stat);
    ~Reserv();
    /* getter setter */
    uint32_t get_id();
    void set_id(uint32_t id);

    uint64_t get_date();
    void set_date(uint64_t date);

    uint32_t get_sid();
    void set_sid(uint32_t sid);

    uint32_t get_mid();
    void set_mid(uint32_t mid);

    uint32_t get_reserv_stat();
    void set_reserv_stat(uint32_t reserv_stat);
    /* to string */
    void show();
};

}  // namespace ent

#endif /* _ENT_RESERV_H_ */