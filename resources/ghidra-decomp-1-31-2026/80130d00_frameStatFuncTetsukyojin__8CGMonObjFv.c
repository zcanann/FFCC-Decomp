// Function: frameStatFuncTetsukyojin__8CGMonObjFv
// Entry: 80130d00
// Size: 1184 bytes

/* WARNING: Removing unreachable block (ram,0x80131180) */
/* WARNING: Removing unreachable block (ram,0x80130d10) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncTetsukyojin__8CGMonObjFv(CGMonObj *gMonObj)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  CRef *pCVar6;
  double dVar7;
  double dVar8;
  Vec local_98;
  CVector CStack_8c;
  CVector local_80;
  CVector CStack_74;
  CVector local_68;
  CVector local_5c;
  CVector local_50;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  Vec local_38;
  longlong local_28;
  
  iVar4 = *(int *)&gMonObj->field_0x520;
  if (iVar4 == 0x66) {
    if ((int)CFlat._4840_4_ < 1) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    else {
      if ((gMonObj->_bossBranchRelated == 1) && (*(int *)&gMonObj->field_0x528 == 0)) {
        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff3fffd;
        gMonObj->_bossBranchRelated = 2;
        CFlat._4844_4_ = 1;
        local_44 = 10;
        local_40 = 0;
        local_3c = 0;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,9,3,&local_44,(CStack *)0x0);
      }
      if (CFlat._4844_4_ == 0) {
        gMonObj->_bossBranchRelated = 0;
        *(undefined4 *)&gMonObj->field_0x6c8 = 0;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
    }
  }
  else if (iVar4 < 0x66) {
    if (iVar4 == 100) {
      if (*(int *)&gMonObj->field_0x528 == 0) {
        __ct__7CVectorFRC3Vec
                  (&local_50,
                   &(Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).gPrgObj.
                    object.m_worldPosition);
        __ct__7CVectorFfff(-local_50.x,-local_50.y,-local_50.z,&local_5c);
        local_38.x = local_5c.x;
        local_38.z = local_5c.z;
        local_38.y = FLOAT_80331cf8;
        dVar7 = (double)PSVECMag(&local_38);
        if (dVar7 < (double)FLOAT_80331d7c) {
          __ct__7CVectorFfff(FLOAT_80331cf8,FLOAT_80331cf8,FLOAT_80331d80,&local_68);
          local_38.x = local_68.x;
          local_38.y = local_68.y;
          local_38.z = local_68.z;
        }
        PSVECNormalize(&local_38,&local_38);
        PSVECScale(FLOAT_80331d84 - (gMonObj->gObject).m_capsuleHalfHeight,&local_38,&local_38);
        SoundBuffer._1264_4_ = local_38.x;
        SoundBuffer._1268_4_ = local_38.y;
        SoundBuffer._1272_4_ = local_38.z;
        __ct__7CVectorFRC3Vec(&CStack_74,&(gMonObj->gObject).m_worldPosition);
        __ct__7CVectorFv(&local_98);
        PSVECSubtract(&local_38,(Vec *)&CStack_74,&local_98);
        local_38.x = local_98.x;
        local_38.y = local_98.y;
        local_38.z = local_98.z;
        dVar8 = (double)PSVECDistance(&local_38,&(gMonObj->gObject).m_worldPosition);
        dVar7 = (double)FLOAT_80331d88;
        if (dVar8 < (double)FLOAT_80331d88) {
          dVar7 = dVar8;
        }
        memset(&gMonObj->field_0x70c,0,0x34);
        dVar8 = (double)FLOAT_80331d30;
        *(undefined4 *)&gMonObj->field_0x70c = 0x2114;
        fVar1 = FLOAT_80331d58;
        *(float *)&gMonObj->field_0x718 = local_38.x;
        local_28 = (longlong)(int)(dVar7 * dVar8);
        *(float *)&gMonObj->field_0x71c = local_38.y;
        *(float *)&gMonObj->field_0x720 = local_38.z;
        *(float *)&gMonObj->field_0x724 = fVar1;
        *(int *)&gMonObj->field_0x72c = (int)(dVar7 * dVar8);
        *(undefined4 *)&gMonObj->field_0x738 = 0x67;
      }
      moveFrame__8CGMonObjFv(gMonObj);
    }
    else if (99 < iVar4) {
      if ((CFlat._4840_4_ != 0) && (*(int *)&gMonObj->field_0x528 == 0x25)) {
        if ((int)CFlat._4840_4_ < 1) {
          CFlat._4840_4_ = 0;
        }
        else if (((CFlat._4840_4_ == 1) && (0x13 < (int)SoundBuffer._1260_4_)) ||
                ((1 < (int)CFlat._4840_4_ && (4 < (int)SoundBuffer._1260_4_)))) {
          SoundBuffer._1260_4_ = 0;
          DispCharaParts__8CGObjectFi(&gMonObj->gObject,1);
          pCVar6 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
          if (pCVar6 == (CRef *)0x0) {
            iVar4 = -1;
          }
          else {
            iVar4 = pCVar6[2].refCount;
          }
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar4 << 8 | 0x2d,0,
                     &gMonObj->gObject,0x101e4);
          if (gMonObj->_bossBranchRelated == 0) {
            CFlat._4840_4_ = CFlat._4840_4_ + -1;
          }
          gMonObj->_bossBranchRelated = 1;
          *(undefined4 *)&gMonObj->field_0x6c8 = 0;
        }
      }
      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
    }
  }
  else if (iVar4 < 0x68) {
    if (*(int *)&gMonObj->field_0x528 == 0x10) {
      memset(&gMonObj->field_0x70c,0,0x34);
      *(undefined4 *)&gMonObj->field_0x70c = 0x2410;
      pfVar5 = (float *)__ct__7CVectorFRC3Vec(&CStack_8c,(Vec *)(SoundBuffer + 0x4f0));
      __ct__7CVectorFfff(-*pfVar5,-pfVar5[1],-pfVar5[2],&local_80);
      fVar2 = FLOAT_80331d78;
      *(float *)&gMonObj->field_0x718 = local_80.x;
      fVar3 = FLOAT_80331d84;
      fVar1 = FLOAT_80331d58;
      *(float *)&gMonObj->field_0x71c = local_80.y;
      *(float *)&gMonObj->field_0x720 = local_80.z;
      *(float *)&gMonObj->field_0x724 = fVar2;
      iVar4 = (int)((fVar1 * (fVar3 - (gMonObj->gObject).m_capsuleHalfHeight)) / fVar2);
      local_28 = (longlong)iVar4;
      *(int *)&gMonObj->field_0x72c = iVar4;
    }
    if (0xf < *(int *)&gMonObj->field_0x528) {
      moveFrame__8CGMonObjFv(gMonObj);
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  return;
}

