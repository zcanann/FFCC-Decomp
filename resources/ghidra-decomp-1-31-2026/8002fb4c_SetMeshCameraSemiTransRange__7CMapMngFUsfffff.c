// Function: SetMeshCameraSemiTransRange__7CMapMngFUsfffff
// Entry: 8002fb4c
// Size: 360 bytes

void SetMeshCameraSemiTransRange__7CMapMngFUsfffff
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               CMapMng *mapMng,short param_7)

{
  float fVar1;
  CMapMng *pCVar2;
  bool bVar3;
  int iVar4;
  
  bVar3 = false;
  pCVar2 = mapMng;
  for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
    if (*(short *)&pCVar2->mapObjArr[0].field_0x34 == param_7) {
      *(float *)&pCVar2->mapObjArr[0].field_0x44 = (float)param_1;
      *(float *)&pCVar2->mapObjArr[0].field_0x48 = (float)param_2;
      *(float *)&pCVar2->mapObjArr[0].field_0x54 = (float)param_5;
      *(float *)&pCVar2->mapObjArr[0].field_0x4c = (float)param_3;
      *(float *)&pCVar2->mapObjArr[0].field_0x50 = (float)param_4;
      fVar1 = FLOAT_8032f98c;
      if ((pCVar2->mapObjArr[0].field12_0xc != (CMapHit *)0x0) &&
         (pCVar2->mapObjArr[0].field_0x1f != -1)) {
        *(float *)&pCVar2->mapObjArr[0].field_0x4c = FLOAT_8032f988;
        *(float *)&pCVar2->mapObjArr[0].field_0x50 = fVar1;
        pCVar2->mapObjArr[0].field_0x15 = 2;
        pCVar2->mapObjArr[0].field_0x26 = 1;
      }
      *(undefined2 *)&pCVar2->mapObjArr[0].field_0x2a = 0x4000;
      bVar3 = true;
      *(undefined2 *)&pCVar2->mapObjArr[0].field_0x28 = 0x4000;
      *(undefined2 *)&pCVar2->mapObjArr[0].field_0x2c = 0;
    }
    pCVar2 = (CMapMng *)&pCVar2->octTreeArr[2].field51_0x3c.z;
  }
  if (!bVar3) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d7350,param_7);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_8032f984);
    }
  }
  return;
}

