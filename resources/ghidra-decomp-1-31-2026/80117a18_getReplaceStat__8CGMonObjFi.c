// Function: getReplaceStat__8CGMonObjFi
// Entry: 80117a18
// Size: 240 bytes

/* WARNING: Removing unreachable block (ram,0x80117abc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int getReplaceStat__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  ushort uVar1;
  
  if (param_2 == 3) {
LAB_80117a5c:
    if (*(int *)&gMonObj->field_0x520 == param_2) {
      param_2 = -1;
    }
  }
  else {
    if (param_2 < 3) {
      if (param_2 == 0) goto LAB_80117a5c;
      if (((param_2 < 0) && (param_2 < -4)) && (-0xf < param_2)) {
        uVar1 = *(ushort *)
                 (Game.game.unkCFlatData0[2] +
                  (uint)*(ushort *)
                         ((int)(gMonObj->gObject).m_scriptHandle + (param_2 + 0xe) * 2 + 0xd0) *
                  0x48 + 0xe);
        if (uVar1 == 3) {
          return 0x12;
        }
        if (uVar1 < 3) {
          if (uVar1 < 2) {
            return 1;
          }
          return 2;
        }
        if (4 < uVar1) {
          return param_2;
        }
        return 8;
      }
    }
    else if (param_2 == 0x1c) goto LAB_80117a5c;
    param_2 = getReplaceStat__10CGCharaObjFi();
  }
  return param_2;
}

