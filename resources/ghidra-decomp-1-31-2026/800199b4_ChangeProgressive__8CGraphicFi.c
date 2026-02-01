// Function: ChangeProgressive__8CGraphicFi
// Entry: 800199b4
// Size: 156 bytes

void ChangeProgressive__8CGraphicFi(CGraphic *graphic,undefined4 param_2)

{
  if (*(int **)&graphic->field_0x71e0 != INT_ARRAY_801e83c0) {
    *(int **)&graphic->field_0x71e0 = INT_ARRAY_801e83c0;
    GXAdjustForOverscan(*(undefined4 *)&graphic->field_0x71e0,*(undefined4 *)&graphic->field_0x71e0,
                        0,0x10);
    VIConfigure(*(undefined4 *)&graphic->field_0x71e0);
    GXSetCopyFilter(*(undefined *)(*(int *)&graphic->field_0x71e0 + 0x19),
                    *(int *)&graphic->field_0x71e0 + 0x1a,1,&DAT_801e83f2);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
  }
  OSGetProgressiveMode(param_2);
  return;
}

