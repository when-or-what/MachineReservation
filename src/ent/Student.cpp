#include "ent/Student.h"

namespace ent {
/**
 * @brief Student
 *
 */
Student::Student() { this->s_name = this->pswd = NULL; }
Student::Student(uint32_t id, uint32_t s_id, const char* s_name,
                 const char* pswd)
    : s_id(s_id), id(id) {
    this->s_name = this->pswd = NULL;
    this->set_sname(s_name);
    this->set_pswd(pswd);
}

Student::~Student(){FREE(this->s_name) FREE(this->pswd)}

/* getter setter */
uint32_t Student::get_id() {
    return this->id;
}
void Student::set_id(uint32_t id) { this->id = id; }

char* Student::get_sname() { return this->s_name; }
void Student::set_sname(const char* sname) {
    FREE(this->s_name)
    size_t sl = strlen(sname) + 1;
    this->s_name = (char*)malloc(sl);
    MEM_ALLOC_FAILED(this->s_name)
    memset(this->s_name, 0, sl);
    strcpy(this->s_name, sname);
}

uint32_t Student::get_sid() { return this->s_id; }
void Student::set_sid(uint32_t sid) { this->s_id = sid; }

char* Student::get_pswd() { return this->pswd; }
void Student::set_pswd(const char* pswd) {
    FREE(this->pswd)
    size_t pl = strlen(pswd) + 1;
    this->pswd = (char*)malloc(pl);
    MEM_ALLOC_FAILED(this->pswd)
    memset(this->pswd, 0, pl);
    strcpy(this->pswd, pswd);
}

/* to string */
void Student::show() {
    INFO("Student(id=%u, s_name='%s', s_id=%u, pswd='%s')", id, s_name, s_id,
         pswd);
}

}  // namespace ent
