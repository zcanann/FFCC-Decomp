// Function: SetAttackCol__8CGObjectFiPcfP3Vec
// Entry: 8007d3d8
// Size: 176 bytes

/* WARNING: Removing unreachable block (ram,0x8007d464) */
/* WARNING: Removing unreachable block (ram,0x8007d3e8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetAttackCol__8CGObjectFiPcfP3Vec
               (double param_1,CGObject *gObject,int hitIndex,char *param_4,Vec *position)

{
  bool bVar1;
  float fVar2;
  CCharaPcsCHandle *pCVar3;
  
  pCVar3 = gObject->m_charaModelHandle;
  bVar1 = false;
  if ((pCVar3 != (CCharaPcsCHandle *)0x0) && (pCVar3->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (bVar1) {
    fVar2 = (float)SearchNode__Q26CChara6CModelFPc(pCVar3->m_model,param_4);
    gObject->m_attackColliders[hitIndex].m_radius2 = fVar2;
    gObject->m_attackColliders[hitIndex].m_hitMask = (uint32_t)(float)param_1;
    gObject->m_attackColliders[hitIndex].m_localStart.y = position->x;
    gObject->m_attackColliders[hitIndex].m_localStart.z = position->y;
    gObject->m_attackColliders[hitIndex].m_localEnd.x = position->z;
  }
  return;
}

