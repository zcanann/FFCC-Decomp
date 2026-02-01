// Function: CheckMenu__10CGPartyObjFv
// Entry: 801233ec
// Size: 104 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CheckMenu__10CGPartyObjFv(void)

{
  CGPartyObj *partyObj;
  int iVar1;
  int iVar2;
  
  iVar2 = -0x7fde1140;
  iVar1 = 0;
  do {
    partyObj = *(CGPartyObj **)(iVar2 + 0xc5b0);
    if ((partyObj != (CGPartyObj *)0x0) &&
       ((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle != (void **)0x0)) {
      menu__10CGPartyObjFv(partyObj);
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 4);
  return;
}

