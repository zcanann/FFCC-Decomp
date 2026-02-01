// Function: Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
// Entry: 800bf620
// Size: 660 bytes

/* WARNING: Removing unreachable block (ram,0x800bf898) */
/* WARNING: Removing unreachable block (ram,0x800bf84c) */
/* WARNING: Removing unreachable block (ram,0x800bf864) */
/* WARNING: Removing unreachable block (ram,0x800bf860) */
/* WARNING: Removing unreachable block (ram,0x800bf7e4) */
/* WARNING: Removing unreachable block (ram,0x800bf7fc) */
/* WARNING: Removing unreachable block (ram,0x800bf7f8) */
/* WARNING: Removing unreachable block (ram,0x800bf77c) */
/* WARNING: Removing unreachable block (ram,0x800bf794) */
/* WARNING: Removing unreachable block (ram,0x800bf790) */
/* WARNING: Removing unreachable block (ram,0x800bf630) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Interp__Q26CChara9CAnimNodeFPQ26CChara5CAnimP3SRTf
               (double param_1,int param_2,int param_3,float *param_4)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  undefined4 uVar6;
  int iVar7;
  float *pfVar8;
  uint uVar9;
  int iVar10;
  
  if (*(int *)(param_3 + 0x20) == 0) {
    do {
      if (*(int *)(param_3 + 0x20) != 0) {
LAB_800bf6bc:
        SetGroup__7CMemoryFPvi(&Memory,*(undefined4 *)(param_3 + 0x20),1);
        CopyFromAMemorySync__7CMemoryFPvPvUl
                  (&Memory,*(undefined4 *)(param_3 + 0x20),
                   *(int *)(param_3 + 0x28) + *(int *)(Chara._8284_4_ + 8),
                   *(undefined4 *)(param_3 + 0x1c));
        goto LAB_800bf6fc;
      }
      uVar6 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,*(undefined4 *)(param_3 + 0x1c),*(undefined4 *)(param_3 + 0x2c),
                         s_chara_anim_cpp_801da980,0x160,1);
      *(undefined4 *)(param_3 + 0x20) = uVar6;
      if (*(int *)(param_3 + 0x20) != 0) goto LAB_800bf6bc;
      iVar7 = TryReleaseAnimBank__9CCharaPcsFi(&CharaPcs,*(undefined4 *)(param_3 + 0x1c));
    } while (iVar7 != 0);
  }
  else {
LAB_800bf6fc:
    dVar5 = DOUBLE_80330c70;
    uVar1 = (uint)param_1;
    *(undefined4 *)(param_3 + 0x24) = 0;
    fVar3 = FLOAT_80330c68;
    fVar4 = (float)(param_1 -
                   (double)(float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - dVar5));
    if (uVar1 == *(ushort *)(param_3 + 0x10) - 1) {
      fVar4 = FLOAT_80330c68;
    }
    uVar9 = *(uint *)(param_2 + 0x14) >> 0xd & 0x3ffff;
    iVar7 = uVar1 * 2;
    pfVar8 = (float *)(*(int *)(param_2 + 0x10) + *(int *)(param_3 + 0x20));
    iVar10 = 3;
    do {
      if ((uVar9 & 3) == 0) {
        *param_4 = fVar3;
      }
      else if ((uVar9 & 3) == 1) {
        fVar2 = *pfVar8;
        pfVar8 = (float *)((int)pfVar8 + 2);
        *param_4 = fVar2;
      }
      else {
        fVar2 = *(float *)((int)pfVar8 + iVar7);
        *param_4 = (*(float *)((int)pfVar8 + iVar7 + 2) - fVar2) * fVar4 + fVar2;
        pfVar8 = (float *)((int)pfVar8 + (*(ushort *)(param_3 + 0x10) + 1) * 2);
      }
      fVar2 = FLOAT_80330c68;
      uVar9 = (int)uVar9 >> 2;
      param_4 = param_4 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    iVar10 = 3;
    do {
      if ((uVar9 & 3) == 0) {
        *param_4 = fVar2;
      }
      else if ((uVar9 & 3) == 1) {
        fVar3 = *pfVar8;
        pfVar8 = (float *)((int)pfVar8 + 2);
        *param_4 = fVar3;
      }
      else {
        fVar3 = *(float *)((int)pfVar8 + iVar7);
        *param_4 = (*(float *)((int)pfVar8 + iVar7 + 2) - fVar3) * fVar4 + fVar3;
        pfVar8 = (float *)((int)pfVar8 + (*(ushort *)(param_3 + 0x10) + 1) * 2);
      }
      fVar3 = FLOAT_80330c6c;
      uVar9 = (int)uVar9 >> 2;
      param_4 = param_4 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    iVar10 = 3;
    do {
      if ((uVar9 & 3) == 0) {
        *param_4 = fVar3;
      }
      else if ((uVar9 & 3) == 1) {
        fVar2 = *pfVar8;
        pfVar8 = (float *)((int)pfVar8 + 2);
        *param_4 = fVar2;
      }
      else {
        fVar2 = *(float *)((int)pfVar8 + iVar7);
        *param_4 = (*(float *)((int)pfVar8 + iVar7 + 2) - fVar2) * fVar4 + fVar2;
        pfVar8 = (float *)((int)pfVar8 + (*(ushort *)(param_3 + 0x10) + 1) * 2);
      }
      uVar9 = (int)uVar9 >> 2;
      param_4 = param_4 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  return;
}

