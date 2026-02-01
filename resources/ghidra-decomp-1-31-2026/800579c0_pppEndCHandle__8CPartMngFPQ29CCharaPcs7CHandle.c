// Function: pppEndCHandle__8CPartMngFPQ29CCharaPcs7CHandle
// Entry: 800579c0
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEndCHandle__8CPartMngFPQ29CCharaPcs7CHandle(CPartMng *partMng,CCharaPcsCHandle *handle)

{
  uint8_t uVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    if (((partMng->m_pppMngStArr[0].m_baseTime != -0x1000) &&
        (((uVar1 = partMng->m_pppMngStArr[0].field38_0xe7, uVar1 == '\x03' ||
          ((byte)(uVar1 - 5) < 3)) || (uVar1 == '\b')))) &&
       ((fVar2 = partMng->m_pppMngStArr[0].m_velocity.x, fVar2 != 0.0 &&
        (*(CCharaPcsCHandle **)((int)fVar2 + 0xf8) == handle)))) {
      partMng->m_pppMngStArr[0].m_stopRequested = '\x01';
      pppStopSe__FP9_pppMngStP7PPPSEST
                (partMng->m_pppMngStArr,&partMng->m_pppMngStArr[0].m_soundEffectData);
    }
    iVar3 = iVar3 + 1;
    partMng = (CPartMng *)partMng->m_rgbaA;
  } while (iVar3 < 0x180);
  return;
}

