// Function: drawCopy__11CGraphicPcsFv
// Entry: 800465bc
// Size: 400 bytes

void drawCopy__11CGraphicPcsFv(int param_1)

{
  undefined4 uVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(int *)(param_1 + 0xbc) != 0) {
    CopySaveFrameBuffer__8CGraphicFv(&Graphic);
    *(undefined4 *)(param_1 + 0xbc) = 0;
  }
  if (*(int *)(param_1 + 0xc0) != 0) {
    local_18 = *(undefined4 *)(param_1 + 0xd4);
    local_14 = *(undefined4 *)(param_1 + 0xd8);
    local_10 = *(undefined4 *)(param_1 + 0xdc);
    RenderDOF__8CGraphicFScScff3Veci
              ((double)*(float *)(param_1 + 200),(double)*(float *)(param_1 + 0xcc),&Graphic,
               *(undefined *)(param_1 + 0xe0),*(undefined *)(param_1 + 0xc4),&local_18);
  }
  uVar1 = 0;
  if ((*(int *)(param_1 + 0xe4) == 1) && (DAT_802381a0 == 0)) {
    DAT_802381a0 = 1;
    InitBlurParameter__8CGraphicFv(&Graphic);
    uVar1 = 1;
    *(byte *)(param_1 + 0xef) = *(byte *)(param_1 + 0xee) / *(byte *)(param_1 + 0xec);
    *(undefined4 *)(param_1 + 0xe8) = 0;
  }
  if (((*(int *)(param_1 + 0xe4) != 0) || (DAT_802381a0 != 0)) || (*(int *)(param_1 + 0xe8) != 0)) {
    if (*(int *)(param_1 + 0xe4) != DAT_802381a0) {
      *(undefined4 *)(param_1 + 0xe8) = 1;
    }
    RenderBlur__8CGraphicFiUcUcUcUcs
              (&Graphic,uVar1,*(undefined *)(param_1 + 0xf1),(uint)*(byte *)(param_1 + 0xf0),
               *(undefined *)(param_1 + 0xed),*(undefined *)(param_1 + 0xee),
               *(undefined2 *)(param_1 + 0xf2));
    if (*(int *)(param_1 + 0xe8) != 0) {
      if ((int)((uint)*(byte *)(param_1 + 0xee) - (uint)*(byte *)(param_1 + 0xef)) < 1) {
        *(undefined *)(param_1 + 0xee) = 0;
        *(undefined4 *)(param_1 + 0xe8) = 0;
        *(undefined4 *)(param_1 + 0xe4) = 0;
        DAT_802381a0 = 0;
      }
      else {
        *(byte *)(param_1 + 0xee) = *(byte *)(param_1 + 0xee) - *(byte *)(param_1 + 0xef);
      }
    }
  }
  drawScreenFade__11CGraphicPcsFv(param_1);
  return;
}

