// Function: frameStatFuncSaw__8CGMonObjFv
// Entry: 80131dd8
// Size: 560 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncSaw__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CRef *pCVar2;
  
  if (*(int *)&gMonObj->field_0x520 == 100) {
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    iVar1 = *(int *)&gMonObj->field_0x52c;
    if (iVar1 == 0) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,10,0,0);
        pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar2 == (CRef *)0x0) {
          iVar1 = -1;
        }
        else {
          iVar1 = pCVar2[2].refCount;
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8,
                   *(int *)&gMonObj->field_0x564,&gMonObj->gObject,0x1c52c);
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1c52b,0x32,0x96,0,0);
        memset(&gMonObj->field_0x70c,0,0x34);
        *(undefined4 *)&gMonObj->field_0x70c = 0x1402;
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
        }
      }
    }
    else if (iVar1 == 1) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        *(undefined4 *)&gMonObj->field_0x560 = 0x495;
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,1,1,0);
      }
      if (*(int *)&gMonObj->field_0x530 == 0x19) {
        resetIgnoreHit__10CGCharaObjFv(gMonObj);
        (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,1,0,0);
        gMonObj->field_0x6c0 = 0;
      }
      if ((0x19 < *(int *)&gMonObj->field_0x530) && (gMonObj->field_0x6c0 != '\0')) {
        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
      }
    }
    else if (iVar1 == 2) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,0,0,0);
        gMonObj->field_0x6c0 = 0;
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xb,0,0);
        endPSlotBit__10CGCharaObjFi(gMonObj,1);
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1c52d,0x32,0x96,0,0);
      }
      else {
        iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar1 != 0) {
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
        }
      }
    }
    moveFrame__8CGMonObjFv(gMonObj);
  }
  return;
}

