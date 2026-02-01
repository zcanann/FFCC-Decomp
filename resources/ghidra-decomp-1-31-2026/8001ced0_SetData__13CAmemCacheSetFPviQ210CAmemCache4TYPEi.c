// Function: SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
// Entry: 8001ced0
// Size: 936 bytes

int SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi
              (CAmemCacheSet *amemCacheSet,byte *param_2,int param_3,undefined param_4,int param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  byte *pbVar14;
  short sVar15;
  undefined4 *puVar16;
  uint uVar17;
  uint uVar18;
  undefined auStack_88 [48];
  undefined auStack_58 [60];
  
  sVar15 = 0;
  iVar13 = 0;
  iVar9 = *(int *)&amemCacheSet->field_0x3c;
  if (0 < iVar9) {
    do {
      if (*(char *)(*(int *)&amemCacheSet->field_0x58 + iVar13 + 0xe) == '\0') {
        iVar9 = (int)sVar15;
        goto LAB_8001cf2c;
      }
      iVar13 = iVar13 + 0x1c;
      sVar15 = sVar15 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  iVar9 = -1;
LAB_8001cf2c:
  if ((short)iVar9 == -1) {
    return -1;
  }
  puVar16 = (undefined4 *)(*(int *)&amemCacheSet->field_0x58 + (short)iVar9 * 0x1c);
  *(undefined *)((int)puVar16 + 0xe) = 1;
  uVar10 = param_3 + 0x1fU & 0xffffffe0;
  *(undefined *)((int)puVar16 + 0xf) = param_4;
  *(char *)((int)puVar16 + 0x1a) = (char)param_5;
  *(undefined2 *)(puVar16 + 3) = 0;
  if (param_5 == 0) {
    while( true ) {
      uVar12 = alloc__Q27CMemory6CStageFUlPcUli
                         (amemCacheSet->m_stage,uVar10,s_memory_cpp_801d6690,0x807,1);
      puVar16[1] = uVar12;
      if (puVar16[1] != 0) break;
      AmemFreeLowPrio__13CAmemCacheSetFi(amemCacheSet,uVar10);
    }
    *puVar16 = 0;
    iVar13 = 0x12345678;
    puVar16[2] = uVar10;
    uVar17 = puVar16[2];
    if (uVar17 != 0) {
      uVar18 = uVar17 >> 3;
      pbVar14 = param_2;
      if (uVar18 != 0) {
        do {
          bVar8 = *pbVar14;
          pbVar1 = pbVar14 + 1;
          pbVar2 = pbVar14 + 2;
          pbVar3 = pbVar14 + 3;
          pbVar4 = pbVar14 + 4;
          pbVar5 = pbVar14 + 5;
          pbVar6 = pbVar14 + 6;
          pbVar7 = pbVar14 + 7;
          pbVar14 = pbVar14 + 8;
          iVar13 = iVar13 + (uint)bVar8 + (uint)*pbVar1 + (uint)*pbVar2 + (uint)*pbVar3 +
                   (uint)*pbVar4 + (uint)*pbVar5 + (uint)*pbVar6 + (uint)*pbVar7;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
        uVar17 = uVar17 & 7;
        if (uVar17 == 0) goto LAB_8001d1ac;
      }
      do {
        iVar13 = iVar13 + (uint)*pbVar14;
        uVar17 = uVar17 - 1;
        pbVar14 = pbVar14 + 1;
      } while (uVar17 != 0);
    }
LAB_8001d1ac:
    puVar16[5] = iVar13;
    if (*(char *)((int)puVar16 + 0x1a) == '\0') {
      memcpy((void *)puVar16[1],param_2,puVar16[2]);
    }
    else {
      iVar13 = DMAEntry__9CRedSoundFiiiiiPFPv_vPv
                         (&Sound.m_redSound,0,0,(int)param_2,puVar16[1],puVar16[2],0,0);
      DumpMapFile__7CSystemFPv((CSystem *)auStack_88);
      Start__10CStopWatchFv(auStack_88);
      while (iVar11 = DMACheck__9CRedSoundFi(&Sound.m_redSound,iVar13), iVar11 != 0) {
        Stop__10CStopWatchFv(auStack_88);
        Get__10CStopWatchFv(auStack_88);
        Start__10CStopWatchFv(auStack_88);
      }
      __ct__10CStopWatchFPc(auStack_88,0xffffffff);
    }
    DCFlushRange(puVar16[1],uVar10);
    return iVar9;
  }
  *(undefined4 *)&amemCacheSet->field_0x34 = *(undefined4 *)&amemCacheSet->field_0x30;
  iVar13 = 0x12345678;
  *(uint *)&amemCacheSet->field_0x30 = *(int *)&amemCacheSet->field_0x30 + uVar10;
  puVar16[1] = *(undefined4 *)&amemCacheSet->field_0x34;
  *puVar16 = 0;
  puVar16[2] = uVar10;
  uVar10 = puVar16[2];
  if (uVar10 != 0) {
    uVar17 = uVar10 >> 3;
    pbVar14 = param_2;
    if (uVar17 != 0) {
      do {
        bVar8 = *pbVar14;
        pbVar1 = pbVar14 + 1;
        pbVar2 = pbVar14 + 2;
        pbVar3 = pbVar14 + 3;
        pbVar4 = pbVar14 + 4;
        pbVar5 = pbVar14 + 5;
        pbVar6 = pbVar14 + 6;
        pbVar7 = pbVar14 + 7;
        pbVar14 = pbVar14 + 8;
        iVar13 = iVar13 + (uint)bVar8 + (uint)*pbVar1 + (uint)*pbVar2 + (uint)*pbVar3 +
                 (uint)*pbVar4 + (uint)*pbVar5 + (uint)*pbVar6 + (uint)*pbVar7;
        uVar17 = uVar17 - 1;
      } while (uVar17 != 0);
      uVar10 = uVar10 & 7;
      if (uVar10 == 0) goto LAB_8001d024;
    }
    do {
      iVar13 = iVar13 + (uint)*pbVar14;
      uVar10 = uVar10 - 1;
      pbVar14 = pbVar14 + 1;
    } while (uVar10 != 0);
  }
LAB_8001d024:
  puVar16[5] = iVar13;
  if (*(char *)((int)puVar16 + 0x1a) == '\0') {
    memcpy((void *)puVar16[1],param_2,puVar16[2]);
  }
  else {
    iVar13 = DMAEntry__9CRedSoundFiiiiiPFPv_vPv
                       (&Sound.m_redSound,0,0,(int)param_2,puVar16[1],puVar16[2],0,0);
    DumpMapFile__7CSystemFPv((CSystem *)auStack_58);
    Start__10CStopWatchFv(auStack_58);
    while (iVar11 = DMACheck__9CRedSoundFi(&Sound.m_redSound,iVar13), iVar11 != 0) {
      Stop__10CStopWatchFv(auStack_58);
      Get__10CStopWatchFv(auStack_58);
      Start__10CStopWatchFv(auStack_58);
    }
    __ct__10CStopWatchFPc(auStack_58,0xffffffff);
  }
  return iVar9;
}

