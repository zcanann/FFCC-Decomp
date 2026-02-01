// Function: aiTargetAttackRomMon__8CGMonObjFi
// Entry: 80117044
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void aiTargetAttackRomMon__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  int iVar1;
  
  iVar1 = getNearParty__8CGMonObjFiiffi
                    ((double)FLOAT_803319d8,(double)FLOAT_803319d8,gMonObj,0xffffffff,0x47,param_2);
  if (-1 < iVar1) {
    *(int *)&gMonObj->field_0x6c4 = iVar1;
  }
  return;
}

