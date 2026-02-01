// Function: enableAttackCol__8CGMonObjFiii
// Entry: 80117b30
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void enableAttackCol__8CGMonObjFiii(CGMonObj *gMonObj,int param_2)

{
  int iVar1;
  float fVar2;
  CGMonObj *pCVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_2 != 0) {
    iVar1 = Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48;
    uVar4 = (uint)*(ushort *)(iVar1 + 0xc);
    if (*(int *)&gMonObj->field_0x560 < 0x1f5) {
      fVar2 = 1.4013e-45;
    }
    else {
      fVar2 = (float)(uint)*(ushort *)(iVar1 + 2);
    }
    uVar5 = 0;
    iVar1 = 4;
    pCVar3 = gMonObj;
    do {
      if (((int)uVar4 >> (uVar5 & 0x3f) & 1U) != 0) {
        if (uVar5 == 0xffffffff) {
          (gMonObj->gObject).m_attackColliders[1].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[2].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[3].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[4].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[5].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[6].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[7].m_localStart.x = fVar2;
          (gMonObj->gObject).m_damageColliders[0].m_localPosition.x = fVar2;
        }
        else {
          (pCVar3->gObject).m_attackColliders[1].m_localStart.x = fVar2;
        }
      }
      if (((int)uVar4 >> (uVar5 + 1 & 0x3f) & 1U) != 0) {
        if (uVar5 + 1 == 0xffffffff) {
          (gMonObj->gObject).m_attackColliders[1].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[2].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[3].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[4].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[5].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[6].m_localStart.x = fVar2;
          (gMonObj->gObject).m_attackColliders[7].m_localStart.x = fVar2;
          (gMonObj->gObject).m_damageColliders[0].m_localPosition.x = fVar2;
        }
        else {
          (pCVar3->gObject).m_attackColliders[2].m_localStart.x = fVar2;
        }
      }
      pCVar3 = (CGMonObj *)&(pCVar3->gObject).m_displayFlags;
      uVar5 = uVar5 + 2;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
  }
  (gMonObj->gObject).m_attackColliders[1].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[2].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[3].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[4].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[5].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[6].m_localStart.x = 0.0;
  (gMonObj->gObject).m_attackColliders[7].m_localStart.x = 0.0;
  (gMonObj->gObject).m_damageColliders[0].m_localPosition.x = 0.0;
  return;
}

