// Function: bgWorldCollision__8CGObjectFv
// Entry: 800804a4
// Size: 560 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void bgWorldCollision__8CGObjectFv(CGObject *gObject)

{
  Vec *vecA;
  int iVar1;
  double dVar2;
  Vec local_c8;
  Vec local_bc;
  Vec local_b0;
  CVector CStack_a4;
  float local_98;
  float local_94;
  float local_90;
  CVector CStack_8c;
  CVector CStack_80;
  CVector CStack_74;
  float local_68;
  float local_64;
  float local_60;
  Vec local_5c;
  float local_50;
  float local_4c;
  float local_48;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  __ct__7CVectorFRC3Vec(&CStack_80,&gObject->m_groundHitOffset);
  vecA = (Vec *)__ct__7CVectorFRC3Vec(&CStack_74,&gObject->m_worldPosition);
  __ct__7CVectorFv(&local_b0);
  PSVECAdd(vecA,(Vec *)&CStack_80,&local_b0);
  local_5c.x = local_b0.x;
  local_5c.y = local_b0.y;
  local_5c.z = local_b0.z;
  dVar2 = (double)PSVECMag(&local_5c);
  if ((double)FLOAT_80330350 < dVar2) {
    Normalize__7CVectorFv((CVector *)&local_5c);
  }
  PSVECScale(FLOAT_80330354,&local_5c,&local_5c);
  __ct__7CVectorFfff(-local_5c.x,-local_5c.y,-local_5c.z,&CStack_8c);
  __ct__7CVectorFv(&local_bc);
  PSVECScale(FLOAT_80330414,(Vec *)&CStack_8c,&local_bc);
  local_68 = local_bc.x;
  local_64 = local_bc.y;
  local_60 = local_bc.z;
  local_20 = FLOAT_8033033c;
  local_24 = FLOAT_8033033c;
  local_28 = FLOAT_8033033c;
  local_14 = FLOAT_80330340;
  local_18 = FLOAT_80330340;
  local_1c = FLOAT_80330340;
  local_50 = local_5c.x;
  local_4c = local_5c.y;
  local_48 = local_5c.z;
  local_38 = local_bc.x;
  local_34 = local_bc.y;
  local_30 = local_bc.z;
  local_2c = FLOAT_80330350;
  iVar1 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                    (&MapMng,&local_50,&local_68,(gObject->m_moveVec).x);
  if (iVar1 != 0) {
    CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&local_5c);
    __ct__7CVectorFRC3Vec(&CStack_a4,&gObject->m_worldPosition);
    __ct__7CVectorFv(&local_c8);
    PSVECSubtract(&local_5c,(Vec *)&CStack_a4,&local_c8);
    local_98 = local_c8.x;
    (gObject->m_groundHitOffset).x = local_c8.x;
    (gObject->m_groundHitOffset).y = local_c8.y;
    (gObject->m_groundHitOffset).z = local_c8.z;
    local_94 = local_c8.y;
    local_90 = local_c8.z;
    if ((*(uint *)(MapMng.mapIdGrpArr + *(byte *)(DAT_8032ec90 + 0x47)) & 0x20) == 0) {
      gObject->m_stateFlags0 = gObject->m_stateFlags0 & 0x7f | 0x80;
      (gObject->m_radiusCtrl).x = *(float *)(MapMng.mapIdGrpArr + *(byte *)(DAT_8032ec90 + 0x47));
      if (*(char *)(DAT_8032ec90 + 0x47) != '\0') {
        *(char *)&gObject->m_lastBgGroup = *(char *)(DAT_8032ec90 + 0x47);
      }
      GetHitFaceNormal__7CMapObjFP3Vec(MapMng._141944_4_,&(gObject->m_hitNormal).y);
    }
  }
  return;
}

