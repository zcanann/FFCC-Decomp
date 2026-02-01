// Function: SetDamageCol__8CGObjectFiPcffP3Vec
// Entry: 8007d310
// Size: 200 bytes

/* WARNING: Removing unreachable block (ram,0x8007d3b4) */
/* WARNING: Removing unreachable block (ram,0x8007d3ac) */
/* WARNING: Removing unreachable block (ram,0x8007d328) */
/* WARNING: Removing unreachable block (ram,0x8007d320) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetDamageCol__8CGObjectFiPcffP3Vec
               (double param_1,double param_2,CGObject *gObject,int param_4,char *param_5,
               Vec *position)

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
    fVar2 = (float)SearchNode__Q26CChara6CModelFPc(pCVar3->m_model,param_5);
    gObject->m_damageColliders[param_4].m_outerRadius = fVar2;
    gObject->m_damageColliders[param_4].m_hitMask = (uint32_t)(float)param_1;
    gObject->m_damageColliders[param_4].m_active = (int32_t)(float)param_2;
    gObject->m_damageColliders[param_4].m_localPosition.y = position->x;
    gObject->m_damageColliders[param_4].m_localPosition.z = position->y;
    gObject->m_damageColliders[param_4].m_worldPosition.x = position->z;
  }
  return;
}

