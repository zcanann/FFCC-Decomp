// Function: frameStatFuncGolem__8CGMonObjFv
// Entry: 80132670
// Size: 700 bytes

/* WARNING: Removing unreachable block (ram,0x80132910) */
/* WARNING: Removing unreachable block (ram,0x80132680) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncGolem__8CGMonObjFv(CGMonObj *gMonObj)

{
  byte bVar1;
  int iVar2;
  double dVar3;
  double in_f31;
  
  iVar2 = *(int *)&gMonObj->field_0x520;
  if (iVar2 != 0x66) {
    if (iVar2 < 0x66) {
      if (iVar2 == 100) {
        if (*(int *)&gMonObj->field_0x528 == 0) {
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa17,0x32,0x96,0,0);
        }
        else if (*(int *)&gMonObj->field_0x528 == 0x14) {
          DispCharaParts__8CGObjectFi(&gMonObj->gObject,1);
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa18,0x32,0x96,0,0);
          gMonObj->_bossBranchRelated = 1;
        }
        _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
        return;
      }
      if (iVar2 < 100) {
        return;
      }
      iVar2 = *(int *)&gMonObj->field_0x528;
      if (iVar2 == 0) {
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0xfa1a,0x32,0x96,0,0);
      }
      else if (iVar2 == 4) {
        DispCharaParts__8CGObjectFi(&gMonObj->gObject,3);
        gMonObj->_bossBranchRelated = 0;
      }
      else if (iVar2 == 5) {
        DispCharaParts__8CGObjectFi(&gMonObj->gObject,7);
      }
      _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
      return;
    }
    if (iVar2 != 0x68) {
      if (0x67 < iVar2) {
        return;
      }
      if (*(int *)&gMonObj->field_0x528 != 0x32) {
        return;
      }
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      return;
    }
  }
  if (((*(int *)&gMonObj->field_0x528 == 0x14) ||
      (bVar1 = (gMonObj->gObject).m_stateFlags0, (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0
      )) || ((iVar2 == 0x66 &&
             (*(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x6c4 * 4) <
              FLOAT_80331d58 * (gMonObj->gObject).m_bodyEllipsoidRadius)))) {
    dVar3 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                              ((CGPrgObj *)gMonObj,
                               Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
    (gMonObj->gObject).m_rotTargetY = (float)dVar3;
    setAttackAfter__8CGMonObjFi(gMonObj,*(undefined4 *)&gMonObj->field_0x560);
  }
  else {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      if (iVar2 != 0x67) {
        if (iVar2 < 0x67) {
          if (0x65 < iVar2) {
            in_f31 = (double)FLOAT_80331cf8;
          }
        }
        else if (iVar2 < 0x69) {
          in_f31 = (double)FLOAT_80331d2c;
        }
      }
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,1,1,0);
      dVar3 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                ((CGPrgObj *)gMonObj,
                                 Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
      (gMonObj->gObject).m_rotTargetY = (float)dVar3;
      SoundBuffer._1276_4_ = (undefined4)((double)(gMonObj->gObject).m_rotTargetY + in_f31);
    }
    moveVectorHRot__8CGObjectFfffi
              ((double)(float)SoundBuffer._1276_4_,(double)FLOAT_80331cf8,
               (double)(*(float *)&gMonObj->field_0x690 *
                       (FLOAT_80331d60 *
                        (float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        ((int)(gMonObj->gObject).m_scriptHandle[9] +
                                                        0xd4)) - DOUBLE_80331dc0) + FLOAT_80331db8))
               ,&gMonObj->gObject,1);
  }
  return;
}

