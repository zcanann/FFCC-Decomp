// Function: CheckHitCylinder__8COctTreeFP12CMapCylinderP3VecUl
// Entry: 8002cd38
// Size: 440 bytes

undefined4
CheckHitCylinder__8COctTreeFP12CMapCylinderP3VecUl
          (COctTree *octTree,Vec *param_2,Vec *param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  Mtx MStack_48;
  
  if ((*(char *)&octTree->vtable == '\x02') && (*(int *)((int)octTree->field2_0x8 + 0xc) != 0)) {
    PSMTXInverse((Mtx *)((int)octTree->field2_0x8 + 0xb8),&MStack_48);
    PSMTXMultVec(&MStack_48,param_2,&s_cyl.m_bottom);
    PSMTXMultVec(&MStack_48,param_2 + 1,&s_cyl.m_direction);
    PSMTXMultVecSR(&MStack_48,param_2 + 2,(Vec *)&s_cyl.m_radius);
    PSMTXMultVecSR(&MStack_48,param_3,&s_mvec);
    s_cyl.m_top.y = param_2[3].x;
    fVar1 = s_cyl.m_direction.x;
    fVar2 = s_cyl.m_bottom.x;
    if (s_cyl.m_bottom.x < s_cyl.m_direction.x) {
      fVar1 = s_cyl.m_bottom.x;
      fVar2 = s_cyl.m_direction.x;
    }
    s_cyl.m_direction2.z = fVar2 + FLOAT_8032f960 + s_cyl.m_top.y;
    s_cyl.m_top.z = fVar1 - (FLOAT_8032f960 + s_cyl.m_top.y);
    fVar1 = s_cyl.m_direction.y;
    fVar2 = s_cyl.m_bottom.y;
    if (s_cyl.m_bottom.y < s_cyl.m_direction.y) {
      fVar1 = s_cyl.m_bottom.y;
      fVar2 = s_cyl.m_direction.y;
    }
    s_cyl.m_radius2 = fVar2 + FLOAT_8032f960 + s_cyl.m_top.y;
    s_cyl.m_direction2.x = fVar1 - (FLOAT_8032f960 + s_cyl.m_top.y);
    fVar1 = s_cyl.m_direction.z;
    fVar2 = s_cyl.m_bottom.z;
    if (s_cyl.m_bottom.z < s_cyl.m_direction.z) {
      fVar1 = s_cyl.m_bottom.z;
      fVar2 = s_cyl.m_direction.z;
    }
    s_cyl.m_height2 = fVar2 + FLOAT_8032f960 + s_cyl.m_top.y;
    s_cyl.m_direction2.y = fVar1 - (FLOAT_8032f960 + s_cyl.m_top.y);
    DAT_8032ecb0 = param_4;
    iVar3 = CheckHitCylinder_r__8COctTreeFP8COctNode(octTree,octTree->rootNode);
    if (iVar3 != 0) {
      return 1;
    }
  }
  return 0;
}

