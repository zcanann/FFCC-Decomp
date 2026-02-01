// Function: _SePlayStart__FP9RedSeINFOiiii
// Entry: 801ca808
// Size: 936 bytes

undefined4
_SePlayStart__FP9RedSeINFOiiii(byte *param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  byte bVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  *(undefined4 *)(DAT_8032f3f0 + 0x1244) = 0;
  iVar7 = (uint)param_1[2] * 0x100 + (uint)param_1[1];
  iVar2 = SearchWaveBase__9CRedEntryFi(&DAT_8032e154,iVar7);
  if (iVar2 == 0) {
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sWave_is_not_Entry___wave_4_4_801e7e18,&DAT_801e7e3e,&DAT_80333d68,iVar7,
               &DAT_80333d70);
      fflush(&DAT_8021d1a8);
    }
  }
  else {
    WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,1,(int)*(short *)(iVar2 + 2));
  }
  bVar1 = *param_1;
  pbVar9 = param_1 + 5;
  bVar5 = param_1[4];
  uVar8 = *param_1 & 0xffffff7f;
  pbVar6 = pbVar9 + uVar8 * 2;
  do {
    uVar10 = uVar8;
    if (param_3 != 1000000) {
      uVar10 = 0;
      do {
        uVar10 = uVar10 + 1;
        if ((pbVar9[uVar10 * 2 + 1] & 0x80) == 0) break;
      } while ((int)uVar10 < (int)uVar8);
    }
    puVar3 = (undefined4 *)SearchSeEmptyTrack__Fiii(uVar10,param_1[3],bVar5);
    bVar5 = 0;
    if (puVar3 == (undefined4 *)0x0) {
      SeStopID__Fi(param_2);
      return 0;
    }
    puVar11 = (undefined4 *)(DAT_8032f444 + *(char *)((int)puVar3 + 0x14e) * 0xc0);
    while( true ) {
      puVar3[6] = iVar2;
      *puVar3 = pbVar6;
      pbVar6 = pbVar6 + ((uint)pbVar9[1] * 0x100 + (uint)*pbVar9 & 0x7fff);
      iVar7 = DeltaTimeSumup__FPPUc(puVar3);
      puVar3[0x42] = iVar7 + 1;
      if (DAT_8032f440 != 0) {
        puVar3[0x42] = puVar3[0x42] - DAT_8032f440;
      }
      puVar3[0x3d] = param_3;
      puVar3[0x3e] = param_2;
      *(undefined2 *)(puVar3 + 0x51) = 0;
      if (DAT_8032f440 == 0) {
        uVar4 = 0xffffffff;
      }
      else {
        uVar4 = 0;
      }
      puVar3[0x43] = uVar4;
      if (*(char *)*puVar3 != '\0') {
        *(byte *)((int)puVar3 + 0x14f) = param_1[3];
        *(byte *)(puVar3 + 0x54) = param_1[4];
        puVar3[0x13] = param_5 << 0xc;
        puVar3[0x15] = 0;
        puVar3[0x16] = 0;
        puVar3[0x19] = 0;
        puVar3[0x17] = 0;
        puVar3[0x40] = (uint)((bVar1 & 0x80) != 0);
        puVar3[10] = 0x7fff000;
        puVar3[0xd] = 0x7f000;
        puVar3[0x10] = param_4 << 0xc;
        puVar3[0x1a] = *(undefined4 *)(DAT_8032f474 + 0xc);
        puVar3[0x1c] = 0;
        puVar3[0x12] = 0;
        puVar3[0xf] = 0;
        puVar3[0xc] = 0;
        puVar3[0x45] = 0;
        puVar3[0x44] = 0;
        puVar3[0x46] = 0;
        *(undefined2 *)(puVar3 + 0x4f) = 0;
        *(undefined2 *)((int)puVar3 + 0x142) = 0;
        *(undefined *)((int)puVar3 + 0x14b) = 2;
        *(undefined2 *)((int)puVar3 + 0x13e) = 0;
        *(undefined2 *)(puVar3 + 0x50) = 0;
        *(undefined *)(puVar3 + 0x52) = 0;
        puVar3[0x2d] = 0;
        puVar3[0x25] = 0;
        puVar3[0x1d] = 0;
        puVar3[0x33] = 0;
        *(undefined2 *)(puVar3 + 0x2c) = 0;
        *(undefined2 *)(puVar3 + 0x24) = 0;
        *(undefined2 *)((int)puVar3 + 0xb2) = 0;
        *(undefined2 *)((int)puVar3 + 0x92) = 0;
        puVar3[7] = 0;
        puVar3[0x41] = 0;
        *(undefined2 *)((int)puVar3 + 0x13a) = 0;
        *(undefined2 *)(puVar3 + 0x4e) = 0;
        puVar3[0x3c] = 0;
        puVar3[0x3b] = 0;
        puVar3[0x3a] = 0;
        puVar3[0x39] = 0;
        puVar3[0x38] = 0;
        puVar3[0x48] = 0xffffffff;
        puVar3[0x3f] = 0xc00;
        memset(puVar3 + 0x35,0xffffffff,0xc);
        *(undefined *)((int)puVar3 + 0x26) = 5;
        *(undefined2 *)((int)puVar3 + 0x146) = 1;
        *puVar11 = puVar3;
        *(undefined *)((int)puVar11 + 0x1a) = 5;
        puVar11[0x24] = 2;
        puVar11[0xc] = 0;
        puVar11[8] = 0;
        puVar11[0x2e] = 0;
      }
      uVar10 = uVar10 - 1;
      pbVar9 = pbVar9 + 2;
      uVar8 = uVar8 - 1;
      if (uVar10 == 0) break;
      puVar3 = puVar3 + 0x55;
      puVar11 = puVar11 + 0x30;
    }
    if (uVar8 == 0) {
      return param_2;
    }
  } while( true );
}

