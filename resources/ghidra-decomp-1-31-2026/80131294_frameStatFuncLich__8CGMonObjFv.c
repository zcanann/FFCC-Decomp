// Function: frameStatFuncLich__8CGMonObjFv
// Entry: 80131294
// Size: 652 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncLich__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CRef *pCVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  if (((CFlat._4840_4_ & 1) == 0) && ((int)((uint)SoundBuffer[0x4fc] << 0x18) < 0)) {
    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0x3f | 0x40;
    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1157c,0x32,0x96,0,0);
  }
  else if (((CFlat._4840_4_ & 1) != 0) && (-1 < (int)((uint)SoundBuffer[0x4fc] << 0x18))) {
    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0x3f | 0xc0;
    *(undefined4 *)&gMonObj->field_0x6c8 = 0;
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x1157d,0x32,0x96,0,0);
  }
  if ((int)((uint)SoundBuffer[0x4fc] << 0x19 | (uint)(SoundBuffer[0x4fc] >> 7)) < 0) {
    endPSlotBit__10CGCharaObjFi(gMonObj,0x800);
    if ((int)((uint)SoundBuffer[0x4fc] << 0x18) < 0) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1d,
                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0);
    }
    SoundBuffer[0x4fc] = SoundBuffer[0x4fc] & 0xbf;
  }
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 0x65) {
    if ((*(int *)&gMonObj->field_0x528 == 0) && (CFlat._4840_4_ == 3)) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    else {
      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
      if (*(int *)&gMonObj->field_0x528 == 0x29) {
        local_20 = 10;
        local_1c = 1;
        local_18 = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,9,3,&local_20,(CStack *)0x0);
      }
    }
  }
  else if ((iVar1 < 0x65) && (99 < iVar1)) {
    teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec
              (gMonObj,1,0xe,0x29,100,0x11578,0x11579,0x2d,0x2b,0x2c,&DAT_802127f0,0x8030014c,
               0x80300150);
  }
  return;
}

