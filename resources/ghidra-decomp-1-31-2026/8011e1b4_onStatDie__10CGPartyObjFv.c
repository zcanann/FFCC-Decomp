// Function: onStatDie__10CGPartyObjFv
// Entry: 8011e1b4
// Size: 376 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatDie__10CGPartyObjFv(CGPrgObj *param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1->m_subState;
  if (iVar2 == 1) {
    if (param_1->m_subFrame == 0) {
      (param_1->object).m_bgColMask = (param_1->object).m_bgColMask & 0xfffefff1;
      (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x94))(param_1,1);
      bVar1 = *(byte *)&param_1[1].object.unk_0x168;
      if ((int)((uint)bVar1 << 0x1d | (uint)(bVar1 >> 3)) < 0) {
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (param_1,0x220,2,0,&(param_1->object).m_worldPosition);
        putParticleFromItem__10CGCharaObjFiiiP3Vec
                  (param_1,0x220,3,0,&(param_1->object).m_worldPosition);
        changeSubStat__8CGPrgObjFi(param_1,2);
      }
    }
    else if (param_1->m_subFrame == 0x19) {
      changeStat__8CGPrgObjFiii(param_1,0x22,0,0);
    }
  }
  else if (iVar2 < 1) {
    if (-1 < iVar2) {
      if (param_1->m_subFrame == 0) {
        (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x94))(param_1,0);
      }
      iVar2 = isLoopAnimDirect__8CGPrgObjFv(param_1);
      if (iVar2 != 0) {
        changeSubStat__8CGPrgObjFi(param_1,1);
      }
    }
  }
  else if ((iVar2 < 3) && (0xba < param_1->m_subFrame)) {
    if (1 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801dccb0);
    }
    changeStat__8CGPrgObjFiii(param_1,0x22,0,0);
  }
  return;
}

