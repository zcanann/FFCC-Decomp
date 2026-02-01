// Function: Reset__9CCharaPcsFQ29CCharaPcs5RESET
// Entry: 80079d9c
// Size: 568 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Reset__9CCharaPcsFQ29CCharaPcs5RESET(CCharaPcs *charaPcs,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  CCharaPcs *pCVar4;
  uint uVar5;
  
  iVar1 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&charaPcs->field_0x6c);
  while (iVar1 = iVar1 + -1, -1 < iVar1) {
    iVar3 = __vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(&charaPcs->field_0x6c,iVar1);
    iVar3 = *(int *)(iVar3 + 0x28);
    if (*(int *)(iVar3 + 0x20) != 0) {
      __dl__FPv();
      *(undefined4 *)(iVar3 + 0x20) = 0;
    }
  }
  iVar1 = 0;
  pCVar4 = charaPcs;
  do {
    *(undefined4 *)&pCVar4->field_0x4 = 0;
    if (*(void **)&pCVar4->field_0x14 != (void *)0x0) {
      __dla__FPv(*(void **)&pCVar4->field_0x14);
      *(undefined4 *)&pCVar4->field_0x14 = 0;
    }
    iVar1 = iVar1 + 1;
    pCVar4 = (CCharaPcs *)&pCVar4->field_0x4;
  } while (iVar1 < 4);
  iVar1 = *(int *)(*(int *)&charaPcs->field_0x4c + 0x160);
  while (*(int *)&charaPcs->field_0x4c != iVar1) {
    iVar3 = *(int *)(iVar1 + 0x160);
    __dt__Q29CCharaPcs7CHandleFv(iVar1,1);
    iVar1 = iVar3;
  }
  if (param_2 != 1) {
    iVar1 = Chara._8308_4_;
    if ((0 < param_2) || (param_2 < 0)) goto LAB_80079fac;
    uVar5 = ~(*(uint *)&charaPcs->field_0x718 | 0x10000000);
    releaseUnuseLoadModel__9CCharaPcsFi(charaPcs,uVar5);
    iVar1 = GetSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&charaPcs->field_0x6c);
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      piVar2 = (int *)__vc__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(&charaPcs->field_0x6c,iVar1);
      if (((piVar2[4] < 0) && (piVar2[1] == 1)) || ((-1 < piVar2[4] && ((uVar5 & piVar2[5]) != 0))))
      {
        iVar3 = piVar2[1];
        piVar2[1] = iVar3 + -1;
        if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
          (**(code **)(*piVar2 + 8))(piVar2,1);
        }
        RemoveAt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl((CPtrArray *)&charaPcs->field_0x6c,iVar1);
      }
    }
    Printf__7CSystemFPce(&System,s_CCharaPcs_FreeMergeFile__0x_08x_801d94cc,uVar5);
    ReleaseAndRemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)&charaPcs->loadPdtArray)
    ;
    iVar1 = correctLoadAnimAmem__9CCharaPcsFv(charaPcs);
    if (-1 < iVar1) goto LAB_80079fac;
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9960);
    }
  }
  ReleaseAndRemoveAll__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv((CPtrArray *)&charaPcs->field_0x50);
  ReleaseAndRemoveAll__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv((CPtrArray *)&charaPcs->field_0x6c);
  ReleaseAndRemoveAll__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv
            ((CPtrArray *)&charaPcs->field_0x88);
  ReleaseAndRemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv((CPtrArray *)&charaPcs->loadPdtArray);
  Chara._8308_4_ = 0;
  iVar1 = Chara._8308_4_;
LAB_80079fac:
  Chara._8308_4_ = iVar1;
  *(undefined *)(DAT_8032edc0 + 0x6b) = 0xff;
  *(undefined4 *)&charaPcs->field_0x718 = 0;
  return;
}

