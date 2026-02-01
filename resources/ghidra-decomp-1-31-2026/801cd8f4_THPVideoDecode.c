// Function: THPVideoDecode
// Entry: 801cd8f4
// Size: 580 bytes

char THPVideoDecode(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  char *pcVar4;
  byte *pbVar5;
  char cVar6;
  int *piVar7;
  
  if (param_1 == 0) {
    cVar6 = '\x19';
  }
  else if (((param_2 == 0) || (param_3 == 0)) || (param_4 == 0)) {
    cVar6 = '\x1b';
  }
  else if (param_5 == 0) {
    cVar6 = '\x1a';
  }
  else {
    uVar3 = PPCMfhid2();
    if ((uVar3 & 0x10000000) == 0) {
      cVar6 = '\x1c';
    }
    else if (DAT_8032f5f4 == 0) {
      cVar6 = '\x1d';
    }
    else {
      DAT_8032f5f0 = param_5 + 0x1fU & 0xffffffe0;
      DAT_8032f5ec = DAT_8032f5f0 + 0x6bc;
      DCZeroRange(DAT_8032f5f0,0x6bc);
      *(undefined4 *)(DAT_8032f5f0 + 0x6a4) = 0x21;
      bVar2 = false;
      *(undefined2 *)(DAT_8032f5f0 + 0x698) = 0;
      *(int *)(DAT_8032f5f0 + 0x69c) = param_1;
      do {
        pcVar4 = *(char **)(DAT_8032f5f0 + 0x69c);
        *(char **)(DAT_8032f5f0 + 0x69c) = pcVar4 + 1;
        if (*pcVar4 != -1) {
          return '\x03';
        }
        while( true ) {
          piVar7 = (int *)(DAT_8032f5f0 + 0x69c);
          pbVar5 = *(byte **)(DAT_8032f5f0 + 0x69c);
          if (*pbVar5 != 0xff) break;
          *piVar7 = *piVar7 + 1;
        }
        *piVar7 = (int)(pbVar5 + 1);
        bVar1 = *pbVar5;
        if (bVar1 < 0xd8) {
          if (bVar1 == 0xc4) {
            cVar6 = __THPReadHuffmanTableSpecification();
          }
          else {
            if (bVar1 != 0xc0) {
              return '\v';
            }
            cVar6 = __THPReadFrameHeader();
          }
joined_r0x801cda20:
          if (cVar6 != '\0') {
            return cVar6;
          }
        }
        else if ((bVar1 < 0xd8) || (0xdf < bVar1)) {
          if (bVar1 >= 0xe0) {
            if (((bVar1 < 0xe0) || (0xef < bVar1)) && (bVar1 != 0xfe)) {
              return '\v';
            }
            *(uint *)(DAT_8032f5f0 + 0x69c) =
                 (int)*(ushort **)(DAT_8032f5f0 + 0x69c) + (uint)**(ushort **)(DAT_8032f5f0 + 0x69c)
            ;
          }
        }
        else if (bVar1 == 0xdd) {
          __THPRestartDefinition();
        }
        else {
          if (bVar1 == 0xdb) {
            cVar6 = __THPReadQuantizationTable();
            goto joined_r0x801cda20;
          }
          if (bVar1 == 0xda) {
            cVar6 = __THPReadScaneHeader();
            if (cVar6 != '\0') {
              return cVar6;
            }
            bVar2 = true;
          }
          else if (bVar1 != 0xd8) {
            return '\v';
          }
        }
      } while (!bVar2);
      __THPSetupBuffers();
      __THPDecompressYUV(param_2,param_3,param_4);
      cVar6 = '\0';
    }
  }
  return cVar6;
}

