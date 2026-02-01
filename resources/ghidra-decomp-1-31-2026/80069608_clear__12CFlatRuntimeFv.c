// Function: clear__12CFlatRuntimeFv
// Entry: 80069608
// Size: 452 bytes

void clear__12CFlatRuntimeFv(CFlatRuntime *flatRuntime)

{
  void **ppvVar1;
  int iVar2;
  CFlatRuntime *pCVar3;
  int iVar4;
  
  iVar2 = 0;
  flatRuntime->m_variableDefs = (void *)0x0;
  flatRuntime->m_funcsPtr = (void *)0x0;
  flatRuntime->m_funcCount = 0;
  flatRuntime->m_classesPtr = (void *)0x0;
  flatRuntime->m_classCount = 0;
  flatRuntime->m_strOffs = (uint16_t *)0x0;
  flatRuntime->m_strBlob = (char *)0x0;
  flatRuntime->m_strCount = 0;
  flatRuntime->m_fstrOffs = (uint16_t *)0x0;
  flatRuntime->m_fstrBlob = (char *)0x0;
  flatRuntime->m_fstrCount = 0;
  flatRuntime->m_vstrOffs = (uint16_t *)0x0;
  flatRuntime->m_vstrBlob = (char *)0x0;
  flatRuntime->m_vstrCount = 0;
  flatRuntime->m_unk0x964 = flatRuntime->m_unk0x964 & 0xf | 0xfff0;
  flatRuntime->m_unk0x968 = flatRuntime->m_unk0x968 & 0xf | 0xfff0;
  (flatRuntime->m_objRoot).m_previous = &flatRuntime->m_objRoot;
  (flatRuntime->m_objRoot).m_next = &flatRuntime->m_objRoot;
  (flatRuntime->m_objRoot).m_scriptGroup = 0x10;
  *(uint8_t **)flatRuntime->m_memChain = flatRuntime->m_memChain;
  *(uint8_t **)(flatRuntime->m_memChain + 4) = flatRuntime->m_memChain;
  flatRuntime->m_memChain[8] = '\0';
  flatRuntime->m_memChain[9] = '\0';
  flatRuntime->m_memChain[10] = 'R';
  flatRuntime->m_memChain[0xb] = ' ';
  flatRuntime->m_memChain[0xc] = '\0';
  flatRuntime->m_memChain[0xd] = '\0';
  flatRuntime->m_memChain[0xe] = '\0';
  flatRuntime->m_memChain[0xf] = '\0';
  flatRuntime->m_freeHead = flatRuntime->m_freeNodes;
  flatRuntime->m_freeTail = flatRuntime->m_freeNodes + 0x8f0;
  iVar4 = 0x30;
  pCVar3 = flatRuntime;
  do {
    if (iVar2 == 0) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_unk0x990 + iVar2 * 0x10 + -8);
    }
    *(void ***)pCVar3->m_freeNodes = ppvVar1;
    if (iVar2 == 0x8f) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_freeNodes + iVar2 * 0x10 + 0x10);
    }
    *(void ***)(pCVar3->m_freeNodes + 4) = ppvVar1;
    if (iVar2 == -1) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_freeNodes + iVar2 * 0x10);
    }
    *(void ***)(pCVar3->m_freeNodes + 0x10) = ppvVar1;
    if (iVar2 == 0x8e) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_freeNodes + iVar2 * 0x10 + 0x20);
    }
    *(void ***)(pCVar3->m_freeNodes + 0x14) = ppvVar1;
    if (iVar2 == -2) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_freeNodes + iVar2 * 0x10 + 0x10);
    }
    *(void ***)(pCVar3->m_freeNodes + 0x20) = ppvVar1;
    if (iVar2 == 0x8d) {
      ppvVar1 = &flatRuntime->m_freeTail;
    }
    else {
      ppvVar1 = (void **)(flatRuntime->m_freeNodes + iVar2 * 0x10 + 0x30);
    }
    *(void ***)(pCVar3->m_freeNodes + 0x24) = ppvVar1;
    pCVar3 = (CFlatRuntime *)&pCVar3->m_fstrCount;
    iVar2 = iVar2 + 3;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  memset(flatRuntime->m_workArea,0,0x804);
  return;
}

