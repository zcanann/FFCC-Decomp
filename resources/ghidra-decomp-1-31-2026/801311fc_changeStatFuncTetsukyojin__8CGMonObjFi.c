// Function: changeStatFuncTetsukyojin__8CGMonObjFi
// Entry: 801311fc
// Size: 128 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void changeStatFuncTetsukyojin__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  if (param_2 == 0x65) {
    setActionParam__8CGMonObjFi(gMonObj,0xfffffff2);
    SoundBuffer._1260_4_ = SoundBuffer._1260_4_ + 1;
  }
  else if (param_2 < 0x65) {
    if (param_2 == -0xd) {
      SoundBuffer._1260_4_ = SoundBuffer._1260_4_ + 1;
    }
  }
  else if (param_2 == 0x67) {
    setActionParam__8CGMonObjFi(gMonObj,0xfffffff4);
  }
  return;
}

