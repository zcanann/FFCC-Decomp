// Function: onStatShield__10CGPartyObjFv
// Entry: 8011f9dc
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatShield__10CGPartyObjFv(CGPrgObj *param_1)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  
  if (param_1->m_subState == 1) {
    bVar1 = false;
    uVar3 = (uint)(char)(param_1->object).m_animStateMisc;
    if ((Pad._452_4_ != 0) || ((uVar3 == 0 && (Pad._448_4_ != -1)))) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar2 = 0;
    }
    else {
      uVar2 = *(ushort *)
               (&Pad.field_0x4 +
               (uVar3 & ~((int)~(Pad._448_4_ - uVar3 | uVar3 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar2 & 0x100) == 0) {
      changeSubStat__8CGPrgObjFi(param_1,3);
    }
    return;
  }
  return;
}

