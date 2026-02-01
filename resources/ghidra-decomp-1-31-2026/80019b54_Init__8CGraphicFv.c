// Function: Init__8CGraphicFv
// Entry: 80019b54
// Size: 1000 bytes

void Init__8CGraphicFv(CGraphic *graphic)

{
  ushort uVar1;
  uint uVar2;
  float fVar3;
  CStage *pCVar4;
  undefined4 uVar5;
  uint8_t *puVar6;
  int iVar7;
  double dVar8;
  
  pCVar4 = CreateStage__7CMemoryFUlPci(&Memory,0x19c000,s_CGraphic_801d6330,0);
  *(CStage **)&graphic->field_0x4 = pCVar4;
  pCVar4 = CreateStage__7CMemoryFUlPci(&Memory,0xd6000,s_CGraphic2_801d6488,0);
  *(CStage **)&graphic->field_0x8 = pCVar4;
  fVar3 = FLOAT_8032f6c0;
  *(undefined4 *)&graphic->field_0x14 = 0;
  graphic->field_0x7200 = 0;
  graphic->field_0x7201 = 0;
  graphic->field_0x7202 = 0;
  graphic->field_0x7203 = 0;
  graphic->fogParamB = fVar3;
  graphic->fogParamA = fVar3;
  graphic->field_0x735f = graphic->field_0x7200;
  graphic->field_0x7360 = graphic->field_0x7201;
  graphic->field_0x7361 = graphic->field_0x7202;
  graphic->field_0x7362 = graphic->field_0x7203;
  memset(&graphic->field_0x7364,0,0x10);
  OSCreateThread(&m_thread,checkThread__FPv,0,&Math,0x4000,1,1);
  OSResumeThread(&m_thread);
  VIInit();
  *(int **)&graphic->field_0x71e0 = INT_ARRAY_801e83c0;
  *(undefined4 *)&graphic->field_0x71f0 = 1;
  iVar7 = *(int *)&graphic->field_0x71e0;
  uVar1 = *(ushort *)(iVar7 + 6);
  uVar2 = *(ushort *)(iVar7 + 4) + 0xf & 0xfff0;
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                    (uVar2 * *(ushort *)(iVar7 + 8) * 2,*(undefined4 *)&graphic->field_0x4,
                     s_graphic_cpp_801d6348,0x86);
  *(undefined4 *)&graphic->field_0x71e4 = uVar5;
  memset(*(undefined4 *)&graphic->field_0x71e4,0,4);
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                    (uVar2 * uVar1 * 2,*(undefined4 *)&graphic->field_0x4,s_graphic_cpp_801d6348,
                     0x88);
  *(undefined4 *)&graphic->field_0x71ec = uVar5;
  memset(*(undefined4 *)&graphic->field_0x71ec,0,4);
  puVar6 = (uint8_t *)
           _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                     (&Memory,(*(ushort *)(*(int *)&graphic->field_0x71e0 + 4) + 0xf & 0xfff0) *
                              (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6) * 2 + 0x46000,
                      *(undefined4 *)&graphic->field_0x8,s_graphic_cpp_801d6348,0xb53,0);
  graphic->tempBuffer = puVar6;
  memset(graphic->tempBuffer,0,0x46004);
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                    (0x60000,*(undefined4 *)&graphic->field_0x4,s_graphic_cpp_801d6348,0x8b);
  *(undefined4 *)&graphic->field_0x10 = uVar5;
  VIConfigure(*(undefined4 *)&graphic->field_0x71e0);
  GXInit(*(undefined4 *)&graphic->field_0x10,0x60000);
  dVar8 = (double)FLOAT_8032f6c0;
  GXSetViewport(dVar8,dVar8,
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 4)) -
                               DOUBLE_8032f6d8),
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        (*(int *)&graphic->field_0x71e0 + 6)) -
                               DOUBLE_8032f6d8),dVar8,(double)FLOAT_8032f6c4);
  GXSetScissor(0,0,*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
               *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  GXGetYScaleFactor(*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6),
                    *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 8));
  GXSetDispCopyYScale();
  GXSetDispCopySrc(0,0,*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  GXSetDispCopyDst(*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  GXSetCopyFilter(*(undefined *)(*(int *)&graphic->field_0x71e0 + 0x19),
                  *(int *)&graphic->field_0x71e0 + 0x1a,1,&DAT_8021c652);
  if (*(char *)(*(int *)&graphic->field_0x71e0 + 0x19) == '\0') {
    GXSetPixelFmt(0,0);
  }
  else {
    GXSetPixelFmt(2,0);
  }
  GXSetDispCopySrc(0,0,*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  GXSetDispCopyDst(*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  GXCopyDisp(*(undefined4 *)&graphic->field_0x71e4,1);
  GXSetDispCopyGamma(0);
  VISetNextFrameBuffer(*(undefined4 *)&graphic->field_0x71e4);
  VIFlush();
  VIWaitForRetrace();
  if ((**(uint **)&graphic->field_0x71e0 & 1) != 0) {
    VIWaitForRetrace();
  }
  uVar5 = VIGetRetraceCount();
  *(undefined4 *)&graphic->field_0x71f4 = uVar5;
  *(undefined4 *)&graphic->field_0xc = 0;
  *(undefined4 *)&graphic->field_0x734c = 0;
  *(undefined4 *)&graphic->field_0x7350 = 0;
  *(undefined4 *)&graphic->field_0x7354 = 0;
  makeSphere__8CGraphicFv(graphic);
  *(undefined4 *)&graphic->field_0x7358 = 0;
  graphic->field_0x735c = 0;
  graphic->field_0x735d = 0;
  graphic->field_0x735e = 0;
  GXCopyDisp(*(undefined4 *)&graphic->field_0x71e4,1);
  *(char **)&graphic->field_0x7368 = s_graphic_cpp_801d6348;
  *(undefined4 *)&graphic->field_0x736c = 0xbe;
  *(undefined4 *)&graphic->field_0x7364 = 1;
  GXSetDrawDone();
  GXWaitDrawDone();
  *(undefined4 *)&graphic->field_0x7364 = 0;
  *(int *)&graphic->field_0x7370 = *(int *)&graphic->field_0x7370 + 1;
  VIFlush();
  return;
}

