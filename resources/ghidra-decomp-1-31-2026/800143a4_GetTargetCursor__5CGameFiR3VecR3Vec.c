// Function: GetTargetCursor__5CGameFiR3VecR3Vec
// Entry: 800143a4
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GetTargetCursor__5CGameFiR3VecR3Vec(CGame *game,int param_2,Vec *param_3,Vec *param_4)

{
  uint32_t uVar1;
  
  uVar1 = game->m_scriptFoodBase[param_2];
  param_3->x = *(float *)(uVar1 + 0xbac);
  param_3->y = *(float *)(uVar1 + 0xbb0);
  param_3->z = *(float *)(uVar1 + 0xbb4);
  uVar1 = game->m_scriptFoodBase[param_2];
  param_4->x = *(float *)(uVar1 + 3000);
  param_4->y = *(float *)(uVar1 + 0xbbc);
  param_4->z = *(float *)(uVar1 + 0xbc0);
  return;
}

