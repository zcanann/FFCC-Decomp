// Function: onDraw__8CGObjectFv
// Entry: 8007df50
// Size: 1180 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDraw__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  Vec *vecA;
  undefined4 *puVar5;
  int iVar6;
  CGObject *pCVar7;
  double dVar8;
  undefined auStack_e8 [4];
  undefined auStack_e4 [4];
  undefined auStack_e0 [4];
  undefined auStack_dc [4];
  undefined auStack_d8 [4];
  undefined auStack_d4 [4];
  undefined4 local_d0;
  undefined auStack_cc [4];
  CVector CStack_c8;
  CVector CStack_bc;
  CVector CStack_b0;
  CVector CStack_a4;
  CVector CStack_98;
  Vec local_8c;
  Mtx MStack_80;
  Mtx MStack_50;
  
  if ((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
           (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6)) < 0) {
    bVar2 = false;
    if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
       (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
      bVar2 = true;
    }
    if (bVar2) {
      if (((CFlat._4764_4_ & 1) != 0) && ((gObject->m_bgColMask & 1) != 0)) {
        uVar3 = __ct__6CColorFUcUcUcUc(auStack_cc,0xff,0,0,0xff);
        uVar4 = __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                   (gObject->m_worldPosition).y + gObject->m_capsuleHalfHeight,
                                   (gObject->m_worldPosition).z,&CStack_98);
        DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                  ((double)gObject->m_capsuleHalfHeight,&Graphic,0x802687ac,uVar4,uVar3);
      }
      if (((CFlat._4764_4_ & 2) != 0) && ((gObject->m_bgColMask & 2) != 0)) {
        __ct__7CVectorFv(&local_8c);
        if (FLOAT_80330350 == gObject->m_bodyEllipsoidOffset) {
          local_8c.z = FLOAT_80330350;
          local_8c.y = FLOAT_80330350;
          local_8c.x = FLOAT_80330350;
        }
        else {
          dVar8 = (double)sin((double)gObject->m_rotBaseY);
          local_8c.y = FLOAT_80330350;
          local_8c.x = gObject->m_bodyEllipsoidOffset * -(float)dVar8;
          dVar8 = (double)cos((double)gObject->m_rotBaseY);
          local_8c.z = gObject->m_bodyEllipsoidOffset * -(float)dVar8;
        }
        fVar1 = gObject->m_bodyEllipsoidRadius;
        PSMTXScale(fVar1 * gObject->m_bodyEllipsoidAspect,fVar1,fVar1,&MStack_50);
        PSMTXRotRad(gObject->m_rotBaseY,&MStack_80,0x79);
        PSMTXConcat(&MStack_80,&MStack_50,&MStack_50);
        vecA = (Vec *)__ct__7CVectorFfff((gObject->m_worldPosition).x,
                                         (gObject->m_worldPosition).y +
                                         gObject->m_bodyEllipsoidRadius,(gObject->m_worldPosition).z
                                         ,&CStack_a4);
        PSVECAdd(vecA,&local_8c,&local_8c);
        MStack_50.value[0][3] = local_8c.x;
        MStack_50.value[1][3] = local_8c.y;
        MStack_50.value[2][3] = local_8c.z;
        PSMTXConcat(&CameraPcs.m_cameraMatrix,&MStack_50,&MStack_50);
        GXLoadPosMtxImm(&MStack_50,0);
        puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_d4,0,0xff,0,0xff);
        local_d0 = *puVar5;
        GXSetChanMatColor(4,&local_d0);
        DrawSphere__8CGraphicFv(&Graphic);
      }
      if (((CFlat._4764_4_ & 4) != 0) && ((gObject->m_bgColMask & 4) != 0)) {
        uVar3 = __ct__6CColorFUcUcUcUc(auStack_d8,0,0,0xff,0xff);
        uVar4 = __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                   (gObject->m_worldPosition).y + gObject->m_bodyColRadius,
                                   (gObject->m_worldPosition).z,&CStack_b0);
        DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                  ((double)gObject->m_bodyColRadius,&Graphic,0x802687ac,uVar4,uVar3);
      }
      if (((CFlat._4764_4_ & 8) != 0) && ((gObject->m_bgColMask & 8) != 0)) {
        uVar3 = __ct__6CColorFUcUcUcUc(auStack_dc,0xff,0xff,0,0xff);
        uVar4 = __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                   (gObject->m_worldPosition).y + gObject->m_attackColRadius,
                                   (gObject->m_worldPosition).z,&CStack_bc);
        DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                  ((double)gObject->m_attackColRadius,&Graphic,0x802687ac,uVar4,uVar3);
      }
      if (((CFlat._4764_4_ & 0x10) != 0) && ((gObject->m_bgColMask & 0x10) != 0)) {
        uVar3 = __ct__6CColorFUcUcUcUc(auStack_e0,0x40,0xff,0x40,0xff);
        DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                  ((double)gObject->m_nearColRadius,&Graphic,0x802687ac,&gObject->m_worldPosition,
                   uVar3);
      }
      if (((CFlat._4764_4_ & 0x40000) != 0) && ((gObject->m_bgColMask & 0x40000) != 0)) {
        iVar6 = 0;
        pCVar7 = gObject;
        do {
          if (pCVar7->m_attackColliders[1].m_localStart.x != 0.0) {
            uVar3 = __ct__6CColorFUcUcUcUc(auStack_e4,0xff,0x80,0x80,0xff);
            DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                      ((double)(float)pCVar7->m_attackColliders[0].m_hitMask,&Graphic,0x802687ac,
                       &pCVar7->m_attackColliders[0].m_worldPosition.y,uVar3);
            GXLoadPosMtxImm(0x802687ac,0);
            GXBegin(0xa8,0,2);
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_localEnd.y;
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_localEnd.z;
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_worldPosition.x;
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_worldPosition.y;
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_worldPosition.z;
            DAT_cc008000 = pCVar7->m_attackColliders[0].m_radius;
          }
          iVar6 = iVar6 + 1;
          pCVar7 = (CGObject *)&(pCVar7->base_object).object.m_particleId;
        } while (iVar6 < 8);
      }
      if (((CFlat._4764_4_ & 0x80000) != 0) && ((gObject->m_bgColMask & 0x80000) != 0)) {
        iVar6 = 0;
        do {
          if (gObject->m_damageColliders[1].m_localPosition.x != 0.0) {
            uVar3 = __ct__6CColorFUcUcUcUc(auStack_e8,0x80,0x80,0xff,0xff);
            fVar1 = (float)gObject->m_damageColliders[0].m_hitMask;
            uVar4 = __ct__7CVectorFfff(fVar1,(float)gObject->m_damageColliders[0].m_active,fVar1,
                                       &CStack_c8);
            DrawSphere__8CGraphicFPA4_fP3VecP3VecP8_GXColor
                      (&Graphic,0x802687ac,&gObject->m_damageColliders[0].m_worldPosition.y,uVar4,
                       uVar3);
          }
          iVar6 = iVar6 + 1;
          gObject = (CGObject *)&(gObject->base_object).object.m_waitCounter;
        } while (iVar6 < 8);
      }
    }
  }
  return;
}

