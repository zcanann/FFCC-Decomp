// Function: InsertOctTree__9CLightPcsFQ29CLightPcs6TARGETR8COctTree
// Entry: 80048cbc
// Size: 128 bytes

void InsertOctTree__9CLightPcsFQ29CLightPcs6TARGETR8COctTree
               (int param_1,int param_2,COctTree *octTree)

{
  uint uVar1;
  int iVar2;
  
  ClearLight__8COctTreeFv(octTree);
  iVar2 = param_1 + 0x63c;
  for (uVar1 = 0; uVar1 < *(uint *)(param_1 + 0xb8); uVar1 = uVar1 + 1) {
    if (*(char *)(param_2 + iVar2 + 0x60) != '\0') {
      InsertLight__8COctTreeFlR3VecfUl
                ((double)*(float *)(iVar2 + 0x24),octTree,uVar1,iVar2 + 4,
                 *(undefined4 *)(iVar2 + 0x34));
    }
    iVar2 = iVar2 + 0xb0;
  }
  return;
}

