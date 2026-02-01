// Function: SetTexAnim__8CGObjectFPc
// Entry: 8007ce04
// Size: 96 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetTexAnim__8CGObjectFPc(CGObject *gObject,undefined4 param_2)

{
  bool bVar1;
  CTexAnimSet *texAnimSet;
  CCharaPcsCHandle *pCVar2;
  
  pCVar2 = gObject->m_charaModelHandle;
  bVar1 = false;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if ((bVar1) && (texAnimSet = pCVar2->m_model->m_texAnimSet, texAnimSet != (CTexAnimSet *)0x0)) {
    Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE
              ((double)FLOAT_80330350,texAnimSet,param_2,0xfffffffe);
  }
  return;
}

