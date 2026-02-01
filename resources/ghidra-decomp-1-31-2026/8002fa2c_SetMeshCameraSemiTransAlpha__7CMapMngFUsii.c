// Function: SetMeshCameraSemiTransAlpha__7CMapMngFUsii
// Entry: 8002fa2c
// Size: 288 bytes

void SetMeshCameraSemiTransAlpha__7CMapMngFUsii
               (CMapMng *mapMng,short param_2,int param_3,int param_4)

{
  CMapMng *pCVar1;
  bool bVar2;
  int iVar3;
  
  bVar2 = false;
  pCVar1 = mapMng;
  for (iVar3 = 0; iVar3 < mapMng->field10_0xc; iVar3 = iVar3 + 1) {
    if (*(short *)&pCVar1->mapObjArr[0].field_0x34 == param_2) {
      *(short *)&pCVar1->mapObjArr[0].field_0x2a = (short)(param_3 << 7);
      bVar2 = true;
      *(short *)&pCVar1->mapObjArr[0].field_0x2c =
           (short)(((int)*(short *)&pCVar1->mapObjArr[0].field_0x2a -
                   (int)*(short *)&pCVar1->mapObjArr[0].field_0x28) / param_4);
    }
    pCVar1 = (CMapMng *)&pCVar1->octTreeArr[2].field51_0x3c.z;
  }
  if (!bVar2) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801ead4c);
    }
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d7318,param_2);
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

