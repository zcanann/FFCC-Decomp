// Function: loadLayer__13CFlatRuntime2FiPc
// Entry: 8006b068
// Size: 372 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadLayer__13CFlatRuntime2FiPc(CFlatRuntime2 *flatRuntime2,int param_2,undefined4 param_3)

{
  void *pvVar1;
  int *piVar2;
  char *pcVar3;
  CFileCHandle *fileHandle;
  undefined4 uVar4;
  CTextureSet *textureSet;
  undefined auStack_118 [268];
  
  piVar2 = *(int **)(&flatRuntime2->field_0x1774 + param_2 * 0xc);
  if (piVar2 != (int *)0x0) {
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2,1);
    }
    *(undefined4 *)(&flatRuntime2->field_0x1774 + param_2 * 0xc) = 0;
  }
  pcVar3 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_118,s_dvd__s_s_tex_801d8fa0,pcVar3,param_3);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_118,0,0);
  if (fileHandle != (CFileCHandle *)0x0) {
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    uVar4 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x44))(flatRuntime2);
    textureSet = (CTextureSet *)
                 __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                           ((CTextureSet *)0x24,uVar4,s_cflat_runtime2_cpp_801d8fb0,0x4f4);
    if (textureSet != (CTextureSet *)0x0) {
      textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
    }
    *(CTextureSet **)(&flatRuntime2->field_0x1774 + param_2 * 0xc) = textureSet;
    pvVar1 = File.m_readBuffer;
    uVar4 = GET_CHARA_ALLOC_STAGE_S__FiPQ27CMemory6CStage(CharaPcs._228_4_,Game.game.m_mainStage);
    Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
              (*(CTextureSet **)(&flatRuntime2->field_0x1774 + param_2 * 0xc),pvVar1,uVar4,0,0,0,0);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  }
  return;
}

