#include "ent/MachineRoom.h"

namespace ent {
/**
 * @brief MachineRoom
 */
MachineRoom::MachineRoom() { this->m_name = NULL; }
MachineRoom::MachineRoom(uint32_t id, uint32_t m_id, const char* m_name,
                         uint32_t sz)
    : id(id), m_id(m_id), maxsize(sz) {
    this->m_name = NULL;
    this->set_mname(m_name);
}

MachineRoom::~MachineRoom(){FREE(this->m_name)}

/* getter setter */
uint32_t MachineRoom::get_id() {
    return this->id;
}
void MachineRoom::set_id(uint32_t id) { this->id = id; }

uint32_t MachineRoom::get_mid() { return this->m_id; }
void MachineRoom::set_mid(uint32_t mid) { this->m_id = mid; }

char* MachineRoom::get_mname() { return this->m_name; }
void MachineRoom::set_mname(const char* mname) {
    FREE(this->m_name)
    size_t sl = strlen(mname) + 1;
    this->m_name = (char*)malloc(sl);
    MEM_ALLOC_FAILED(this->m_name)
    memset(this->m_name, 0, sl);
    strcpy(this->m_name, mname);
}

uint32_t MachineRoom::get_maxsize() { return this->maxsize; }
void MachineRoom::set_maxsize(uint32_t maxsize) { this->maxsize = maxsize; }

/* to string */
void MachineRoom::show() {
    INFO("MachineRoom(id=%u, m_id=%u, m_name='%s', maxsize=%u)", id, m_id,
         m_name, maxsize);
}

}  // namespace ent
