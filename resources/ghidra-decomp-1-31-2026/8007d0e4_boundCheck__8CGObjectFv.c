// Function: boundCheck__8CGObjectFv
// Entry: 8007d0e4
// Size: 556 bytes

/* WARNING: Removing unreachable block (ram,0x8007d2e8) */
/* WARNING: Removing unreachable block (ram,0x8007d2e0) */
/* WARNING: Removing unreachable block (ram,0x8007d2d8) */
/* WARNING: Removing unreachable block (ram,0x8007d104) */
/* WARNING: Removing unreachable block (ram,0x8007d0fc) */
/* WARNING: Removing unreachable block (ram,0x8007d0f4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void boundCheck__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  Vec local_118;
  Vec4d local_10c;
  Mat4x4 MStack_fc;
  Mat4x4 MStack_bc;
  Mtx MStack_7c;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_7c);
  PSMTXCopy(&MStack_7c,(Mtx *)&MStack_bc);
  MStack_bc.value[3][2] = FLOAT_80330350;
  MStack_bc.value[3][1] = FLOAT_80330350;
  MStack_bc.value[3][0] = FLOAT_80330350;
  MStack_bc.value[3][3] = FLOAT_80330338;
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_fc);
  PSMTX44Concat(&MStack_fc,&MStack_bc,&MStack_fc);
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    dVar4 = (double)FLOAT_80330350;
    dVar5 = (double)FLOAT_80330338;
    dVar6 = (double)FLOAT_80330390;
    uVar3 = 0x1f;
    uVar2 = 0;
    while( true ) {
      if ((uVar2 & 1) == 0) {
        local_118.x = gObject->m_nearColRadius;
      }
      else {
        local_118.x = -gObject->m_nearColRadius;
      }
      local_118.x = (gObject->m_worldPosition).x + local_118.x;
      if ((uVar2 & 4) == 0) {
        local_118.y = gObject->m_nearColRadius;
      }
      else {
        local_118.y = -gObject->m_nearColRadius;
      }
      local_118.y = (gObject->m_worldPosition).y + local_118.y;
      if ((uVar2 & 2) == 0) {
        local_118.z = gObject->m_nearColRadius;
      }
      else {
        local_118.z = -gObject->m_nearColRadius;
      }
      local_118.z = (gObject->m_worldPosition).z + local_118.z;
      MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d(&Math,&MStack_fc,&local_118,&local_10c);
      if (dVar4 < (double)local_10c.w) {
        uVar3 = uVar3 & 0xffffffef;
      }
      if (uVar3 == 0) break;
      fVar1 = (float)(dVar5 / (double)local_10c.w);
      local_10c.x = local_10c.x * fVar1;
      local_10c.y = local_10c.y * fVar1;
      if (dVar6 < (double)local_10c.x) {
        uVar3 = uVar3 & 0xfffffffe;
      }
      if (dVar6 < (double)local_10c.y) {
        uVar3 = uVar3 & 0xfffffffd;
      }
      if ((double)local_10c.x < dVar5) {
        uVar3 = uVar3 & 0xfffffffb;
      }
      if ((double)local_10c.y < dVar5) {
        uVar3 = uVar3 & 0xfffffff7;
      }
      if ((uVar3 == 0) || (uVar2 = uVar2 + 1, 7 < (int)uVar2)) break;
    }
    uVar3 = countLeadingZeros(uVar3);
    *(byte *)&gObject->m_weaponNodeFlags =
         (byte)((int)(char)(uVar3 >> 5) << 5) & 0x20 | *(byte *)&gObject->m_weaponNodeFlags & 0xdf;
  }
  MTX44MultVec4__5CMathFPA4_fP3VecP5Vec4d
            (&Math,&MStack_fc,&gObject->m_worldPosition,(Vec4d *)&(gObject->m_projection).y);
  return;
}

