#include "srv/Admin.h"

namespace srv {

const std::unordered_map<char, const char*> Admin::MENU = {
    {'1', "Add account"},
    {'2', "View account"},
    {'3', "Modify account"},
    {'4', "Remove account"},
    {'5', "Add machine room"},
    {'6', "View machine room"},
    {'7', "Modify machine room"},
    {'8', "Remove machine room"},
    {'9', "Clear reservation"},
    {'a', "Change password"},
    {'q', "Quit"},
    {'c', "Clear"},
    {'h', "Help"}};

Admin::Admin() {}

Admin::Admin(ent::Admin* admin, dao::Config* conf, dao::MachineRoom* mr,
             dao::Reserv* reserv, dao::Student* stu, dao::Teacher* tea)
    : admin(admin), conf(conf), mr(mr), reserv(reserv), stu(stu), tea(tea) {}

Admin::~Admin() { DELETE(this->admin) }

// 学生账号的增删查改
void Admin::add_stu(uint32_t sid, const char* sname, const char* pswd) {
    // 给密码加密
    char* tmp = (char*)malloc(gv::Global::PSWD_LEN);
    MEM_ALLOC_FAILED(tmp)
    memset(tmp, 0, gv::Global::PSWD_LEN);
    gv::Global::sha256(pswd, tmp);
    // 创建学生实体对象
    ent::Student* s = new ent::Student(0, sid, sname, tmp);
    MEM_ALLOC_FAILED(s)
    // 添加数据到学生表
    stu->update(s);
    DELETE(s)
    FREE(tmp)
}

void Admin::view_stu() {
    std::vector<ent::Student*> stus = stu->select();
    // 输出表头
    printf("+------------+------------------+\n");
    printf("|   %-6s   |   %-15s|\n", "id", "name");
    printf("+------------+------------------+\n");
    for (auto&& s : stus) {
        // SID_LEN
        printf("|   %-6u   |   %-15s|\n", s->get_sid(), s->get_sname());
        DELETE(s)
    }
    printf("+------------+------------------+\n");
    printf("Total: %ld\n", stus.size());
}

void Admin::mod_stu(uint32_t sid, const char* sname, const char* pswd) {
    this->add_stu(sid, sname, pswd);
}

void Admin::rmv_stu(uint32_t sid) { this->stu->delet(sid); }

// 老师账号的增删查改
void Admin::add_tea(uint32_t tid, const char* tname, const char* pswd,
                    uint32_t mid) {
    // 给密码加密
    char* tmp = (char*)malloc(gv::Global::PSWD_LEN);
    MEM_ALLOC_FAILED(tmp)
    memset(tmp, 0, gv::Global::PSWD_LEN);
    gv::Global::sha256(pswd, tmp);
    // 创建老师实体对象
    ent::Teacher* t = new ent::Teacher(0, tid, mid, tname, tmp);
    MEM_ALLOC_FAILED(t)
    // 添加数据到老师表
    tea->update(t);
    DELETE(t)
    FREE(tmp)
}

void Admin::view_tea() {
    std::vector<ent::Teacher*> teas = tea->select();
    // 输出表头
    printf("+---------+-----------------+--------+\n");
    printf("|  %-5s  |  %-15s|  %-4s  |\n", "id", "name", "m_id");
    printf("+---------+-----------------+--------+\n");
    for (auto&& t : teas) {
        printf("|  %-5u  |  %-15s|  %-4u  |\n", t->get_tid(), t->get_tname(),
               t->get_mid());
        DELETE(t)
    }
    printf("+---------+-----------------+--------+\n");
    printf("Total: %ld\n", teas.size());
}

void Admin::mod_tea(uint32_t tid, const char* tname, const char* pswd,
                    uint32_t mid) {
    this->add_tea(tid, tname, pswd, mid);
}

void Admin::rmv_tea(uint32_t tid) { this->tea->delet(tid); }

// 机房的增删查改
void Admin::add_mach(uint32_t mid, const char* mname, uint32_t maxsize) {
    ent::MachineRoom* m = new ent::MachineRoom(0, mid, mname, maxsize);
    MEM_ALLOC_FAILED(m)
    this->mr->update(m);
    DELETE(m);
}

void Admin::view_mach() {
    std::vector<ent::MachineRoom*> mrs = this->mr->select();
    // 输出表头
    printf("+-------+-----------------+--------+\n");
    printf("|  %-3s  |  %-15s|  %-4s  |\n", "id", "name", "size");
    printf("+-------+-----------------+--------+\n");
    for (auto&& m : mrs) {
        printf("|  %-3u  |  %-15s|  %-4u  |\n", m->get_mid(), m->get_mname(),
               m->get_maxsize());
        DELETE(m)
    }
    printf("+-------+-----------------+--------+\n");
    printf("Total: %ld\n", mrs.size());
}

void Admin::mod_mach(uint32_t mid, const char* mname, uint32_t maxsize) {
    this->add_mach(mid, mname, maxsize);
}

void Admin::rmv_mach(uint32_t mid) { this->mr->delet(mid); }

// 清空预约
void Admin::clear_reserv() { this->reserv->delet(); }

// 修改管理员密码
void Admin::modi_pswd(const char* pswd) {
    auto c = new ent::Config(gv::Global::ADMIN_PSWD, this->admin->get_pswd());
    MEM_ALLOC_FAILED(c)
    // 加密
    char tmp[gv::Global::PSWD_LEN];
    memset(tmp, 0, gv::Global::PSWD_LEN);
    gv::Global::sha256(pswd, tmp);
    // 更新
    c->set_value(tmp);
    this->conf->update(c);
    // 更新实体信息
    this->admin->set_pswd(tmp);
    DELETE(c)
}

bool Admin::check_info(const char* pswd) {
    // 加密
    char tmp[gv::Global::PSWD_LEN];
    memset(tmp, 0, gv::Global::PSWD_LEN);
    gv::Global::sha256(pswd, tmp);
    // 比较
    bool res = !strcmp(tmp, this->admin->get_pswd());
    return res;
}

void Admin::show_ui() {
    printf("Commands: \n");
    for (auto&& p : MENU) {
        printf("         %c. %s\n", p.first, p.second);
    }
}

// 上层接口
void Admin::ui() {
    uint32_t id = 0, mid = 0;
    char cmd[gv::Global::CMD_LEN];
    char name[gv::Global::NAME_LEN];
    char pswd[gv::Global::PSWD_LEN];
    printf("\n");
    do {
        SHOW_CMD_TIP("admin> ");
        cmd[0] = 0;
        scanf("%[^\n]", cmd);
        getchar();
        if (!cmd[0]) continue;
        switch (cmd[0]) {
            case 'q':
                OUT("Bye, admin.\n");
                return;
            case '1': {
                OUT("%s\n", MENU.at('1'));
                OUT("Teacher(0)/student(1)/cancel(other)? ");
                scanf("%s", cmd + 1);
                if (cmd[1] == '0') {
                    OUT("Employee number(5 digits): ");
                    scanf("%u", &id);
                    auto t = this->tea->select(id);
                    if (t) {
                        DELETE(t)
                        OUT("Teacher already exists.\n");
                    } else {
                        OUT("Employee name: ");
                        scanf("%s", name);
                        OUT("Set password: ");
                        scanf("%s", pswd);
                        OUT("Machine room number: ");
                        scanf("%u", &mid);
                        this->add_tea(id, name, pswd, mid);
                        OUT("Add teacher successfully.\n");
                    }
                } else if (cmd[1] == '1') {
                    OUT("Student number(6 digits): ");
                    scanf("%u", &id);
                    auto t = this->stu->select(id);
                    if (t) {
                        DELETE(t)
                        OUT("Student already exists.\n");
                    } else {
                        OUT("Student name: ");
                        scanf("%s", name);
                        OUT("Set password: ");
                        scanf("%s", pswd);
                        this->add_stu(id, name, pswd);
                        OUT("Add student successfully.\n");
                    }
                } else {
                    OUT("Canceled.\n");
                }
                getchar();
                break;
            }
            case '2': {
                OUT("%s\n", MENU.at('2'));
                OUT("Teacher(0)/student(1)/cancel(other)? ");
                scanf("%s", cmd + 1);
                if (cmd[1] == '0') {
                    this->view_tea();
                } else if (cmd[1] == '1') {
                    this->view_stu();
                } else {
                    OUT("Canceled.\n");
                }
                getchar();
                break;
            }
            case '3': {
                OUT("%s\n", MENU.at('3'));
                OUT("Teacher(0)/student(1)/cancel(other)? ");
                scanf("%s", cmd + 1);
                if (cmd[1] == '0') {
                    OUT("Employee number(5 digits): ");
                    scanf("%u", &id);
                    auto t = this->tea->select(id);
                    if (!t) {
                        OUT("Teacher does not exists.\n");
                    } else {
                        DELETE(t)
                        OUT("Employee name: ");
                        scanf("%s", name);
                        OUT("Set password: ");
                        scanf("%s", pswd);
                        OUT("Machine room number: ");
                        scanf("%u", &mid);
                        this->mod_tea(id, name, pswd, mid);
                        OUT("Modify teacher successfully.\n");
                    }
                } else if (cmd[1] == '1') {
                    OUT("Student number(6 digits): ");
                    scanf("%u", &id);
                    auto t = this->stu->select(id);
                    if (!t) {
                        OUT("Student does not exists.\n");
                    } else {
                        DELETE(t)
                        OUT("Student name: ");
                        scanf("%s", name);
                        OUT("Set password: ");
                        scanf("%s", pswd);
                        this->mod_stu(id, name, pswd);
                        OUT("Modify student successfully.\n");
                    }
                } else {
                    OUT("Canceled.\n");
                }
                getchar();
                break;
            }
            case '4': {
                OUT("%s\n", MENU.at('4'));
                OUT("Teacher(0)/student(1)/cancel(other)? ");
                scanf("%s", cmd + 1);
                if (cmd[1] == '0') {
                    OUT("Employee number(5 digits): ");
                    scanf("%u", &id);
                    auto t = this->tea->select(id);
                    if (!t) {
                        OUT("Teacher does not exists.\n");
                    } else {
                        DELETE(t)
                        this->rmv_tea(id);
                        OUT("Remove teacher successfully.\n");
                    }
                } else if (cmd[1] == '1') {
                    OUT("Student number(6 digits): ");
                    scanf("%u", &id);
                    auto t = this->stu->select(id);
                    if (!t) {
                        OUT("Student does not exists.\n");
                    } else {
                        DELETE(t)
                        this->rmv_stu(id);
                        OUT("Remove student successfully.\n");
                    }
                } else {
                    OUT("Canceled.\n");
                }
                getchar();
                break;
            }
            case '5': {
                OUT("%s\n", MENU.at('5'));
                OUT("Machine room id: ");
                scanf("%u", &mid);
                auto t = this->mr->select(mid);
                if (t) {
                    DELETE(t)
                    OUT("Machine room already exists.\n");
                } else {
                    OUT("Machine room name: ");
                    scanf("%s", name);
                    OUT("Machine room max size: ");
                    scanf("%u", &id);
                    this->add_mach(mid, name, id);
                    OUT("Add machine room successfully.\n");
                }
                getchar();
                break;
            }
            case '6':
                OUT("%s\n", MENU.at('6'));
                this->view_mach();
                break;
            case '7': {
                OUT("%s\n", MENU.at('7'));
                OUT("Machine room id: ");
                scanf("%u", &mid);
                auto t = this->mr->select(mid);
                if (!t) {
                    OUT("Machine room does not exists.\n");
                } else {
                    DELETE(t)
                    OUT("Machine room name: ");
                    scanf("%s", name);
                    OUT("Machine room max size: ");
                    scanf("%u", &id);
                    this->mod_mach(mid, name, id);
                    OUT("Modify machine room successfully.\n");
                }
                getchar();
                break;
            }
            case '8': {
                OUT("%s\n", MENU.at('8'));
                OUT("Machine room id: ");
                scanf("%u", &mid);
                auto t = this->mr->select(mid);
                if (!t) {
                    OUT("Machine room does not exists.\n");
                } else {
                    DELETE(t)
                    OUT("Remove this machine room?(Y/n) ");
                    scanf("%s", cmd + 2);
                    if (cmd[2] == 'y' || cmd[2] == 'Y') {
                        this->rmv_mach(mid);
                        OUT("Remove machine room successfully.\n");
                    } else {
                        OUT("Canceled.\n");
                    }
                }
                getchar();
                break;
            }
            case '9': {
                OUT("%s\n", MENU.at('9'));
                OUT("Clear all reservations?(Y/n) ");
                scanf("%s", cmd + 1);
                if (cmd[1] == 'y' || cmd[1] == 'Y') {
                    this->clear_reserv();
                    OUT("Clear reservations successfully.\n");
                } else {
                    OUT("Canceled.\n");
                }
                getchar();
                break;
            }
            case 'a': {
                OUT("%s\n", MENU.at('a'));
                OUT("Old password: ");
                system("stty -echo");
                scanf("%s", pswd);
                system("stty echo");
                printf("\n");
                if (!this->check_info(pswd)) {
                    getchar();
                    OUT("Wrong password.\n");
                    break;
                }
                OUT("New password: ");
                system("stty -echo");
                scanf("%s", pswd);
                system("stty echo");
                printf("\n");
                OUT("Confirm new password: ");
                system("stty -echo");
                scanf("%s", name);
                system("stty echo");
                printf("\n");
                if (!strcmp(pswd, name)) {
                    this->modi_pswd(pswd);
                    OUT("Modify administrator's password successfully.\n");
                } else {
                    OUT("Modify administrator's password failed.\n");
                }
                getchar();
                break;
            }
            case 'c':
                system("clear");
                break;
            case 'h':
                this->show_ui();
                break;
            default:
                OUT("Invalid input. Please enter `h` for help.\n");
                break;
        }
    } while (true);
}

}  // namespace srv
