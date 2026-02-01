// Function: CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUl
// Entry: 80025838
// Size: 332 bytes

/* WARNING: Removing unreachable block (ram,0x8002595c) */
/* WARNING: Removing unreachable block (ram,0x80025848) */

undefined4
CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUl
          (CMapHit *mapHit,CMapCylinder *map_cylinder,Vec *position,uint param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  g_hit_cyl.m_bottom.x = (map_cylinder->m_bottom).x;
  g_hit_cyl.m_bottom.y = (map_cylinder->m_bottom).y;
  dVar4 = (double)FLOAT_8032f8c0;
  iVar2 = 0;
  iVar3 = 0;
  g_hit_cyl.m_bottom.z = (map_cylinder->m_bottom).z;
  g_hit_cyl.m_direction.x = (map_cylinder->m_direction).x;
  g_hit_cyl.m_direction.y = (map_cylinder->m_direction).y;
  g_hit_cyl.m_direction.z = (map_cylinder->m_direction).z;
  g_hit_cyl.m_radius = map_cylinder->m_radius;
  g_hit_cyl.m_height = map_cylinder->m_height;
  g_hit_cyl.m_top.x = (map_cylinder->m_top).x;
  g_hit_cyl.m_top.y = (map_cylinder->m_top).y;
  g_hit_cyl.m_top.z = (map_cylinder->m_top).z;
  g_hit_cyl.m_direction2.x = (map_cylinder->m_direction2).x;
  g_hit_cyl.m_direction2.y = (map_cylinder->m_direction2).y;
  g_hit_cyl.m_direction2.z = (map_cylinder->m_direction2).z;
  g_hit_cyl.m_radius2 = map_cylinder->m_radius2;
  g_hit_cyl.m_height2 = map_cylinder->m_height2;
  g_hit_mvec.x = position->x;
  g_hit_mvec.y = position->y;
  g_hit_mvec.z = position->z;
  while( true ) {
    if ((int)(uint)mapHit->m_faceCount <= iVar2) {
      return 0;
    }
    DAT_8032ec8c = &mapHit->m_faces->field_0x0 + iVar3;
    FLOAT_8032ec80 = (float)dVar4;
    iVar1 = CheckHitFaceCylinder__7CMapHitFUl(mapHit,param_4);
    if (iVar1 != 0) break;
    iVar3 = iVar3 + 0x50;
    iVar2 = iVar2 + 1;
  }
  return 1;
}

