#include "ent/Reserv.h"

namespace ent {
/**
 * @brief Reserv
 */
// 预约状态
const uint32_t Reserv::PENDING = 0;  // 审核中
const uint32_t Reserv::SUCC = 1;     // 预约成功
const uint32_t Reserv::FAIL = 2;     // 预约失败
const uint32_t Reserv::CANCEL = 3;   // 已取消
const char* Reserv::MAPPING[] = {"pending", "success", "fail",
                                 "cancel"};  // 预约状态与英文的映射

std::pair<char*, char*> Reserv::get_time_str(uint64_t d) {
    char* dd = (char*)malloc(11);
    MEM_ALLOC_FAILED(dd)
    memset(dd, 0, 11);
    char* ii = (char*)malloc(12);
    MEM_ALLOC_FAILED(ii)
    memset(ii, 0, 12);
    uint32_t h = d / 1'0000'0000, l = d % 1'0000'0000;
    sprintf(dd, "%04u-%02u-%02u", h / 1'0000, (h / 100) % 100, h % 100);
    sprintf(ii, "%02u:%02u~%02u:%02u", l / 1'0000'00, (l / 10000) % 100,
            (l / 100) % 100, l % 100);
    return {dd, ii};
}

Reserv::Reserv() {}
Reserv::Reserv(uint32_t id, uint64_t d, uint32_t s, uint32_t m, uint32_t r)
    : id(id), date(d), s_id(s), m_id(m), reserv_stat(r) {}
Reserv::~Reserv() {}

/* getter setter */
uint32_t Reserv::get_id() { return this->id; }
void Reserv::set_id(uint32_t id) { this->id = id; }

uint64_t Reserv::get_date() { return this->date; }
void Reserv::set_date(uint64_t date) { this->date = date; }

uint32_t Reserv::get_sid() { return this->s_id; }
void Reserv::set_sid(uint32_t sid) { this->s_id = sid; }

uint32_t Reserv::get_mid() { return this->m_id; }
void Reserv::set_mid(uint32_t mid) { this->m_id = mid; }

uint32_t Reserv::get_reserv_stat() { return this->reserv_stat; }
void Reserv::set_reserv_stat(uint32_t reserv_stat) {
    this->reserv_stat = reserv_stat;
}
/* to string */
void Reserv::show() {
    INFO(
        "Reserv(id=%u, date=%lu, s_id=%u, m_id=%u, "
        "reserv_stat=%u)",
        id, date, s_id, m_id, reserv_stat);
}

}  // namespace ent
