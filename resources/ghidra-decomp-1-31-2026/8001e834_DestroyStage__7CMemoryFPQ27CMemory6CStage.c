// Function: DestroyStage__7CMemoryFPQ27CMemory6CStage
// Entry: 8001e834
// Size: 404 bytes

/* WARNING: Possible PIC construction at 0x8001e9c4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x8001e9c4) */

void DestroyStage__7CMemoryFPQ27CMemory6CStage(CMemory *memory,CStage *stage)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = stage->m_allocationMode * 0x27d8;
  if (stage->m_allocationMode != 2) {
    bVar1 = false;
    iVar2 = *(int *)(stage->field269_0x110 + 8);
    while( true ) {
      if ((*(byte *)(iVar2 + 2) & 2) != 0) break;
      if ((*(byte *)(iVar2 + 2) & 4) != 0) {
        bVar1 = true;
      }
      iVar2 = *(int *)(iVar2 + 8);
    }
    if (bVar1) {
      Printf__7CSystemFPce(&System,&DAT_801d6a7c,&stage->m_allocationSourceStr);
      heapWalker__Q27CMemory6CStageFiPvUl(stage,0xffffffff,0,0xffffffff);
    }
    goto LAB_8001e9dc;
  }
  iVar2 = stage->field269_0x110;
  if (iVar2 == 0) goto LAB_8001e9dc;
  if ((iVar2 != 0) && (iVar2 != 0x10)) {
    if (*(short *)(iVar2 + -0x50) == 0x4b41) {
      if (*(short *)(iVar2 + -0x12) != 0x4d49) goto LAB_8001e90c;
    }
    else {
LAB_8001e90c:
      Printf__7CSystemFPce
                (&System,&DAT_801d6648,iVar2 + -0x10,iVar2 + -0x36,*(undefined2 *)(iVar2 + -0x38));
    }
    *(byte *)(iVar2 + -0x4e) = *(byte *)(iVar2 + -0x4e) & 0xfb;
    if ((*(byte *)(*(int *)(iVar2 + -0x48) + 2) & 4) == 0) {
      *(int *)(iVar2 + -0x40) =
           *(int *)(*(int *)(iVar2 + -0x48) + 0x10) + *(int *)(iVar2 + -0x40) + 0x40;
      *(int *)(*(int *)(*(int *)(iVar2 + -0x48) + 8) + 4) = iVar2 + -0x50;
      *(undefined4 *)(iVar2 + -0x48) = *(undefined4 *)(*(int *)(iVar2 + -0x48) + 8);
    }
    iVar4 = *(int *)(iVar2 + -0x4c);
    if ((*(byte *)(iVar4 + 2) & 4) == 0) {
      *(int *)(iVar4 + 0x10) = *(int *)(iVar2 + -0x40) + *(int *)(iVar4 + 0x10) + 0x40;
      *(undefined4 *)(*(int *)(iVar2 + -0x4c) + 8) = *(undefined4 *)(iVar2 + -0x48);
      *(undefined4 *)(*(int *)(iVar2 + -0x48) + 4) = *(undefined4 *)(iVar2 + -0x4c);
    }
    *(int *)(*(int *)(iVar2 + -0x44) + 0x124) = *(int *)(*(int *)(iVar2 + -0x44) + 0x124) + -1;
  }
  stage->field269_0x110 = 0;
LAB_8001e9dc:
  *(undefined4 *)(*(int *)stage + 4) = *(undefined4 *)&stage->field_0x4;
  **(undefined4 **)&stage->field_0x4 = *(undefined4 *)stage;
  *(undefined4 *)&stage->field_0x4 = *(undefined4 *)(&memory->field_0x134 + iVar3);
  *(CStage **)(&memory->field_0x134 + iVar3) = stage;
  return;
}

