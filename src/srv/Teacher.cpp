#include "srv/Teacher.h"

namespace srv {

const std::unordered_map<char, const char*> Teacher::MENU = {
    {'1', "View all reservations"},
    {'2', "Audit reservations"},
    {'q', "Quit"},
    {'c', "Clear"},
    {'h', "Help"}};

Teacher::Teacher() {}

Teacher::Teacher(ent::Teacher* tea, dao::Reserv* r, dao::Teacher* t)
    : tea(tea), r(r), t(t) {}

Teacher::~Teacher() { DELETE(this->tea) }

bool Teacher::audit_reservations(uint32_t id, uint32_t newstat) {
    auto rr = this->r->select_one(id);
    // 不存在的id
    if (!rr) return false;
    // 不属于自己管的id
    if (rr->get_mid() != this->tea->get_mid()) {
        DELETE(rr)
        return false;
    }
    // 已取消的id
    if (rr->get_reserv_stat() == ent::Reserv::CANCEL) {
        DELETE(rr)
        return false;
    }
    rr->set_reserv_stat(newstat);
    this->r->update(rr);
    DELETE(rr)
    return true;
}

void Teacher::view_reservations() {
    auto v = this->r->select_by_mid(this->tea->get_mid());
    // 输出表头
    printf(
        "+--------+--------------+---------------+----------+--------+---------"
        "--+"
        "\n");
    printf("|  %-4s  |  %-10s  |  %-11s  |  %-6s  |  %-4s  |  %-7s  |\n", "id",
           "date", "interval", "s_id", "m_id", "stat");
    printf(
        "+--------+--------------+---------------+----------+--------+---------"
        "--+"
        "\n");
    char *d = NULL, *i = NULL;
    for (auto&& e : v) {
        auto pp = ent::Reserv::get_time_str(e->get_date());
        d = pp.first, i = pp.second;
        printf("|  %-4u  |  %-10s  |  %-11s  |  %-6u  |  %-4u  |  %-7s  |\n",
               e->get_id(), d, i, e->get_sid(), e->get_mid(),
               ent::Reserv::MAPPING[e->get_reserv_stat()]);
        FREE(d)
        FREE(i)
        DELETE(e)
    }
    printf(
        "+--------+--------------+---------------+----------+--------+---------"
        "--+"
        "\n");
    printf("Total: %ld\n", v.size());
}

void Teacher::show_ui() {
    printf("Commands: \n");
    for (auto&& p : MENU) {
        printf("         %c. %s\n", p.first, p.second);
    }
}

// 上层接口
bool Teacher::check_info(const char* tname, const char* plain_pswd) {
    // 加密密码
    char pswd[gv::Global::PSWD_LEN];
    gv::Global::sha256(plain_pswd, pswd);
    // 比较密码密文是否一样，姓名是否一样
    bool ans = !strcmp(this->tea->get_pswd(), pswd) &&
               !strcmp(this->tea->get_tname(), tname);
    return ans;
}

void Teacher::ui() {
    uint32_t id = 0, st = 0;
    char cmd[gv::Global::CMD_LEN];
    printf("\n");
    do {
        SHOW_CMD_TIP("%u> ", this->tea->get_tid());
        cmd[0] = 0;
        scanf("%[^\n]", cmd);
        getchar();
        if (!cmd[0]) continue;
        switch (cmd[0]) {
            case 'q':
                OUT("Bye, %s\n", this->tea->get_tname());
                return;
            case '1':
                OUT("%s\n", MENU.at('1'));
                this->view_reservations();
                break;
            case '2':
                OUT("%s\n", MENU.at('2'));
                OUT("Audit id: ");
                scanf("%u", &id);
                OUT("Pass(1)/reject(0): ");
                scanf("%s", cmd + 1);
                getchar();
                if (cmd[1] != '0' && cmd[1] != '1') {
                    OUT("Audit abort.\n");
                    break;
                }
                st = cmd[1] == '0' ? ent::Reserv::FAIL : ent::Reserv::SUCC;
                if (this->audit_reservations(id, st)) {
                    OUT("Audit successfully.\n");
                } else {
                    OUT("Invalid id.\n");
                }
                break;
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
