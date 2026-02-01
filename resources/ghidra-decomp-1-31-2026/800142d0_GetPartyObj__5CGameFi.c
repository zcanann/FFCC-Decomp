// Function: GetPartyObj__5CGameFi
// Entry: 800142d0
// Size: 20 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CGPartyObj * GetPartyObj__5CGameFi(CGame *game,int index)

{
  return game->m_partyObjArr[index];
}

