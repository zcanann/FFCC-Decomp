// Function: Exec__5CGameFv
// Entry: 800157a8
// Size: 1764 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Exec__5CGameFv(CGame *game)

{
  uint32_t uVar1;
  
  AddScenegraph__7CSystemFP8CProcessi(&System,&DAT_8032ed08,0);
  AddScenegraph__7CSystemFP8CProcessi(&System,&GraphicsPcs,0);
  AddScenegraph__7CSystemFP8CProcessi(&System,&LightPcs,0);
  AddScenegraph__7CSystemFP8CProcessi(&System,0x80306708,0);
  do {
    game->m_cfdLoadedFlag = '\0';
    game->m_assetsLoadedFlag = '\0';
    IncHeapWalkerLevel__7CMemoryFv(&Memory);
    game->m_currentSceneId = game->m_sceneId;
    game->m_currentMapId = game->m_mapId;
    game->m_currentMapVariantId = game->m_mapVariant;
    strcpy(game->m_currentScriptName,game->m_sceneScript + 4);
    uVar1 = game->m_currentSceneId;
    if (((int)uVar1 < 0) || (8 < (int)uVar1)) {
      Printf__7CSystemFPce(&System,&DAT_801d626c);
    }
    else {
      Printf__7CSystemFPce(&System,s_CGame_Exec__scene____s_801d6254,(&m_tStatus)[uVar1]);
    }
    switch(game->m_currentSceneId) {
    case 2:
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,1);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs,1);
      break;
    case 3:
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,2);
      AddScenegraph__7CSystemFP8CProcessi(&System,&MapPcs,1);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,6);
      break;
    case 4:
      AddScenegraph__7CSystemFP8CProcessi(&System,&MenuPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&MapPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,6);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&DAT_8032ed00,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&PartPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&GbaPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,0x80300268,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&McPcs,0);
      AddScenegraph__7CSystemFP8CProcessi(&System,&SoundPcs,0);
      break;
    case 5:
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,3);
      AddScenegraph__7CSystemFP8CProcessi(&System,&MaterialEditorPcs,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&LightPcs.process,0);
      break;
    case 6:
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,4);
      AddScenegraph__7CSystemFP8CProcessi(&System,&FunnyShapePcs,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&LightPcs.process,0);
      break;
    case 7:
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,5);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs,2);
      AddScenegraph__7CSystemFP8CProcessi(&System,&MapPcs,1);
      AddScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs,6);
      AddScenegraph__7CSystemFP8CProcessi(&System,&PartPcs,1);
    }
    ExecScenegraph__7CSystemFv(&System);
    switch(game->m_currentSceneId) {
    case 2:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,1);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs.process,1);
      break;
    case 3:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,2);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,6);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&MapPcs.process,1);
      break;
    case 4:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&SoundPcs,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&McPcs,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,6);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&MapPcs.process,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs.process,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&PartPcs.process,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&GbaPcs,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&DAT_8032ed00,0);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&MenuPcs.process,0);
      break;
    case 5:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,3);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&MaterialEditorPcs.process,0);
      break;
    case 6:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,4);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&FunnyShapePcs.process,0);
      break;
    case 7:
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,5);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CameraPcs.process,6);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&CharaPcs.process,2);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&MapPcs.process,1);
      RemoveScenegraph__7CSystemFP8CProcessi(&System,&PartPcs.process,1);
    }
    HeapWalker__7CMemoryFv(&Memory);
    DecHeapWalkerLevel__7CMemoryFv(&Memory);
  } while (game->m_sceneId != 0);
  RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&MiniGamePcs.field_0x6480,0);
  RemoveScenegraph__7CSystemFP8CProcessi(&System,&LightPcs.process,0);
  RemoveScenegraph__7CSystemFP8CProcessi(&System,&GraphicsPcs.process,0);
  RemoveScenegraph__7CSystemFP8CProcessi(&System,(CProcess *)&DAT_8032ed08,0);
  return;
}

