// Function: GetButtonRepeat__8CMenuPcsFi
// Entry: 80095e70
// Size: 116 bytes

undefined2 GetButtonRepeat__8CMenuPcsFi(CMenuPcs *menuPcs,uint param_2)

{
  bool bVar1;
  undefined2 uVar2;
  
  bVar1 = false;
  if (Pad._452_4_ == 0) {
    if (param_2 != 0) goto LAB_80095ea0;
    if (Pad._448_4_ == -1) goto LAB_80095ea0;
  }
  bVar1 = true;
LAB_80095ea0:
  if (bVar1) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined2 *)
             (&Pad.field_0x14 +
             (param_2 & ~((int)~(Pad._448_4_ - param_2 | param_2 - Pad._448_4_) >> 0x1f)) * 0x54);
  }
  return uVar2;
}

