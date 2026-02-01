// Function: AddRsdList__18CMaterialEditorPcsFP5ZLIST
// Entry: 8004ddc0
// Size: 212 bytes

undefined4 AddRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs *param_1,ZLIST *zlist)

{
  int *tail;
  undefined4 uVar1;
  int iVar2;
  
  tail = (int *)__nw__FUlPQ27CMemory6CStagePci
                          (0x10,MaterialEditorPcs._4_4_,s_ME_AppRequest_cpp_801d7da8,0x61);
  if (tail == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    memset(tail,0,0x10);
    iVar2 = __nw__FUlPQ27CMemory6CStagePci
                      (0x1c,MaterialEditorPcs._4_4_,s_ME_AppRequest_cpp_801d7da8,0x67);
    if (iVar2 == 0) {
      if (tail != (int *)0x0) {
        __dl__FPv(tail);
      }
      uVar1 = 0;
    }
    else {
      memset(iVar2,0,0x1c);
      *tail = iVar2;
      tail[3] = 1;
      AddTail__5ZLISTFPv(zlist,tail);
      uVar1 = 1;
    }
  }
  return uVar1;
}

