// Function: drawEnd__8CPartMngFv
// Entry: 8005de70
// Size: 120 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawEnd__8CPartMngFv(CPartMng *partMng)

{
  DAT_801eae08 = pppHeapCheckLeak__FPQ27CMemory6CStage(pppEnvStPtr->m_stagePtr);
  if ((DAT_801eae10 == 0) || (DAT_801eae10 = DAT_801eae10 + -1, DAT_801eae0c < DAT_801eae08)) {
    DAT_801eae10 = partMng->m_heapCheckInterval << 1;
    DAT_801eae0c = DAT_801eae08;
  }
  return;
}

