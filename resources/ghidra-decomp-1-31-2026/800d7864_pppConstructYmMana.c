// Function: pppConstructYmMana
// Entry: 800d7864
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMana(pppYmMana *pppYmMana,UnkC *param_2)

{
  CCharaPcsCHandle *handle;
  CGObject *gObject;
  undefined4 *puVar1;
  
  gObject = (CGObject *)(pppMngStPtr->m_velocity).x;
  puVar1 = (undefined4 *)((int)(&pppYmMana->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  if (Game.game.m_currentSceneId == 7) {
    gObject->m_lookAtTimer = FLOAT_80330e58;
  }
  if (Game.game.m_currentMapId != 0x21) {
    gObject->m_stepSlopeLimit = FLOAT_80330eb8;
  }
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
  GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  handle->m_model->m_meshVisibleMask = 0x3f;
  puVar1[1] = pppMngStPtr;
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[9] = 0;
  puVar1[8] = 0;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  puVar1[0x12] = 0;
  puVar1[0x13] = 0;
  puVar1[0x14] = 0;
  puVar1[0x15] = 0;
  puVar1[0x16] = 0;
  puVar1[0x18] = 0;
  puVar1[0x11] = 0;
  puVar1[0x17] = 0;
  puVar1[0x1e] = 0;
  puVar1[0x1d] = 0;
  puVar1[0x1f] = 0;
  puVar1[0x20] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 0;
  puVar1[0x1b] = 0;
  puVar1[0x1c] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  *(undefined *)(puVar1 + 0x3a) = 0xff;
  PSMTXIdentity((Mtx *)(puVar1 + 0x22));
  PSMTXIdentity((Mtx *)(puVar1 + 0x2e));
  *(undefined *)(puVar1 + 0xe) = 0xff;
  *(undefined *)((int)puVar1 + 0x39) = 0xff;
  *(undefined *)((int)puVar1 + 0x3a) = 0xff;
  *(undefined *)((int)puVar1 + 0x3b) = 0xff;
  *(undefined *)(puVar1 + 0x3f) = 0xff;
  *(undefined *)((int)puVar1 + 0xfd) = 0xff;
  *(undefined *)((int)puVar1 + 0xfe) = 0xff;
  *(undefined *)((int)puVar1 + 0xff) = 0xff;
  *(undefined *)(puVar1 + 0x40) = 0xff;
  *(undefined *)((int)puVar1 + 0x101) = 0xff;
  *(undefined *)((int)puVar1 + 0x102) = 0xff;
  *(undefined *)((int)puVar1 + 0x103) = 0xff;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0;
  puVar1[0x3b] = 0;
  puVar1[0x3c] = 0;
  *(undefined *)(puVar1 + 0x3d) = 0;
  puVar1[0x3e] = 0;
  return;
}

