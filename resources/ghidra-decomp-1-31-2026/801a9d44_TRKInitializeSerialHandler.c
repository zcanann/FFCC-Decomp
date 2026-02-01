// Function: TRKInitializeSerialHandler
// Entry: 801a9d44
// Size: 196 bytes

undefined4 TRKInitializeSerialHandler(void)

{
  DAT_8032a100 = 0xffffffff;
  DAT_8032a108 = 0;
  DAT_8032a10c = 0;
  MWTRACE(1,s_TRK_Packet_Header__ld_bytes_801e6698,0x40);
  MWTRACE(1,s_TRK_CMD_ReadMemory__ld_bytes_801e66bc,0x40);
  MWTRACE(1,s_TRK_CMD_WriteMemory__ld_bytes_801e66e0,0x40);
  MWTRACE(1,s_TRK_CMD_Connect__ld_bytes_801e6704,0x40);
  MWTRACE(1,s_TRK_CMD_ReplyAck__ld_bytes_801e6724,0x40);
  MWTRACE(1,s_TRK_CMD_ReadRegisters__ld_bytes_801e6744,0x40);
  return 0;
}

