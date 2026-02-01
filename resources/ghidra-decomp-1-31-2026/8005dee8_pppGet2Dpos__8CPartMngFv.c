// Function: pppGet2Dpos__8CPartMngFv
// Entry: 8005dee8
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppGet2Dpos__8CPartMngFv(CPartMng *partMng)

{
  uint uVar1;
  uint uVar2;
  int local_78;
  Vec local_74;
  Vec VStack_68;
  Mtx MStack_58;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  if (partMng->m_requestFlag != 0) {
    uVar2 = *(int *)((partMng->m_cursorPacket).m_cursorPacketRaw + 0x10) + 0x140;
    uVar1 = *(int *)((partMng->m_cursorPacket).m_cursorPacketRaw + 0x14) + 0xe0;
    if ((((-1 < (int)uVar2) && ((int)uVar2 < 0x27e)) && (-1 < (int)uVar1)) && ((int)uVar1 < 0x1be))
    {
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x2a2);
      GXPeekZ(uVar2 & 0xffff,uVar1 & 0xffff,&local_78);
      uStack_24 = *(uint *)((partMng->m_cursorPacket).m_cursorPacketRaw + 0x14) ^ 0x80000000;
      local_28 = 0x43300000;
      uStack_14 = *(uint *)((partMng->m_cursorPacket).m_cursorPacketRaw + 0x10) ^ 0x80000000;
      uStack_1c = local_78 - 0xffffffU ^ 0x80000000;
      local_20 = 0x43300000;
      local_18 = 0x43300000;
      local_74.z = ppvScreenMatrix0.value[2][3] /
                   ((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8032fe80) /
                    FLOAT_8032fe78 + ppvScreenMatrix0.value[2][2]);
      local_74.x = local_74.z *
                   (((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8032fe80) /
                    FLOAT_8032fe7c) / ppvScreenMatrix0.value[0][0]);
      local_74.y = local_74.z *
                   ((-(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8032fe80) /
                    FLOAT_8032fe74) / ppvScreenMatrix0.value[1][1]);
      local_74.z = -local_74.z;
      PSMTXInverse(&ppvCameraMatrix0,&MStack_58);
      PSMTXMultVec(&MStack_58,&local_74,&VStack_68);
      SendDataCode__7CUSBPcsFiPvii(&USBPcs,0x60,&VStack_68,1,0xc);
    }
    partMng->m_requestFlag = 0;
  }
  return;
}

