// Function: AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei
// Entry: 8004975c
// Size: 880 bytes

undefined4 *
AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei
          (int param_1,undefined4 *param_2,int param_3,CStage *stage,int param_5)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  
  fVar1 = FLOAT_8032fc10;
  iVar5 = param_1 + param_3 * 0x9c0;
  iVar3 = 0;
  iVar8 = 8;
  iVar4 = iVar5;
  do {
    if (*(char *)(iVar4 + 0x1cec) == '\0') {
      puVar7 = (undefined4 *)(iVar5 + iVar3 * 0x138 + 0x1c3c);
      goto LAB_800497b8;
    }
    iVar4 = iVar4 + 0x138;
    iVar3 = iVar3 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar7 = (undefined4 *)0x0;
LAB_800497b8:
  if (puVar7 == (undefined4 *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,&DAT_801d7c94);
    }
    puVar7 = (undefined4 *)0x0;
  }
  else {
    *puVar7 = *param_2;
    uVar2 = param_2[2];
    puVar7[1] = param_2[1];
    puVar7[2] = uVar2;
    puVar7[3] = param_2[3];
    uVar2 = param_2[5];
    puVar7[4] = param_2[4];
    puVar7[5] = uVar2;
    puVar7[6] = param_2[6];
    puVar7[7] = param_2[7];
    puVar7[8] = param_2[8];
    puVar7[9] = param_2[9];
    puVar7[10] = param_2[10];
    puVar7[0xb] = param_2[0xb];
    puVar7[0xc] = param_2[0xc];
    puVar7[0xd] = param_2[0xd];
    uVar2 = param_2[0xf];
    puVar7[0xe] = param_2[0xe];
    puVar7[0xf] = uVar2;
    puVar7[0x10] = param_2[0x10];
    puVar7[0x11] = param_2[0x11];
    puVar7[0x12] = param_2[0x12];
    *(undefined *)(puVar7 + 0x13) = *(undefined *)(param_2 + 0x13);
    *(undefined *)((int)puVar7 + 0x4d) = *(undefined *)((int)param_2 + 0x4d);
    *(undefined *)((int)puVar7 + 0x4e) = *(undefined *)((int)param_2 + 0x4e);
    *(undefined *)((int)puVar7 + 0x4f) = *(undefined *)((int)param_2 + 0x4f);
    uVar2 = param_2[0x15];
    puVar7[0x14] = param_2[0x14];
    puVar7[0x15] = uVar2;
    uVar2 = param_2[0x17];
    puVar7[0x16] = param_2[0x16];
    puVar7[0x17] = uVar2;
    puVar7[0x18] = param_2[0x18];
    puVar7[0x19] = param_2[0x19];
    puVar7[0x1a] = param_2[0x1a];
    uVar2 = param_2[0x1c];
    puVar7[0x1b] = param_2[0x1b];
    puVar7[0x1c] = uVar2;
    uVar2 = param_2[0x1e];
    puVar7[0x1d] = param_2[0x1d];
    puVar7[0x1e] = uVar2;
    uVar2 = param_2[0x20];
    puVar7[0x1f] = param_2[0x1f];
    puVar7[0x20] = uVar2;
    uVar2 = param_2[0x22];
    puVar7[0x21] = param_2[0x21];
    puVar7[0x22] = uVar2;
    uVar2 = param_2[0x24];
    puVar7[0x23] = param_2[0x23];
    puVar7[0x24] = uVar2;
    uVar2 = param_2[0x26];
    puVar7[0x25] = param_2[0x25];
    puVar7[0x26] = uVar2;
    uVar2 = param_2[0x28];
    puVar7[0x27] = param_2[0x27];
    puVar7[0x28] = uVar2;
    uVar2 = param_2[0x2a];
    puVar7[0x29] = param_2[0x29];
    puVar7[0x2a] = uVar2;
    puVar7[0x2b] = param_2[0x2b];
    if (fVar1 <= (float)puVar7[8]) {
      puVar7[8] = puVar7[7];
    }
    fVar1 = FLOAT_8032fc14;
    puVar7[0x2b] = (float)puVar7[7] * (float)puVar7[7];
    puVar7[9] = puVar7[7];
    if ((float)puVar7[9] < fVar1) {
      puVar7[9] = -(float)puVar7[9];
    }
    puVar7[9] = (float)puVar7[9] * FLOAT_8032fc18 * (float)puVar7[10];
    *(undefined *)((int)puVar7 + 99) = 1;
    *(undefined *)((int)puVar7 + 0x62) = 1;
    *(undefined *)((int)puVar7 + 0x61) = 1;
    *(undefined *)(puVar7 + 0x18) = 1;
    if (puVar7[0x14] == 0) {
      *(undefined *)(puVar7 + 0x18) = 0;
    }
    if (puVar7[0x15] == 0) {
      *(undefined *)((int)puVar7 + 0x61) = 0;
    }
    if (puVar7[0x16] == 0) {
      *(undefined *)((int)puVar7 + 0x62) = 0;
    }
    *(char *)((int)puVar7 + 0xb2) = (char)param_3;
    *(undefined *)(puVar7 + 0x2c) = 1;
    *(char *)((int)puVar7 + 0xb3) = (char)param_5;
    iVar4 = GXGetTexBufferSize(0x40,0x40,3,0,0);
    uVar2 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                      (&Memory,iVar4 * param_5,stage,s_p_light_cpp_801d7cac,0x13b,0);
    puVar7[0x2d] = uVar2;
    iVar5 = 0;
    puVar6 = puVar7;
    for (iVar3 = 0; iVar3 < param_5; iVar3 = iVar3 + 1) {
      GXInitTexObj(puVar6 + 0x2e,puVar7[0x2d] + iVar5,0x40,0x40,3,0,0,0);
      iVar5 = iVar5 + iVar4;
      puVar6 = puVar6 + 8;
    }
  }
  return puVar7;
}

