// Function: SetViewport__8CGraphicFv
// Entry: 80019830
// Size: 136 bytes

void SetViewport__8CGraphicFv(CGraphic *graphic)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8032f6c0;
  GXSetViewport(dVar1,dVar1,
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 4)) -
                               DOUBLE_8032f6d8),
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 6)) -
                               DOUBLE_8032f6d8),dVar1,(double)FLOAT_8032f6c4);
  GXSetScissor(0,0,*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
               *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  return;
}

