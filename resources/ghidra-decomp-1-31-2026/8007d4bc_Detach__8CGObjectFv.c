// Function: Detach__8CGObjectFv
// Entry: 8007d4bc
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Detach__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  int iVar2;
  CNode *pCVar3;
  
  if ((*(byte *)&gObject->m_weaponNodeFlags & 1) != 0) {
    iVar2 = gObject->m_attachNode;
    pCVar3 = gObject->m_attachOwner->m_charaModelHandle->m_model->m_nodes;
    (gObject->m_worldPosition).x = pCVar3[iVar2].m_mtx.value[0][3];
    (gObject->m_worldPosition).y = pCVar3[iVar2].m_mtx.value[1][3];
    (gObject->m_worldPosition).z = pCVar3[iVar2].m_mtx.value[2][3];
    PSVECAdd(&gObject->m_worldPosition,&gObject->m_attachOwner->m_worldPosition,
             &gObject->m_worldPosition);
    fVar1 = gObject->m_rotBaseY + gObject->m_attachOwner->m_rotBaseY;
    gObject->m_rotTargetY = fVar1;
    gObject->m_rotBaseY = fVar1;
  }
  *(byte *)&gObject->m_weaponNodeFlags = *(byte *)&gObject->m_weaponNodeFlags & 0xfe;
  return;
}

