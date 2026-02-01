// Function: pppSetDeltaIdx__8CPartMngFsl
// Entry: 80057ccc
// Size: 20 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetDeltaIdx__8CPartMngFsl(CPartMng *partMng,short param_2,undefined4 param_3)

{
  _pppMngSt *p_Var1;
  
  p_Var1 = partMng->m_pppMngStArr + param_2;
  p_Var1->m_envColorR = (char)((uint)param_3 >> 0x18);
  p_Var1->m_envColorG = (char)((uint)param_3 >> 0x10);
  p_Var1->m_envColorB = (char)((uint)param_3 >> 8);
  p_Var1->m_envColorA = (char)param_3;
  return;
}

