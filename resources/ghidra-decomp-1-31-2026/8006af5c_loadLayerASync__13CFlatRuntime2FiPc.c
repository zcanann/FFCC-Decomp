// Function: loadLayerASync__13CFlatRuntime2FiPc
// Entry: 8006af5c
// Size: 244 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadLayerASync__13CFlatRuntime2FiPc(CFlatRuntime2 *flatRuntime2,int param_2,undefined4 param_3)

{
  int *piVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  undefined auStack_118 [260];
  
  iVar4 = param_2 * 0xc;
  if (*(CFileCHandle **)(&flatRuntime2->field_0x1778 + iVar4) != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)(&flatRuntime2->field_0x1778 + iVar4));
    *(undefined4 *)(&flatRuntime2->field_0x1778 + iVar4) = 0;
  }
  piVar1 = *(int **)(&flatRuntime2->field_0x1774 + iVar4);
  if (piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)(&flatRuntime2->field_0x1774 + iVar4) = 0;
  }
  pcVar2 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_118,s_dvd__s_s_tex_801d8fa0,pcVar2,param_3);
  uVar3 = Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
  *(undefined4 *)(&flatRuntime2->field_0x1778 + iVar4) = uVar3;
  if (*(CFileCHandle **)(&flatRuntime2->field_0x1778 + iVar4) != (CFileCHandle *)0x0) {
    ReadASync__5CFileFPQ25CFile7CHandle
              (&File,*(CFileCHandle **)(&flatRuntime2->field_0x1778 + iVar4));
  }
  *(undefined4 *)(&flatRuntime2->field_0x1770 + iVar4) = CharaPcs._228_4_;
  return;
}

