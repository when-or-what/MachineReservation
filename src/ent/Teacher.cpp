#include "ent/Teacher.h"

namespace ent {
/**
 * @brief Teacher
 *
 */
Teacher::Teacher() { this->t_name = this->pswd = NULL; }
Teacher::Teacher(uint32_t id, uint32_t t_id, uint32_t m_id, const char* t_name,
                 const char* pswd)
    : t_id(t_id), id(id), m_id(m_id) {
    this->t_name = this->pswd = NULL;
    this->set_tname(t_name);
    this->set_pswd(pswd);
}

Teacher::~Teacher(){FREE(this->t_name) FREE(this->pswd)}

/* getter setter */
uint32_t Teacher::get_id() {
    return this->id;
}
void Teacher::set_id(uint32_t id) { this->id = id; }

char* Teacher::get_tname() { return this->t_name; }
void Teacher::set_tname(const char* tname) {
    FREE(this->t_name)
    size_t sl = strlen(tname) + 1;
    this->t_name = (char*)malloc(sl);
    MEM_ALLOC_FAILED(this->t_name)
    memset(this->t_name, 0, sl);
    strcpy(this->t_name, tname);
}

uint32_t Teacher::get_tid() { return this->t_id; }
void Teacher::set_tid(uint32_t tid) { this->t_id = tid; }

char* Teacher::get_pswd() { return this->pswd; }
void Teacher::set_pswd(const char* pswd) {
    FREE(this->pswd)
    size_t pl = strlen(pswd) + 1;
    this->pswd = (char*)malloc(pl);
    MEM_ALLOC_FAILED(this->pswd)
    memset(this->pswd, 0, pl);
    strcpy(this->pswd, pswd);
}

uint32_t Teacher::get_mid() { return this->m_id; }
void Teacher::set_mid(uint32_t mid) { this->m_id = mid; }

/* to string */
void Teacher::show() {
    INFO("Teacher(id=%u, t_name='%s', t_id=%u, pswd='%s', m_id=%u)", id, t_name,
         t_id, pswd, m_id);
}

}  // namespace ent
