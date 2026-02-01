// Function: __as__Q26CAStar6CATempFRCQ26CAStar6CATemp
// Entry: 80142bd4
// Size: 276 bytes

void __as__Q26CAStar6CATempFRCQ26CAStar6CATemp(CATemp *aTemp,CATemp *other)

{
  float fVar1;
  undefined4 uVar2;
  int32_t iVar3;
  undefined4 uVar4;
  
  uVar4 = *(undefined4 *)(other->m_visited + 4);
  *(undefined4 *)aTemp->m_visited = *(undefined4 *)other->m_visited;
  uVar2 = *(undefined4 *)(other->m_visited + 8);
  *(undefined4 *)(aTemp->m_visited + 4) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0xc);
  *(undefined4 *)(aTemp->m_visited + 8) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x10);
  *(undefined4 *)(aTemp->m_visited + 0xc) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x14);
  *(undefined4 *)(aTemp->m_visited + 0x10) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x18);
  *(undefined4 *)(aTemp->m_visited + 0x14) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x1c);
  *(undefined4 *)(aTemp->m_visited + 0x18) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x20);
  *(undefined4 *)(aTemp->m_visited + 0x1c) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x24);
  *(undefined4 *)(aTemp->m_visited + 0x20) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x28);
  *(undefined4 *)(aTemp->m_visited + 0x24) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x2c);
  *(undefined4 *)(aTemp->m_visited + 0x28) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x30);
  *(undefined4 *)(aTemp->m_visited + 0x2c) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x34);
  *(undefined4 *)(aTemp->m_visited + 0x30) = uVar2;
  uVar2 = *(undefined4 *)(other->m_visited + 0x38);
  *(undefined4 *)(aTemp->m_visited + 0x34) = uVar4;
  uVar4 = *(undefined4 *)(other->m_visited + 0x3c);
  *(undefined4 *)(aTemp->m_visited + 0x38) = uVar2;
  uVar2 = *(undefined4 *)other->m_path;
  *(undefined4 *)(aTemp->m_visited + 0x3c) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 4);
  *(undefined4 *)aTemp->m_path = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 8);
  *(undefined4 *)(aTemp->m_path + 4) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0xc);
  *(undefined4 *)(aTemp->m_path + 8) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x10);
  *(undefined4 *)(aTemp->m_path + 0xc) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x14);
  *(undefined4 *)(aTemp->m_path + 0x10) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x18);
  *(undefined4 *)(aTemp->m_path + 0x14) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x1c);
  *(undefined4 *)(aTemp->m_path + 0x18) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x20);
  *(undefined4 *)(aTemp->m_path + 0x1c) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x24);
  *(undefined4 *)(aTemp->m_path + 0x20) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x28);
  *(undefined4 *)(aTemp->m_path + 0x24) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x2c);
  *(undefined4 *)(aTemp->m_path + 0x28) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x30);
  *(undefined4 *)(aTemp->m_path + 0x2c) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x34);
  *(undefined4 *)(aTemp->m_path + 0x30) = uVar2;
  uVar2 = *(undefined4 *)(other->m_path + 0x38);
  *(undefined4 *)(aTemp->m_path + 0x34) = uVar4;
  uVar4 = *(undefined4 *)(other->m_path + 0x3c);
  *(undefined4 *)(aTemp->m_path + 0x38) = uVar2;
  iVar3 = other->m_pathLength;
  *(undefined4 *)(aTemp->m_path + 0x3c) = uVar4;
  fVar1 = other->m_cost;
  aTemp->m_pathLength = iVar3;
  aTemp->m_cost = fVar1;
  return;
}

