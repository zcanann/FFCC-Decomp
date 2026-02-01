// Function: AttachMapHit__7CMapMngFP7CMapHitPc
// Entry: 80032fd0
// Size: 252 bytes

void AttachMapHit__7CMapMngFP7CMapHitPc(CMapMng *mapMng,CMapHit *mapHit,undefined4 unkString)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  CMapObj *pCVar4;
  
  pCVar4 = mapMng->mapObjArr;
  do {
    uVar3 = (uint)((int)(mapMng->mapObjArr + mapMng->field10_0xc) + (0xef - (int)pCVar4)) / 0xf0;
    if (pCVar4 < mapMng->mapObjArr + mapMng->field10_0xc) {
      do {
        if ((*(int *)&pCVar4->field_0xec != 0) && (*(int *)(*(int *)&pCVar4->field_0xec + 4) == 3))
        goto LAB_800330a4;
        pCVar4 = pCVar4 + 1;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
    pCVar4 = (CMapObj *)0x0;
LAB_800330a4:
    if (pCVar4 == (CMapObj *)0x0) {
      return;
    }
    iVar1 = strcmp(unkString,*(int *)&pCVar4->field_0xec + 8);
    if (iVar1 == 0) {
      pCVar4->field12_0xc = mapHit;
      piVar2 = *(int **)&pCVar4->field_0xec;
      if (piVar2 != (int *)0x0) {
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 8))(piVar2,1);
        }
        *(undefined4 *)&pCVar4->field_0xec = 0;
      }
    }
    pCVar4 = pCVar4 + 1;
  } while( true );
}

