// Function: Quit__8CFontManFv
// Entry: 80092ef8
// Size: 120 bytes

void Quit__8CFontManFv(CFontMan *fontMan)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)&fontMan->field_0x8;
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&fontMan->field_0x8 = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&fontMan->field_0x4);
  return;
}

