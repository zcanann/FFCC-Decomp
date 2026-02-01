// Function: Attach__8CGObjectFP8CGObjectPcP3Vec
// Entry: 8007d568
// Size: 224 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Attach__8CGObjectFP8CGObjectPcP3Vec(CGObject *gObject,int param_2,char *param_3,Vec *vec)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  
  bVar2 = false;
  iVar3 = *(int *)(param_2 + 0xf8);
  if ((iVar3 != 0) && (*(int *)(iVar3 + 0x168) != 0)) {
    bVar2 = true;
  }
  if ((bVar2) &&
     (iVar3 = SearchNode__Q26CChara6CModelFPc(*(CModel **)(iVar3 + 0x168),param_3), -1 < iVar3)) {
    *(byte *)&gObject->m_weaponNodeFlags = *(byte *)&gObject->m_weaponNodeFlags & 0xfe | 1;
    gObject->m_attachOwner = (CGObject *)param_2;
    gObject->m_attachNode = iVar3;
    (gObject->m_attachLocal).x = vec->x;
    (gObject->m_attachLocal).y = vec->y;
    (gObject->m_attachLocal).z = vec->z;
    if ((gObject->m_worldParamA != 5.04467e-44) && (gObject->m_worldParamB != 4.1058e-43)) {
      fVar1 = gObject->m_rotBaseY - *(float *)(param_2 + 0x1a8);
      gObject->m_rotTargetY = fVar1;
      gObject->m_rotBaseY = fVar1;
    }
    gObject->m_moveMode = gObject->m_moveModePrevious;
  }
  return;
}

