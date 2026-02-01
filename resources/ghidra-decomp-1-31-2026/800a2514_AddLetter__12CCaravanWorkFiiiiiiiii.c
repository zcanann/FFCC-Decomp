// Function: AddLetter__12CCaravanWorkFiiiiiiiii
// Entry: 800a2514
// Size: 392 bytes

void AddLetter__12CCaravanWorkFiiiiiiiii
               (CCaravanWork *caravanWork,int param_2,uint param_3,int param_4,int param_5,
               int param_6,undefined2 param_7,undefined2 param_8,undefined2 param_9,
               undefined2 param_10)

{
  int32_t iVar1;
  uint8_t *puVar2;
  int iVar3;
  
  puVar2 = caravanWork->m_letterSlots + 0xac;
  iVar3 = 0x21;
  do {
    *(undefined4 *)(puVar2 + 0x3ec) = *(undefined4 *)(puVar2 + 0x3e0);
    *(undefined4 *)(puVar2 + 0x3f0) = *(undefined4 *)(puVar2 + 0x3e4);
    *(undefined4 *)(puVar2 + 0x3f4) = *(undefined4 *)(puVar2 + 1000);
    *(undefined4 *)(puVar2 + 0x3e0) = *(undefined4 *)(puVar2 + 0x3d4);
    *(undefined4 *)(puVar2 + 0x3e4) = *(undefined4 *)(puVar2 + 0x3d8);
    *(undefined4 *)(puVar2 + 1000) = *(undefined4 *)(puVar2 + 0x3dc);
    *(undefined4 *)(puVar2 + 0x3d4) = *(undefined4 *)(puVar2 + 0x3c8);
    *(undefined4 *)(puVar2 + 0x3d8) = *(undefined4 *)(puVar2 + 0x3cc);
    *(undefined4 *)(puVar2 + 0x3dc) = *(undefined4 *)(puVar2 + 0x3d0);
    puVar2 = puVar2 + -0x24;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  memset(caravanWork->m_letter0,0,0xc);
  *(ushort *)caravanWork->m_letter0 =
       (ushort)(param_2 << 2) & 0x7fc | *(ushort *)caravanWork->m_letter0 & 0xf803;
  *(uint *)caravanWork->m_letter0 =
       (param_3 & 0x1ff) << 9 | *(uint *)caravanWork->m_letter0 & 0xfffc01ff;
  caravanWork->m_letter0[0] = (byte)(param_5 << 3) & 8 | caravanWork->m_letter0[0] & 0xf7;
  if ((caravanWork->m_letter0[0] >> 3 & 1) != 0) {
    iVar3 = param_4 / 100 + (param_4 >> 0x1f);
    param_4 = iVar3 - (iVar3 >> 0x1f);
  }
  *(ushort *)(caravanWork->m_letter0 + 2) =
       (ushort)param_4 & 0x1ff | *(ushort *)(caravanWork->m_letter0 + 2) & 0xfe00;
  caravanWork->m_letter0[0] = caravanWork->m_letter0[0] & 0x7f;
  caravanWork->m_letter0[0] = caravanWork->m_letter0[0] & 0xbf;
  caravanWork->m_letter0[0] = caravanWork->m_letter0[0] & 0xdf;
  caravanWork->m_letter0[0] = (byte)(param_6 << 4) & 0x10 | caravanWork->m_letter0[0] & 0xef;
  *(undefined2 *)(caravanWork->m_letter0 + 4) = param_7;
  *(undefined2 *)(caravanWork->m_letter0 + 6) = param_8;
  *(undefined2 *)(caravanWork->m_letter0 + 8) = param_9;
  *(undefined2 *)(caravanWork->m_letter0 + 10) = param_10;
  iVar3 = caravanWork->m_letterCount + 1;
  iVar1 = 100;
  if (iVar3 < 100) {
    iVar1 = iVar3;
  }
  caravanWork->m_letterCount = iVar1;
  SetAddLetter__8GbaQueueFi(&GbaQue,caravanWork->m_joybusCaravanId);
  return;
}

