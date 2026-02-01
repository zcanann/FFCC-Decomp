// Function: SetVoiceVolumeMix__FP12RedVoiceDATAii
// Entry: 801c3df8
// Size: 720 bytes

void SetVoiceVolumeMix__FP12RedVoiceDATAii(int *param_1,uint param_2,int param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  undefined2 uVar6;
  ushort *puVar7;
  
  iVar4 = *param_1;
  if (iVar4 != 0) {
    puVar7 = (ushort *)(param_1 + 0x1a);
    memset(puVar7,0,0x24);
    if (DAT_8032f400 == 2) {
      *puVar7 = (ushort)((uint)(param_3 * *(short *)(&DAT_8021ddce + param_2 * 2)) >> 8);
      *(short *)(param_1 + 0x1e) =
           (short)((uint)(param_3 * *(short *)(&DAT_8021dfce + param_2 * 2)) >> 8);
      *(short *)(param_1 + 0x1b) =
           (short)((uint)(param_3 * *(short *)(&DAT_8021ddce + (param_2 ^ 0x7f) * 2)) >> 8);
      *(short *)(param_1 + 0x1f) =
           (short)((uint)(param_3 * *(short *)(&DAT_8021dfce + (param_2 ^ 0x7f) * 2)) >> 8);
      if ((param_1[0x25] & 0x1000U) != 0) {
        *(short *)(param_1 + 0x1c) =
             (short)((int)((uint)*puVar7 * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1)) >> 0xf);
        *(short *)(param_1 + 0x22) =
             (short)((int)((uint)*(ushort *)(param_1 + 0x1e) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1)
                          ) >> 0xf);
      }
      if ((param_1[0x25] & 0x2000U) != 0) {
        *(short *)(param_1 + 0x1d) =
             (short)((int)((uint)*(ushort *)(param_1 + 0x1b) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1)
                          ) >> 0xf);
        *(short *)(param_1 + 0x20) =
             (short)((int)((uint)*(ushort *)(param_1 + 0x1f) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1)
                          ) >> 0xf);
      }
    }
    else if ((DAT_8032f400 < 2) && (0 < DAT_8032f400)) {
      iVar3 = (int)DAT_8021de4e;
      if ((param_1[0x25] & 0xc00U) != 0) {
        uVar5 = (ushort)((uint)(param_3 * iVar3) >> 8);
        *puVar7 = uVar5;
        *(ushort *)(param_1 + 0x1b) = uVar5;
      }
      if ((param_1[0x25] & 0x3000U) != 0) {
        uVar6 = (undefined2)((param_3 * iVar3 >> 8) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1) >> 0xf);
        if ((param_1[0x25] & 2U) == 0) {
          *(undefined2 *)(param_1 + 0x1e) = uVar6;
          *(undefined2 *)(param_1 + 0x1f) = uVar6;
        }
        else {
          *(undefined2 *)(param_1 + 0x1c) = uVar6;
          *(undefined2 *)(param_1 + 0x1d) = uVar6;
        }
      }
    }
    else {
      if (0x80 < (int)param_2) {
        param_2 = 0x100 - param_2;
      }
      sVar1 = *(short *)(&DAT_8021ddce + param_2 * 2);
      sVar2 = *(short *)(&DAT_8021ddce + (param_2 ^ 0x7f) * 2);
      if ((param_1[0x25] & 0x400U) != 0) {
        *puVar7 = (ushort)((uint)(param_3 * sVar1) >> 8);
      }
      if ((param_1[0x25] & 0x800U) != 0) {
        *(short *)(param_1 + 0x1b) = (short)((uint)(param_3 * sVar2) >> 8);
      }
      if ((param_1[0x25] & 0x1000U) != 0) {
        uVar6 = (undefined2)((param_3 * sVar1 >> 8) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1) >> 0xf);
        if ((param_1[0x25] & 2U) == 0) {
          *(undefined2 *)(param_1 + 0x1e) = uVar6;
        }
        else {
          *(undefined2 *)(param_1 + 0x1c) = uVar6;
        }
      }
      if ((param_1[0x25] & 0x2000U) != 0) {
        uVar6 = (undefined2)((param_3 * sVar2 >> 8) * ((*(int *)(iVar4 + 0x68) >> 0xc) + 1) >> 0xf);
        if ((param_1[0x25] & 2U) == 0) {
          *(undefined2 *)(param_1 + 0x1f) = uVar6;
        }
        else {
          *(undefined2 *)(param_1 + 0x1d) = uVar6;
        }
      }
    }
    param_1[0x24] = param_1[0x24] | 8;
  }
  return;
}

