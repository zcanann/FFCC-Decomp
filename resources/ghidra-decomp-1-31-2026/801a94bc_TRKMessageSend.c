// Function: TRKMessageSend
// Entry: 801a94bc
// Size: 68 bytes

undefined4 TRKMessageSend(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = TRKWriteUARTN(param_1 + 0x10,*(undefined4 *)(param_1 + 8));
  MWTRACE(1,s_MessageSend___cc_write_returned___801e6650,uVar1);
  return 0;
}

