// Function: calc__8CPartPcsFv
// Entry: 80053138
// Size: 144 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__8CPartPcsFv(CPartPcs *partPcs)

{
  uint uVar1;
  
  FUN_8005992c(&PartMng);
  if ((partPcs->m_usbStreamData).m_printFreeOnNext != '\0') {
    (partPcs->m_usbStreamData).m_printFreeOnNext = '\0';
    uVar1 = AmemGetFreeSize__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
    Printf__7CSystemFPce
              (&System,&DAT_801d8068,
               ((int)uVar1 >> 10) + (uint)((int)uVar1 < 0 && (uVar1 & 0x3ff) != 0));
  }
  CalcPrio__13CAmemCacheSetFv((CAmemCacheSet *)CAMemCacheSet);
  pppDumpCacheIdx__8CPartMngFv(&PartMng);
  return;
}

