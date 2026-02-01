// Function: __GBAX01
// Entry: 801a7c74
// Size: 476 bytes

void __GBAX01(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  undefined8 uVar4;
  
  iVar1 = param_1 * 0x100;
  if (param_2 == 0) {
    *(undefined4 *)(&DAT_803283b8 + iVar1) = *(undefined4 *)((&DAT_80328418)[param_1 * 0x40] + 0x20)
    ;
    *(undefined4 *)(&DAT_803283bc + iVar1) = *(undefined4 *)((&DAT_80328418)[param_1 * 0x40] + 0x24)
    ;
    if ((&DAT_8032837b)[iVar1] != '\0') {
      if ((&DAT_8032837a)[iVar1] != '\0') {
        if ((*(uint *)(&DAT_803283b8 + iVar1) & (uint)DAT_8021cb4d << 9) != 0) {
          if ((((&DAT_80328379)[iVar1] != '\0') && (*(uint *)(&DAT_803283b8 + iVar1) >> 0xf != 0))
             && ((&DAT_80328378)[iVar1] != '\0')) {
            *(uint *)(&DAT_80328380 + iVar1) =
                 ~(uint)DAT_8021cb6c & *(int *)(&DAT_8032836c + iVar1) + (uint)DAT_8021cb6c;
            iVar2 = (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xb] << (uint)DAT_8021cb69;
            if (*(int *)(&DAT_80328380 + iVar1) < iVar2) {
              *(int *)(&DAT_80328380 + iVar1) = iVar2;
            }
            *(undefined4 *)(&DAT_803283c4 + iVar1) = *(undefined4 *)(&DAT_80328380 + iVar1);
            *(int *)(&DAT_80328380 + iVar1) = *(int *)(&DAT_80328380 + iVar1) - iVar2;
            *(int *)(&DAT_80328380 + iVar1) =
                 *(int *)(&DAT_80328380 + iVar1) >> (DAT_8021cb68 & 0x3f);
            (&DAT_8032837c)[iVar1] = (char)*(undefined4 *)(&DAT_803283bc + iVar1);
            (&DAT_8032837d)[iVar1] = (char)((uint)*(undefined4 *)(&DAT_803283bc + iVar1) >> 8);
            (&DAT_8032837f)[iVar1] = (char)((uint)*(undefined4 *)(&DAT_803283bc + iVar1) >> 0x18);
            (&DAT_8032837e)[iVar1] = (char)((uint)*(undefined4 *)(&DAT_803283bc + iVar1) >> 0x10);
            *(uint *)(&DAT_80328398 + iVar1) = DAT_8021cb6e + 1 << (uint)DAT_8021cb6a;
            *(uint *)(&DAT_80328394 + iVar1) = (uint)DAT_8021cb50;
            uVar4 = OSGetTime();
            *(undefined8 *)(&DAT_80328388 + iVar1) = uVar4;
            *(undefined4 *)(&DAT_80328390 + iVar1) = 1;
            param_2 = GBAWriteAsync(param_1,&DAT_8032837c + iVar1,
                                    *(undefined4 *)(&DAT_80328370 + iVar1),F31);
            goto LAB_801a7df8;
          }
        }
      }
    }
    param_2 = 3;
  }
LAB_801a7df8:
  if (param_2 != 0) {
    *(undefined4 *)(&DAT_8032838c + iVar1) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar1) = 0;
    pcVar3 = *(code **)(&DAT_80328374 + iVar1);
    if (pcVar3 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar1) = 0;
      (*pcVar3)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar1) = param_2;
  return;
}

