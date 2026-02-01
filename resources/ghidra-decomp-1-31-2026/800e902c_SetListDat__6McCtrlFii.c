// Function: SetListDat__6McCtrlFii
// Entry: 800e902c
// Size: 796 bytes

void SetListDat__6McCtrlFii(McCtrl *mcCtrl,int param_2,int param_3)

{
  uint8_t *puVar1;
  int iVar2;
  char cVar4;
  undefined4 uVar3;
  uint32_t *puVar5;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  undefined auStack_2c [21];
  undefined local_17;
  undefined local_16;
  undefined local_15;
  
  puVar1 = MemoryCardMan.m_saveBuffer;
  memset(&local_58,0,0x48);
  if (puVar1[0x10c0] == '\0') {
    local_16 = 0;
    local_17 = 0;
  }
  else {
    iVar2 = memcmp(puVar1 + 0xc,PTR_DAT_8032e8a8,4);
    cVar4 = ChkCrc__14CMemoryCardManFPQ22Mc7SaveDat(&MemoryCardMan,0);
    if ((cVar4 == '\x01') && (iVar2 == 0)) {
      if (param_3 == 0) {
        local_50 = *(uint32_t *)(puVar1 + 0x20);
      }
      else {
        local_50 = 0;
      }
      memcpy(&local_58,puVar1 + 0x8ad0,8);
      local_4c = *(uint32_t *)(puVar1 + 0x24);
      local_48 = *(uint32_t *)(puVar1 + 0x28);
      local_44 = *(uint32_t *)(puVar1 + 0x2c);
      iVar2 = *(int *)(puVar1 + 0x30);
      if (*(int *)(puVar1 + iVar2 * 0x9c0 + 0x1a84) == 0) {
        puVar1[0x30] = 0xff;
        puVar1[0x31] = 0xff;
        puVar1[0x32] = 0xff;
        puVar1[0x33] = 0xff;
      }
      if (puVar1[iVar2 * 0x9c0 + 0x1d90] != '\0') {
        puVar1[0x30] = 0xff;
        puVar1[0x31] = 0xff;
        puVar1[0x32] = 0xff;
        puVar1[0x33] = 0xff;
      }
      iVar2 = *(int *)(puVar1 + 0x34);
      if (*(int *)(puVar1 + iVar2 * 0x9c0 + 0x1a84) == 0) {
        puVar1[0x34] = 0xff;
        puVar1[0x35] = 0xff;
        puVar1[0x36] = 0xff;
        puVar1[0x37] = 0xff;
      }
      if (puVar1[iVar2 * 0x9c0 + 0x1d90] != '\0') {
        puVar1[0x34] = 0xff;
        puVar1[0x35] = 0xff;
        puVar1[0x36] = 0xff;
        puVar1[0x37] = 0xff;
      }
      iVar2 = *(int *)(puVar1 + 0x38);
      if (*(int *)(puVar1 + iVar2 * 0x9c0 + 0x1a84) == 0) {
        puVar1[0x38] = 0xff;
        puVar1[0x39] = 0xff;
        puVar1[0x3a] = 0xff;
        puVar1[0x3b] = 0xff;
      }
      if (puVar1[iVar2 * 0x9c0 + 0x1d90] != '\0') {
        puVar1[0x38] = 0xff;
        puVar1[0x39] = 0xff;
        puVar1[0x3a] = 0xff;
        puVar1[0x3b] = 0xff;
      }
      iVar2 = *(int *)(puVar1 + 0x3c);
      if (*(int *)(puVar1 + iVar2 * 0x9c0 + 0x1a84) == 0) {
        puVar1[0x3c] = 0xff;
        puVar1[0x3d] = 0xff;
        puVar1[0x3e] = 0xff;
        puVar1[0x3f] = 0xff;
      }
      if (puVar1[iVar2 * 0x9c0 + 0x1d90] != '\0') {
        puVar1[0x3c] = 0xff;
        puVar1[0x3d] = 0xff;
        puVar1[0x3e] = 0xff;
        puVar1[0x3f] = 0xff;
      }
      uVar3 = CalcCrc__14CMemoryCardManFPQ22Mc7SaveDat(&MemoryCardMan,puVar1);
      *(undefined4 *)(puVar1 + 0x1c) = uVar3;
      if (*(int *)(puVar1 + 0x30) < 0) {
        local_40 = 0xffffffff;
      }
      else {
        local_40 = (uint32_t)*(ushort *)(puVar1 + *(int *)(puVar1 + 0x30) * 0x9c0 + 0x14d0);
      }
      if (*(int *)(puVar1 + 0x34) < 0) {
        local_3c = 0xffffffff;
      }
      else {
        local_3c = (uint32_t)*(ushort *)(puVar1 + *(int *)(puVar1 + 0x34) * 0x9c0 + 0x14d0);
      }
      if (*(int *)(puVar1 + 0x38) < 0) {
        local_38 = 0xffffffff;
      }
      else {
        local_38 = (uint32_t)*(ushort *)(puVar1 + *(int *)(puVar1 + 0x38) * 0x9c0 + 0x14d0);
      }
      if (*(int *)(puVar1 + 0x3c) < 0) {
        local_34 = 0xffffffff;
      }
      else {
        local_34 = (uint32_t)*(ushort *)(puVar1 + *(int *)(puVar1 + 0x3c) * 0x9c0 + 0x14d0);
      }
      local_30 = *(uint32_t *)(puVar1 + 0xb8);
      memcpy(auStack_2c,puVar1 + 0x10c0,0x10);
      local_17 = 1;
    }
    else {
      local_16 = 1;
    }
  }
  puVar5 = MenuPcs.m_unk0x838 + param_2 * 0x12;
  puVar5[1] = local_54;
  *puVar5 = local_58;
  puVar5[2] = local_50;
  puVar5[3] = local_4c;
  puVar5[4] = local_48;
  puVar5[5] = local_44;
  puVar5[6] = local_40;
  puVar5[7] = local_3c;
  puVar5[8] = local_38;
  puVar5[9] = local_34;
  puVar5[10] = local_30;
  __copy(puVar5 + 0xb,auStack_2c,0x15);
  *(undefined *)((int)puVar5 + 0x41) = local_17;
  *(undefined *)((int)puVar5 + 0x42) = local_16;
  *(undefined *)((int)puVar5 + 0x43) = local_15;
  return;
}

