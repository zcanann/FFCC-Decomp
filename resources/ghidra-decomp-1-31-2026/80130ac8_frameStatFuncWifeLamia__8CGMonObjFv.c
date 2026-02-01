// Function: frameStatFuncWifeLamia__8CGMonObjFv
// Entry: 80130ac8
// Size: 300 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncWifeLamia__8CGMonObjFv(CGMonObj *gMonObj)

{
  float fVar1;
  float y;
  int iVar2;
  undefined4 *puVar3;
  CVector CStack_18;
  
  if (*(int *)&gMonObj->field_0x520 == 100) {
    iVar2 = *(int *)&gMonObj->field_0x52c;
    if (iVar2 == 0) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        memset(&gMonObj->field_0x70c,0,0x34);
        y = FLOAT_80331d70;
        fVar1 = FLOAT_80331d6c;
        *(undefined4 *)&gMonObj->field_0x70c = 0x10022;
        puVar3 = (undefined4 *)__ct__7CVectorFfff(fVar1,y,FLOAT_80331d74,&CStack_18);
        fVar1 = FLOAT_80331d78;
        *(undefined4 *)&gMonObj->field_0x718 = *puVar3;
        *(undefined4 *)&gMonObj->field_0x71c = puVar3[1];
        *(undefined4 *)&gMonObj->field_0x720 = puVar3[2];
        *(float *)&gMonObj->field_0x724 = fVar1;
        *(float *)&gMonObj->field_0x728 = (gMonObj->gObject).m_bodyEllipsoidRadius;
      }
      moveFrame__8CGMonObjFv(gMonObj);
      if ((*(uint *)&gMonObj->field_0x710 & 1) != 0) {
        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
      }
    }
    else if (iVar2 == 1) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x1a,0,0);
      }
      else {
        iVar2 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar2 != 0) {
          addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
        }
      }
    }
    else if ((iVar2 == 2) && (*(int *)&gMonObj->field_0x530 == 0)) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x1b,1,0);
    }
  }
  return;
}

