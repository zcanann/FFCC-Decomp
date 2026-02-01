// Function: Init__4CPadFv
// Entry: 80021008
// Size: 416 bytes

void Init__4CPadFv(int param_1)

{
  int iVar1;
  CStage *pCVar2;
  undefined4 uVar3;
  
  PADInit();
  memset(param_1 + 4,0,0x1a4);
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  *(undefined4 *)(param_1 + 0x1ac) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c8) = 1;
  iVar1 = IsGdev__7CSystemFv(&System);
  if (iVar1 != 0) {
    pCVar2 = CreateStage__7CMemoryFUlPci(&Memory,0x800000,&DAT_8032f818,1);
    *(CStage **)(param_1 + 0x1ac) = pCVar2;
    if (*(int *)(param_1 + 0x1ac) != 0) {
      uVar3 = __nwa__FUlPQ27CMemory6CStagePci(0x69780c,*(int *)(param_1 + 0x1ac),&DAT_8032f840,0x54)
      ;
      *(undefined4 *)(param_1 + 0x1b0) = uVar3;
      if ((*(int *)(param_1 + 0x1b4) == 0) ||
         (iVar1 = fopen(s__replay_dat_801d6d34,&DAT_8032f848), iVar1 == 0)) {
        **(undefined4 **)(param_1 + 0x1b0) = 0xc;
        *(undefined4 *)(*(int *)(param_1 + 0x1b0) + 8) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x1b0) + 4) = 1;
      }
      else {
        fseek(iVar1,0,2);
        uVar3 = ftell(iVar1);
        fseek(iVar1,0,0);
        fread(*(undefined4 *)(param_1 + 0x1b0),1,uVar3,iVar1);
        fclose(iVar1);
        *(undefined4 *)(*(int *)(param_1 + 0x1b0) + 4) = 0;
        iVar1 = *(int *)(*(int *)(param_1 + 0x1b0) + 8);
        iVar1 = iVar1 / 0x1e + (iVar1 >> 0x1f);
        Printf__7CSystemFPce(&System,&DAT_801d6d40,iVar1 - (iVar1 >> 0x1f));
      }
    }
  }
  return;
}

