// Function: CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
// Entry: 8002fe6c
// Size: 528 bytes

undefined4
CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
          (CMapMng *mapMng,Vec *param_2,Vec *param_3,undefined4 param_4)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  CMapMng *pCVar4;
  
  fVar1 = param_3->x;
  if (((FLOAT_8032f9a0 == fVar1) && (FLOAT_8032f9a0 == param_3->z)) &&
     (FLOAT_8032f9a0 == param_3->y)) {
    uVar2 = 0;
  }
  else {
    if ((((fVar1 <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= fVar1)) &&
        ((param_3->y <= FLOAT_8032f9a4 &&
         ((FLOAT_8032f9a8 <= param_3->y && (param_3->z <= FLOAT_8032f9a4)))))) &&
       (FLOAT_8032f9a8 <= param_3->z)) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce
                  ((double)param_3->x,(double)param_3->y,(double)param_3->z,&System,&DAT_801d7384);
      }
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801ead4c);
      }
    }
    DAT_8032ec78 = 0xfffffffe;
    FLOAT_8032ec80 = FLOAT_8032f9ac;
    uVar2 = 0;
    PSVECAdd(param_2,param_3,param_2 + 1);
    pCVar4 = mapMng;
    for (iVar3 = 0; iVar3 < mapMng->field8_0x8; iVar3 = iVar3 + 1) {
      DAT_8032ec88 = '\0';
      CheckHitCylinderNear__8COctTreeFP12CMapCylinderP3VecUl
                (pCVar4->octTreeArr,param_2,param_3,param_4);
      if (DAT_8032ec88 != '\0') {
        uVar2 = 1;
        *(void **)&mapMng->field_0x22a78 = pCVar4->octTreeArr[0].field2_0x8;
      }
      pCVar4 = (CMapMng *)&pCVar4->octTreeArr[0].field_0x38;
    }
    pCVar4 = mapMng;
    for (iVar3 = 0; iVar3 < mapMng->field10_0xc; iVar3 = iVar3 + 1) {
      DAT_8032ec88 = '\0';
      CheckHitCylinderNear__7CMapObjFP12CMapCylinderP3VecUl
                (pCVar4->mapObjArr,param_2,param_3,param_4);
      if (DAT_8032ec88 != '\0') {
        uVar2 = 1;
        *(CMapObj **)&mapMng->field_0x22a78 = pCVar4->mapObjArr;
      }
      pCVar4 = (CMapMng *)&pCVar4->octTreeArr[2].field51_0x3c.z;
    }
  }
  return uVar2;
}

