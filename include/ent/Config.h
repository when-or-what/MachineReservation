#ifndef _ENT_CONFIG_H_
#define _ENT_CONFIG_H_

#include "../Global.h"

namespace ent {
class Config {
   private:
    char* key;
    char* value;

   public:
    Config();
    Config(const char* key, const char* value);
    ~Config();

    char* get_key();
    void set_key(const char* key);

    char* get_value();
    void set_value(const char* value);

    void show();
};
}  // namespace ent

#endif /* _ENT_CONFIG_H_ */