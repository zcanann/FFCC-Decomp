// Function: objectCollision__8CGObjectFv
// Entry: 80080d04
// Size: 1556 bytes

/* WARNING: Removing unreachable block (ram,0x800812fc) */
/* WARNING: Removing unreachable block (ram,0x800812f4) */
/* WARNING: Removing unreachable block (ram,0x800812ec) */
/* WARNING: Removing unreachable block (ram,0x80080d24) */
/* WARNING: Removing unreachable block (ram,0x80080d1c) */
/* WARNING: Removing unreachable block (ram,0x80080d14) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void objectCollision__8CGObjectFv(CGObject *gObject)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  CGQuadObj *gQuadObj;
  CGObject *gObject_00;
  CGObject *pCVar4;
  int iVar5;
  CGObject **ppCVar6;
  CGObject **ppCVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  Vec VStack_d8;
  Vec local_cc;
  CGObject *local_c0;
  Vec VStack_bc;
  Vec VStack_b0;
  Vec local_a4;
  CGObject *local_98;
  Vec VStack_94;
  Vec VStack_88;
  Vec local_7c;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  
  bVar1 = false;
  local_98 = gObject;
  PSVECAdd(&gObject->m_worldPosition,&gObject->m_groundHitOffset,&VStack_94);
  dVar9 = (double)sin((double)gObject->m_rotBaseY);
  local_7c.y = FLOAT_80330350;
  local_7c.x = gObject->m_bodyEllipsoidOffset * -(float)dVar9;
  dVar9 = (double)cos((double)gObject->m_rotBaseY);
  local_7c.z = gObject->m_bodyEllipsoidOffset * -(float)dVar9;
  PSVECAdd(&VStack_94,&local_7c,&VStack_88);
  if ((gObject->m_bgColMask & 0x10000) != 0) {
    for (gQuadObj = (CGQuadObj *)FindGQuadObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        gQuadObj != (CGQuadObj *)0x0;
        gQuadObj = (CGQuadObj *)
                   FindGQuadObjNext__13CFlatRuntime2FP9CGQuadObj((CFlatRuntime2 *)&CFlat,gQuadObj))
    {
      iVar5 = isInner__9CGQuadObjFP3Vec(gQuadObj,&VStack_94);
      if (iVar5 != 0) {
        (**(code **)((int)(gQuadObj->field0_0x0).object.m_vtable + 0x14))(gQuadObj,gObject,0);
      }
    }
  }
  gObject_00 = (CGObject *)FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject)
  ;
  for (; gObject_00 != (CGObject *)0x0;
      gObject_00 = (CGObject *)
                   FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject_00)) {
    if (((gObject->m_bgColMask & 0xe) != 0) && ((gObject_00->m_bgColMask & 0xe) != 0)) {
      local_c0 = gObject_00;
      PSVECAdd(&gObject_00->m_worldPosition,&gObject_00->m_groundHitOffset,&VStack_bc);
      dVar9 = (double)sin((double)gObject_00->m_rotBaseY);
      local_a4.y = FLOAT_80330350;
      local_a4.x = gObject_00->m_bodyEllipsoidOffset * -(float)dVar9;
      dVar9 = (double)cos((double)gObject_00->m_rotBaseY);
      local_a4.z = gObject_00->m_bodyEllipsoidOffset * -(float)dVar9;
      PSVECAdd(&VStack_bc,&local_a4,&VStack_b0);
      dVar9 = (double)PSVECDistance(&VStack_b0,&VStack_88);
      if (((double)FLOAT_80330350 != dVar9) &&
         (dVar9 <= (double)(gObject->m_nearColRadius + gObject_00->m_nearColRadius))) {
        if (((gObject->m_bgColMask & 8) != 0) && ((gObject_00->m_bgColMask & 8) != 0)) {
          uVar3 = gObject->m_objectFlags & 2;
          if ((((uVar3 != 0) && ((gObject_00->m_objectFlags & 0xc) != 0)) ||
              (((gObject->m_objectFlags & 0xc) != 0 && ((gObject_00->m_objectFlags & 2) != 0)))) &&
             ((((*(byte *)&gObject->m_weaponNodeFlags & 1) == 0 ||
               (gObject->m_attachOwner != gObject_00)) &&
              ((((*(byte *)&gObject_00->m_weaponNodeFlags & 1) == 0 ||
                (gObject_00->m_attachOwner != gObject)) &&
               (dVar9 < (double)(gObject->m_attackColRadius + gObject_00->m_attackColRadius))))))) {
            if (uVar3 == 0) {
              ppCVar7 = &local_c0;
              ppCVar6 = &local_98;
            }
            else {
              ppCVar7 = &local_98;
              ppCVar6 = &local_c0;
            }
            PSVECSubtract((Vec *)(ppCVar6 + 4),(Vec *)(ppCVar7 + 4),&local_cc);
            dVar10 = (double)atan2((double)local_cc.x,(double)local_cc.z);
            dVar10 = (double)DstRot__5CMathFff((double)(*ppCVar7)->m_rotBaseY,(double)(float)dVar10,
                                               &Math);
            pCVar4 = *ppCVar7;
            if (ABS(dVar10) < (double)pCVar4->m_frontHitAngle) {
              (**(code **)((int)(pCVar4->base_object).object.m_vtable + 0x18))(pCVar4,*ppCVar6,1);
              (**(code **)((int)((*ppCVar6)->base_object).object.m_vtable + 0x18))
                        (*ppCVar6,*ppCVar7,0);
            }
          }
        }
        if ((((gObject->m_bgColMask & 4) != 0) && ((gObject_00->m_bgColMask & 4) != 0)) &&
           (dVar9 < (double)(gObject->m_bodyColRadius + gObject_00->m_bodyColRadius))) {
          (**(code **)((int)(gObject->base_object).object.m_vtable + 0x14))(gObject,gObject_00,1);
          (**(code **)((int)(gObject_00->base_object).object.m_vtable + 0x14))(gObject_00,gObject,0)
          ;
        }
        if (((((gObject->m_bgColMask & 2) != 0) && ((gObject_00->m_bgColMask & 2) != 0)) &&
            ((FLOAT_80330350 < gObject->m_bodyEllipsoidRadius &&
             (FLOAT_80330350 < gObject_00->m_bodyEllipsoidRadius)))) &&
           ((((*(byte *)&gObject->m_weaponNodeFlags & 1) == 0 ||
             (gObject->m_attachOwner != gObject_00)) &&
            (((*(byte *)&gObject_00->m_weaponNodeFlags & 1) == 0 ||
             (gObject_00->m_attachOwner != gObject)))))) {
          bVar2 = false;
          if (((gObject->m_objectFlags & 0x40) != 0) && ((gObject_00->m_objectFlags & 0x40) != 0)) {
            bVar2 = true;
          }
          dVar10 = (double)(gObject->m_bodyEllipsoidRadius + gObject_00->m_bodyEllipsoidRadius);
          if (dVar9 < dVar10) {
            if ((bVar2) &&
               ((((FLOAT_80330350 != (gObject->m_groundHitOffset).x ||
                  (FLOAT_80330350 != (gObject->m_groundHitOffset).z)) ||
                 (FLOAT_80330350 != (gObject_00->m_groundHitOffset).x)) ||
                (FLOAT_80330350 != (gObject_00->m_groundHitOffset).z)))) {
              bVar1 = true;
            }
            if (((!bVar2) || (gObject->m_collisionPushTimerMax != 0)) ||
               (gObject_00->m_collisionPushTimerMax == 0)) {
              uStack_6c = (uint)gObject->m_pushParamA + (uint)gObject->m_pushParamB ^ 0x80000000;
              local_70 = 0x43300000;
              uStack_64 = (uint)gObject_00->m_pushParamA + (uint)gObject_00->m_pushParamB ^
                          0x80000000;
              local_68 = 0x43300000;
              dVar11 = (double)FLOAT_80330350;
              dVar8 = (double)(FLOAT_80330368 +
                              ((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80330348) -
                              (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80330348)) /
                              FLOAT_80330424);
              if ((dVar11 <= dVar8) && (dVar11 = dVar8, (double)FLOAT_80330338 < dVar8)) {
                dVar11 = (double)FLOAT_80330338;
              }
              PSVECSubtract(&VStack_88,&VStack_b0,&local_cc);
              PSVECScale((float)((double)(float)(dVar10 - dVar9) / dVar10),&local_cc,&local_cc);
              PSVECScale((float)((double)FLOAT_80330338 - dVar11),&local_cc,&VStack_d8);
              PSVECAdd(&VStack_88,&VStack_d8,&VStack_88);
              PSVECScale((float)-dVar11,&local_cc,&VStack_d8);
              PSVECAdd(&VStack_b0,&VStack_d8,&VStack_b0);
            }
          }
        }
        PSVECSubtract(&VStack_b0,&gObject_00->m_worldPosition,&gObject_00->m_groundHitOffset);
        PSVECSubtract(&gObject_00->m_groundHitOffset,&local_a4,&gObject_00->m_groundHitOffset);
      }
    }
  }
  if (bVar1) {
    iVar5 = gObject->m_collisionPushTimerMax + -1;
    gObject->m_collisionPushTimerMax = (ushort)iVar5 & ~(ushort)(iVar5 >> 0x1f);
  }
  else {
    gObject->m_collisionPushTimerMax = 0x32;
  }
  PSVECSubtract(&VStack_88,&gObject->m_worldPosition,&gObject->m_groundHitOffset);
  PSVECSubtract(&gObject->m_groundHitOffset,&local_7c,&gObject->m_groundHitOffset);
  return;
}

