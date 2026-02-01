// Function: createObject__12CFlatRuntimeFi
// Entry: 800684c8
// Size: 724 bytes

CObject * createObject__12CFlatRuntimeFi(CFlatRuntime *flatRuntime,int param_2)

{
  uint uVar1;
  int iVar2;
  uint32_t *puVar3;
  CObject *pCVar4;
  undefined4 uVar5;
  void **ppvVar6;
  void *pvVar7;
  int iVar8;
  void *pvVar9;
  void *pvVar10;
  
  if (param_2 == -1) {
    pvVar10 = (void *)0x0;
  }
  else {
    pvVar10 = (void *)((int)flatRuntime->m_classesPtr + param_2 * 0x22c);
  }
  if (pvVar10 == (void *)0x0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(undefined4 *)((int)pvVar10 + 0x228);
  }
  pCVar4 = (CObject *)(**(code **)((int)flatRuntime->vtable + 0x38))(flatRuntime,uVar5);
  iVar8 = 0;
  pCVar4->m_previous = (flatRuntime->m_objRoot).m_previous;
  pCVar4->m_next = &flatRuntime->m_objRoot;
  ((flatRuntime->m_objRoot).m_previous)->m_next = pCVar4;
  (flatRuntime->m_objRoot).m_previous = pCVar4;
  pCVar4->m_flags = pCVar4->m_flags & 0x7f;
  pCVar4->m_flags = pCVar4->m_flags & 0xdf;
  pCVar4->m_flags = pCVar4->m_flags & 0xef | 0x10;
  pCVar4->m_scriptPriority = 0;
  pCVar4->m_scriptGroup = 0xf;
  pCVar4->m_waitCounter = 0;
  pCVar4->m_reqFlag0 = '\0';
  pCVar4->m_reqFlag1 = '\0';
  pCVar4->m_reqFlag2 = '\0';
  pCVar4->m_reqFlag3 = '\0';
  pCVar4->m_classIndex = (int16_t)param_2;
  *(int16_t *)&pCVar4->field_0x16 = pCVar4->m_classIndex;
  pCVar4->m_flags = pCVar4->m_flags & 0xbf | 0x40;
  if (param_2 != -1) {
    iVar8 = *(int *)((int)pvVar10 + 0x224);
  }
  uVar1 = countLeadingZeros((int)flatRuntime +
                            (0x978 - (int)*(void **)(flatRuntime->m_memChain + 4)));
  uVar1 = uVar1 >> 5 & 0xff;
  pvVar7 = *(void **)(flatRuntime->m_memChain + 4);
  do {
    pvVar9 = pvVar7;
    if (uVar1 != 0) break;
    pvVar7 = *(void **)((int)pvVar9 + 4);
  } while (*(int *)((int)*(void **)((int)pvVar9 + 4) + 8) <
           iVar8 + 0x60 + *(int *)((int)pvVar9 + 8) + *(int *)((int)pvVar9 + 0xc));
  ppvVar6 = (void **)flatRuntime->m_freeHead;
  flatRuntime->m_freeHead = ppvVar6[1];
  *ppvVar6 = pvVar9;
  ppvVar6[1] = *(void **)((int)pvVar9 + 4);
  *(void ***)ppvVar6[1] = ppvVar6;
  *(void ***)((int)pvVar9 + 4) = ppvVar6;
  if (uVar1 == 0) {
    iVar2 = *(int *)((int)pvVar9 + 8);
  }
  else {
    iVar2 = 0;
  }
  ppvVar6[2] = (void *)(*(int *)((int)pvVar9 + 0xc) + iVar2);
  ppvVar6[3] = (void *)(iVar8 + 0x60);
  pCVar4->m_freeListNode = ppvVar6;
  pCVar4->m_id = (uint32_t)((int)flatRuntime->m_workBasePtr + (int)ppvVar6[2] * 4);
  if (param_2 == -1) {
    puVar3 = (uint32_t *)flatRuntime->m_variableValuesPtr;
  }
  else {
    puVar3 = (uint32_t *)pCVar4->m_id;
  }
  pCVar4->m_thisBase = puVar3;
  if (param_2 == -1) {
    puVar3 = (uint32_t *)pCVar4->m_id;
  }
  else {
    puVar3 = pCVar4->m_thisBase + *(int *)((int)pvVar10 + 0x224);
  }
  pCVar4->m_stackPointer = puVar3;
  pCVar4->m_localBase = (uint32_t *)0x0;
  pCVar4->m_engineObject = pCVar4;
  *(ushort *)&pCVar4->m_codePos = *(ushort *)&pCVar4->m_codePos & 0xf | 0xfff0;
  pCVar4->m_argCount = 0;
  if (param_2 == -1) {
    uVar1 = countLeadingZeros(flatRuntime->m_isCreated);
    uVar1 = uVar1 >> 5 & 0xff;
  }
  else {
    uVar1 = 1;
  }
  puVar3 = pCVar4->m_thisBase;
  if (param_2 == -1) {
    pvVar7 = flatRuntime->m_variableDefs;
    iVar8 = flatRuntime->m_variableCount;
  }
  else {
    pvVar7 = (void *)0x0;
    iVar8 = *(int *)((int)pvVar10 + 0x224);
  }
  if (0 < iVar8) {
    do {
      if ((uVar1 != 0) || ((*(byte *)((int)pvVar7 + 1) & 0x20) == 0)) {
        *puVar3 = 0;
      }
      pvVar7 = (void *)((int)pvVar7 + 4);
      puVar3 = puVar3 + 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  if (param_2 == -1) {
    request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
              (flatRuntime,pCVar4,1,0,0,(CStack *)0x0);
  }
  (**(code **)((int)flatRuntime->vtable + 0x18))(flatRuntime,pCVar4);
  return pCVar4;
}

