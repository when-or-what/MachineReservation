#include "srv/Student.h"

namespace srv {

const std::unordered_map<char, const char*> Student::MENU = {
    {'1', "Reserve machine room"},
    {'2', "View my reservations"},
    {'3', "View all reservations"},
    {'4', "Cancel reservation"},
    {'q', "Quit"},
    {'c', "Clear"},
    {'h', "Help"}};

Student::Student() {}

Student::Student(ent::Student* stu, dao::Reserv* r, dao::Student* s,
                 dao::MachineRoom* m)
    : stu(stu), s(s), r(r), m(m) {}

Student::~Student() { DELETE(this->stu) }

void Student::reserv(uint32_t mid, uint64_t date) {
    // 新创建的预约就是审核中的状态
    ent::Reserv* rr = new ent::Reserv(0, date, this->stu->get_sid(), mid,
                                      ent::Reserv::PENDING);
    MEM_ALLOC_FAILED(rr)
    // 插入
    this->r->insert(rr);
    DELETE(rr)
}

void Student::view_reservations() {
    std::vector<ent::Reserv*> v = r->select();
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

void Student::view_my_reservations() {
    std::vector<ent::Reserv*> v = r->select_by_sid(this->stu->get_sid());
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

bool Student::cancel(uint32_t id) {
    auto rr = this->r->select_one(id);
    // 不存在的id
    if (!rr) return false;
    // 不是自己的id
    if (rr->get_sid() != this->stu->get_sid()) {
        DELETE(rr)
        return false;
    }
    // 不是审核中的id
    if (rr->get_reserv_stat() != ent::Reserv::PENDING) {
        DELETE(rr)
        return false;
    }
    rr->set_reserv_stat(ent::Reserv::CANCEL);
    this->r->update(rr);
    DELETE(rr)
    return true;
}

void Student::show_ui() {
    printf("Commands: \n");
    for (auto&& p : MENU) {
        printf("         %c. %s\n", p.first, p.second);
    }
}

bool Student::check_info(const char* sname, const char* plain_pswd) {
    // 加密密码
    char pswd[gv::Global::PSWD_LEN];
    gv::Global::sha256(plain_pswd, pswd);
    // 比较密码密文是否一样，姓名是否一样
    bool ans = !strcmp(this->stu->get_pswd(), pswd) &&
               !strcmp(this->stu->get_sname(), sname);
    return ans;
}

void Student::ui() {
    uint32_t mid = 0;
    uint64_t date = 0, in = 0;
    char cmd[gv::Global::CMD_LEN];
    printf("\n");
    do {
        SHOW_CMD_TIP("%u> ", this->stu->get_sid());
        cmd[0] = 0;
        scanf("%[^\n]", cmd);
        getchar();
        if (!cmd[0]) continue;
        switch (cmd[0]) {
            case 'q':
                OUT("Bye, %s\n", this->stu->get_sname());
                return;
            case '1': {
                OUT("%s\n", MENU.at('1'));
                OUT("Machine room number: ");
                scanf("%u", &mid);
                bool flag = false;
                auto v = this->m->select();
                for (auto&& e : v) {
                    if (e->get_mid() == mid) {
                        flag = true;
                    }
                    DELETE(e)
                }
                if (flag) {
                    OUT("Date(yyyymmdd): ");
                    scanf("%lu", &date);
                    OUT("Time(hhmmhhmm): ");
                    scanf("%lu", &in);
                    date = date * 1'0000'0000 + in;
                    OUT("Confirm your reservation(Y/n): ");
                    scanf("%s", cmd + 1);
                    getchar();
                    do {
                        if (cmd[1] == 'y' || cmd[1] == 'Y') {
                            this->reserv(mid, date);
                            OUT("Reserve successfully.\n");
                            break;
                        } else if (cmd[1] == 'n' || cmd[1] == 'N') {
                            OUT("Canceled.\n");
                            break;
                        }
                    } while (true);
                } else {
                    OUT("Invalid machine room id.\n");
                }
                break;
            }
            case '2':
                OUT("%s\n", MENU.at('2'));
                this->view_my_reservations();
                break;
            case '3':
                OUT("%s\n", MENU.at('3'));
                this->view_reservations();
                break;
            case '4':
                OUT("%s\n", MENU.at('4'));
                OUT("Cancel id: ");
                scanf("%u", &mid);
                OUT("Cancel this reservation?(Y/n) ");
                scanf("%s", cmd + 1);
                getchar();
                if (cmd[1] == 'y' || cmd[1] == 'Y') {
                    if (this->cancel(mid)) {
                        OUT("Reservation canceled successfully.\n");
                    } else {
                        OUT("Invalid reservation id.\n");
                    }
                } else {
                    OUT("Canceled.\n");
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
