// Function: pppLoadPan__8CPartMngFPCc
// Entry: 80058e58
// Size: 844 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 pppLoadPan__8CPartMngFPCc(CPartMng *partMng,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *baseAddress;
  int iVar3;
  void *pvVar4;
  pppShapeSt *pppShapeSt;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined auStack_1c8 [4];
  undefined local_1c4 [32];
  CChunkFile aCStack_1a4 [3];
  CChunkFile aCStack_e8 [4];
  
  sprintf(StrTmp,s__s_pan_8032fe28,param_2);
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s_ReadPan_fn__s_801d82c0,StrTmp);
  }
  iVar1 = pppPartInit__8CPartMngFv(partMng,StrTmp,auStack_1c8,0,0);
  if (iVar1 == 0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CAN_NOT_READ__s________801d82a8,StrTmp);
    }
    uVar2 = 0;
  }
  else {
    if (*(int *)partMng->m_usbEdit == 0) {
      baseAddress = (void *)__nw__FUlPQ27CMemory6CStagePci
                                      (0x2c00,PartPcs.m_usbStreamData.m_stageLoad,
                                       s_partMng_cpp_801d8230,0xd0b);
      if (baseAddress != (void *)0x0) {
        __construct_array(baseAddress,__ct__10pppShapeStFv,__dt__10pppShapeStFv,0x2c,0x100);
        iVar6 = 8;
        pvVar4 = baseAddress;
        do {
          *(undefined *)((int)pvVar4 + 0x2a) = 0;
          *(undefined *)((int)pvVar4 + 0x56) = 0;
          *(undefined *)((int)pvVar4 + 0x82) = 0;
          *(undefined *)((int)pvVar4 + 0xae) = 0;
          *(undefined *)((int)pvVar4 + 0xda) = 0;
          *(undefined *)((int)pvVar4 + 0x106) = 0;
          *(undefined *)((int)pvVar4 + 0x132) = 0;
          *(undefined *)((int)pvVar4 + 0x15e) = 0;
          *(undefined *)((int)pvVar4 + 0x18a) = 0;
          *(undefined *)((int)pvVar4 + 0x1b6) = 0;
          *(undefined *)((int)pvVar4 + 0x1e2) = 0;
          *(undefined *)((int)pvVar4 + 0x20e) = 0;
          *(undefined *)((int)pvVar4 + 0x23a) = 0;
          *(undefined *)((int)pvVar4 + 0x266) = 0;
          *(undefined *)((int)pvVar4 + 0x292) = 0;
          *(undefined *)((int)pvVar4 + 0x2be) = 0;
          *(undefined *)((int)pvVar4 + 0x2ea) = 0;
          *(undefined *)((int)pvVar4 + 0x316) = 0;
          *(undefined *)((int)pvVar4 + 0x342) = 0;
          *(undefined *)((int)pvVar4 + 0x36e) = 0;
          *(undefined *)((int)pvVar4 + 0x39a) = 0;
          *(undefined *)((int)pvVar4 + 0x3c6) = 0;
          *(undefined *)((int)pvVar4 + 0x3f2) = 0;
          *(undefined *)((int)pvVar4 + 0x41e) = 0;
          *(undefined *)((int)pvVar4 + 0x44a) = 0;
          *(undefined *)((int)pvVar4 + 0x476) = 0;
          *(undefined *)((int)pvVar4 + 0x4a2) = 0;
          *(undefined *)((int)pvVar4 + 0x4ce) = 0;
          *(undefined *)((int)pvVar4 + 0x4fa) = 0;
          *(undefined *)((int)pvVar4 + 0x526) = 0;
          *(undefined *)((int)pvVar4 + 0x552) = 0;
          *(undefined *)((int)pvVar4 + 0x57e) = 0;
          pvVar4 = (void *)((int)pvVar4 + 0x580);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      *(void **)partMng->m_usbEdit = baseAddress;
    }
    __ct__10CChunkFileFv(aCStack_e8);
    SetBuf__10CChunkFileFPv(aCStack_e8,iVar1);
    while (iVar1 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_e8,(CChunkFile *)(local_1c4 + 0x10)), iVar1 != 0) {
      PushChunk__10CChunkFileFv(aCStack_e8);
      if ((uint8_t *)local_1c4._16_4_ == (uint8_t *)0x53534554) {
        iVar1 = *(int *)partMng->m_usbEdit;
        pppShapeSt = (pppShapeSt *)0x0;
        while (iVar6 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_e8,(CChunkFile *)local_1c4), iVar6 != 0) {
          if (local_1c4._0_4_ == 0x5348504d) {
            if (pppShapeSt != (pppShapeSt *)0x0) {
              __ct__10CChunkFileFv(aCStack_1a4);
              uVar2 = GetAddress__10CChunkFileFv(aCStack_e8);
              SetBuf__10CChunkFileFPv(aCStack_1a4,uVar2);
              pppReadShp__8CPartMngFR10CChunkFileP10pppShapeSt(&PartMng,aCStack_1a4,pppShapeSt);
              pppShapeSt->m_refCount = pppShapeSt->m_refCount + 1;
              pppShapeSt = (pppShapeSt *)0x0;
            }
          }
          else if (((int)local_1c4._0_4_ < 0x5348504d) && (local_1c4._0_4_ == 0x4e414d45)) {
            uVar2 = GetString__10CChunkFileFv(aCStack_e8);
            uVar5 = 0;
            iVar6 = iVar1;
            do {
              if ((*(char *)(iVar6 + 0x2a) != '\0') && (iVar3 = strcmp(iVar6 + 8,uVar2), iVar3 == 0)
                 ) goto LAB_800590ac;
              uVar5 = uVar5 + 1;
              iVar6 = iVar6 + 0x2c;
            } while (uVar5 < 0x100);
            iVar6 = 0;
LAB_800590ac:
            if (iVar6 == 0) {
              iVar3 = 0;
              iVar7 = 0x100;
              iVar6 = iVar1;
              do {
                if (*(char *)(iVar6 + 0x2a) == '\0') {
                  pppShapeSt = (pppShapeSt *)(iVar1 + iVar3 * 0x2c);
                  goto LAB_800590f4;
                }
                iVar6 = iVar6 + 0x2c;
                iVar3 = iVar3 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              pppShapeSt = (pppShapeSt *)0x0;
LAB_800590f4:
              pppShapeSt->m_refCount = 0;
              pppShapeSt->m_inUse = '\x01';
              strcpy(pppShapeSt->m_name,uVar2);
            }
            else {
              pppShapeSt = (pppShapeSt *)0x0;
            }
          }
        }
      }
      PopChunk__10CChunkFileFv(aCStack_e8);
    }
    uVar2 = 1;
  }
  return uVar2;
}

