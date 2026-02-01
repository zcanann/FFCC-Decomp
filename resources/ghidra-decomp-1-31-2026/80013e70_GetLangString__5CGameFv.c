// Function: GetLangString__5CGameFv
// Entry: 80013e70
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

char * GetLangString__5CGameFv(CGame *game)

{
  undefined *local_18 [4];
  undefined *local_8;
  undefined *local_4;
  
  local_18[0] = PTR_DAT_801d60b0;
  local_18[1] = PTR_DAT_801d60b4;
  local_18[2] = PTR_DAT_801d60b8;
  local_18[3] = PTR_DAT_801d60bc;
  local_8 = PTR_DAT_801d60c0;
  local_4 = PTR_DAT_801d60c4;
  return local_18[(game->m_gameWork).m_languageId];
}

