// Function: GetTexShadow__9CCharaPcsFiiP9_GXTexObjP3VecPA3_A4_f
// Entry: 80079494
// Size: 252 bytes

void GetTexShadow__9CCharaPcsFiiP9_GXTexObjP3VecPA3_A4_f
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Mtx MStack_58;
  
  iVar4 = 0;
  iVar5 = *(int *)(*(int *)(param_1 + 0x4c) + 0x160);
  do {
    if (*(int *)(param_1 + 0x4c) == iVar5) {
      return;
    }
    if (((*(uint *)(iVar5 + 8) & 0x200) != 0) && (*(int *)(iVar5 + 0x120) != 0)) {
      if (param_2 <= iVar4) {
        iVar3 = iVar4 - param_2;
        PSMTXConcat((Mtx *)(param_1 + 0x14c),(Mtx *)(iVar5 + 0x124),(Mtx *)(param_6 + iVar3 * 0x30))
        ;
        uVar1 = *(uint *)(param_1 + 0x44) & 0xffff;
        GXInitTexObj(param_4 + iVar3 * 0x20,*(undefined4 *)(iVar5 + 0x120),uVar1,uVar1,0,0,0,0);
        PSMTXCopy((Mtx *)(*(int *)(iVar5 + 0x168) + 8),&MStack_58);
        pfVar2 = (float *)(param_5 + iVar3 * 0xc);
        *pfVar2 = MStack_58.value[0][3];
        pfVar2[1] = MStack_58.value[1][3];
        pfVar2[2] = MStack_58.value[2][3];
      }
      iVar4 = iVar4 + 1;
      if (param_2 + param_3 <= iVar4) {
        return;
      }
    }
    iVar5 = *(int *)(iVar5 + 0x160);
  } while( true );
}

