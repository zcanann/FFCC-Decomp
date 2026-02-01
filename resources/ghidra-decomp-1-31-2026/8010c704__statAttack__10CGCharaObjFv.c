// Function: ?statAttack__10CGCharaObjFv
// Entry: 8010c704
// Size: 1000 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _statAttack__10CGCharaObjFv(CGCharaObj *gCharaObj)

{
  ushort uVar1;
  bool bVar2;
  void *pvVar3;
  uint uVar4;
  CModel *pCVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  CCharaPcsCHandle *pCVar9;
  
  uVar4 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))();
  if ((((uVar4 & 0xad) == 0xad) && ((gCharaObj->gPrgObj).m_subState == 0)) &&
     ((pvVar3 = (gCharaObj->gPrgObj).object.m_scriptHandle[4], pvVar3 == (void *)0x88 ||
      (pvVar3 == (void *)0x87)))) {
    pCVar9 = (gCharaObj->gPrgObj).object.m_charaModelHandle;
    bVar2 = false;
    if ((pCVar9 != (CCharaPcsCHandle *)0x0) && (pCVar9->m_model != (CModel *)0x0)) {
      bVar2 = true;
    }
    if (bVar2) {
      pCVar5 = pCVar9->m_model;
      if (pCVar5->m_anim == (CAnim *)0x0) {
        uVar4 = 1;
      }
      else {
        uVar4 = (uint)(FLOAT_80331964 + (pCVar5->m_animEnd - pCVar5->m_animStart));
        if (uVar4 == 1) {
          uVar4 = 1;
        }
        else {
          uVar7 = (uint)(gCharaObj->gPrgObj).object.m_turnSpeed;
          if (FLOAT_80331988 <= *(float *)(gCharaObj->gPrgObj).object.m_lastBgAttr) {
            uVar4 = ((int)uVar7 >> 0x1f) + ((uint)(uVar4 <= uVar7) - ((int)uVar4 >> 0x1f)) & 0xff;
          }
          else {
            uVar4 = countLeadingZeros(uVar7 - ((int)uVar7 / (int)uVar4) * uVar4);
            uVar4 = (1 << (uVar4 & 0x1f) | 1U >> 0x20 - (uVar4 & 0x1f)) & 1;
          }
        }
      }
    }
    else {
      uVar4 = 1;
    }
    if (uVar4 == 0) {
      return;
    }
    (gCharaObj->gPrgObj).m_subState = 1;
    (gCharaObj->gPrgObj).m_stateFrame = 0;
  }
  (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x88))(gCharaObj,0);
  if ((gCharaObj->gPrgObj).m_stateFrame == 0) {
    gCharaObj->field_0x640 = gCharaObj->field_0x640 & 0x7f;
    gCharaObj->field_0x648 = gCharaObj->field_0x648 & 0x7f;
    gCharaObj->field_0x650 = gCharaObj->field_0x650 & 0x7f;
    gCharaObj->field_0x658 = gCharaObj->field_0x658 & 0x7f;
    putParticleFromItem__10CGCharaObjFiiiP3Vec
              (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,0,
               *(undefined4 *)&gCharaObj->field_0x564,0);
    putParticleFromItem__10CGCharaObjFiiiP3Vec
              (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,1,
               *(undefined4 *)&gCharaObj->field_0x564,0);
    putParticleFromItem__10CGCharaObjFiiiP3Vec
              (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,2,
               *(undefined4 *)&gCharaObj->field_0x564,0);
    putParticleFromItem__10CGCharaObjFiiiP3Vec
              (gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,3,
               *(undefined4 *)&gCharaObj->field_0x564,0);
    reqAnim__8CGPrgObjFiii(&gCharaObj->gPrgObj,*(undefined4 *)&gCharaObj->field_0x550,0,0);
  }
  if ((gCharaObj->gPrgObj).m_stateFrame == *(int *)&gCharaObj->field_0x630) {
    (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x90))
              (gCharaObj,1,0,0);
  }
  if ((gCharaObj->gPrgObj).m_stateFrame == *(int *)&gCharaObj->field_0x634) {
    (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x90))
              (gCharaObj,0,0,0);
  }
  iVar6 = Game.game.unkCFlatData0[2] + *(int *)&gCharaObj->field_0x560 * 0x48;
  uVar1 = *(ushort *)(iVar6 + 0x3a);
  if (((uVar1 & 0x8000) == 0) && ((gCharaObj->gPrgObj).m_stateFrame == (uint)uVar1)) {
    uVar1 = *(ushort *)(iVar6 + 0x38);
    uVar4 = (uint)uVar1;
    if (uVar4 != 0) {
      if (uVar4 == 0xffff) {
        iVar6 = 0;
      }
      else {
        iVar6 = (uVar1 & 0xff) + ((int)uVar4 >> 8) * 1000;
      }
      playSe3D__8CGPrgObjFiiiiP3Vec(&gCharaObj->gPrgObj,iVar6,0x32,0x96,0,0);
    }
  }
  iVar6 = Game.game.unkCFlatData0[2] + *(int *)&gCharaObj->field_0x560 * 0x48;
  uVar1 = *(ushort *)(iVar6 + 0x3e);
  if (((uVar1 & 0x8000) == 0) && ((gCharaObj->gPrgObj).m_stateFrame == (uint)uVar1)) {
    uVar1 = *(ushort *)(iVar6 + 0x3c);
    uVar4 = (uint)uVar1;
    if (uVar4 != 0) {
      uVar7 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                        (gCharaObj);
      if ((uVar7 & 0xad) == 0xad) {
        if (uVar4 == 0xffff) {
          iVar6 = 0;
        }
        else {
          iVar6 = (uVar1 & 0xff) + ((int)uVar4 >> 8) * 1000;
        }
        iVar8 = Rand__5CMathFUl(&Math,3);
        playSe3D__8CGPrgObjFiiiiP3Vec(&gCharaObj->gPrgObj,iVar6 + iVar8,0x32,0x96,0,0);
      }
      else {
        playSe3D__8CGPrgObjFiiiiP3Vec(&gCharaObj->gPrgObj,uVar4,0x32,0x96,0,0);
      }
    }
  }
  (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x88))(gCharaObj,1);
  return;
}

