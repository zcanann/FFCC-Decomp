// Function: StaticFrame__10CGCharaObjFv
// Entry: 8010c0c4
// Size: 228 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void StaticFrame__10CGCharaObjFv(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = -0x7fde1140;
  iVar4 = 4;
  do {
    iVar2 = *(int *)(iVar3 + 0xc5b0);
    if (iVar2 != 0) {
      if (((int)((uint)*(byte *)(iVar2 + 0x9a) << 0x18) < 0) &&
         ((int)((uint)*(byte *)(iVar2 + 0x9b) << 0x18) < 0)) {
        uVar1 = *(ushort *)(*(int *)(iVar2 + 0x58) + 0x1c);
        if (uVar1 != 0) {
          if (uVar1 <= *(ushort *)(*(int *)(iVar2 + 0x58) + 0x1a) >> 2) {
            iVar3 = (int)System.m_frameCounter / 0x1e + ((int)System.m_frameCounter >> 0x1f);
            if (System.m_frameCounter == (iVar3 - (iVar3 >> 0x1f)) * 0x1e) {
              PlaySe__6CSoundFiiii(&Sound,0x53,0x40,0x7f,0);
            }
            break;
          }
        }
      }
    }
    iVar3 = iVar3 + 4;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  combi2__10CGCharaObjFv();
  return;
}

