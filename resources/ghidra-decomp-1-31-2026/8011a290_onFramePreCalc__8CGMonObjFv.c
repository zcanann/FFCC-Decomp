// Function: onFramePreCalc__8CGMonObjFv
// Entry: 8011a290
// Size: 540 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFramePreCalc__8CGMonObjFv(CGMonObj *gMonObj)

{
  void *pvVar1;
  undefined2 uVar3;
  void **ppvVar2;
  undefined4 local_18 [5];
  
  onFramePreCalc__10CGCharaObjFv();
  *(int *)&gMonObj->field_0x6f4 = *(int *)&gMonObj->field_0x6f4 + 1;
  pvVar1 = (gMonObj->gObject).m_scriptHandle[9];
  if (*(short *)((int)pvVar1 + 0x10c) == 1) {
    if (*(short *)&gMonObj->field_0x6e4 != 0) {
      pvVar1 = (void *)(Game.game.unkCFlatData0[1] +
                       ((int)*(short *)&gMonObj->field_0x6e4 +
                       (uint)*(ushort *)((int)pvVar1 + 0x100)) * 0x1d0 + 0x10);
    }
    uVar3 = __ptmf_scall(gMonObj,*(ushort *)((int)pvVar1 + 0x102) & 3,
                         *(undefined4 *)&gMonObj->field_0x708);
    *(undefined2 *)&gMonObj->field_0x6e4 = uVar3;
    if (*(short *)&gMonObj->field_0x6e4 != *(short *)&gMonObj->field_0x6e6) {
      *(short *)&gMonObj->field_0x6e6 = *(short *)&gMonObj->field_0x6e4;
      *(undefined4 *)&gMonObj->field_0x6cc = 0;
    }
  }
  ppvVar2 = (gMonObj->gObject).m_scriptHandle;
  if (((((*(short *)((int)ppvVar2 + 0x3e) == 0) && (*(short *)(ppvVar2 + 0x14) == 0)) &&
       (*(short *)(ppvVar2 + 0x11) == 0)) &&
      ((*(short *)((int)ppvVar2 + 0x46) == 0 &&
       ((int)((uint)(byte)gMonObj->field_0x63c << 0x18) < 0)))) &&
     ((gMonObj->field_0x6b9 == '\0' && (gMonObj->field_0x6c1 == '\0')))) {
    if (*(short *)((int)ppvVar2[9] + 0x10c) == 1) {
      SoundBuffer._1252_4_ = 0xffffffff;
    }
    else {
      SoundBuffer._1252_4_ = 0;
    }
    SoundBuffer._1256_4_ = *(undefined4 *)&gMonObj->field_0x6c4;
    SoundBuffer._1248_4_ = 0xffffffff;
    pvVar1 = (gMonObj->gObject).m_scriptHandle[4];
    local_18[0] = 0;
    if (((int)pvVar1 < 0x9a) && (0x8d < (int)pvVar1)) {
      aiAddDuct__8CGMonObjFRi(gMonObj,(int)local_18);
    }
    else {
      __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
    }
    if (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x10c) == 1) {
      if ((SoundBuffer._1252_4_ != -1) && (SoundBuffer._1252_4_ != *(int *)&gMonObj->field_0x520)) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,SoundBuffer._1252_4_,0,0);
      }
    }
    else if (SoundBuffer._1252_4_ != *(int *)&gMonObj->field_0x520) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,SoundBuffer._1252_4_,0,0);
    }
  }
  return;
}

