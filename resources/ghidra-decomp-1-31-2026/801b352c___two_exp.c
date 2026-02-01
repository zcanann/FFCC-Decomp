// Function: __two_exp
// Entry: 801b352c
// Size: 5936 bytes

void __two_exp(undefined4 *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined2 local_40;
  undefined local_3c [2];
  undefined2 local_3a;
  byte local_38 [48];
  
  switch(param_2) {
  case 0:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e709c; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 1:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e709e; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 2:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70a0; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 3:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70a2; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 4:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70a4; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 5:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70a7; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 6:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70aa; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 7:
    *(undefined2 *)((int)param_1 + 2) = 2;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70ad; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 8:
    *(undefined2 *)((int)param_1 + 2) = 2;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e70b1; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffc0:
    *(undefined2 *)((int)param_1 + 2) = 0xffec;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e6ffd; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  default:
    __two_exp(local_3c,(int)param_2 / 2);
    __timesdec(param_1,local_3c,local_3c);
    if ((param_2 & 1) != 0) {
      local_68 = *param_1;
      local_64 = param_1[1];
      local_60 = param_1[2];
      local_5c = param_1[3];
      local_58 = param_1[4];
      local_54 = param_1[5];
      local_50 = param_1[6];
      local_4c = param_1[7];
      local_48 = param_1[8];
      local_44 = param_1[9];
      local_40 = *(undefined2 *)(param_1 + 10);
      if ((int)param_2 < 1) {
        local_3a = 0xffff;
        uVar5 = 0;
        for (pcVar6 = &DAT_801e709a; ((int)uVar5 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1)
        {
          local_38[uVar5 + 1] = *pcVar6 - 0x30;
          uVar5 = uVar5 + 1;
        }
        local_38[0] = (byte)uVar5;
        cVar1 = *pcVar6;
        if ((cVar1 != '\0') && ('\x04' < cVar1)) {
          if (cVar1 < '\x06') {
            do {
              pcVar6 = pcVar6 + 1;
              if (*pcVar6 == '\0') {
                if ((local_38[uVar5] & 1) == 0) goto LAB_801b4c88;
                break;
              }
            } while (*pcVar6 == '0');
          }
          for (pbVar4 = local_38 + 1 + ((uVar5 & 0xff) - 1); 8 < *pbVar4; pbVar4 = pbVar4 + -1) {
            if (pbVar4 == local_38 + 1) {
              *pbVar4 = 1;
              local_3a = 0;
              goto LAB_801b4c88;
            }
            *pbVar4 = 0;
          }
          *pbVar4 = *pbVar4 + 1;
        }
      }
      else {
        local_3a = 0;
        uVar5 = 0;
        for (pcVar6 = &DAT_801e709e; ((int)uVar5 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1)
        {
          local_38[uVar5 + 1] = *pcVar6 - 0x30;
          uVar5 = uVar5 + 1;
        }
        local_38[0] = (byte)uVar5;
        cVar1 = *pcVar6;
        if ((cVar1 != '\0') && ('\x04' < cVar1)) {
          if (cVar1 < '\x06') {
            do {
              pcVar6 = pcVar6 + 1;
              if (*pcVar6 == '\0') {
                if ((local_38[uVar5] & 1) == 0) goto LAB_801b4c88;
                break;
              }
            } while (*pcVar6 == '0');
          }
          for (pbVar4 = local_38 + 1 + ((uVar5 & 0xff) - 1); 8 < *pbVar4; pbVar4 = pbVar4 + -1) {
            if (pbVar4 == local_38 + 1) {
              *pbVar4 = 1;
              local_3a = 1;
              goto LAB_801b4c88;
            }
            *pbVar4 = 0;
          }
          *pbVar4 = *pbVar4 + 1;
        }
      }
LAB_801b4c88:
      local_3c[0] = 0;
      __timesdec(param_1,&local_68,local_3c);
    }
    break;
  case 0xffffffcb:
    *(undefined2 *)((int)param_1 + 2) = 0xfff0;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e702b; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffe0:
    *(undefined2 *)((int)param_1 + 2) = 0xfff6;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e7052; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff0:
    *(undefined2 *)((int)param_1 + 2) = 0xfffb;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e706a; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff8:
    *(undefined2 *)((int)param_1 + 2) = 0xfffd;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e7077; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff9:
    *(undefined2 *)((int)param_1 + 2) = 0xfffd;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e707e; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffa:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e7084; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffb:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e708a; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffc:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e708f; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffd:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e7093; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffe:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e7097; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffff:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined *)param_1 = 0;
    for (pcVar6 = &DAT_801e709a; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
  }
  return;
}

