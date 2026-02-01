// Function: onStatDie__8CGMonObjFv
// Entry: 80117690
// Size: 812 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatDie__8CGMonObjFv(CGMonObj *gMonObj,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  CRef *pCVar2;
  void *pvVar3;
  uint uVar4;
  void **ppvVar5;
  undefined8 uVar6;
  
  iVar1 = *(int *)&gMonObj->field_0x52c;
  if (iVar1 == 1) {
    ppvVar5 = (gMonObj->gObject).m_scriptHandle;
    if ((*(ushort *)((int)ppvVar5[9] + 0xfe) & 2) == 0) {
      if (*(int *)&gMonObj->field_0x530 != 0) {
        return;
      }
    }
    else {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        pvVar3 = ppvVar5[4];
        if (pvVar3 == (void *)0x5) {
          param_3 = 599;
        }
        else if ((int)pvVar3 < 5) {
          if (3 < (int)pvVar3) {
            param_3 = 0x253;
          }
        }
        else if ((int)pvVar3 < 7) {
          param_3 = 0x25b;
        }
        *(undefined4 *)&gMonObj->field_0x560 = param_3;
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,0,
                   *(undefined4 *)&gMonObj->field_0x564,0);
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,1,
                   *(undefined4 *)&gMonObj->field_0x564,0);
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,2,
                   *(undefined4 *)&gMonObj->field_0x564,0);
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (gMonObj,*(undefined4 *)&gMonObj->field_0x560,3,
                   *(undefined4 *)&gMonObj->field_0x564,0);
        return;
      }
      if (*(int *)&gMonObj->field_0x530 != 0x19) {
        return;
      }
    }
    endPSlotBit__10CGCharaObjFi(gMonObj,0x231000);
    *(float *)&gMonObj->field_0x694 = FLOAT_803319d8;
    (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x90))(gMonObj,0,0,0);
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff6fffd;
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x17,0x32,0x96,0,0);
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)(FLOAT_80331a44 * (gMonObj->gObject).m_attackColRadius),(CGPrgObj *)gMonObj,
               0x116,0,&gMonObj->gObject,0);
    CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
              ((double)FLOAT_803319d8,1,0,0,gMonObj,0);
    PutDropItem__8CGObjectFv(&gMonObj->gObject);
    changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,2);
    return;
  }
  if (0 < iVar1) {
    if (2 < iVar1) {
      return;
    }
    if (*(ushort *)&gMonObj->field_0x6d6 == 0) {
      return;
    }
    if (*(int *)&gMonObj->field_0x530 != (uint)*(ushort *)&gMonObj->field_0x6d6 * 0x1e) {
      return;
    }
    setRepop__8CGMonObjFi(gMonObj,0);
    return;
  }
  if (iVar1 < 0) {
    return;
  }
  if (*(int *)&gMonObj->field_0x530 == 0) {
    pvVar3 = (gMonObj->gObject).m_scriptHandle[9];
    playSe3D__8CGPrgObjFiiiiP3Vec
              ((CGPrgObj *)gMonObj,
               (uint)*(ushort *)((int)pvVar3 + 0x192) +
               (uint)*(ushort *)((int)pvVar3 + 400) * 1000 + 9,0x32,0x96,0,0);
    uVar4 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x19e);
    if (uVar4 != 0xffff) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_80331a44 * (gMonObj->gObject).m_attackColRadius),(CGPrgObj *)gMonObj
                 ,uVar4 | iVar1 << 8,0,&gMonObj->gObject,0);
    }
    iVar1 = (int)(short)Game.game.m_gameWork.m_optionValue;
    if (8 < iVar1) {
      return;
    }
    if (*(short *)&gMonObj->field_0x6d6 != 0) {
      return;
    }
    uVar6 = __shl2i(0,1,(gMonObj->gObject).m_scriptHandle[2]);
    iVar1 = iVar1 * 8;
    *(uint *)(&CFlat.field_0x12f4 + iVar1) = *(uint *)(&CFlat.field_0x12f4 + iVar1) | (uint)uVar6;
    *(uint *)(&CFlat.field_0x12f0 + iVar1) =
         *(uint *)(&CFlat.field_0x12f0 + iVar1) | (uint)((ulonglong)uVar6 >> 0x20);
    return;
  }
  iVar1 = isLoopAnimDirect__8CGPrgObjFv((CGPrgObj *)gMonObj);
  if (iVar1 == 0) {
    return;
  }
  changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,1);
  return;
}

