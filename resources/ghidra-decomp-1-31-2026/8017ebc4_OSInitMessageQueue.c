// Function: OSInitMessageQueue
// Entry: 8017ebc4
// Size: 96 bytes

void OSInitMessageQueue(int param_1,undefined4 param_2,undefined4 param_3)

{
  OSInitThreadQueue();
  OSInitThreadQueue(param_1 + 8);
  *(undefined4 *)(param_1 + 0x10) = param_2;
  *(undefined4 *)(param_1 + 0x14) = param_3;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}

