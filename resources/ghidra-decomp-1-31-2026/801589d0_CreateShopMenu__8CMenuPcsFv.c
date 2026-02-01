// Function: CreateShopMenu__8CMenuPcsFv
// Entry: 801589d0
// Size: 292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CreateShopMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  CShopMenu *pCVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  
  uVar2 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar2 = MenuPcs._244_4_;
  }
  pCVar1 = (CShopMenu *)__nw__FUlPQ27CMemory6CStagePci(0x158,uVar2,s_shopmenu_cpp_801ded8c,0x2e2);
  menuPcs->m_shopMenuPtr = pCVar1;
  pCVar1 = menuPcs->m_shopMenuPtr;
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_shopmenu_cpp_801ded8c,0x2fe);
  (pCVar1->field0_0x0).ref.vtable = (void *)0x0;
  *(uint32_t *)&pCVar1->field_0x20 = Game.game.m_scriptFoodBase[0];
  SetMode__9CShopMenuFi(pCVar1,0);
  uVar2 = LoadMenuPdt__8CPartPcsFPc(&PartPcs,&DAT_80332e54);
  *(undefined4 *)&pCVar1->field_0x18 = uVar2;
  iVar3 = *(int *)&pCVar1->field_0x18;
  puVar4 = (undefined2 *)(PartMng.m_pdtSlots[iVar3].m_pppDataHead)->m_cacheChunks;
  uVar2 = GetData__13CAmemCacheSetFsPci
                    ((CAmemCacheSet *)CAMemCacheSet,*puVar4,s_shopmenu_cpp_801ded8c,0x32a);
  *(undefined4 *)(puVar4 + 2) = uVar2;
  pppCacheLoadShape__FPsP12_pppDataHead
            (*(int *)(puVar4 + 2) + *(int *)(*(int *)(puVar4 + 2) + 0x14),
             PartMng.m_pdtSlots[iVar3].m_pppDataHead);
  return;
}

