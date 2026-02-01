// Function: FGLetterOpen__12CCaravanWorkFi
// Entry: 800a23d8
// Size: 316 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FGLetterOpen__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  uint local_18;
  uint local_14;
  
  local_18 = *(ushort *)(caravanWork->m_letter0 + param_2 * 0xc) >> 2 & 0x1ff;
  local_14 = *(uint *)(caravanWork->m_letter0 + param_2 * 0xc) >> 9 & 0x1ff;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,Game.game.m_partyObjArr[caravanWork->m_joybusCaravanId],2,0xf,2,&local_18,
             (CStack *)0x0);
  m_tempVar__4CMes._0_4_ = ZEXT24(*(ushort *)(caravanWork->m_letter0 + param_2 * 0xc + 4));
  m_tempVar__4CMes._4_4_ = ZEXT24(*(ushort *)(caravanWork->m_letter0 + param_2 * 0xc + 6));
  m_tempVar__4CMes._8_4_ = ZEXT24(*(ushort *)(caravanWork->m_letterSlots + param_2 * 0xc + -4));
  m_tempVar__4CMes._12_4_ = ZEXT24(*(ushort *)(caravanWork->m_letterSlots + param_2 * 0xc + -2));
  m_tempVar__4CMes._16_4_ = *(ushort *)(caravanWork->m_letter0 + param_2 * 0xc) >> 2 & 0x1ff;
  m_tempVar__4CMes._20_4_ = *(uint *)(caravanWork->m_letter0 + param_2 * 0xc) >> 9 & 0x1ff;
  if ((caravanWork->m_letter0[param_2 * 0xc] >> 3 & 1) == 0) {
    m_tempVar__4CMes._24_4_ = *(ushort *)(caravanWork->m_letter0 + param_2 * 0xc + 2) & 0x1ff;
  }
  else {
    m_tempVar__4CMes._24_4_ = 0;
  }
  if ((caravanWork->m_letter0[param_2 * 0xc] >> 3 & 1) == 0) {
    m_tempVar__4CMes._28_4_ = 0;
  }
  else {
    m_tempVar__4CMes._28_4_ =
         (*(ushort *)(caravanWork->m_letter0 + param_2 * 0xc + 2) & 0x1ff) * 100;
  }
  m_tempVar__4CMes[0x20] = (caravanWork->gObjWork).m_saveSlot;
  m_tempVar__4CMes[0x21] = (caravanWork->gObjWork).m_partyIndex;
  m_tempVar__4CMes[0x22] = (caravanWork->gObjWork).m_isLoadingFlag;
  m_tempVar__4CMes[0x23] = (caravanWork->gObjWork).m_miscFlags;
  caravanWork->m_letter0[param_2 * 0xc] = caravanWork->m_letter0[param_2 * 0xc] & 0x7f | 0x80;
  return;
}

