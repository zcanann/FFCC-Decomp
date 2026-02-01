// Function: Interp__12CMapAnimNodeFi
// Entry: 8004a9b4
// Size: 996 bytes

/* WARNING: Removing unreachable block (ram,0x8004ad70) */
/* WARNING: Removing unreachable block (ram,0x8004a9c4) */

void Interp__12CMapAnimNodeFi(CMapAnimNode *mapAnimNode,uint param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  double dVar13;
  Vec VStack_78;
  Vec VStack_6c;
  Vec VStack_60;
  Vec VStack_54;
  Vec VStack_48;
  Vec VStack_3c;
  undefined4 local_30;
  int iStack_2c;
  undefined4 local_28;
  int iStack_24;
  
  iVar8 = *(int *)(*(int *)&mapAnimNode->field_0x4 + 0x1c);
  uVar7 = **(uint **)&mapAnimNode->field_0x8;
  iVar3 = *(int *)mapAnimNode;
  uVar10 = (*(int *)(*(int *)&mapAnimNode->field_0x4 + 0x20) - iVar8) + 1;
  puVar6 = (uint *)(*(uint **)&mapAnimNode->field_0x8)[1];
  uVar12 = iVar8 + (param_2 - (param_2 / uVar10) * uVar10);
  if (uVar7 == 1) {
    ((Vec *)(iVar3 + 100))->x = (float)puVar6[1];
    *(uint *)(iVar3 + 0x68) = puVar6[2];
    *(uint *)(iVar3 + 0x6c) = puVar6[3];
  }
  else {
    iVar8 = 0;
    puVar9 = puVar6;
    for (uVar2 = uVar7; uVar2 != 0; uVar2 = uVar2 - 1) {
      uVar5 = iVar8 + 1U & ~-(uint)(uVar7 <= iVar8 + 1U);
      puVar11 = puVar6 + uVar5 * 4;
      if (uVar5 == 0) {
        uVar5 = *puVar11 + uVar10;
      }
      else {
        uVar5 = *puVar11;
      }
      uVar4 = *puVar9;
      if ((uVar4 <= uVar12) && ((int)uVar12 < (int)uVar5)) {
        iVar8 = uVar5 - uVar4;
        fVar1 = FLOAT_8032fc98;
        if (iVar8 != 0) {
          iStack_2c = uVar12 - uVar4;
          local_30 = 0x43300000;
          local_28 = 0x43300000;
          fVar1 = (float)((double)CONCAT44(0x43300000,iStack_2c) - DOUBLE_8032fca0) /
                  (float)((double)CONCAT44(0x43300000,iVar8) - DOUBLE_8032fca0);
          iStack_24 = iVar8;
        }
        dVar13 = (double)fVar1;
        PSVECScale(fVar1,(Vec *)(puVar9 + 1),&VStack_48);
        PSVECScale((float)((double)FLOAT_8032fc9c - dVar13),(Vec *)(puVar11 + 1),&VStack_3c);
        PSVECAdd(&VStack_48,&VStack_3c,(Vec *)(iVar3 + 100));
        break;
      }
      puVar9 = puVar9 + 4;
      iVar8 = iVar8 + 1;
    }
  }
  iVar3 = *(int *)mapAnimNode;
  uVar7 = *(uint *)(*(int *)&mapAnimNode->field_0x8 + 8);
  puVar6 = *(uint **)(*(int *)&mapAnimNode->field_0x8 + 0xc);
  if (uVar7 == 1) {
    ((Vec *)(iVar3 + 0x70))->x = (float)puVar6[1];
    *(uint *)(iVar3 + 0x74) = puVar6[2];
    *(uint *)(iVar3 + 0x78) = puVar6[3];
  }
  else {
    iVar8 = 0;
    puVar9 = puVar6;
    for (uVar10 = uVar7; uVar10 != 0; uVar10 = uVar10 - 1) {
      uVar2 = iVar8 + 1U & ~-(uint)(uVar7 <= iVar8 + 1U);
      puVar11 = puVar6 + uVar2 * 4;
      if (uVar2 == 0) {
        uVar2 = (*(int *)(*(int *)&mapAnimNode->field_0x4 + 0x20) -
                *(int *)(*(int *)&mapAnimNode->field_0x4 + 0x1c)) + *puVar11 + 1;
      }
      else {
        uVar2 = *puVar11;
      }
      uVar5 = *puVar9;
      if ((uVar5 <= uVar12) && ((int)uVar12 < (int)uVar2)) {
        iVar8 = uVar2 - uVar5;
        fVar1 = FLOAT_8032fc98;
        if (iVar8 != 0) {
          iStack_24 = uVar12 - uVar5;
          local_28 = 0x43300000;
          local_30 = 0x43300000;
          fVar1 = (float)((double)CONCAT44(0x43300000,iStack_24) - DOUBLE_8032fca0) /
                  (float)((double)CONCAT44(0x43300000,iVar8) - DOUBLE_8032fca0);
          iStack_2c = iVar8;
        }
        dVar13 = (double)fVar1;
        PSVECScale(fVar1,(Vec *)(puVar9 + 1),&VStack_60);
        PSVECScale((float)((double)FLOAT_8032fc9c - dVar13),(Vec *)(puVar11 + 1),&VStack_54);
        PSVECAdd(&VStack_60,&VStack_54,(Vec *)(iVar3 + 0x70));
        break;
      }
      puVar9 = puVar9 + 4;
      iVar8 = iVar8 + 1;
    }
  }
  iVar3 = *(int *)mapAnimNode;
  uVar7 = *(uint *)(*(int *)&mapAnimNode->field_0x8 + 0x10);
  puVar6 = *(uint **)(*(int *)&mapAnimNode->field_0x8 + 0x14);
  if (uVar7 == 1) {
    ((Vec *)(iVar3 + 0x7c))->x = (float)puVar6[1];
    *(uint *)(iVar3 + 0x80) = puVar6[2];
    *(uint *)(iVar3 + 0x84) = puVar6[3];
  }
  else {
    iVar8 = 0;
    puVar9 = puVar6;
    for (uVar10 = uVar7; uVar10 != 0; uVar10 = uVar10 - 1) {
      uVar2 = iVar8 + 1U & ~-(uint)(uVar7 <= iVar8 + 1U);
      puVar11 = puVar6 + uVar2 * 4;
      if (uVar2 == 0) {
        uVar2 = (*(int *)(*(int *)&mapAnimNode->field_0x4 + 0x20) -
                *(int *)(*(int *)&mapAnimNode->field_0x4 + 0x1c)) + *puVar11 + 1;
      }
      else {
        uVar2 = *puVar11;
      }
      uVar5 = *puVar9;
      if ((uVar5 <= uVar12) && ((int)uVar12 < (int)uVar2)) {
        iVar8 = uVar2 - uVar5;
        fVar1 = FLOAT_8032fc98;
        if (iVar8 != 0) {
          iStack_24 = uVar12 - uVar5;
          local_28 = 0x43300000;
          local_30 = 0x43300000;
          fVar1 = (float)((double)CONCAT44(0x43300000,iStack_24) - DOUBLE_8032fca0) /
                  (float)((double)CONCAT44(0x43300000,iVar8) - DOUBLE_8032fca0);
          iStack_2c = iVar8;
        }
        dVar13 = (double)fVar1;
        PSVECScale(fVar1,(Vec *)(puVar9 + 1),&VStack_78);
        PSVECScale((float)((double)FLOAT_8032fc9c - dVar13),(Vec *)(puVar11 + 1),&VStack_6c);
        PSVECAdd(&VStack_78,&VStack_6c,(Vec *)(iVar3 + 0x7c));
        break;
      }
      puVar9 = puVar9 + 4;
      iVar8 = iVar8 + 1;
    }
  }
  *(undefined *)(*(int *)mapAnimNode + 0x1b) = 1;
  return;
}

