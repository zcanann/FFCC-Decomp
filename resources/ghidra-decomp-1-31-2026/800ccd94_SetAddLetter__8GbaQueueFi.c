// Function: SetAddLetter__8GbaQueueFi
// Entry: 800ccd94
// Size: 24 bytes

void SetAddLetter__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  gbaQueue->field_0x2c89 = gbaQueue->field_0x2c89 | (byte)(1 << param_2);
  return;
}

