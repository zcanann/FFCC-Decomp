// Function: GetSysMes__5CGameFi
// Entry: 800b9504
// Size: 16 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 GetSysMes__5CGameFi(CGame *game,int param_2)

{
  return *(undefined4 *)((game->m_gameWork).m_linkTable[0][0][5] + param_2 * 4 + 4);
}

