#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/buffer_io.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/errno.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/critical_regions.h"

extern int DAT_8032f390;

int ftell(int param_1)
{
    char cVar1;
    unsigned int uVar2;
    unsigned short uVar3;
    int iVar4;
    int iVar5;
    char *pcVar6;
    int iVar7;
    
    __begin_critical_region(2);
    iVar4 = 0;
    uVar3 = *(unsigned short *)(param_1 + 4) >> 6 & 7;
    if (((uVar3 == 1) || (uVar3 == 2)) && (*(char *)(param_1 + 10) == '\0')) {
        uVar2 = (unsigned int)(*(unsigned char *)(param_1 + 8) >> 5);
        if (uVar2 == 0) {
            iVar7 = *(int *)(param_1 + 0x18);
        }
        else {
            pcVar6 = *(char **)(param_1 + 0x1c);
            iVar5 = *(int *)(param_1 + 0x24) - (int)pcVar6;
            iVar7 = *(int *)(param_1 + 0x34) + iVar5;
            if (2 < uVar2) {
                iVar4 = uVar2 - 2;
                iVar7 = iVar7 - iVar4;
            }
            if ((*(unsigned char *)(param_1 + 5) >> 3 & 1) == 0) {
                for (iVar5 = iVar5 - iVar4; iVar5 != 0; iVar5 = iVar5 + -1) {
                    cVar1 = *pcVar6;
                    pcVar6 = pcVar6 + 1;
                    if (cVar1 == '\n') {
                        iVar7 = iVar7 + 1;
                    }
                }
            }
        }
    }
    else {
        iVar7 = -1;
        DAT_8032f390 = 0x28;
    }
    __end_critical_region(2);
    return iVar7;
}

int _fseek(int *param_1, unsigned int param_2, int param_3)
{
    char cVar1;
    unsigned int uVar2;
    unsigned short uVar3;
    int iVar5;
    int iVar6;
    char *pcVar7;
    unsigned int local_18[4];
    
    if (((*(unsigned short *)(param_1 + 1) >> 6 & 7) == 1) && (*(char *)((int)param_1 + 10) == '\0')) {
        local_18[0] = param_2;
        if ((*(unsigned char *)(param_1 + 2) >> 5 == 1) && (iVar5 = __flush_buffer((FILE*)param_1, 0), iVar5 != 0)) {
            *(unsigned char *)((int)param_1 + 10) = 1;
            param_1[10] = 0;
            DAT_8032f390 = 0x28;
            return -1;
        }
        else {
            if (param_3 == 1) {
                param_3 = 0;
                iVar5 = 0;
                uVar3 = *(unsigned short *)(param_1 + 1) >> 6 & 7;
                if (((uVar3 == 1) || (uVar3 == 2)) && (*(char *)((int)param_1 + 10) == '\0')) {
                    uVar2 = (unsigned int)(*(unsigned char *)(param_1 + 2) >> 5);
                    if (uVar2 == 0) {
                        iVar6 = param_1[6];
                    }
                    else {
                        pcVar7 = (char *)param_1[7];
                        iVar6 = param_1[0xd] + (param_1[9] - (int)pcVar7);
                        if (2 < uVar2) {
                            iVar5 = uVar2 - 2;
                            iVar6 = iVar6 - iVar5;
                        }
                        if ((*(unsigned char *)((int)param_1 + 5) >> 3 & 1) == 0) {
                            for (iVar5 = (param_1[9] - (int)pcVar7) - iVar5; iVar5 != 0; iVar5 = iVar5 + -1) {
                                cVar1 = *pcVar7;
                                pcVar7 = pcVar7 + 1;
                                if (cVar1 == '\n') {
                                    iVar6 = iVar6 + 1;
                                }
                            }
                        }
                    }
                }
                else {
                    iVar6 = -1;
                    DAT_8032f390 = 0x28;
                }
                local_18[0] = local_18[0] + iVar6;
            }
            if (((param_3 == 2) || ((*(unsigned char *)(param_1 + 1) >> 3 & 7) == 3)) ||
               ((*(unsigned char *)(param_1 + 2) >> 5 != 2 && (*(unsigned char *)(param_1 + 2) >> 5 != 3)))) {
                *(unsigned char *)(param_1 + 2) = *(unsigned char *)(param_1 + 2) & 0x1f;
            }
            else if ((local_18[0] < (unsigned int)param_1[6]) && ((unsigned int)param_1[0xd] <= local_18[0])) {
                param_1[9] = param_1[7] + (local_18[0] - param_1[0xd]);
                param_1[10] = param_1[6] - local_18[0];
                *(unsigned char *)(param_1 + 2) = *(unsigned char *)(param_1 + 2) & 0x1f | 0x40;
            }
            else {
                *(unsigned char *)(param_1 + 2) = *(unsigned char *)(param_1 + 2) & 0x1f;
            }
            if (*(unsigned char *)(param_1 + 2) >> 5 == 0) {
                if (((void *)param_1[0xe] != (void *)0x0) &&
                   (iVar5 = (*(int (**)(void *, unsigned int *, int, void *))((int)param_1 + 0x38))((void*)*param_1, local_18, param_3, (void*)param_1[0x12]), iVar5 != 0)) {
                    *(unsigned char *)((int)param_1 + 10) = 1;
                    param_1[10] = 0;
                    DAT_8032f390 = 0x28;
                    return -1;
                }
                *(unsigned char *)((int)param_1 + 9) = 0;
                param_1[6] = local_18[0];
                param_1[10] = 0;
            }
            return 0;
        }
    }
    else {
        DAT_8032f390 = 0x28;
        return -1;
    }
}

int fseek(int *param_1, int param_2, int param_3)
{
    int uVar1;
    
    __begin_critical_region(2);
    uVar1 = _fseek(param_1, param_2, param_3);
    __end_critical_region(2);
    return uVar1;
}
