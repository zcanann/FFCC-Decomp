// Function: GetCtrlMode__6JoyBusFi
// Entry: 800a76f8
// Size: 88 bytes

uint8_t GetCtrlMode__6JoyBusFi(JoyBus *joyBus,int portIndex)

{
  char cVar1;
  uint8_t uVar2;
  
  cVar1 = IsSingleMode__8GbaQueueFi(&GbaQue,portIndex);
  if (cVar1 == '\0') {
    uVar2 = joyBus->m_ctrlModeArr[portIndex];
  }
  else {
    uVar2 = '\0';
  }
  return uVar2;
}

