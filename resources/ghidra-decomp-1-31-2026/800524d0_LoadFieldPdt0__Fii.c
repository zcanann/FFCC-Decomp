// Function: LoadFieldPdt0__Fii
// Entry: 800524d0
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadFieldPdt0__Fii(undefined4 param_1,undefined4 param_2)

{
  _pppDataHead *p_Var1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined auStack_418 [1024];
  
  DAT_8032ed3c = 0;
  DAT_8032ed38 = 0;
  if (PartMng.m_partLoadMode != 3) {
    pppReleasePdt__8CPartMngFi(&PartMng,0);
    pppReleasePdt__8CPartMngFi(&PartMng,6);
    pppReleasePdt__8CPartMngFi(&PartMng,7);
    AmemGetLock__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
    RefCnt0Compare__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  }
  PartPcs.m_usbStreamData.m_fieldLoadReq = '\x01';
  sprintf(auStack_418,s_dvd_tina_stage_03d_fp_03d_801d7fec,param_1,param_2);
  iVar2 = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng,auStack_418,0,1,0,0);
  if ((((iVar2 != 0) &&
       (iVar2 = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng,auStack_418,0,1,0,0),
       p_Var1 = PartMng.m_pdtSlots[0].m_pppDataHead, iVar2 != 0)) && (PartMng.m_partLoadMode != 2))
     && (PartMng.m_partLoadMode != 3)) {
    uVar3 = pppGetDefaultCreateParam__8CPartMngFv();
    iVar4 = 0;
    for (iVar2 = 0; iVar2 < (int)(uint)p_Var1->m_partCount; iVar2 = iVar2 + 1) {
      if (*(int *)((int)&PartMng.m_pdtSlots[0].m_pppDataHead[2].m_shapeGroupCount + iVar4) !=
          -0x1000) {
        pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng,0,iVar2,uVar3,0);
      }
      iVar4 = iVar4 + 0x60;
    }
  }
  return;
}

