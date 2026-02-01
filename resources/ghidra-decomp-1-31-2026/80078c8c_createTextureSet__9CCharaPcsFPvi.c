// Function: createTextureSet__9CCharaPcsFPvi
// Entry: 80078c8c
// Size: 284 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CTextureSet * createTextureSet__9CCharaPcsFPvi(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  CTextureSet *textureSet;
  CStage *stage;
  
  textureSet = (CTextureSet *)
               __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                         ((CTextureSet *)0x24,CharaPcs._192_4_,s_p_chara_cpp_801d91bc,0x397);
  if (textureSet != (CTextureSet *)0x0) {
    textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
  }
  iVar1 = 1;
  if (param_3 != 0) {
    iVar1 = 3;
  }
  stage = PartMng.m_pppEnvSt.m_stagePtr;
  if (CharaPcs._228_4_ != 3) {
    if ((int)CharaPcs._228_4_ < 3) {
      stage = (CStage *)MapMng._0_4_;
      if ((CharaPcs._228_4_ != 1) &&
         (stage = PartPcs.m_usbStreamData.m_stageLoad, (int)CharaPcs._228_4_ < 1)) {
        stage = *(CStage **)(&CharaPcs.field_0xcc + iVar1 * 4);
      }
    }
    else {
      stage = *(CStage **)(&CharaPcs.field_0xcc + iVar1 * 4);
      if ((int)CharaPcs._228_4_ < 5) {
        stage = (CStage *)CharaPcs._212_4_;
      }
    }
  }
  Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(textureSet,param_2,stage,0,0,0,0);
  return textureSet;
}

