// Function: onFrameStat__10CGCharaObjFv
// Entry: 80111920
// Size: 1744 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameStat__10CGCharaObjFv(CGCharaObj *gCharaObj)

{
  uint uVar1;
  undefined4 uVar2;
  CGCharaObj *pCVar3;
  int iVar4;
  
  if ((gCharaObj->gPrgObj).m_stateFrameGate == 0) {
    switch((gCharaObj->gPrgObj).m_lastStateId) {
    case 1:
    case 0x12:
      _statAttack__10CGCharaObjFv(gCharaObj);
      break;
    case 2:
      iVar4 = (gCharaObj->gPrgObj).m_subState;
      if (iVar4 == 1) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x554,1,0);
        }
      }
      else if (iVar4 < 1) {
        if (-1 < iVar4) {
          if ((gCharaObj->gPrgObj).m_subFrame == 0) {
            reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x550,0,0);
          }
          iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
          if (iVar4 != 0) {
            if (*(int *)&gCharaObj->field_0x560 == 0x103) {
              changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,2);
              return;
            }
            changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,1);
            return;
          }
        }
      }
      else if (iVar4 < 3) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          iVar4 = 0;
          pCVar3 = gCharaObj;
          do {
            if ((1 << iVar4 & 8U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
            }
            iVar4 = iVar4 + 1;
            pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
          } while (iVar4 < 0x16);
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x558,0,0);
        }
        if ((*(int *)&gCharaObj->field_0x560 != 0) && ((gCharaObj->gPrgObj).m_subFrame == 10)) {
          iVar4 = 0;
          pCVar3 = gCharaObj;
          do {
            if ((1 << iVar4 & 2U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
            }
            iVar4 = iVar4 + 1;
            pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
          } while (iVar4 < 0x16);
          putParticleFromItem__10CGCharaObjFiiiP3Vec
                    (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,2,
                     *(undefined4 *)&gCharaObj->field_0x568,&gCharaObj->field_0x66c);
          putParticleFromItem__10CGCharaObjFiiiP3Vec
                    (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,3,
                     *(undefined4 *)&gCharaObj->field_0x568,&gCharaObj->field_0x66c);
        }
      }
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x84))(gCharaObj);
      break;
    case 4:
      if ((gCharaObj->gPrgObj).m_stateFrame == 0) {
        StopSe3DGroup__6CSoundFi
                  (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
        iVar4 = 0;
        pCVar3 = gCharaObj;
        do {
          if ((1 << iVar4 & 0x3bU) != 0) {
            DeleteParticleSlot__13CFlatRuntime2Fii
                      ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
          }
          iVar4 = iVar4 + 1;
          pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
        } while (iVar4 < 0x16);
        reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,4,0,0);
      }
      iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
      if (iVar4 != 0) {
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
      }
      break;
    case 8:
      iVar4 = (gCharaObj->gPrgObj).m_subState;
      if (iVar4 == 2) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x558,0,0);
        }
        iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
        if (iVar4 != 0) {
          changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,1);
          return;
        }
      }
      else if (iVar4 < 2) {
        if (iVar4 == 0) {
          if ((gCharaObj->gPrgObj).m_subFrame == 0) {
            reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x550,0,0);
          }
          iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
          if (iVar4 != 0) {
            changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,1);
            return;
          }
        }
        else if ((-1 < iVar4) && ((gCharaObj->gPrgObj).m_subFrame == 0)) {
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x554,1,0);
        }
      }
      else if (iVar4 < 4) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                            ();
          uVar1 = countLeadingZeros(0xad - (uVar1 & 0xad));
          if ((uVar1 >> 5 & 0xff) == 0) {
            uVar2 = *(undefined4 *)&gCharaObj->field_0x55c;
          }
          else {
            uVar2 = *(undefined4 *)&gCharaObj->field_0x558;
          }
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,uVar2,0,0);
        }
        iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
        if (iVar4 != 0) {
          changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
          return;
        }
      }
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x8c))(gCharaObj);
      break;
    case 9:
      if (((gCharaObj->gPrgObj).m_subState == 0) && ((gCharaObj->gPrgObj).m_subFrame == 0)) {
        StopSe3DGroup__6CSoundFi
                  (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
        iVar4 = 0;
        pCVar3 = gCharaObj;
        do {
          if ((1 << iVar4 & 0x3bU) != 0) {
            DeleteParticleSlot__13CFlatRuntime2Fii
                      ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
          }
          iVar4 = iVar4 + 1;
          pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
        } while (iVar4 < 0x16);
        reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,6,1,0);
        uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                          (gCharaObj);
        if ((uVar1 & 0x6d) == 0x6d) {
          playSe3D__8CGPrgObjFiiiiP3Vec
                    (&gCharaObj->gPrgObj,
                     *(ushort *)((gCharaObj->gPrgObj).object.m_scriptHandle + 0xf8) + 0x10,0x32,0x96
                     ,0,0);
        }
      }
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x7c))(gCharaObj);
      break;
    case 10:
      iVar4 = (gCharaObj->gPrgObj).m_subState;
      if (iVar4 == 1) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1b,1,0);
        }
        if (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x46) == 0) {
          changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,2);
        }
      }
      else if (iVar4 < 1) {
        if (-1 < iVar4) {
          if ((gCharaObj->gPrgObj).m_subFrame == 0) {
            StopSe3DGroup__6CSoundFi
                      (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
            iVar4 = 0;
            pCVar3 = gCharaObj;
            do {
              if ((1 << iVar4 & 0x3bU) != 0) {
                DeleteParticleSlot__13CFlatRuntime2Fii
                          ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
              }
              iVar4 = iVar4 + 1;
              pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
            } while (iVar4 < 0x16);
            reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1a,0,0);
          }
          iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
          if (iVar4 != 0) {
            changeSubStat__8CGPrgObjFi(&gCharaObj->gPrgObj,1);
          }
        }
      }
      else if (iVar4 < 3) {
        if ((gCharaObj->gPrgObj).m_subFrame == 0) {
          reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1c,0,0);
        }
        iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
        if (iVar4 != 0) {
          changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
        }
      }
      break;
    case 0x19:
      if ((gCharaObj->gPrgObj).m_stateFrame == 0) {
        uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))();
        if ((uVar1 & 0x6d) == 0x6d) {
          carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)gCharaObj,1,(CGObject *)0x0,1);
        }
        StopSe3DGroup__6CSoundFi
                  (&Sound,(int)(gCharaObj->gPrgObj).object.base_object.object.m_particleId);
        iVar4 = 0;
        pCVar3 = gCharaObj;
        do {
          if ((1 << iVar4 & 0x3bU) != 0) {
            DeleteParticleSlot__13CFlatRuntime2Fii
                      ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar3->field_0x564);
          }
          iVar4 = iVar4 + 1;
          pCVar3 = (CGCharaObj *)&(pCVar3->gPrgObj).object.base_object.object.m_freeListNode;
        } while (iVar4 < 0x16);
        reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,0x1d,0,0);
      }
      iVar4 = isLoopAnim__8CGPrgObjFv(&gCharaObj->gPrgObj);
      if (iVar4 != 0) {
        changeStat__8CGPrgObjFiii(&gCharaObj->gPrgObj,0,0,0);
      }
    }
  }
  return;
}

