// Function: GetDebugPlaySta__7CMapMngFiP3Vec
// Entry: 80032f1c
// Size: 180 bytes

undefined4 GetDebugPlaySta__7CMapMngFiP3Vec(CMapMng *mapMng,uint param_2,Vec *vec)

{
  float fVar1;
  uint uVar2;
  CMapObj *pCVar3;
  
  fVar1 = FLOAT_8032f9a0;
  pCVar3 = mapMng->mapObjArr;
  do {
    uVar2 = (uint)((int)(mapMng->mapObjArr + mapMng->field10_0xc) + (0xef - (int)pCVar3)) / 0xf0;
    if (pCVar3 < mapMng->mapObjArr + mapMng->field10_0xc) {
      do {
        if ((*(int *)&pCVar3->field_0xec != 0) && (*(int *)(*(int *)&pCVar3->field_0xec + 4) == 4))
        goto LAB_80032fb0;
        pCVar3 = pCVar3 + 1;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    pCVar3 = (CMapObj *)0x0;
LAB_80032fb0:
    if (pCVar3 == (CMapObj *)0x0) {
      vec->z = FLOAT_8032f9a0;
      vec->y = fVar1;
      vec->x = fVar1;
      return 0;
    }
    if (*(byte *)(*(int *)&pCVar3->field_0xec + 8) == param_2) {
      vec->x = *(float *)&pCVar3->field_0xc4;
      vec->y = *(float *)&pCVar3->field_0xd4;
      vec->z = *(float *)&pCVar3->field_0xe4;
      return 1;
    }
    pCVar3 = pCVar3 + 1;
  } while( true );
}

