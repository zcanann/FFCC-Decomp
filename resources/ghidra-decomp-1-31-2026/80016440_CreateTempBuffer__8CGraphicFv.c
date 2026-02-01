// Function: CreateTempBuffer__8CGraphicFv
// Entry: 80016440
// Size: 132 bytes

void CreateTempBuffer__8CGraphicFv(CGraphic *graphic)

{
  uint8_t *puVar1;
  
  puVar1 = (uint8_t *)
           _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                     (&Memory,(*(ushort *)(*(int *)&graphic->field_0x71e0 + 4) + 0xf & 0xfff0) *
                              (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6) * 2 + 0x46000,
                      *(undefined4 *)&graphic->field_0x8,s_graphic_cpp_801d6348,0xb53,0);
  graphic->tempBuffer = puVar1;
  memset(graphic->tempBuffer,0,0x46004);
  return;
}

