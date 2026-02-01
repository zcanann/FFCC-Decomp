// Function: FreeAnim__Q29CCharaPcs7CHandleFi
// Entry: 800754e8
// Size: 532 bytes

void FreeAnim__Q29CCharaPcs7CHandleFi(CCharaPcsCHandle *handle,int param_2)

{
  int iVar1;
  CRef *pCVar2;
  int *piVar3;
  CRef *pCVar4;
  int iVar5;
  
  if (param_2 == -1) {
    iVar5 = 0;
    do {
      pCVar2 = handle->m_animSlot[0];
      if ((pCVar2 != (CRef *)0x0) && (pCVar2 != (CRef *)0x0)) {
        iVar1 = pCVar2->refCount + -1;
        pCVar2->refCount = iVar1;
        if ((iVar1 == 0) && (pCVar2 != (CRef *)0x0)) {
          (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
        }
        handle->m_animSlot[0] = (CRef *)0x0;
      }
      iVar5 = iVar5 + 1;
      handle = (CCharaPcsCHandle *)&handle->m_charaNo;
    } while (iVar5 < 0x40);
    iVar5 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c);
    while (iVar5 = iVar5 + -1, -1 < iVar5) {
      piVar3 = (int *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,iVar5);
      if ((piVar3[4] < 0) && (piVar3[1] == 1)) {
        piVar3[1] = 0;
        if (piVar3 != (int *)0x0) {
          (**(code **)(*piVar3 + 8))(piVar3,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&CharaPcs.field_0x6c,iVar5);
      }
    }
  }
  else {
    pCVar2 = handle->m_animSlot[param_2];
    if (pCVar2 != (CRef *)0x0) {
      iVar5 = pCVar2->refCount + -1;
      pCVar2->refCount = iVar5;
      if ((iVar5 == 0) && (pCVar2 != (CRef *)0x0)) {
        (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
      }
      pCVar2 = handle->m_animSlot[param_2];
      iVar5 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&CharaPcs.field_0x6c);
      do {
        do {
          iVar5 = iVar5 + -1;
          if (iVar5 < 0) goto LAB_800756d4;
          pCVar4 = (CRef *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(0x802e99d0,iVar5);
        } while (((-1 < (int)pCVar4[2].vtable) || (pCVar4->refCount != 1)) ||
                ((pCVar2 != (CRef *)0x0 && (pCVar2 != pCVar4))));
        iVar1 = pCVar4->refCount + -1;
        pCVar4->refCount = iVar1;
        if ((iVar1 == 0) && (pCVar4 != (CRef *)0x0)) {
          (**(code **)((int)pCVar4->vtable + 8))(pCVar4,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&CharaPcs.field_0x6c,iVar5);
      } while (pCVar2 == (CRef *)0x0);
LAB_800756d4:
      handle->m_animSlot[param_2] = (CRef *)0x0;
    }
  }
  return;
}

