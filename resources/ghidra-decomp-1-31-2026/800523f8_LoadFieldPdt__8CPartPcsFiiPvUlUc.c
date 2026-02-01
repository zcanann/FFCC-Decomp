// Function: LoadFieldPdt__8CPartPcsFiiPvUlUc
// Entry: 800523f8
// Size: 216 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadFieldPdt__8CPartPcsFiiPvUlUc
               (CPartPcs *partPcs,undefined4 param_2,undefined4 param_3,int32_t param_4,int param_5,
               char param_6)

{
  PartMng.m_partChunkIndex = 0;
  PartMng.m_asyncHandleCount = 0;
  if (param_5 == 0) {
    PartMng.m_partLoadMode = 0;
  }
  else if (param_6 == '\x01') {
    PartMng.m_partLoadMode = 2;
  }
  else if (param_6 == '\x02') {
    PartMng.m_partLoadMode = 3;
    PartMng.m_partAsyncBusy[0] = 0;
    PartMng.m_partAsyncBusy[1] = 0;
    PartMng.m_partAsyncBusy[2] = 0;
    PartMng.m_partAsyncBusy[3] = 0;
    PartMng.m_partAsyncBusy[4] = 0;
    PartMng.m_partAsyncBusy[5] = 0;
    PartMng.m_partAsyncBusy[6] = 0;
    PartMng.m_partAsyncBusy[7] = 0;
    PartMng.m_partAsyncBusy[8] = 0;
    PartMng.m_partAsyncBusy[9] = 0;
    PartMng.m_partAsyncBusy[10] = 0;
    PartMng.m_partAsyncBusy[0xb] = 0;
    PartMng.m_partAsyncBusy[0xc] = 0;
    PartMng.m_partAsyncBusy[0xd] = 0;
    PartMng.m_partAsyncBusy[0xe] = 0;
    PartMng.m_partAsyncBusy[0xf] = 0;
  }
  else {
    PartMng.m_partLoadMode = 1;
  }
  PartMng.m_partAMemBase = param_4;
  PartMng.m_partAMemCursor = param_4;
  PartMng.m_partLoadCacheParam = param_5;
  LoadFieldPdt0__Fii(param_2,param_3);
  return;
}

