#include "MachineReservation.h"

int main(int argc, char** argv) {
    // 初始化系统
    gv::Global::sys_init();
    auto* m = new MachineReservation();
    m->start();
    DELETE(m);
    // 系统还原
    gv::Global::sys_restore();
    return 0;
}
