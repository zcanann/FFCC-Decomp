// Function: __write_console
// Entry: 801b9140
// Size: 208 bytes

undefined4
__write_console(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = OSGetConsoleType();
  if ((uVar1 & 0x20000000) == 0) {
    iVar2 = 0;
    if ((DAT_8032f398 == 0) && (iVar2 = InitializeUART(0xe100), iVar2 == 0)) {
      DAT_8032f398 = 1;
    }
    if (iVar2 != 0) {
      return 1;
    }
    iVar2 = WriteUARTN(param_2,*param_3);
    if (iVar2 != 0) {
      *param_3 = 0;
      return 1;
    }
  }
  __TRK_write_console(param_1,param_2,param_3,param_4);
  return 0;
}

