// Function: pppIsDeadCHandle__8CPartMngFPQ29CCharaPcs7CHandle
// Entry: 800578b0
// Size: 272 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppIsDeadCHandle__8CPartMngFPQ29CCharaPcs7CHandle(CPartMng *partMng,CCharaPcsCHandle *handle)

{
  uint8_t uVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = 0x80;
  while (((partMng->m_pppMngStArr[0].m_baseTime == -0x1000 ||
          (((uVar1 = partMng->m_pppMngStArr[0].field38_0xe7, uVar1 != '\x03' &&
            (2 < (byte)(uVar1 - 5))) && (uVar1 != '\b')))) ||
         ((fVar2 = partMng->m_pppMngStArr[0].m_velocity.x, fVar2 == 0.0 ||
          (*(CCharaPcsCHandle **)((int)fVar2 + 0xf8) != handle))))) {
    if ((partMng->m_pppMngStArr[1].m_baseTime != -0x1000) &&
       ((((uVar1 = partMng->m_pppMngStArr[1].field38_0xe7, uVar1 == '\x03' ||
          ((byte)(uVar1 - 5) < 3)) || (uVar1 == '\b')) &&
        ((fVar2 = partMng->m_pppMngStArr[1].m_velocity.x, fVar2 != 0.0 &&
         (*(CCharaPcsCHandle **)((int)fVar2 + 0xf8) == handle)))))) {
      return 0;
    }
    if ((partMng->m_pppMngStArr[2].m_baseTime != -0x1000) &&
       ((((uVar1 = partMng->m_pppMngStArr[2].field38_0xe7, uVar1 == '\x03' ||
          ((byte)(uVar1 - 5) < 3)) || (uVar1 == '\b')) &&
        ((fVar2 = partMng->m_pppMngStArr[2].m_velocity.x, fVar2 != 0.0 &&
         (*(CCharaPcsCHandle **)((int)fVar2 + 0xf8) == handle)))))) {
      return 0;
    }
    partMng = (CPartMng *)(partMng->m_streamTextRaw + 0xc);
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return 1;
    }
  }
  return 0;
}

