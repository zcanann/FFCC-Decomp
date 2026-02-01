// Function: TimeMogFur__6CCharaFv
// Entry: 800df618
// Size: 480 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void TimeMogFur__6CCharaFv(CChara *chara)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  
  if (*(int *)&chara->field_0x2014 + 0x1a5e0 < (int)System.m_frameCounter) {
    *(uint32_t *)&chara->field_0x2014 = System.m_frameCounter;
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_803310e8);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801db6b4);
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_803310e8);
    }
  }
  memset(&chara->field_0x2018,0,0x40);
  uVar4 = 0;
  do {
    iVar3 = (int)uVar4 >> 0x1f;
    uVar5 = 0;
    iVar12 = 0x40;
    do {
      iVar2 = (int)uVar5 >> 0x1f;
      iVar2 = (((iVar2 * 4 | uVar5 * 0x40000000 + iVar2 >> 0x1e) - iVar2) +
              ((iVar3 * 4 | uVar4 * 0x40000000 + iVar3 >> 0x1e) - iVar3) * 4 +
              (((int)uVar5 >> 2) + (uint)((int)uVar5 < 0 && (uVar5 & 3) != 0)) * 0x10 +
              (((int)uVar4 >> 2) + (uint)((int)uVar4 < 0 && (uVar4 & 3) != 0)) * 0x100) * 2;
      uVar1 = *(ushort *)((int)chara + iVar2 + 4);
      uVar10 = uVar1 >> 0xc & 7;
      iVar11 = 7 - uVar10;
      iVar6 = iVar11 + (uVar1 >> 8 & 0xf) + 4;
      iVar8 = iVar11 + (uVar1 & 0xf) + 4;
      iVar9 = iVar11 + (uVar1 >> 4 & 0xf) + 4;
      iVar11 = 0xf;
      if (iVar6 < 0xf) {
        iVar11 = iVar6;
      }
      iVar6 = 0xf;
      if (iVar9 < 0xf) {
        iVar6 = iVar9;
      }
      iVar9 = 0xf;
      if (iVar8 < 0xf) {
        iVar9 = iVar8;
      }
      uVar10 = uVar10 + 2;
      uVar7 = 7;
      if (uVar10 < 7) {
        uVar7 = uVar10;
      }
      uVar5 = uVar5 + 1;
      *(ushort *)((int)chara + iVar2 + 4) =
           (ushort)iVar9 | (ushort)(iVar6 << 4) | (ushort)(uVar7 << 0xc) | (ushort)(iVar11 << 8);
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x40);
  CalcMogScore__6CCharaFv(chara);
  return;
}

