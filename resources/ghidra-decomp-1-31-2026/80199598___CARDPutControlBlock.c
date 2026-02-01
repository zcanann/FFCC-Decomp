// Function: __CARDPutControlBlock
// Entry: 80199598
// Size: 100 bytes

int32_t __CARDPutControlBlock(CARDControl *param_1,int32_t result)

{
  OSDisableInterrupts();
  if (param_1->attached == 0) {
    if (param_1->result == -1) {
      param_1->result = result;
    }
  }
  else {
    param_1->result = result;
  }
  OSRestoreInterrupts();
  return result;
}

