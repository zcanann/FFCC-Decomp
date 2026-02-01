// Function: frameStatFuncGiantCrab__8CGMonObjFv
// Entry: 801329e8
// Size: 1168 bytes

/* WARNING: Removing unreachable block (ram,0x80132e58) */
/* WARNING: Removing unreachable block (ram,0x801329f8) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncGiantCrab__8CGMonObjFv(CGMonObj *gMonObj,undefined4 param_2)

{
  void *pvVar1;
  int iVar2;
  CRef *pCVar3;
  CGPartyObj *pCVar4;
  double dVar5;
  double in_f31;
  
  iVar2 = *(int *)&gMonObj->field_0x520;
  if (iVar2 == 100) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      if (SoundBuffer._1264_4_ == 2) {
        SoundBuffer._1268_4_ = FLOAT_80331dd0;
        SoundBuffer._1272_4_ = FLOAT_80331cf8;
        SoundBuffer._1276_4_ = FLOAT_80331dcc;
      }
      else if ((int)SoundBuffer._1264_4_ < 2) {
        if (SoundBuffer._1264_4_ == 0) {
          SoundBuffer._1268_4_ = FLOAT_80331dc8;
          SoundBuffer._1272_4_ = FLOAT_80331cf8;
          SoundBuffer._1276_4_ = FLOAT_80331dcc;
        }
        else if (-1 < (int)SoundBuffer._1264_4_) {
          SoundBuffer._1268_4_ = FLOAT_80331dc8;
          SoundBuffer._1272_4_ = FLOAT_80331cf8;
          SoundBuffer._1276_4_ = FLOAT_80331dc8;
        }
      }
      else if ((int)SoundBuffer._1264_4_ < 4) {
        SoundBuffer._1268_4_ = FLOAT_80331dd0;
        SoundBuffer._1272_4_ = FLOAT_80331cf8;
        SoundBuffer._1276_4_ = FLOAT_80331dc8;
      }
      iVar2 = SoundBuffer._1264_4_ + 1 >> 0x1f;
      SoundBuffer._1264_4_ =
           (iVar2 * 4 | (uint)((SoundBuffer._1264_4_ + 1) * 0x40000000 + iVar2) >> 0x1e) - iVar2;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xc,0,0);
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 6,0,&gMonObj->gObject,0);
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 7,0,&gMonObj->gObject,0);
    }
    iVar2 = *(int *)&gMonObj->field_0x528;
    if (0x20 < iVar2) {
      if (iVar2 == 0x21) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x4e30,0x32,0x1c2,0,0);
      }
      else if (iVar2 == 0x32) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x4e35,0x32,0x1c2,0,0);
      }
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7fffd;
      dVar5 = (double)PSVECDistance((Vec *)(SoundBuffer + 0x4f4),&(gMonObj->gObject).m_worldPosition
                                   );
      Move__8CGObjectFP3Vecfiiiii
                ((double)(float)(dVar5 * (double)FLOAT_80331dd4),&gMonObj->gObject,0x80300154,0x10,1
                 ,0,0,0);
      if (-1 < *(int *)&gMonObj->field_0x6c4) {
        pCVar4 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
        dVar5 = (double)atan2((double)((pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.x -
                                      (gMonObj->gObject).m_worldPosition.x),
                              (double)(*(float *)((int)&(pCVar4->gCharaObj).gPrgObj.object.
                                                        m_worldPosition + 8) -
                                      (gMonObj->gObject).m_worldPosition.z));
        (gMonObj->gObject).m_rotTargetY = (float)dVar5;
      }
    }
    iVar2 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar2 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x80002;
    }
  }
  else if ((99 < iVar2) && (iVar2 < 0x69)) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      if (iVar2 == 0x67) {
        in_f31 = (double)FLOAT_80331d24;
        param_2 = 0x12;
      }
      else if (iVar2 < 0x67) {
        if (iVar2 == 0x65) {
          in_f31 = (double)FLOAT_80331cf8;
          param_2 = 1;
        }
        else if (100 < iVar2) {
          in_f31 = (double)FLOAT_80331d2c;
          param_2 = 1;
        }
      }
      else if (iVar2 < 0x69) {
        in_f31 = (double)FLOAT_80331dd8;
        param_2 = 0x13;
      }
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,param_2,0,0);
      moveVectorHRot__8CGObjectFfffi
                ((double)(float)((double)(gMonObj->gObject).m_rotTargetY + in_f31),
                 (double)FLOAT_80331cf8,
                 (double)(*(float *)&gMonObj->field_0x690 *
                         (FLOAT_80331d60 *
                          (float)((double)CONCAT44(0x43300000,
                                                   (uint)*(ushort *)
                                                          ((int)(gMonObj->gObject).m_scriptHandle[9]
                                                          + 0xd4)) - DOUBLE_80331dc0) +
                         FLOAT_80331db8)),&gMonObj->gObject,0x1e);
      if (-1 < *(int *)&gMonObj->field_0x6c4) {
        pCVar4 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
        dVar5 = (double)atan2((double)((pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.x -
                                      (gMonObj->gObject).m_worldPosition.x),
                              (double)(*(float *)((int)&(pCVar4->gCharaObj).gPrgObj.object.
                                                        m_worldPosition + 8) -
                                      (gMonObj->gObject).m_worldPosition.z));
        (gMonObj->gObject).m_rotTargetY = (float)dVar5;
      }
      pvVar1 = (gMonObj->gObject).m_scriptHandle[4];
      if (pvVar1 == (void *)0x63) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x8cab,0x32,0x1c2,0,0);
      }
      else if ((int)pvVar1 < 99) {
        if (pvVar1 == (void *)0x5b) {
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x4e2a,0x32,0x1c2,0,0);
        }
      }
      else if (pvVar1 == (void *)0x6b) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfdf3,0x32,0x1c2,0,0);
      }
    }
    if (*(int *)&gMonObj->field_0x528 == 0x19) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
  }
  return;
}

