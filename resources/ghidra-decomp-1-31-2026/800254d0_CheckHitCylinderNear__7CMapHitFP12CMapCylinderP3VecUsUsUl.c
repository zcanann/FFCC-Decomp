// Function: CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUsUsUl
// Entry: 800254d0
// Size: 268 bytes

void CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUsUsUl
               (CMapHit *mapHit,CMapCylinder *mapCylinder,Vec *position,uint param_4,int param_5,
               undefined4 param_6)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = param_4 & 0xffff;
  iVar2 = uVar1 * 0x50;
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
  for (; (int)uVar1 < (int)(param_5 + param_4 & 0xffff); uVar1 = uVar1 + 1) {
    DAT_8032ec8c = &mapHit->m_faces->field_0x0 + iVar2;
    CheckHitFaceCylinder__7CMapHitFUl(mapHit,param_6);
    iVar2 = iVar2 + 0x50;
  }
  return;
}

