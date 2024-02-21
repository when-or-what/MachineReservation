#include "ent/Config.h"

namespace ent {
Config::Config() { this->key = this->value = NULL; }
Config::Config(const char* key, const char* value) {
    this->key = this->value = NULL;
    this->set_key(key);
    this->set_value(value);
}
Config::~Config() {
    FREE(this->key)
    FREE(this->value)
}

char* Config::get_key() { return this->key; }
void Config::set_key(const char* key) {
    FREE(this->key);
    size_t klen = strlen(key) + 1;
    this->key = (char*)malloc(klen);
    MEM_ALLOC_FAILED(this->key)
    memset(this->key, 0, klen);
    strcpy(this->key, key);
}

char* Config::get_value() { return this->value; }
void Config::set_value(const char* value) {
    FREE(this->value);
    size_t vlen = strlen(value) + 1;
    this->value = (char*)malloc(vlen);
    MEM_ALLOC_FAILED(this->value)
    memset(this->value, 0, vlen);
    strcpy(this->value, value);
}

void Config::show() { INFO("Config(key='%s', value='%s')", key, value); }

}  // namespace ent
