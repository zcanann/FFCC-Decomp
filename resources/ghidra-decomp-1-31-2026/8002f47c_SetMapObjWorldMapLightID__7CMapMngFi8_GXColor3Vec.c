// Function: SetMapObjWorldMapLightID__7CMapMngFi8_GXColor3Vec
// Entry: 8002f47c
// Size: 204 bytes

void SetMapObjWorldMapLightID__7CMapMngFi8_GXColor3Vec
               (CMapMng *mapMng,short param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  CMapMng *pCVar7;
  undefined local_18;
  undefined uStack_17;
  undefined uStack_16;
  undefined uStack_15;
  
  iVar5 = 0;
  iVar2 = (int)mapMng->field10_0xc;
  pCVar7 = mapMng;
  if (0 < iVar2) {
    do {
      if (*(short *)&pCVar7->mapObjArr[0].field_0x2e == param_2) goto LAB_8002f4bc;
      pCVar7 = (CMapMng *)&pCVar7->octTreeArr[2].field51_0x3c.z;
      iVar5 = iVar5 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  iVar5 = -1;
LAB_8002f4bc:
  uVar6 = *param_4;
  uVar1 = param_4[1];
  uVar4 = param_4[2];
  uVar3 = *param_3;
  iVar2 = *(int *)&mapMng->mapObjArr[iVar5].field_0xec;
  if (*(int *)(iVar2 + 4) == 1) {
    local_18 = (undefined)((uint)uVar3 >> 0x18);
    uStack_17 = (undefined)((uint)uVar3 >> 0x10);
    *(undefined *)(iVar2 + 8) = local_18;
    uStack_16 = (undefined)((uint)uVar3 >> 8);
    *(undefined *)(iVar2 + 9) = uStack_17;
    uStack_15 = (undefined)uVar3;
    *(undefined *)(iVar2 + 10) = uStack_16;
    *(undefined *)(iVar2 + 0xb) = uStack_15;
    *(undefined4 *)&mapMng->mapObjArr[iVar5].field_0x70 = uVar6;
    *(undefined4 *)&mapMng->mapObjArr[iVar5].field_0x74 = uVar1;
    *(undefined4 *)&mapMng->mapObjArr[iVar5].field_0x78 = uVar4;
    mapMng->mapObjArr[iVar5].field_0x1c = 1;
    mapMng->mapObjArr[iVar5].field_0x1b = 1;
  }
  return;
}

