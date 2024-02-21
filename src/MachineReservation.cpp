#include "MachineReservation.h"

MachineReservation::MachineReservation() : is_init(false), password(NULL) {
    this->mr = new dao::MachineRoom();
    MEM_ALLOC_FAILED(this->mr)
    this->reserv = new dao::Reserv();
    MEM_ALLOC_FAILED(this->reserv)
    this->stu = new dao::Student();
    MEM_ALLOC_FAILED(this->stu)
    this->tea = new dao::Teacher();
    MEM_ALLOC_FAILED(this->tea)
    this->conf = new dao::Config();
    MEM_ALLOC_FAILED(this->conf)
    // 初始化系统
    this->init();
}

MachineReservation::~MachineReservation() {
    DELETE(this->mr)
    DELETE(this->reserv)
    DELETE(this->stu)
    DELETE(this->tea)
    DELETE(this->conf)
    FREE(this->password)
}

void MachineReservation::init() {
    // 向配置文件中写入管理员初始密码
    // 首先读取初始化标志
    auto c = this->conf->select(gv::Global::INIT_FLAG);
    if (!c) {
        INFO("Config file is not inited. try to init...");
        // 如果不存在，则写入，默认值为未设置密码
        c = new ent::Config(gv::Global::INIT_FLAG, gv::Global::N_INIT);
        MEM_ALLOC_FAILED(c)
        this->conf->insert(c);
        this->is_init = false;  // 管理员密码未被初始化
        INFO("Config file inited.");
    } else {
        INFO("Config file is already inited.");
        // 设置管理员密码是否初始化标志
        this->is_init = !strcmp(c->get_value(), gv::Global::INITED);
    }
    // 查看是否初始化密码
    if (!this->is_init) {
        // 如果未初始化密码，则初始化密码为随机值
        INFO("Admin's password is not inited. try to init...");
        this->password = gv::Global::rand_string(gv::Global::PSW_LEN);
        // 给密码加密
        char tmp[gv::Global::PSWD_LEN];
        memset(tmp, 0, gv::Global::PSWD_LEN);
        gv::Global::sha256(this->password, tmp);
        // 写入文件
        c->set_key(gv::Global::ADMIN_PSWD);
        c->set_value(tmp);
        this->conf->update(c);
        INFO("Admin's password inited.");
    } else {
        // 如果已经初始化密码，则不管
        INFO("Admin's password is already inited.");
    }
    DELETE(c)
    INFO("System check done.");
}

void MachineReservation::show_ui() {
    printf("Commands: \n");
    printf("         s. Sign in\n");
    printf("         q. Quit\n");
    printf("         c. Clear\n");
    printf("         h. Help\n");
    if (!this->is_init) {
        printf("         p. Password\n");
    }
}

void MachineReservation::start() {
    char cmd[gv::Global::CMD_LEN];
    char name[gv::Global::NAME_LEN];
    char pswd[gv::Global::PSWD_LEN];
    uint32_t id = 0;
    size_t t = 0;
    printf("\n");
    do {
        SHOW_CMD_TIP("> ");
        cmd[0] = 0;
        scanf("%[^\n]", cmd);
        getchar();
        if (!cmd[0]) continue;
        switch (cmd[0]) {
            case 'q':
                OUT("Bye\n");
                return;
            case 's': {
                OUT("ID: ");
                scanf("%u", &id);
                OUT("Password: ");
                system("stty -echo");
                scanf("%s", pswd);
                getchar();
                system("stty echo");
                printf("\n");
                t = gv::Global::get_uint_len(id);
                if (id == 0) {
                    // 如果账号为0，则说明是管理员
                    auto cc = this->conf->select(gv::Global::ADMIN_PSWD);
                    if (!cc) {
                        OUT("Config item not found.\n");
                        break;
                    }
                    ent::Admin *a = new ent::Admin(0, cc->get_value());
                    MEM_ALLOC_FAILED(a)
                    DELETE(cc)
                    srv::Admin *admin =
                        new srv::Admin(a, this->conf, this->mr, this->reserv,
                                       this->stu, this->tea);
                    MEM_ALLOC_FAILED(admin)
                    // 校验密码是否正确
                    if (admin->check_info(pswd)) {
                        admin->ui();
                    } else {
                        OUT("Identity verification failure.\n");
                    }
                    DELETE(admin)
                } else if (t == gv::Global::SID_LEN) {
                    // 学生
                    OUT("Name: ");
                    scanf("%s", name);
                    getchar();
                    auto ss = this->stu->select(id);
                    if (!ss) {
                        OUT("User not found.\n");
                        break;
                    }
                    ent::Student *s =
                        new ent::Student(ss->get_id(), ss->get_sid(),
                                         ss->get_sname(), ss->get_pswd());
                    MEM_ALLOC_FAILED(s)
                    DELETE(ss)
                    srv::Student *stu =
                        new srv::Student(s, this->reserv, this->stu, this->mr);
                    MEM_ALLOC_FAILED(stu)
                    if (stu->check_info(name, pswd)) {
                        stu->ui();
                    } else {
                        OUT("Identity verification failure.\n");
                    }
                    DELETE(stu)
                } else if (t == gv::Global::TID_LEN) {
                    // 老师
                    OUT("Name: ");
                    scanf("%s", name);
                    getchar();
                    auto tt = this->tea->select(id);
                    if (!tt) {
                        OUT("User not found.\n");
                        break;
                    }
                    ent::Teacher *te = new ent::Teacher(
                        tt->get_id(), tt->get_tid(), tt->get_mid(),
                        tt->get_tname(), tt->get_pswd());
                    MEM_ALLOC_FAILED(te)
                    DELETE(tt)
                    srv::Teacher *tea =
                        new srv::Teacher(te, this->reserv, this->tea);
                    MEM_ALLOC_FAILED(tea)
                    if (tea->check_info(name, pswd)) {
                        tea->ui();
                    } else {
                        OUT("Identity verification failure.\n");
                    }
                    DELETE(tea)
                } else {
                    OUT("Invalid account.\n");
                }
                break;
            }
            case 'c':
                system("clear");
                break;
            case 'h':
                this->show_ui();
                break;
            case 'p':
                if (!this->is_init) {
                    OUT("Admin password is: %s\n", this->password);
                    this->is_init = true;
                    auto c = new ent::Config(gv::Global::INIT_FLAG,
                                             gv::Global::INITED);
                    this->conf->update(c);
                    DELETE(c)
                } else {
                    OUT("Invalid input. Please enter `h` for help.\n");
                }
                break;
            default:
                OUT("Invalid input. Please enter `h` for help.\n");
                break;
        }
    } while (true);
}