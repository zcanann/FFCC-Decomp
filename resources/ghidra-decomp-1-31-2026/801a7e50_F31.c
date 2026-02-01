// Function: F31
// Entry: 801a7e50
// Size: 1176 bytes

void F31(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  code *pcVar10;
  
  iVar2 = param_1 * 0x100;
  if (param_2 != 0) goto LAB_801a8290;
  if (*(int *)(&DAT_80328390 + iVar2) == 0) {
    if ((**(byte **)(&DAT_80328370 + iVar2) & s____Coded_by_Kawasedo_8021cb51[0xb]) != 0) {
      if ((int)(uint)(**(byte **)(&DAT_80328370 + iVar2) & DAT_8021cb72) >> (DAT_8021cb69 & 0x3f) ==
          (int)(*(uint *)(&DAT_80328394 + iVar2) & (uint)DAT_8021cb69) >> (DAT_8021cb67 & 0x3f)) {
        *(uint *)(&DAT_80328394 + iVar2) =
             *(uint *)(&DAT_80328394 + iVar2) -
             ((uint)(byte)s____Coded_by_Kawasedo_8021cb51[0x10] -
             (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xe]);
        goto LAB_801a7f08;
      }
    }
    param_2 = 3;
  }
  else {
    *(undefined4 *)(&DAT_80328390 + iVar2) = 0;
LAB_801a7f08:
    iVar5 = *(int *)(&DAT_80328394 + iVar2);
    if (*(int *)(&DAT_803283c4 + iVar2) < iVar5) {
      uVar4 = OSGetTick();
      *(undefined4 *)(&DAT_80328384 + iVar2) = uVar4;
      param_2 = GBAReadAsync(param_1,&DAT_80328378 + iVar2,*(undefined4 *)(&DAT_80328370 + iVar2),
                             F33);
    }
    else {
      if (iVar5 < *(int *)(&DAT_803283c4 + iVar2)) {
        uVar3 = (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0x14];
        *(uint *)(&DAT_80328380 + iVar2) = (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0x14];
        while (*(int *)(&DAT_80328380 + iVar2) < (int)(uint)DAT_8021cb69) {
          if (*(int *)(&DAT_8032836c + iVar2) != 0) {
            pbVar6 = *(byte **)(&DAT_80328368 + iVar2);
            *(byte **)(&DAT_80328368 + iVar2) = pbVar6 + 1;
            uVar8 = (uint)DAT_8021cb6d;
            bVar1 = *pbVar6;
            *(int *)(&DAT_8032836c + iVar2) = *(int *)(&DAT_8032836c + iVar2) + -1;
            uVar3 = uVar3 | (uint)bVar1 << *(int *)(&DAT_80328380 + iVar2) * uVar8;
          }
          *(int *)(&DAT_80328380 + iVar2) = *(int *)(&DAT_80328380 + iVar2) + 1;
        }
        if (*(uint *)(&DAT_80328394 + iVar2) == (uint)DAT_8021cb6e) {
          *(uint *)(&DAT_803283c0 + iVar2) = uVar3;
        }
        else if (*(uint *)(&DAT_80328394 + iVar2) == (uint)DAT_8021cb6f) {
          uVar3 = param_1 << (uint)DAT_8021cb6d;
        }
        if ((int)(uint)DAT_8021cb4a <= *(int *)(&DAT_80328394 + iVar2)) {
          uVar8 = *(uint *)(&DAT_80328398 + iVar2);
          uVar7 = (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xb];
          uVar9 = uVar3;
          while( true ) {
            if ((int)uVar7 <= (int)(uint)DAT_8021cb66) break;
            if (((uVar9 ^ uVar8) & 1) == 0) {
              uVar8 = uVar8 >> 1;
            }
            else {
              uVar8 = uVar8 >> 1 ^
                      (uint)DAT_8021cb6e * 0x100 +
                      (((uint)DAT_8021cb70 + (uint)DAT_8021cb73 + (uint)DAT_8021cb73 * -0x10) -
                      (uint)DAT_8021cb6b);
            }
            uVar9 = uVar9 >> 1;
            uVar7 = uVar7 - 1;
          }
          *(uint *)(&DAT_80328398 + iVar2) = uVar8;
        }
        if (*(int *)(&DAT_80328394 + iVar2) == DAT_8021cb70 + 0x100) {
          *(uint *)(&DAT_8032839c + iVar2) = uVar3;
        }
        else if (*(int *)(&DAT_80328394 + iVar2) == DAT_8021cb49 + 0x100) {
          *(uint *)(&DAT_80328380 + iVar2) = (uint)DAT_8021cb4f;
          *(uint *)(&DAT_80328360 + *(int *)(&DAT_80328380 + iVar2) * 4 + iVar2 + 0x3c) = uVar3;
        }
      }
      else {
        uVar3 = *(uint *)(&DAT_80328398 + iVar2) | iVar5 << 0x10;
      }
      if ((int)(uint)DAT_8021cb73 < *(int *)(&DAT_80328394 + iVar2)) {
        *(uint *)(&DAT_803283b8 + iVar2) =
             *(int *)(&DAT_803283b8 + iVar2) *
             ((uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xe] << (uint)DAT_8021cb72 |
             (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xc] |
             (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xf] << (uint)DAT_8021cb6d |
             (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0xf] << (uint)DAT_8021cb74) -
             ((uint)(byte)s____Coded_by_Kawasedo_8021cb51[0x12] -
             (uint)(byte)s____Coded_by_Kawasedo_8021cb51[0x11]);
        uVar3 = uVar3 ^ *(uint *)(&DAT_803283b8 + iVar2) ^
                -(*(int *)(&DAT_80328394 + iVar2) +
                 (uint)(byte)s____Coded_by_Kawasedo_8021cb51[2] * 0x100000) ^
                ((uint)(byte)s____Coded_by_Kawasedo_8021cb51[9] << 8 |
                (uint)(byte)s____Coded_by_Kawasedo_8021cb51[10] << 0x10 |
                (uint)(byte)s____Coded_by_Kawasedo_8021cb51[2] << 0x18 |
                (uint)(byte)s____Coded_by_Kawasedo_8021cb51[2]);
      }
      (&DAT_8032837f)[iVar2] = (char)(uVar3 >> (uint)DAT_8021cb48);
      (&DAT_8032837c)[iVar2] = (char)(uVar3 >> (uint)DAT_8021cb66);
      (&DAT_8032837d)[iVar2] = (char)(uVar3 >> (uint)DAT_8021cb71);
      (&DAT_8032837e)[iVar2] = (char)(uVar3 >> (uint)DAT_8021cb72);
      if (*(int *)(&DAT_80328394 + iVar2) == (uint)DAT_8021cb49 + (uint)DAT_8021cb49) {
        *(uint *)(&DAT_803283a4 + iVar2) = uVar3;
      }
      if (*(int *)(&DAT_80328380 + iVar2) < (int)(uint)DAT_8021cb69) {
        *(uint *)(&DAT_80328360 + (3 - (1 - *(int *)(&DAT_80328380 + iVar2))) * 4 + iVar2 + 0x3c) =
             uVar3;
        iVar5 = *(int *)(&DAT_80328380 + iVar2);
        *(int *)(&DAT_80328360 + (5 - iVar5) * 4 + iVar2 + 0x3c) =
             *(int *)(&DAT_80328360 + (2 - (1 - iVar5)) * 4 + iVar2 + 0x3c) *
             *(int *)(&DAT_80328360 + (4 - iVar5) * 4 + iVar2 + 0x3c);
        iVar5 = 1 - *(int *)(&DAT_80328380 + iVar2);
        *(int *)(&DAT_80328360 + (5 - iVar5) * 4 + iVar2 + 0x3c) =
             *(int *)(&DAT_80328360 + iVar5 * 4 + iVar2 + 0x3c) *
             *(int *)(&DAT_80328360 + *(int *)(&DAT_80328380 + iVar2) * 4 + iVar2 + 0x3c);
        iVar5 = *(int *)(&DAT_80328380 + iVar2);
        *(int *)(&DAT_80328360 + (7 - iVar5) * 4 + iVar2 + 0x3c) =
             *(int *)(&DAT_80328360 + (1 - iVar5) * -4 + iVar2 + 0x3c) *
             *(int *)(&DAT_80328360 + (4 - iVar5) * 4 + iVar2 + 0x3c);
      }
      param_2 = GBAWriteAsync(param_1,&DAT_8032837c + iVar2,*(undefined4 *)(&DAT_80328370 + iVar2),
                              F31);
    }
  }
LAB_801a8290:
  if (param_2 != 0) {
    *(undefined4 *)(&DAT_8032838c + iVar2) = 0;
    *(undefined4 *)(&DAT_80328388 + iVar2) = 0;
    pcVar10 = *(code **)(&DAT_80328374 + iVar2);
    if (pcVar10 != (code *)0x0) {
      *(undefined4 *)(&DAT_80328374 + iVar2) = 0;
      (*pcVar10)(param_1,param_2);
    }
  }
  *(int *)(&DAT_80328340 + iVar2) = param_2;
  return;
}

