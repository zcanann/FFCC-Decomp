// Function: CalcSafePos__8CGObjectFiP8CGObjectP3Vec
// Entry: 8007bf34
// Size: 644 bytes

/* WARNING: Removing unreachable block (ram,0x8007c190) */
/* WARNING: Removing unreachable block (ram,0x8007bf44) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

double CalcSafePos__8CGObjectFiP8CGObjectP3Vec
                 (CGObject *gObject,undefined4 param_2,CGObject *other,float *param_4)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  Vec local_b8;
  Vec local_ac;
  float local_a0;
  float local_9c;
  float local_98;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  local_ac.x = (other->m_worldPosition).x;
  dVar4 = (double)FLOAT_80330350;
  fVar1 = (other->m_worldPosition).y;
  local_ac.y = (gObject->m_worldPosition).y;
  if (local_ac.y < fVar1) {
    local_ac.y = fVar1;
  }
  local_ac.y = local_ac.y + gObject->m_capsuleHalfHeight;
  local_ac.z = (other->m_worldPosition).z;
  PSVECSubtract(&gObject->m_worldPosition,&local_ac,&local_b8);
  local_b8.y = FLOAT_80330350;
  local_3c = gObject->m_capsuleHalfHeight;
  local_30 = FLOAT_8033033c;
  local_34 = FLOAT_8033033c;
  local_38 = FLOAT_8033033c;
  local_24 = FLOAT_80330340;
  local_28 = FLOAT_80330340;
  local_2c = FLOAT_80330340;
  local_60 = local_ac.x;
  local_5c = local_ac.y;
  local_58 = local_ac.z;
  local_48 = local_b8.x;
  local_44 = FLOAT_80330350;
  local_40 = local_b8.z;
  iVar2 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng,&local_60,&local_b8,param_2)
  ;
  if (iVar2 == 0) {
    *param_4 = (gObject->m_worldPosition).x;
    param_4[1] = (gObject->m_worldPosition).y;
    param_4[2] = (gObject->m_worldPosition).z;
    dVar3 = (double)sin((double)other->m_rotBaseY);
    local_b8.y = FLOAT_80330350;
    local_b8.x = (gObject->m_capsuleHalfHeight + other->m_capsuleHalfHeight) * (float)dVar3;
    dVar3 = (double)cos((double)other->m_rotBaseY);
    local_7c = gObject->m_capsuleHalfHeight;
    local_b8.z = (local_7c + other->m_capsuleHalfHeight) * (float)dVar3;
    local_70 = FLOAT_8033033c;
    local_74 = FLOAT_8033033c;
    local_78 = FLOAT_8033033c;
    local_64 = FLOAT_80330340;
    local_68 = FLOAT_80330340;
    local_6c = FLOAT_80330340;
    local_a0 = local_ac.x;
    local_9c = local_ac.y;
    local_98 = local_ac.z;
    local_88 = local_b8.x;
    local_84 = local_b8.y;
    local_80 = local_b8.z;
    iVar2 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_a0,&local_b8,param_2);
    if (iVar2 != 0) {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_ac);
      dVar4 = (double)PSVECDistance(&gObject->m_worldPosition,&local_ac);
      dVar4 = (double)(float)((double)(gObject->m_capsuleHalfHeight + other->m_capsuleHalfHeight) -
                             dVar4);
    }
  }
  else {
    CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_ac);
    local_ac.y = local_ac.y - gObject->m_capsuleHalfHeight;
    *param_4 = local_ac.x;
    param_4[1] = local_ac.y;
    param_4[2] = local_ac.z;
    dVar4 = (double)PSVECDistance(&gObject->m_worldPosition,&local_ac);
  }
  return dVar4;
}

