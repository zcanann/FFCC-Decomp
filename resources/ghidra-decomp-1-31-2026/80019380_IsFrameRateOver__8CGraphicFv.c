// Function: IsFrameRateOver__8CGraphicFv
// Entry: 80019380
// Size: 8 bytes

undefined4 IsFrameRateOver__8CGraphicFv(CGraphic *graphic)

{
  return *(undefined4 *)&graphic->field_0x7350;
}

