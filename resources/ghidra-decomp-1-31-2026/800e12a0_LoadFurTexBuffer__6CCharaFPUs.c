// Function: LoadFurTexBuffer__6CCharaFPUs
// Entry: 800e12a0
// Size: 68 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadFurTexBuffer__6CCharaFPUs(CChara *param_1,undefined4 param_2)

{
  memcpy(&Chara.field0_0x0.object.base_object.object.m_freeListNode,param_2,0x2000);
  CalcMogScore__6CCharaFv(param_1);
  return;
}

