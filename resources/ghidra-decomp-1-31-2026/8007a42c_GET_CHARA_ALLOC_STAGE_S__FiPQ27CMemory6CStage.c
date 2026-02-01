// Function: GET_CHARA_ALLOC_STAGE_S__FiPQ27CMemory6CStage
// Entry: 8007a42c
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CStage * GET_CHARA_ALLOC_STAGE_S__FiPQ27CMemory6CStage(int param_1,CStage *stage)

{
  if (param_1 == 3) {
    return PartMng.m_pppEnvSt.m_stagePtr;
  }
  if (param_1 < 3) {
    if (param_1 == 1) {
      return (CStage *)MapMng._0_4_;
    }
    if (0 < param_1) {
      return PartPcs.m_usbStreamData.m_stageLoad;
    }
  }
  else if (param_1 < 5) {
    return (CStage *)CharaPcs._212_4_;
  }
  return stage;
}

