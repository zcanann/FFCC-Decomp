// Function: pppSetDeltaSlot__8CPartMngFil
// Entry: 80057c08
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetDeltaSlot__8CPartMngFil(CPartMng *partMng,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = 0x40;
  do {
    if ((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[0].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[0].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[0].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[0].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[0].m_envColorA = (char)param_3;
    }
    if ((partMng->m_pppMngStArr[1].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[1].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[1].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[1].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[1].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[1].m_envColorA = (char)param_3;
    }
    if ((partMng->m_pppMngStArr[2].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[2].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[2].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[2].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[2].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[2].m_envColorA = (char)param_3;
    }
    if ((partMng->m_pppMngStArr[3].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[3].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[3].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[3].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[3].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[3].m_envColorA = (char)param_3;
    }
    if ((partMng->m_pppMngStArr[4].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[4].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[4].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[4].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[4].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[4].m_envColorA = (char)param_3;
    }
    if ((partMng->m_pppMngStArr[5].m_baseTime != -0x1000) &&
       (*(int *)&partMng->m_pppMngStArr[5].field_0x100 == param_2)) {
      partMng->m_pppMngStArr[5].m_envColorR = (char)((uint)param_3 >> 0x18);
      partMng->m_pppMngStArr[5].m_envColorG = (char)((uint)param_3 >> 0x10);
      partMng->m_pppMngStArr[5].m_envColorB = (char)((uint)param_3 >> 8);
      partMng->m_pppMngStArr[5].m_envColorA = (char)param_3;
    }
    partMng = (CPartMng *)(partMng->m_usbEdit + 0x20);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

