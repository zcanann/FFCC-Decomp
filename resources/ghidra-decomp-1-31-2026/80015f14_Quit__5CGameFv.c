// Function: Quit__5CGameFv
// Entry: 80015f14
// Size: 248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Quit__5CGameFv(CGame *game)

{
  Quit__12CFlatRuntimeFv(&CFlat);
  if (game->m_debugStage != (CStage *)0x0) {
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,game->m_debugStage);
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,game->m_mainStage);
  Quit__11CDbgMenuPcsFv(0x80306708);
  Quit__6CMcPcsFv(&McPcs);
  Quit__7CGbaPcsFv(&GbaPcs);
  Quit__8CMenuPcsFv(&MenuPcs);
  Quit__7CUSBPcsFv(&USBPcs);
  Quit__6CCharaFv(&Chara);
  Quit__9CCharaPcsFv(&CharaPcs);
  Quit__9CLightPcsFv(&LightPcs);
  Quit__7CMapPcsFv(&MapPcs);
  Quit__18CMaterialEditorPcsFv(&MaterialEditorPcs);
  Quit__14CFunnyShapePcsFv(&FunnyShapePcs);
  Quit__11CGraphicPcsFv(&GraphicsPcs);
  Quit__10CCameraPcsFv(&CameraPcs);
  return;
}

