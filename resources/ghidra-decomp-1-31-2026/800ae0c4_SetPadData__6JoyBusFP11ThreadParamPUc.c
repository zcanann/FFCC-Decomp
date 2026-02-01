// Function: SetPadData__6JoyBusFP11ThreadParamPUc
// Entry: 800ae0c4
// Size: 356 bytes

void SetPadData__6JoyBusFP11ThreadParamPUc(JoyBus *joyBus,ThreadParam *threadParam,char *param_3)

{
  byte bVar1;
  uint8_t uVar2;
  ushort uVar3;
  
  uVar3 = 0;
  bVar1 = param_3[1];
  if ((bVar1 & 1) != 0) {
    uVar3 = 0x100;
  }
  if ((bVar1 & 2) != 0) {
    uVar3 = uVar3 | 0x200;
  }
  if ((bVar1 & 8) != 0) {
    uVar3 = uVar3 | 0x1000;
  }
  if ((bVar1 & 0x10) != 0) {
    uVar3 = uVar3 | 2;
  }
  if ((bVar1 & 0x20) != 0) {
    uVar3 = uVar3 | 1;
  }
  if ((bVar1 & 0x40) != 0) {
    uVar3 = uVar3 | 8;
  }
  if ((bVar1 & 0x80) != 0) {
    uVar3 = uVar3 | 4;
  }
  uVar2 = threadParam->m_state;
  if ((((uVar2 != '\x05') && (uVar2 != '!')) && (uVar2 != '\"')) &&
     ((uVar2 != '#' && (uVar2 != '$')))) {
    if (joyBus->m_stageId != '!') goto LAB_800ae1b4;
  }
  if ((bVar1 & 4) != 0) {
    uVar3 = uVar3 | 0x10;
  }
LAB_800ae1b4:
  if ((param_3[2] & 1U) != 0) {
    uVar3 = uVar3 | 0x20;
  }
  if ((param_3[2] & 2U) != 0) {
    uVar3 = uVar3 | 0x40;
  }
  OSWaitSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  joyBus->m_stageFlags[threadParam->m_portIndex] = uVar3;
  OSSignalSemaphore(joyBus->m_accessSemaphores + threadParam->m_portIndex);
  return;
}

