// Function: ChangeMap__5CGameFiiii
// Entry: 80014e78
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChangeMap__5CGameFiiii(CGame *game,uint32_t param_2,uint32_t param_3,uint param_4,int param_5)

{
  uint uVar1;
  
  if (param_5 == 0) {
    uVar1 = (int)(-param_4 | param_4) >> 0x1f;
    LoadMap__7CMapPcsFiiPvUlUc
              (&MapPcs,param_2,param_3,uVar1 & 0x800000,uVar1 & 0x580000,param_4 & 0xff);
    uVar1 = (int)(-param_4 | param_4) >> 0x1f;
    LoadFieldPdt__8CPartPcsFiiPvUlUc
              (&PartPcs,param_2,param_3,uVar1 & 0xd80000,uVar1 & 0x80000,(char)param_4);
  }
  else {
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_game_cpp_801d6190,0x24e);
    MapChanging__7CSystemFii(&System,param_2,param_3);
    game->m_currentMapId = param_2;
    uVar1 = (int)(-param_4 | param_4) >> 0x1f;
    game->m_currentMapVariantId = param_3;
    LoadMap__7CMapPcsFiiPvUlUc(&MapPcs,param_2,param_3,uVar1 & 0x800000,uVar1 & 0x580000,0);
    uVar1 = (int)(-param_4 | param_4) >> 0x1f;
    LoadFieldPdt__8CPartPcsFiiPvUlUc(&PartPcs,param_2,param_3,uVar1 & 0xd80000,uVar1 & 0x80000,0);
    MapChanged__7CSystemFiii(&System,param_2,param_3,1);
  }
  return;
}

