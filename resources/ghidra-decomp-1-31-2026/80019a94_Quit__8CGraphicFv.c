// Function: Quit__8CGraphicFv
// Entry: 80019a94
// Size: 192 bytes

void Quit__8CGraphicFv(CGraphic *graphic)

{
  if (*(void **)&graphic->field_0x71ec != (void *)0x0) {
    __dla__FPv(*(void **)&graphic->field_0x71ec);
    *(undefined4 *)&graphic->field_0x71ec = 0;
  }
  if (*(void **)&graphic->field_0x71e4 != (void *)0x0) {
    __dla__FPv(*(void **)&graphic->field_0x71e4);
    *(undefined4 *)&graphic->field_0x71e4 = 0;
  }
  if (graphic->tempBuffer != (uint8_t *)0x0) {
    __dla__FPv(graphic->tempBuffer);
    graphic->tempBuffer = (uint8_t *)0x0;
  }
  if (*(void **)&graphic->field_0x71fc != (void *)0x0) {
    __dla__FPv(*(void **)&graphic->field_0x71fc);
    *(undefined4 *)&graphic->field_0x71fc = 0;
  }
  if (*(void **)&graphic->field_0x10 != (void *)0x0) {
    __dla__FPv(*(void **)&graphic->field_0x10);
    *(undefined4 *)&graphic->field_0x10 = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&graphic->field_0x8);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&graphic->field_0x4);
  return;
}

