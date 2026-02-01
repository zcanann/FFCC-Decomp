// Function: __CARDGetFatBlock
// Entry: 8019adc8
// Size: 8 bytes

uint16_t * __CARDGetFatBlock(CARDControl *cardControl)

{
  return cardControl->currentFat;
}

