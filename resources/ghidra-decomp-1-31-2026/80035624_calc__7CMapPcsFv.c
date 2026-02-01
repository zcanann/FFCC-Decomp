// Function: calc__7CMapPcsFv
// Entry: 80035624
// Size: 796 bytes

void calc__7CMapPcsFv(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  Vec local_88;
  Mat4x4 MStack_7c;
  Mtx MStack_3c;
  
  _MapFileRead__7CMapMngFPcRUl(&MapMng);
  MapMng._141548_4_ = CameraPcs._224_4_;
  MapMng._141552_4_ = CameraPcs._228_4_;
  MapMng._141556_4_ = CameraPcs._232_4_;
  if (*(char *)(param_1 + 0x184) == '\0') {
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_3c);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_7c);
  }
  else {
    memcpy(&MStack_3c,param_1 + 4,0x30);
    memcpy(&MStack_7c,param_1 + 0x34,0x40);
  }
  SetViewMtx__7CMapMngFPA4_fPA4_f(&MapMng,&MStack_3c,&MStack_7c);
  if (*(int *)(param_1 + 0x174) == 0) {
    *(undefined4 *)(param_1 + 0x178) = 0;
    Calc__7CMapMngFv(&MapMng);
  }
  else {
    DestroyMap__7CMapMngFv(&MapMng);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs,1);
    SetDrawRangeOctTree__7CMapMngFf(DrawRangeDefault,&MapMng);
    SetDrawRangeMapObj__7CMapMngFf(DrawRangeDefault,&MapMng);
    MapMng._141716_4_ = 0;
    MapMng._141720_4_ = 0;
    MapMng._141724_4_ = 0;
    MapMng._141728_4_ = 0;
    MapMng._141732_4_ = 0;
    MapMng._141736_4_ = 0;
    ReadMtx__7CMapMngFPc(&MapMng,param_1 + 0x74);
    ReadMpl__7CMapMngFPc(&MapMng,param_1 + 0x74);
    ReadOtm__7CMapMngFPc(&MapMng,param_1 + 0x74);
    ReadMid__7CMapMngFPc(&MapMng,param_1 + 0x74);
    if ((*(int *)(param_1 + 0x17c) != 0) &&
       (iVar1 = strcmp(&DAT_801e8eec,param_1 + 0x74), iVar1 != 0)) {
      strcpy(&DAT_801e8eec,param_1 + 0x74);
      iVar1 = GetDebugPlaySta__7CMapMngFiP3Vec(&MapMng,0,&local_88);
      if (iVar1 == 0) {
        if (MapMng.octTreeArr[0].rootNode == (COctNode *)0x0) {
          local_88.x = MapMng.mapObjArr[1].drawRange;
          local_88.y = (float)MapMng.mapObjArr[1]._104_4_;
          local_88.z = (float)MapMng.mapObjArr[1]._108_4_;
        }
        else {
          local_88.x = (((MapMng.octTreeArr[0].rootNode)->boundsMin).x +
                       ((MapMng.octTreeArr[0].rootNode)->boundsMax).x) * FLOAT_8032fa0c;
          local_88.y = (((MapMng.octTreeArr[0].rootNode)->boundsMin).y +
                       ((MapMng.octTreeArr[0].rootNode)->boundsMax).y) * FLOAT_8032fa0c;
          local_88.z = (((MapMng.octTreeArr[0].rootNode)->boundsMin).z +
                       ((MapMng.octTreeArr[0].rootNode)->boundsMax).z) * FLOAT_8032fa0c;
        }
      }
      CameraPcs._228_4_ = local_88.y + FLOAT_8032fa10;
      CameraPcs._224_4_ = local_88.x;
      CameraPcs._232_4_ = local_88.z;
      local_88.y = (float)CameraPcs._228_4_;
    }
    if (2 < (uint)System.m_execParam) {
      uVar2 = GetHeapUnuse__Q27CMemory6CStageFv((CStage *)MapMng._0_4_);
      Printf__7CSystemFPce
                (&System,s__________________________________801d7734,param_1 + 0x74,
                 (int)MapMng.field10_0xc,(int)MapMng.field8_0x8,
                 ((int)uVar2 >> 10) + (uint)((int)uVar2 < 0 && (uVar2 & 0x3ff) != 0));
    }
    iVar1 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(MapMng.mapLightHolderArr + 1);
    if (iVar1 != 0) {
      uVar3 = __vc__29CPtrArray<P15CMapLightHolder>FUl(0x80266bd0,0);
      GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec(uVar3,0x802680f0,0);
    }
    *(undefined4 *)(param_1 + 0x174) = 0;
    *(undefined4 *)(param_1 + 0x178) = 1;
  }
  return;
}

