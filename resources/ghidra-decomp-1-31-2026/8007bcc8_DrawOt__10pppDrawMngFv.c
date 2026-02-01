// Function: DrawOt__10pppDrawMngFv
// Entry: 8007bcc8
// Size: 292 bytes

/* WARNING: Removing unreachable block (ram,0x8007bd18) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawOt__10pppDrawMngFv(pppDrawMng *pppDrawMng)

{
  pppDrawPrimitive *ppVar1;
  uint8_t uVar2;
  pppDrawPrimitive **pppVar3;
  int iVar4;
  
  iVar4 = 0x400;
  pppVar3 = pppDrawMng->m_primitiveRefs + 0x3ff;
  uVar2 = '\x03';
  do {
    for (ppVar1 = *pppVar3; ppVar1 != (pppDrawPrimitive *)0x0; ppVar1 = ppVar1->m_next) {
      if (ppVar1->m_type == '\x01') {
        SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7ffe);
        if (uVar2 != ppVar1->m_type) {
          pppInitDrawEnv__FUc(0);
          InitEnv__9CCharaPcsFi(&CharaPcs,4);
        }
        Draw__Q29CCharaPcs7CHandleFi(ppVar1->m_handle,4);
        SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
      }
      else if (ppVar1->m_type == '\0') {
        if (uVar2 != '\0') {
          pppInitDrawEnv__FUc(0);
        }
                    /* WARNING: Load size is inaccurate */
        pppEnvStPtr = (_pppEnvSt *)(*ppVar1->m_handle + 4);
        pppMngStPtr = (_pppMngSt *)ppVar1->m_handle;
        pppSetFpMatrix__FP9_pppMngSt((_pppMngSt *)ppVar1->m_handle);
        _pppDrawPart__FP9_pppMngSt(ppVar1->m_handle);
      }
      uVar2 = ppVar1->m_type;
    }
    iVar4 = iVar4 + -1;
    pppVar3 = pppVar3 + -1;
  } while (iVar4 != 0);
  return;
}

