#include "types.h"
#include "riscv.h"
#include "sysinfo.h"
#include "defs.h"

uint64 sys_sysinfo(void) {
    uint64 sinfo; // user pointer to struct sysinfo

    if(argaddr(0, &sinfo) < 0)
        return -1;

    return sysinfo(sinfo);
}
