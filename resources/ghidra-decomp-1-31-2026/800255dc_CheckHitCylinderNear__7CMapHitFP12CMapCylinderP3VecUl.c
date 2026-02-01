// Function: CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUl
// Entry: 800255dc
// Size: 292 bytes

void CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUl
               (CMapHit *param_1,CMapCylinder *mapCylinder,Vec *position,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  g_hit_cyl.m_bottom.x = (mapCylinder->m_bottom).x;
  g_hit_cyl.m_bottom.y = (mapCylinder->m_bottom).y;
  g_hit_cyl.m_bottom.z = (mapCylinder->m_bottom).z;
  g_hit_cyl.m_direction.x = (mapCylinder->m_direction).x;
  g_hit_cyl.m_direction.y = (mapCylinder->m_direction).y;
  g_hit_cyl.m_direction.z = (mapCylinder->m_direction).z;
  g_hit_cyl.m_radius = mapCylinder->m_radius;
  g_hit_cyl.m_height = mapCylinder->m_height;
  g_hit_cyl.m_top.x = (mapCylinder->m_top).x;
  g_hit_cyl.m_top.y = (mapCylinder->m_top).y;
  g_hit_cyl.m_top.z = (mapCylinder->m_top).z;
  g_hit_cyl.m_direction2.x = (mapCylinder->m_direction2).x;
  g_hit_cyl.m_direction2.y = (mapCylinder->m_direction2).y;
  g_hit_cyl.m_direction2.z = (mapCylinder->m_direction2).z;
  g_hit_cyl.m_radius2 = mapCylinder->m_radius2;
  g_hit_cyl.m_height2 = mapCylinder->m_height2;
  g_hit_mvec.x = position->x;
  g_hit_mvec.y = position->y;
  g_hit_mvec.z = position->z;
  for (iVar1 = 0; iVar1 < (int)(uint)param_1->m_faceCount; iVar1 = iVar1 + 1) {
    DAT_8032ec8c = &param_1->m_faces->field_0x0 + iVar2;
    CheckHitFaceCylinder__7CMapHitFUl(param_1,param_4);
    iVar2 = iVar2 + 0x50;
  }
  return;
}

