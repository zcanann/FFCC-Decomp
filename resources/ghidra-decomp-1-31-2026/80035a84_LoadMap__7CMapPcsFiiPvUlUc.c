// Function: LoadMap__7CMapPcsFiiPvUlUc
// Entry: 80035a84
// Size: 844 bytes

void LoadMap__7CMapPcsFiiPvUlUc
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
               char param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  Vec local_128;
  undefined auStack_11c [260];
  
  uVar2 = DAT_8032ecc4;
  uVar1 = DAT_8032ecc0;
  DAT_8032ecc0 = param_2;
  DAT_8032ecc4 = param_3;
  sprintf(auStack_11c,s_dvd_map_stg_03d_map_03d_801d7844,param_2,param_3);
  if (param_6 != '\x02') {
    DestroyMap__7CMapMngFv(&MapMng);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs,1);
    SetDrawRangeOctTree__7CMapMngFf(DrawRangeDefault,&MapMng);
    SetDrawRangeMapObj__7CMapMngFf(DrawRangeDefault,&MapMng);
  }
  MapMng._141728_4_ = 0;
  MapMng._141732_4_ = 0;
  if (param_5 == 0) {
    MapMng._141736_4_ = 0;
  }
  else if (param_6 == '\x01') {
    MapMng._141736_4_ = 2;
  }
  else if (param_6 == '\x02') {
    MapMng._141736_4_ = 3;
    MapMng._141868_4_ = 0;
    MapMng._141872_4_ = 0;
    MapMng._141876_4_ = 0;
    MapMng._141880_4_ = 0;
    MapMng._141884_4_ = 0;
    MapMng._141888_4_ = 0;
    MapMng._141892_4_ = 0;
    MapMng._141896_4_ = 0;
    MapMng._141900_4_ = 0;
    MapMng._141904_4_ = 0;
    MapMng._141908_4_ = 0;
    MapMng._141912_4_ = 0;
    MapMng._141916_4_ = 0;
    MapMng._141920_4_ = 0;
    MapMng._141924_4_ = 0;
    MapMng._141928_4_ = 0;
  }
  else {
    MapMng._141736_4_ = 1;
  }
  MapMng._141716_4_ = param_4;
  MapMng._141720_4_ = param_4;
  MapMng._141724_4_ = param_5;
  ReadMtx__7CMapMngFPc(&MapMng,auStack_11c);
  ReadMpl__7CMapMngFPc(&MapMng,auStack_11c);
  ReadOtm__7CMapMngFPc(&MapMng,auStack_11c);
  ReadMid__7CMapMngFPc(&MapMng,auStack_11c);
  if (1 < (byte)(param_6 - 1U)) {
    if ((*(int *)(param_1 + 0x17c) != 0) && (iVar3 = strcmp(&DAT_801e8eec,auStack_11c), iVar3 != 0))
    {
      strcpy(&DAT_801e8eec,auStack_11c);
      iVar3 = GetDebugPlaySta__7CMapMngFiP3Vec(&MapMng,0,&local_128);
      if (iVar3 == 0) {
        if (MapMng.octTreeArr[0].rootNode == (COctNode *)0x0) {
          local_128.x = MapMng.mapObjArr[1].drawRange;
          local_128.y = (float)MapMng.mapObjArr[1]._104_4_;
          local_128.z = (float)MapMng.mapObjArr[1]._108_4_;
        }
        else {
          local_128.x = (((MapMng.octTreeArr[0].rootNode)->boundsMin).x +
                        ((MapMng.octTreeArr[0].rootNode)->boundsMax).x) * FLOAT_8032fa0c;
          local_128.y = (((MapMng.octTreeArr[0].rootNode)->boundsMin).y +
                        ((MapMng.octTreeArr[0].rootNode)->boundsMax).y) * FLOAT_8032fa0c;
          local_128.z = (((MapMng.octTreeArr[0].rootNode)->boundsMin).z +
                        ((MapMng.octTreeArr[0].rootNode)->boundsMax).z) * FLOAT_8032fa0c;
        }
      }
      CameraPcs._228_4_ = local_128.y + FLOAT_8032fa10;
      CameraPcs._224_4_ = local_128.x;
      CameraPcs._232_4_ = local_128.z;
      local_128.y = (float)CameraPcs._228_4_;
    }
    if (2 < (uint)System.m_execParam) {
      uVar4 = GetHeapUnuse__Q27CMemory6CStageFv((CStage *)MapMng._0_4_);
      Printf__7CSystemFPce
                (&System,s__________________________________801d7734,auStack_11c,
                 (int)MapMng.field10_0xc,(int)MapMng.field8_0x8,
                 ((int)uVar4 >> 10) + (uint)((int)uVar4 < 0 && (uVar4 & 0x3ff) != 0));
    }
    iVar3 = GetSize__29CPtrArray<P15CMapLightHolder>Fv(MapMng.mapLightHolderArr + 1);
    if (iVar3 != 0) {
      uVar5 = __vc__29CPtrArray<P15CMapLightHolder>FUl(0x80266bd0,0);
      GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec(uVar5,0x802680f0,0);
    }
  }
  if (param_6 == '\x02') {
    DAT_8032ecc0 = uVar1;
    DAT_8032ecc4 = uVar2;
  }
  return;
}

