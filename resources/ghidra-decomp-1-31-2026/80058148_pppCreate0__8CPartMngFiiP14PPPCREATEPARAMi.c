// Function: pppCreate0__8CPartMngFiiP14PPPCREATEPARAMi
// Entry: 80058148
// Size: 1632 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int pppCreate0__8CPartMngFiiP14PPPCREATEPARAMi
              (CPartMng *partMng,int pdtSlotIndex,int param_3,PPPCREATEPARAM *pppCreateParam,
              int param_5)

{
  byte bVar1;
  undefined2 uVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  Vec *pVVar6;
  int16_t iVar7;
  int iVar8;
  int32_t iVar9;
  CPartMng *pCVar10;
  _pppDataHead *p_Var11;
  pppPdtSlot *ppVar12;
  _pppMngSt *p_Var13;
  int iVar14;
  double dVar15;
  
  ppVar12 = partMng->m_pdtSlots + pdtSlotIndex;
  if ((ppVar12 == (pppPdtSlot *)0x0) || (ppVar12->m_pppDataHead == (_pppDataHead *)0x0)) {
    return -1;
  }
  iVar8 = 0;
  p_Var11 = ppVar12->m_pppDataHead + param_3 * 3 + 1;
  iVar14 = 0x180;
  pCVar10 = partMng;
  do {
    if (pCVar10->m_pppMngStArr[0].m_baseTime == -0x1000) {
      p_Var13 = partMng->m_pppMngStArr + iVar8;
      goto LAB_800581dc;
    }
    pCVar10 = (CPartMng *)pCVar10->m_rgbaA;
    iVar8 = iVar8 + 1;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  p_Var13 = (_pppMngSt *)0x0;
LAB_800581dc:
  if (p_Var13 == (_pppMngSt *)0x0) {
    return -1;
  }
  if (System.m_execParam != 0) {
    iVar8 = (int)p_Var13 - (int)partMng->m_pppMngStArr;
    iVar8 = iVar8 / 0x158 + (iVar8 >> 0x1f);
    Printf__7CSystemFPce
              (&System,s_pppCreate0_pdtID__d_fpno__d_mngN_801d823c,pdtSlotIndex,param_3,
               iVar8 - (iVar8 >> 0x1f),partMng->m_pdtSlots[pdtSlotIndex].m_name);
  }
  *(undefined4 *)&p_Var13->field_0x104 = 0xffffffff;
  p_Var13->m_prioTime = 0;
  p_Var13->m_kind = (int16_t)pdtSlotIndex;
  p_Var13->m_nodeIndex = (int16_t)param_3;
  (p_Var13->m_hitParams).m_particleIndex = pppCreateParam->m_hitParamA;
  (p_Var13->m_hitParams).m_classId = pppCreateParam->m_hitParamB;
  (p_Var13->m_hitParams).m_hitObjectCount = pppCreateParam->m_hitObjectCount;
  (p_Var13->m_hitParams).m_hitFlags = pppCreateParam->m_hitFlags;
  iVar9 = pppCreateParam->m_hitObjectIds[1];
  *(int32_t *)p_Var13->m_hitObjectIds = pppCreateParam->m_hitObjectIds[0];
  *(int32_t *)(p_Var13->m_hitObjectIds + 2) = iVar9;
  iVar9 = pppCreateParam->m_hitObjectIds[3];
  *(int32_t *)(p_Var13->m_hitObjectIds + 4) = pppCreateParam->m_hitObjectIds[2];
  *(int32_t *)(p_Var13->m_hitObjectIds + 6) = iVar9;
  iVar9 = pppCreateParam->m_hitObjectIds[5];
  *(int32_t *)(p_Var13->m_hitObjectIds + 8) = pppCreateParam->m_hitObjectIds[4];
  *(int32_t *)(p_Var13->m_hitObjectIds + 10) = iVar9;
  iVar9 = pppCreateParam->m_hitObjectIds[7];
  *(int32_t *)(p_Var13->m_hitObjectIds + 0xc) = pppCreateParam->m_hitObjectIds[6];
  *(int32_t *)(p_Var13->m_hitObjectIds + 0xe) = iVar9;
  p_Var13->m_mapTexLoaded = '\0';
  p_Var13->m_hasMapRef = '\0';
  p_Var13->m_envColorR = '\0';
  p_Var13->m_envColorG = '\0';
  p_Var13->m_envColorB = '\x13';
  p_Var13->m_envColorA = '3';
  if (((PartPcs.m_usbStreamData.m_miruraEventActive != '\0') && (pdtSlotIndex == 7)) &&
     (param_3 == 0)) {
    p_Var13->m_envColorR = '\0';
    p_Var13->m_envColorG = '\0';
    p_Var13->m_envColorB = '\x10';
    p_Var13->m_envColorA = '\0';
  }
  (p_Var13->m_soundEffectData).m_soundEffectSlot =
       (pppCreateParam->m_soundEffectParams).m_soundEffectSlot;
  (p_Var13->m_soundEffectData).m_soundEffectStopFlag =
       (pppCreateParam->m_soundEffectParams).m_soundEffectStopFlag;
  (p_Var13->m_soundEffectData).m_soundEffectKind =
       (pppCreateParam->m_soundEffectParams).m_soundEffectKind;
  (p_Var13->m_soundEffectData).m_soundEffectStartedOnce =
       (pppCreateParam->m_soundEffectParams).m_soundEffectStartedOnce;
  (p_Var13->m_soundEffectData).unkSoundEffectRelated =
       (pppCreateParam->m_soundEffectParams).unkSoundEffectRelated;
  (p_Var13->m_soundEffectData).m_soundEffectStartFrame =
       (pppCreateParam->m_soundEffectParams).m_soundEffectStartFrame;
  (p_Var13->m_soundEffectData).m_soundEffectFadeFrames =
       (pppCreateParam->m_soundEffectParams).m_soundEffectFadeFrames;
  (p_Var13->m_soundEffectData).m_soundEffectHandle =
       (pppCreateParam->m_soundEffectParams).m_soundEffectHandle;
  (p_Var13->m_soundEffectData).m_soundEffectStartFrame =
       (p_Var13->m_soundEffectData).m_soundEffectStartFrame << 0xc;
  p_Var13->field37_0xe6 = '\0';
  p_Var13->m_endRequested = '\0';
  p_Var13->m_stopRequested = '\0';
  p_Var13->m_isVisible = '\x01';
  p_Var13->m_ownerVisible = '\x01';
  if (*(int *)&p_Var11[1].m_shapeGroupCount == -0x1000) {
    p_Var13->m_baseTime = 0;
  }
  else {
    iVar8 = *(int *)&p_Var11[1].m_shapeGroupCount * 0x19;
    iVar8 = iVar8 / 0x1e + (iVar8 >> 0x1f);
    p_Var13->m_baseTime = iVar8 - (iVar8 >> 0x1f);
  }
  p_Var13->m_pppResSet = ppVar12;
  dVar3 = DOUBLE_8032fe08;
  p_Var13->m_partIndex = p_Var11[1].m_cacheChunks;
  p_Var13->m_cullRadiusSq = (float)p_Var11[1].m_modelNames;
  dVar15 = (double)p_Var13->m_cullRadiusSq;
  if (dVar3 < dVar15) {
    p_Var13->m_cullRadiusSq = (float)(dVar15 * dVar15);
  }
  p_Var13->m_cullRadius = (float)p_Var11[1].m_shapeNames;
  p_Var13->m_cullYOffset = (float)p_Var11[1].m_shapeGroups;
  (p_Var13->m_pppPObjLinkHead).m_next = (pppPObjLink *)0x0;
  p_Var13->m_pppPDataVals = (_pppPDataVal *)0x0;
  *(undefined2 *)&p_Var13->field_0xfc = *(undefined2 *)&p_Var11[2].m_version;
  *(undefined2 *)&p_Var13->field_0x118 = *(undefined2 *)((int)&p_Var11[2].m_version + 2);
  p_Var13->field38_0xe7 = *(uint8_t *)((int)&p_Var11[2].m_partCount + 1);
  p_Var13->field42_0xeb = *(uint8_t *)&p_Var11[2].m_cacheChunkCount;
  p_Var13->m_rotOrder = *(uint8_t *)((int)&p_Var11[2].m_cacheChunkCount + 1);
  p_Var13->m_drawMode = *(uint8_t *)&p_Var11[2].m_partCount;
  p_Var13->m_primTypeOrLayer = *(int8_t *)&p_Var11[2].m_shapeGroupCount;
  p_Var13->m_lockVisFromOwner = *(uint8_t *)((int)&p_Var11[2].m_shapeGroupCount + 1);
  p_Var13->m_lockScaleFromOwner = p_Var11[2].field_0xe;
  p_Var13->field49_0xf2 = '\x01';
  if (param_5 == 0) goto LAB_80058464;
  bVar1 = *(byte *)((int)&p_Var11[2].m_partCount + 1);
  if (bVar1 == 4) {
LAB_8005845c:
    p_Var13->field49_0xf2 = p_Var11[2].field_0xf;
  }
  else if (bVar1 < 4) {
    if (bVar1 < 3) goto LAB_8005845c;
  }
  else if (8 < bVar1) goto LAB_8005845c;
LAB_80058464:
  p_Var13->m_fpBillboard = *(uint8_t *)&p_Var11[2].m_shapeCount;
  p_Var13->m_prio = *(uint8_t *)((int)&p_Var11[2].m_shapeCount + 1);
  p_Var13->m_mapObjIndex = p_Var11[2].m_modelCount;
  (p_Var13->m_velocity).z = 0.0;
  p_Var13->m_objHitMask = pppCreateParam->m_objectHitMask;
  p_Var13->m_cylinderAttribute = pppCreateParam->m_cylinderAttribute;
  *(uint32_t *)&p_Var13->field_0x100 = pppCreateParam->m_paramA;
  p_Var13->m_paramC = pppCreateParam->m_paramC;
  p_Var13->m_paramD = pppCreateParam->m_paramD;
  if (pppCreateParam->m_positionOffsetPtr == (Vec *)0x0) {
    (p_Var13->m_position).x = (float)p_Var11->m_version;
    (p_Var13->m_position).y = *(float *)&p_Var11->m_partCount;
    (p_Var13->m_position).z = *(float *)&p_Var11->m_modelCount;
    (p_Var13->m_savedPosition).x = (p_Var13->m_position).x;
    (p_Var13->m_savedPosition).y = (p_Var13->m_position).y;
    (p_Var13->m_savedPosition).z = (p_Var13->m_position).z;
    (p_Var13->m_previousPosition).x = (p_Var13->m_savedPosition).x;
    (p_Var13->m_previousPosition).y = (p_Var13->m_savedPosition).y;
    (p_Var13->m_previousPosition).z = (p_Var13->m_savedPosition).z;
  }
  else {
    (p_Var13->m_position).x = pppCreateParam->m_positionOffsetPtr->x + (float)p_Var11->m_version;
    (p_Var13->m_position).y =
         pppCreateParam->m_positionOffsetPtr->y + *(float *)&p_Var11->m_partCount;
    (p_Var13->m_position).z =
         pppCreateParam->m_positionOffsetPtr->z + *(float *)&p_Var11->m_modelCount;
    (p_Var13->m_savedPosition).x = (p_Var13->m_position).x;
    (p_Var13->m_savedPosition).y = (p_Var13->m_position).y;
    (p_Var13->m_savedPosition).z = (p_Var13->m_position).z;
    (p_Var13->m_previousPosition).x = (p_Var13->m_savedPosition).x;
    (p_Var13->m_previousPosition).y = (p_Var13->m_savedPosition).y;
    (p_Var13->m_previousPosition).z = (p_Var13->m_savedPosition).z;
  }
  pVVar6 = pppCreateParam->m_extraPositionPtr;
  if (pVVar6 != (Vec *)0x0) {
    (p_Var13->m_paramVec0).x = pVVar6->x;
    (p_Var13->m_paramVec0).y = pVVar6->y;
    (p_Var13->m_paramVec0).z = pVVar6->z;
    (p_Var13->m_paramVec0).x = (p_Var13->m_paramVec0).x + (float)p_Var11->m_version;
    (p_Var13->m_paramVec0).y = (p_Var13->m_paramVec0).y + *(float *)&p_Var11->m_partCount;
    (p_Var13->m_paramVec0).z = (p_Var13->m_paramVec0).z + *(float *)&p_Var11->m_modelCount;
  }
  fVar5 = FLOAT_8032fe14;
  fVar4 = FLOAT_8032fe10;
  if (pppCreateParam->m_rotationPtr == (Vec *)0x0) {
    uVar2 = *(undefined2 *)((int)&p_Var11->m_cacheChunks + 2);
    (p_Var13->m_rotation).x = *(undefined2 *)&p_Var11->m_cacheChunks;
    (p_Var13->m_rotation).y = uVar2;
    uVar2 = *(undefined2 *)((int)&p_Var11->m_modelNames + 2);
    (p_Var13->m_rotation).z = *(undefined2 *)&p_Var11->m_modelNames;
    (p_Var13->m_rotation).w = uVar2;
    p_Var13->m_rotationSpeed = p_Var11->m_shapeNames;
  }
  else {
    iVar8 = (int)((FLOAT_8032fe10 * pppCreateParam->m_rotationPtr->x) / FLOAT_8032fe14);
    (p_Var13->m_rotation).x = (short)((uint)iVar8 >> 0x10);
    (p_Var13->m_rotation).y = (short)iVar8;
    iVar8 = (int)((fVar4 * pppCreateParam->m_rotationPtr->y) / fVar5);
    (p_Var13->m_rotation).z = (short)((uint)iVar8 >> 0x10);
    (p_Var13->m_rotation).w = (short)iVar8;
    p_Var13->m_rotationSpeed = (int)((fVar4 * pppCreateParam->m_rotationPtr->z) / fVar5);
  }
  if (pppCreateParam->m_scalePtr == (Vec *)0x0) {
    (p_Var13->m_scale).x = (float)p_Var11[1].m_version;
    (p_Var13->m_scale).y = *(float *)&p_Var11[1].m_partCount;
    (p_Var13->m_scale).z = *(float *)&p_Var11[1].m_modelCount;
  }
  else {
    (p_Var13->m_scale).x = pppCreateParam->m_scalePtr->x * (float)p_Var11[1].m_version;
    (p_Var13->m_scale).y = pppCreateParam->m_scalePtr->y * *(float *)&p_Var11[1].m_partCount;
    (p_Var13->m_scale).z = pppCreateParam->m_scalePtr->z * *(float *)&p_Var11[1].m_modelCount;
  }
  fVar4 = FLOAT_8032fe18;
  (p_Var13->m_velocity).y = (float)pppCreateParam->m_lookTargetPtr;
  p_Var13->m_ownerScale = fVar4;
  p_Var13->m_scaleFactor = fVar4;
  p_Var13->m_userFloat1 = fVar4;
  p_Var13->m_userFloat0 = fVar4;
  p_Var13->m_ownerScaleMode = '\0';
  (p_Var13->m_velocity).x = 0.0;
  bVar1 = *(byte *)((int)&p_Var11[2].m_partCount + 1);
  if (bVar1 == 4) {
LAB_80058700:
    iVar7 = GetMapObjEffectIdx__7CMapMngFUs(&MapMng,p_Var11[2].m_modelCount);
    p_Var13->m_mapObjIndex = iVar7;
  }
  else {
    if (bVar1 < 4) {
      if (bVar1 == 2) goto LAB_80058700;
      if (bVar1 < 2) goto LAB_80058774;
    }
    else if (8 < bVar1) goto LAB_80058774;
    p_Var13->m_ownerVisible = '\0';
    (p_Var13->m_velocity).x = (float)pppCreateParam->m_paramB;
    (p_Var13->m_velocity).y = (float)pppCreateParam->m_lookTargetPtr;
    if ((pppCreateParam->m_paramB != (CGObject *)0x0) &&
       (iVar8 = SearchNodeSk__Q26CChara6CModelFPc
                          (pppCreateParam->m_paramB->m_charaModelHandle->m_model,
                           &p_Var11[2].m_cacheChunks), -1 < iVar8)) {
      (p_Var13->m_velocity).z =
           (float)(pppCreateParam->m_paramB->m_charaModelHandle->m_model->m_nodes + iVar8);
    }
  }
LAB_80058774:
  iVar8 = (int)p_Var13 - (int)partMng->m_pppMngStArr;
  iVar8 = iVar8 / 0x158 + (iVar8 >> 0x1f);
  return iVar8 - (iVar8 >> 0x1f);
}

