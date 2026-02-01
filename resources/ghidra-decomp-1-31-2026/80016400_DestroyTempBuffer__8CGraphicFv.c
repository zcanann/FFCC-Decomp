// Function: DestroyTempBuffer__8CGraphicFv
// Entry: 80016400
// Size: 64 bytes

void DestroyTempBuffer__8CGraphicFv(CGraphic *graphic)

{
  if (graphic->tempBuffer != (uint8_t *)0x0) {
    __dla__FPv(graphic->tempBuffer);
    graphic->tempBuffer = (uint8_t *)0x0;
  }
  return;
}

