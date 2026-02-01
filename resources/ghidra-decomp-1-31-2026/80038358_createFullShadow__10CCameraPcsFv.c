// Function: createFullShadow__10CCameraPcsFv
// Entry: 80038358
// Size: 624 bytes

void createFullShadow__10CCameraPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  double dVar11;
  
  *(undefined4 *)(param_1 + 0x31c) = 0;
  uVar3 = GXGetTexBufferSize(0x1e0,0x1e0,1,0,0);
  uVar3 = __nwa__FUlPQ27CMemory6CStagePci(uVar3,MapMng._0_4_,s_p_camera_cpp_801d7918,0x3a5);
  *(undefined4 *)(param_1 + 0x31c) = uVar3;
  *(undefined4 *)(param_1 + 800) = 0;
  uVar3 = GXGetTexBufferSize(0x10,0x10,1,0,0);
  iVar4 = __nwa__FUlPQ27CMemory6CStagePci(uVar3,MapMng._0_4_,s_p_camera_cpp_801d7918,0x361);
  uVar5 = 0;
  *(int *)(param_1 + 800) = iVar4;
  iVar10 = 0x20;
  do {
    uVar6 = uVar5 + 1;
    uVar9 = uVar5 + 2;
    *(char *)(iVar4 + (uVar5 & 0xc) * 0x10 + (uVar5 >> 2 & 0x20) + (uVar5 >> 4 & 7)) = (char)uVar5;
    uVar8 = uVar5 + 3;
    *(char *)(iVar4 + (uVar6 * 8 & 0x18) + (uVar6 * 0x10 & 0xc0) + (uVar6 >> 2 & 0x20) +
                      (uVar6 >> 4 & 7)) = (char)uVar6;
    uVar7 = uVar5 + 4;
    *(char *)(iVar4 + (uVar9 * 8 & 0x18) + (uVar9 * 0x10 & 0xc0) + (uVar9 >> 2 & 0x20) +
                      (uVar9 >> 4 & 7)) = (char)uVar9;
    uVar6 = uVar5 + 5;
    *(char *)(iVar4 + (uVar8 * 8 & 0x18) + (uVar8 * 0x10 & 0xc0) + (uVar8 >> 2 & 0x20) +
                      (uVar8 >> 4 & 7)) = (char)uVar8;
    *(char *)(iVar4 + (uVar7 * 0x10 & 0xc0) + (uVar7 >> 2 & 0x20) + (uVar7 >> 4 & 7)) = (char)uVar7;
    uVar7 = uVar5 + 6;
    *(char *)(iVar4 + (uVar6 * 8 & 0x18) + (uVar6 * 0x10 & 0xc0) + (uVar6 >> 2 & 0x20) +
                      (uVar6 >> 4 & 7)) = (char)uVar6;
    uVar6 = uVar5 + 7;
    *(char *)(iVar4 + (uVar7 * 8 & 0x18) + (uVar7 * 0x10 & 0xc0) + (uVar7 >> 2 & 0x20) +
                      (uVar7 >> 4 & 7)) = (char)uVar7;
    uVar5 = uVar5 + 8;
    *(char *)(iVar4 + (uVar6 * 8 & 0x18) + (uVar6 * 0x10 & 0xc0) + (uVar6 >> 2 & 0x20) +
                      (uVar6 >> 4 & 7)) = (char)uVar6;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  GXInitTexObj(param_1 + 0x344,iVar4,0x10,0x10,1,0,1,0);
  dVar11 = (double)FLOAT_8032fa34;
  GXInitTexObjLOD(dVar11,dVar11,dVar11,param_1 + 0x344,0,0,0,0,0);
  DCFlushRange(iVar4,uVar3);
  fVar2 = FLOAT_8032faa4;
  *(undefined *)(param_1 + 0x404) = 1;
  fVar1 = FLOAT_8032fa34;
  *(float *)(param_1 + 0x364) = fVar2;
  fVar2 = FLOAT_8032faa8;
  *(float *)(param_1 + 0x368) = fVar1;
  *(float *)(param_1 + 0x370) = fVar2;
  return;
}

