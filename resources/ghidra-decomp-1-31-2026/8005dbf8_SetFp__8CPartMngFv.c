// Function: SetFp__8CPartMngFv
// Entry: 8005dbf8
// Size: 632 bytes

/* WARNING: Removing unreachable block (ram,0x8005de54) */
/* WARNING: Removing unreachable block (ram,0x8005de4c) */
/* WARNING: Removing unreachable block (ram,0x8005dc10) */
/* WARNING: Removing unreachable block (ram,0x8005dc08) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetFp__8CPartMngFv(CPartMng *partMng)

{
  byte bVar1;
  void *pvVar2;
  float *pfVar3;
  int16_t iVar5;
  int iVar4;
  int iVar6;
  CPartMng *pCVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  
  dVar11 = (double)FLOAT_8032fe18;
  iVar6 = 0;
  iVar8 = 0;
  pCVar7 = partMng;
  dVar10 = DOUBLE_8032fe08;
  do {
    if (partMng->m_editCount <= iVar6) {
      return;
    }
    pvVar2 = partMng->m_recvBuff;
    pCVar7->m_pppMngStArr[0].m_pppResSet = &partMng->m_unk0x23518;
    pfVar3 = (float *)((int)pvVar2 + iVar8);
    if (pCVar7->m_pppMngStArr[0].m_baseTime < 0) {
      pCVar7->m_pppMngStArr[0].m_baseTime = (int32_t)pfVar3[0xb];
    }
    else {
      iVar4 = ((int)pfVar3[0xb] * 0x19) / 0x1e + ((int)pfVar3[0xb] * 0x19 >> 0x1f);
      pCVar7->m_pppMngStArr[0].m_baseTime = iVar4 - (iVar4 >> 0x1f);
    }
    pCVar7->m_pppMngStArr[0].m_cullRadiusSq = pfVar3[0xd];
    dVar9 = (double)pCVar7->m_pppMngStArr[0].m_cullRadiusSq;
    if (dVar10 < dVar9) {
      pCVar7->m_pppMngStArr[0].m_cullRadiusSq = (float)(dVar9 * dVar9);
    }
    pCVar7->m_pppMngStArr[0].m_nodeIndex = (int16_t)iVar6;
    pCVar7->m_pppMngStArr[0].m_cullRadius = pfVar3[0xe];
    pCVar7->m_pppMngStArr[0].m_cullYOffset = pfVar3[0xf];
    pCVar7->m_pppMngStArr[0].m_position.x = *pfVar3;
    pCVar7->m_pppMngStArr[0].m_position.y = pfVar3[1];
    pCVar7->m_pppMngStArr[0].m_position.z = pfVar3[2];
    *(float *)&pCVar7->m_pppMngStArr[0].m_rotation = pfVar3[4];
    *(float *)&pCVar7->m_pppMngStArr[0].m_rotation.z = pfVar3[5];
    pCVar7->m_pppMngStArr[0].m_rotationSpeed = (int32_t)pfVar3[6];
    pCVar7->m_pppMngStArr[0].m_scale.x = pfVar3[8];
    pCVar7->m_pppMngStArr[0].m_scale.y = pfVar3[9];
    pCVar7->m_pppMngStArr[0].m_scale.z = pfVar3[10];
    pCVar7->m_pppMngStArr[0].m_ownerScale = (float)dVar11;
    pCVar7->m_pppMngStArr[0].m_scaleFactor = (float)dVar11;
    pCVar7->m_pppMngStArr[0].m_userFloat1 = (float)dVar11;
    pCVar7->m_pppMngStArr[0].m_userFloat0 = (float)dVar11;
    pCVar7->m_pppMngStArr[0].m_ownerScaleMode = '\0';
    pCVar7->m_pppMngStArr[0].field38_0xe7 = *(uint8_t *)((int)pfVar3 + 0x45);
    pCVar7->m_pppMngStArr[0].field42_0xeb = *(uint8_t *)((int)pfVar3 + 0x46);
    pCVar7->m_pppMngStArr[0].m_rotOrder = *(uint8_t *)((int)pfVar3 + 0x47);
    pCVar7->m_pppMngStArr[0].m_drawMode = *(uint8_t *)(pfVar3 + 0x11);
    pCVar7->m_pppMngStArr[0].m_primTypeOrLayer = *(int8_t *)(pfVar3 + 0x13);
    pCVar7->m_pppMngStArr[0].m_lockVisFromOwner = *(uint8_t *)((int)pfVar3 + 0x4d);
    pCVar7->m_pppMngStArr[0].m_lockScaleFromOwner = *(uint8_t *)((int)pfVar3 + 0x4e);
    pCVar7->m_pppMngStArr[0].field49_0xf2 = '\x01';
    pCVar7->m_pppMngStArr[0].m_fpBillboard = *(uint8_t *)((int)pfVar3 + 0x4a);
    pCVar7->m_pppMngStArr[0].m_prio = *(uint8_t *)((int)pfVar3 + 0x4b);
    pCVar7->m_pppMngStArr[0].m_mapObjIndex = *(int16_t *)(pfVar3 + 0x12);
    pCVar7->m_pppMngStArr[0].m_velocity.z = 0.0;
    pCVar7->m_pppMngStArr[0].m_objHitMask = 0xffffffff;
    pCVar7->m_pppMngStArr[0].m_cylinderAttribute = 0xffffffff;
    *(undefined4 *)&pCVar7->m_pppMngStArr[0].field_0x100 = 0;
    pCVar7->m_pppMngStArr[0].m_endRequested = '\0';
    pCVar7->m_pppMngStArr[0].m_isVisible = '\x01';
    pCVar7->m_pppMngStArr[0].m_ownerVisible = '\x01';
    pCVar7->m_pppMngStArr[0].m_velocity.x = 0.0;
    bVar1 = pCVar7->m_pppMngStArr[0].field38_0xe7;
    if (bVar1 == 4) {
LAB_8005ddc0:
      iVar5 = GetMapObjEffectIdx__7CMapMngFUs(&MapMng,*(undefined2 *)(pfVar3 + 0x12));
      pCVar7->m_pppMngStArr[0].m_mapObjIndex = iVar5;
    }
    else if (bVar1 < 4) {
      if (bVar1 == 2) goto LAB_8005ddc0;
      if (1 < bVar1) goto LAB_8005dddc;
    }
    else if (bVar1 < 9) {
LAB_8005dddc:
      pCVar7->m_pppMngStArr[0].m_ownerVisible = '\0';
      pCVar7->m_pppMngStArr[0].m_velocity.x = *(float *)(partMng->m_usbEdit + 0x1c);
      pCVar7->m_pppMngStArr[0].m_velocity.y = *(float *)(partMng->m_usbEdit + 0x1c);
      if ((*(int *)(partMng->m_usbEdit + 0x1c) != 0) &&
         (iVar4 = SearchNodeSk__Q26CChara6CModelFPc
                            (*(CModel **)
                              (*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 0x168),
                             pfVar3 + 0x14), -1 < iVar4)) {
        pCVar7->m_pppMngStArr[0].m_velocity.z =
             (float)(*(int *)(*(int *)(*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 0x168)
                             + 0xa8) + iVar4 * 0xc0);
      }
    }
    iVar8 = iVar8 + 0x60;
    pCVar7 = (CPartMng *)pCVar7->m_rgbaA;
    iVar6 = iVar6 + 1;
  } while( true );
}

