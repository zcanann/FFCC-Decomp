// Function: FGLetterReply__12CCaravanWorkFiiii
// Entry: 800a2330
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FGLetterReply__12CCaravanWorkFiiii
               (CCaravanWork *caravanWork,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  uint local_28;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = param_2 * 0xc;
  local_28 = *(ushort *)(caravanWork->m_letter0 + iVar1) >> 2 & 0x1ff;
  local_24 = *(uint *)(caravanWork->m_letter0 + iVar1) >> 9 & 0x1ff;
  local_20 = param_3;
  local_1c = param_4;
  local_18 = param_5;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,Game.game.m_partyObjArr[caravanWork->m_joybusCaravanId],2,0x10,5,&local_28,
             (CStack *)0x0);
  caravanWork->m_letter0[iVar1] = caravanWork->m_letter0[iVar1] & 0xdf | 0x20;
  return;
}

