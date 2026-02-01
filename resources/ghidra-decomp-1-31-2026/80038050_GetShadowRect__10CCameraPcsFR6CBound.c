// Function: GetShadowRect__10CCameraPcsFR6CBound
// Entry: 80038050
// Size: 680 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetShadowRect__10CCameraPcsFR6CBound(int param_1,float *param_2)

{
  float fVar1;
  bool bVar2;
  CGObject *gObject;
  uint uVar3;
  int iVar4;
  int iVar5;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  Mtx MStack_7c;
  Mtx MStack_4c;
  
  iVar5 = 0;
  PSMTXInverse((Mtx *)(param_1 + 4),&MStack_4c);
  local_b8 = MStack_4c.value[0][3];
  local_b4 = MStack_4c.value[1][3];
  local_b0 = MStack_4c.value[2][3];
  PSMTXScaleApply(FLOAT_8032fa94 * *(float *)(param_1 + 0x94),
                  FLOAT_8032fa98 * *(float *)(param_1 + 0xa8),FLOAT_8032fa1c,(Mtx *)(param_1 + 4),
                  &MStack_7c);
  SetFrustum__6CBoundFR3VecPA4_f(&local_b8,&MStack_7c);
  for (gObject = (CGObject *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      gObject != (CGObject *)0x0;
      gObject = (CGObject *)
                FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject)) {
    bVar2 = false;
    if (((((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
          (uVar3 = gObject->m_displayFlags, (uVar3 & 1) != 0)) && ((uVar3 & 0x40) == 0)) &&
        ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
              (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0)) &&
       (((uVar3 & 0x80) != 0 || (FLOAT_8032fa1c == gObject->m_lookAtTimer)))) {
      bVar2 = true;
    }
    if (bVar2) {
      local_84 = gObject->m_nearColRadius;
      if (FLOAT_8032fa9c < gObject->m_nearColRadius) {
        local_84 = FLOAT_8032fa9c;
      }
      local_88 = (gObject->m_worldPosition).x;
      local_94 = local_88 - local_84;
      local_88 = local_88 + local_84;
      local_80 = (gObject->m_worldPosition).z;
      local_8c = local_80 - local_84;
      local_80 = local_80 + local_84;
      local_90 = (gObject->m_worldPosition).y;
      local_84 = local_90 + local_84;
      local_a4 = FLOAT_8032fa78;
      local_a8 = FLOAT_8032fa78;
      local_ac = FLOAT_8032fa78;
      local_98 = FLOAT_8032fa7c;
      local_9c = FLOAT_8032fa7c;
      local_a0 = FLOAT_8032fa7c;
      iVar4 = CheckFrustum0__6CBoundFR6CBound(&local_94,&local_ac);
      if (((iVar4 != 0) && (FLOAT_8032faa0 < local_a4)) &&
         ((FLOAT_8032fa48 < (local_a0 - local_ac) / -local_a4 ||
          (FLOAT_8032fa48 < (local_9c - local_a8) / -local_a4)))) {
        fVar1 = local_94;
        if (*param_2 < local_94) {
          fVar1 = *param_2;
        }
        *param_2 = fVar1;
        fVar1 = local_90;
        if (param_2[1] < local_90) {
          fVar1 = param_2[1];
        }
        param_2[1] = fVar1;
        fVar1 = local_8c;
        if (param_2[2] < local_8c) {
          fVar1 = param_2[2];
        }
        param_2[2] = fVar1;
        fVar1 = local_88;
        if (local_88 < param_2[3]) {
          fVar1 = param_2[3];
        }
        param_2[3] = fVar1;
        fVar1 = local_84;
        if (local_84 < param_2[4]) {
          fVar1 = param_2[4];
        }
        param_2[4] = fVar1;
        fVar1 = local_80;
        if (local_80 < param_2[5]) {
          fVar1 = param_2[5];
        }
        param_2[5] = fVar1;
        iVar5 = iVar5 + 1;
      }
    }
  }
  return iVar5;
}

