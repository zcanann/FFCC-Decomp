// Function: GetFoodLevel__5CGameFii
// Entry: 800143ec
// Size: 32 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined2 GetFoodLevel__5CGameFii(CGame *game,int param_2,int param_3)

{
  return *(undefined2 *)(game->m_scriptFoodBase[param_2] + param_3 * 2 + 0x3b8);
}

