// Function: playSe3D__8CGPrgObjFiiiiP3Vec
// Entry: 80127650
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
playSe3D__8CGPrgObjFiiiiP3Vec
          (CGPrgObj *gPrgObj,int param_2,uint param_3,uint param_4,int param_5,Vec *param_6)

{
  undefined4 uVar1;
  
  if ((param_2 == 0) || (param_2 == 0xffff)) {
    uVar1 = 0xffffffff;
  }
  else {
    if (param_6 == (Vec *)0x0) {
      param_6 = &(gPrgObj->object).m_worldPosition;
    }
    uVar1 = PlaySe3D__6CSoundFiP3Vecffi
                      ((double)(float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) -
                                      DOUBLE_80331be0),
                       (double)(float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) -
                                      DOUBLE_80331be0),&Sound,param_2,param_6,0);
    if (param_5 != 0) {
      ChangeSe3DPitch__6CSoundFiii(&Sound,uVar1,param_5,0);
    }
  }
  return uVar1;
}

