// Function: alwaysFuncOrcKing__8CGMonObjFv
// Entry: 80132160
// Size: 380 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void alwaysFuncOrcKing__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CRef *pCVar2;
  CGMonObj *monObj;
  
  if (SoundBuffer._1260_4_ != 0) {
    if (SoundBuffer._1264_4_ == 0x3c) {
      ChangeTexture__Q29CCharaPcs7CHandleFiUlUlii
                ((gMonObj->gObject).m_charaModelHandle,1,0x39,1,0xffffffff,0);
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
    else if ((SoundBuffer._1264_4_ == 300) && (Game.game.m_gameWork.m_gameOverFlag == '\0')) {
      for (monObj = (CGMonObj *)FindGMonObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          monObj != (CGMonObj *)0x0;
          monObj = (CGMonObj *)
                   FindGMonObjNext__13CFlatRuntime2FP8CGMonObj((CFlatRuntime2 *)&CFlat,monObj)) {
        addHp__10CGCharaObjFiP8CGPrgObj
                  ((CGCharaObj *)monObj,
                   -(uint)*(ushort *)((int)(monObj->gObject).m_scriptHandle + 0x1a),(CGPrgObj *)0x0)
        ;
      }
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x8cbf,0x32,0x96,0,0);
      SoundBuffer._1260_4_ = 0;
      CFlat._4840_4_ = 1;
    }
    if (SoundBuffer._1260_4_ != 0) {
      SoundBuffer._1264_4_ = SoundBuffer._1264_4_ + 1;
    }
  }
  return;
}

