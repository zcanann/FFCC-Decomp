// Function: CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUsUsUl
// Entry: 80025700
// Size: 312 bytes

/* WARNING: Removing unreachable block (ram,0x8002581c) */
/* WARNING: Removing unreachable block (ram,0x80025710) */

undefined4
CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUsUsUl
          (CMapHit *mapHit,CMapCylinder *mapCylinder,Vec *vec,uint param_4,int param_5,
          undefined4 param_6)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  g_hit_cyl.m_bottom.x = (mapCylinder->m_bottom).x;
  uVar2 = param_4 & 0xffff;
  g_hit_cyl.m_bottom.y = (mapCylinder->m_bottom).y;
  dVar4 = (double)FLOAT_8032f8c0;
  iVar3 = uVar2 * 0x50;
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
  g_hit_mvec.x = vec->x;
  g_hit_mvec.y = vec->y;
  g_hit_mvec.z = vec->z;
  while( true ) {
    if ((int)(param_5 + param_4 & 0xffff) <= (int)uVar2) {
      return 0;
    }
    DAT_8032ec8c = &mapHit->m_faces->field_0x0 + iVar3;
    FLOAT_8032ec80 = (float)dVar4;
    iVar1 = CheckHitFaceCylinder__7CMapHitFUl(mapHit,param_6);
    if (iVar1 != 0) break;
    iVar3 = iVar3 + 0x50;
    uVar2 = uVar2 + 1;
  }
  return 1;
}

