// Function: ?aiSeq__8CGMonObjFiiiiii
// Entry: 801145d0
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
_aiSeq__8CGMonObjFiiiiii
          (CGMonObj *gMonObj,undefined4 param_2,int param_3,int param_4,int param_5,uint param_6,
          int param_7)

{
  uint uVar1;
  
  if (((int)SoundBuffer._1248_4_ < param_3) && (param_4 == *(int *)&gMonObj->field_0x6c8)) {
    uVar1 = Rand__5CMathFUl(&Math,100);
    if (uVar1 <= param_6) {
      if ((int)SoundBuffer._1248_4_ < param_3) {
        SoundBuffer._1248_4_ = param_3;
        SoundBuffer._1252_4_ = param_2;
      }
      *(int *)&gMonObj->field_0x6c8 = param_5;
      return 1;
    }
    if (-1 < param_7) {
      *(int *)&gMonObj->field_0x6c8 = param_7;
    }
  }
  return 0;
}

