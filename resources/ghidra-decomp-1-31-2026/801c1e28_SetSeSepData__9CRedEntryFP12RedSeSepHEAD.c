// Function: SetSeSepData__9CRedEntryFP12RedSeSepHEAD
// Entry: 801c1e28
// Size: 296 bytes

int SetSeSepData__9CRedEntryFP12RedSeSepHEAD(int param_1,char *param_2)

{
  int iVar1;
  
  if ((((*param_2 == 'S') && (param_2[1] == 'e')) && (param_2[2] == 'S')) &&
     ((param_2[3] == 'e' && (param_2[4] == 'p')))) {
    iVar1 = SearchSeSepSequence__9CRedEntryFi(param_1,*(undefined4 *)(param_2 + 8));
    if (iVar1 < 0) {
      iVar1 = SeSepHeadAdd__9CRedEntryFP12RedSeSepHEAD(param_1,param_2);
      if (iVar1 == 0) {
        RedDelete__FPv(param_2);
      }
    }
    else {
      RedDelete__FPv(param_2);
      SeSepHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*(int *)(param_1 + 4) + iVar1 * 0x10)
      ;
      iVar1 = *(int *)(*(int *)(param_1 + 4) + iVar1 * 0x10 + 8);
    }
  }
  else {
    RedDelete__FPv(param_2);
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sSE_Sep_Header_was_broken__s_801e7b50,&DAT_801e7905,&DAT_80333d3d,&DAT_80333d38)
      ;
      fflush(&DAT_8021d1a8);
    }
    iVar1 = 0;
  }
  return iVar1;
}

