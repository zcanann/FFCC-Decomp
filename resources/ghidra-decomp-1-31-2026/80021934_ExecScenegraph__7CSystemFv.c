// Function: ExecScenegraph__7CSystemFv
// Entry: 80021934
// Size: 1480 bytes

/* WARNING: Removing unreachable block (ram,0x80021ee0) */
/* WARNING: Removing unreachable block (ram,0x80021944) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ExecScenegraph__7CSystemFv(CSystem *system)

{
  bool bVar1;
  ushort uVar3;
  uint uVar2;
  ushort uVar4;
  ushort uVar7;
  int iVar5;
  uint uVar6;
  uint uVar8;
  COrder *pCVar9;
  uint uVar10;
  double dVar11;
  undefined auStack_78 [48];
  
  (system->m_stopwatch).hits = 0;
  do {
    if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != Game.game.m_gameWork.m_gamePaused)
    {
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_system_cpp_801d6f20,0x219);
      Game.game.m_gameWork.m_gamePaused = Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag;
      if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == '\x01') {
        PauseAllSe__6CSoundFi(&Sound,1);
        BackAllFilesToQueue__5CFileFPQ25CFile7CHandle(&File,0);
      }
      else {
        PauseAllSe__6CSoundFi(&Sound,0);
      }
    }
    Frame__4CPadFv(&Pad);
    Frame__5CFileFv(&File);
    Frame__7CMemoryFv(&Memory);
    if (Pad._452_4_ == 0) {
      uVar3 = *(ushort *)
               (&Pad.field_0x36 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54
               );
      uVar7 = *(ushort *)
               (&Pad.field_0x34 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54
               );
    }
    else {
      uVar3 = 0;
      uVar7 = 0;
    }
    if ((uVar3 & 0xc) != 0) {
      if ((uVar3 & 8) == 0) {
        if ((uVar3 & 4) != 0) {
          iVar5 = system->m_scenegraphStepMode;
          if (iVar5 == 2) {
            system->m_scenegraphStepMode = 3;
          }
          else if (iVar5 == 3) {
            system->m_scenegraphStepMode = 4;
          }
          else if (iVar5 == 4) {
            system->m_scenegraphStepMode = 5;
          }
          else {
            system->m_scenegraphStepMode = 2;
          }
        }
      }
      else {
        uVar2 = countLeadingZeros(system->m_scenegraphStepMode);
        system->m_scenegraphStepMode = uVar2 >> 5;
      }
    }
    if (((MiniGamePcs._25732_4_ & 0x40) != 0) && (Game.game.m_gameWork.m_gamePaused == '\0')) {
      uVar2 = 0;
      do {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || ((uVar2 == 0 && (Pad._448_4_ != -1)))) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          uVar3 = *(ushort *)
                   (&Pad.field_0xa +
                   (uVar2 & ~((int)~(Pad._448_4_ - uVar2 | uVar2 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        bVar1 = false;
        if ((Pad._452_4_ != 0) || ((uVar2 == 0 && (Pad._448_4_ != -1)))) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar4 = 0;
        }
        else {
          uVar4 = *(ushort *)
                   (&Pad.field_0x8 +
                   (uVar2 & ~((int)~(Pad._448_4_ - uVar2 | uVar2 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        if (((uVar4 | uVar3) & 0x1000) != 0) {
          if (System.m_scenegraphStepMode == 2) {
            PauseAllSe__6CSoundFi(&Sound,0);
            System.m_scenegraphStepMode = 0;
            ClrShopMode__8GbaQueueFv(&GbaQue);
            SetPauseMode__8GbaQueueFi(&GbaQue,0);
          }
          else if ((CFlat._4768_4_ & 0x10) != 0) {
            PauseAllSe__6CSoundFi(&Sound,1);
            System.m_scenegraphStepMode = 2;
            SetPauseMode__8GbaQueueFi(&GbaQue,1);
          }
        }
        uVar2 = uVar2 + 1;
      } while ((int)uVar2 < 4);
    }
    iVar5 = system->m_scenegraphStepMode;
    if (iVar5 == 1) {
      uVar2 = countLeadingZeros(system->m_frameCounter & 3);
      uVar2 = uVar2 >> 5 & 0xff;
    }
    else {
      uVar2 = 1;
    }
    uVar10 = 0;
    if (iVar5 == 4) {
      uVar10 = -(system->m_frameCounter & 3) >> 0x1f;
    }
    else if (iVar5 < 4) {
      if (iVar5 == 2) {
        uVar10 = 1;
      }
      else if (1 < iVar5) {
        uVar10 = -(system->m_frameCounter & 7) >> 0x1f;
      }
    }
    else if (iVar5 < 6) {
      uVar10 = system->m_frameCounter & 1;
    }
    DumpMapFile__7CSystemFPv((CSystem *)auStack_78);
    iVar5 = 0;
    for (pCVar9 = *(COrder **)((int)&(system->m_stopwatch).max + 4);
        pCVar9 != (COrder *)&(system->m_stopwatch).total; pCVar9 = pCVar9->mNext) {
      system->m_currentOrder = pCVar9;
      system->m_currentOrderIndex = iVar5;
      uVar6 = *(uint *)((int)pCVar9->mEntry + 0x10);
      if ((uVar6 & 1) == 0) {
        uVar8 = uVar10;
        if (((uVar10 != 0) && (uVar2 != 0)) && ((uVar6 & 4) != 0)) {
          uVar8 = 0;
        }
      }
      else {
        uVar8 = 0;
        if (uVar2 == 0) {
          uVar8 = 1;
        }
      }
      if (Game.game.m_gameWork.m_gamePaused == '\0') {
        if ((uVar6 & 0x10) != 0) {
          uVar8 = 1;
        }
      }
      else {
        if ((uVar6 & 8) == 0) {
          uVar8 = 1;
        }
        if ((uVar6 & 0x10) != 0) {
          uVar8 = 0;
        }
      }
      if (uVar8 == 0) {
        Reset__10CStopWatchFv(auStack_78);
        Start__10CStopWatchFv(auStack_78);
        if ((*(uint *)((int)pCVar9->mEntry + 0x10) & 1) != 0) {
          SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xffffffff);
        }
        __ptmf_scall(pCVar9->mOwner);
        Stop__10CStopWatchFv(auStack_78);
        dVar11 = (double)Get__10CStopWatchFv(auStack_78);
        pCVar9->mLastTime = (float)dVar11;
        Start__10CStopWatchFv(auStack_78);
        if ((uVar7 & 1) != 0) {
          _WaitDrawDone__8CGraphicFPci(&Graphic,s_system_cpp_801d6f20,0x2ca);
          GXReadGP0Metric();
          GXReadGP1Metric();
        }
        Stop__10CStopWatchFv(auStack_78);
        if ((uVar7 & 1) != 0) {
          dVar11 = (double)Get__10CStopWatchFv(auStack_78);
          pCVar9->mLastTime = (float)dVar11;
        }
        Get__10CStopWatchFv(auStack_78);
      }
      else {
        pCVar9->mLastTime = FLOAT_8032f870;
      }
      iVar5 = iVar5 + 1;
    }
    system->m_currentOrder = (COrder *)0x0;
    system->m_frameCounter = system->m_frameCounter + 1;
    __ct__10CStopWatchFPc(auStack_78,0xffffffff);
  } while ((system->m_stopwatch).hits == 0);
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_system_cpp_801d6f20,0x2f6);
  return;
}

