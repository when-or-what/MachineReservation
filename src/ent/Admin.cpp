#include "ent/Admin.h"

namespace ent {
/**
 * @brief Admin
 *
 */
Admin::Admin() { this->pswd = NULL; }
Admin::Admin(uint32_t no, const char* pswd) : no(no) {
    this->pswd = NULL;
    this->set_pswd(pswd);
}
Admin::~Admin(){FREE(this->pswd)}

uint32_t Admin::get_no() {
    return this->no;
}
void Admin::set_no(uint32_t no) { this->no = no; }

char* Admin::get_pswd() { return this->pswd; }
void Admin::set_pswd(const char* pswd) {
    FREE(this->pswd);
    size_t pl = strlen(pswd) + 1;
    this->pswd = (char*)malloc(pl);
    MEM_ALLOC_FAILED(this->pswd)
    memset(this->pswd, 0, pl);
    strcpy(this->pswd, pswd);
}

/* to string */
void Admin::show() { INFO("Admin(no=%u, pswd='%s')", no, pswd); }

}  // namespace ent