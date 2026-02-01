// Function: ThreadMain__6JoyBusFPv
// Entry: 800ae3dc
// Size: 12208 bytes

/* WARNING: Removing unreachable block (ram,0x800ae964) */
/* WARNING: Removing unreachable block (ram,0x800ae78c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ThreadMain__6JoyBusFPv(JoyBus *joyBus,ThreadParam *threadParam)

{
  uint32_t *puVar1;
  uint uVar2;
  uint32_t uVar3;
  uint uVar4;
  uint32_t uVar5;
  int iVar6;
  JoyBus *pJVar7;
  char cVar10;
  int iVar8;
  undefined2 uVar9;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined2 local_38 [2];
  undefined4 local_34;
  uint32_t local_30;
  byte local_2c [4];
  
  uVar5 = GBAReset(threadParam->m_portIndex,&threadParam->m_unk3);
  threadParam->m_gbaStatus = uVar5;
  ThreadSleep__6JoyBusFx(joyBus,0x10624dd3,0,(DAT_800000f8 / 4000) * 0xf);
LAB_800ae448:
  uVar2 = (uint)threadParam->m_state;
  if (uVar2 == 5) {
LAB_800ae4a8:
    uVar2 = (DAT_800000f8 / 4000) * 500;
  }
  else {
    if (uVar2 < 5) {
      if (uVar2 != 3) {
        if (2 < uVar2) {
          uVar2 = (DAT_800000f8 / 4000) * 500;
          goto LAB_800ae528;
        }
        if (1 < uVar2) {
          uVar2 = (DAT_800000f8 / 4000) * 2000;
          goto LAB_800ae528;
        }
      }
    }
    else if (uVar2 == 900) goto LAB_800ae4a8;
    uVar2 = (DAT_800000f8 / 4000) * 1000;
  }
LAB_800ae528:
  uVar11 = OSGetTime();
LAB_800ae564:
  iVar6 = IsDiskError__5CFileFv(&File);
  if (iVar6 == 0) {
    if (threadParam != joyBus->m_threadParams + threadParam->m_portIndex) {
      uVar5 = 0;
      iVar6 = 4;
      pJVar7 = joyBus;
      do {
        if (threadParam == pJVar7->m_threadParams) {
          memset(threadParam,0,0x3c);
          threadParam->m_portIndex = uVar5;
          break;
        }
        pJVar7 = (JoyBus *)(pJVar7->m_pathBuf + 0x3c);
        uVar5 = uVar5 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    if (joyBus->m_threadInitFlag != '\0') {
      joyBus->m_threadRunningMask =
           joyBus->m_threadRunningMask & ~(byte)(1 << threadParam->m_portIndex);
      joyBus->m_stageFlags[threadParam->m_portIndex] = 0;
      OSExitThread(&DAT_8032edb8);
    }
    cVar10 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar10 != '\0') && (threadParam->m_portIndex != 1)) {
      threadParam->m_state = '\0';
      uVar11 = OSGetTime();
      goto LAB_800ae538;
    }
    uVar5 = SIProbe(threadParam->m_portIndex);
    BlockSem__6JoyBusFi(joyBus,threadParam->m_portIndex);
    if ((((uVar5 == 0x40000) || (uVar5 == 0x9000000)) || (uVar5 == 0x8b100000)) ||
       (uVar5 == 0x88000000)) {
      threadParam->m_padType = uVar5;
    }
    else if (uVar5 != 0x80) {
      threadParam->m_padType = 0x40;
      threadParam->m_sentStartFlag = '\0';
    }
    ReleaseSem__6JoyBusFi(joyBus,threadParam->m_portIndex);
    if (joyBus->m_nextModeTypeArr[threadParam->m_portIndex] !=
        joyBus->m_modeXArr[threadParam->m_portIndex]) {
      threadParam->m_state = '\x14';
      threadParam->m_subState = '\0';
      joyBus->m_modeXArr[threadParam->m_portIndex] =
           joyBus->m_nextModeTypeArr[threadParam->m_portIndex];
    }
    cVar10 = IsSingleMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
    if ((cVar10 == '\0') || (threadParam->m_portIndex != 1)) {
      uVar3 = threadParam->m_portIndex;
    }
    else {
      uVar3 = 0;
    }
    puVar1 = Game.game.m_scriptFoodBase + uVar3;
    uVar3 = *puVar1;
    if ((uVar3 == 0) && (uVar5 == 0x40000)) {
      uVar4 = (uint)threadParam->m_state;
      if (uVar4 < 0x17) {
        if (uVar4 != 6) {
          if (uVar4 < 6) {
            if (4 < uVar4) goto LAB_800ae7e4;
          }
          else if (uVar4 < 0x14) goto LAB_800ae7e4;
        }
      }
      else if (uVar4 < 900) {
        if ((0x20 < uVar4) || (uVar4 < 0x1d)) {
LAB_800ae7e4:
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if ((iVar6 < 0) ||
             ((joyBus->m_ctrlModeArr[threadParam->m_portIndex] != '\0' &&
              (iVar6 = SendCtrlMode__6JoyBusFP11ThreadParami(joyBus,threadParam,0), iVar6 < 0))))
          goto LAB_800ae538;
          goto LAB_800ae448;
        }
        iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
        if (iVar6 < 0) goto LAB_800ae538;
        threadParam->m_state = ';';
      }
      else if (0x386 < uVar4) goto LAB_800ae7e4;
    }
    else if ((uVar3 == 0) || (uVar5 != 0x40000)) {
      joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\0';
      if ((*puVar1 == 0) || (threadParam->m_state != '\x02')) {
        threadParam->m_state = '\0';
      }
      else {
        threadParam->m_state = '\x01';
      }
      ThreadSleep__6JoyBusFx(joyBus,0x10624dd3,0,(DAT_800000f8 / 4000) * 0xf);
      goto LAB_800ae448;
    }
    uVar12 = OSGetTime();
    if (0x80000000 <
        (uint)(uVar2 < (uint)uVar12 - (uint)uVar11) +
        ((int)((ulonglong)uVar12 >> 0x20) -
         ((uint)((uint)uVar12 < (uint)uVar11) + (int)((ulonglong)uVar11 >> 0x20)) ^ 0x80000000)) {
      threadParam->m_prevState = threadParam->m_state;
      if (threadParam->m_gbaStatus == 3) {
        threadParam->m_state = 0x86;
      }
      else {
        threadParam->m_gbaStatus = 1;
        threadParam->m_state = 0x85;
      }
      goto LAB_800ae448;
    }
    if (threadParam->m_skipProcessingFlag != '\0') {
      threadParam->m_skipProcessingFlag = '\0';
    }
    uVar4 = (uint)threadParam->m_state;
    if (uVar4 == 0x2f) {
      iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
      if (iVar6 < 0) goto LAB_800ae538;
      if ((threadParam->m_skipProcessingFlag != '\0') ||
         (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
      threadParam->m_subState = '\0';
      iVar6 = SendCompatibility__6JoyBusFP11ThreadParam(joyBus,threadParam);
      if (-1 < iVar6) {
        threadParam->m_state = '0';
        goto LAB_800ae448;
      }
    }
    else if (uVar4 < 0x2f) {
      if (uVar4 == 0x1d) {
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (iVar6 < 0) goto LAB_800ae538;
        if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
        iVar6 = SendMapNo__6JoyBusFP11ThreadParam(joyBus,threadParam);
        if (-1 < iVar6) {
          if (joyBus->m_fileBaseB_dup == 0) {
            ClrStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            threadParam->m_state = 'F';
            goto LAB_800ae448;
          }
          threadParam->m_state = '\x1e';
          local_38[0] = 0xffff;
          uVar9 = Crc16__6JoyBusFiPUcPUs
                            (joyBus,joyBus->m_fileBaseB_dup,joyBus->m_fileBaseB,local_38);
          iVar6 = SendChkCrc__6JoyBusFP11ThreadParamiUsPUi(joyBus,threadParam,1,uVar9,&local_30);
          if (iVar6 == 0) goto LAB_800ae448;
          threadParam->m_altState = threadParam->m_state;
          threadParam->m_recvWriteIdx = local_30;
          threadParam->m_state = 0x84;
        }
      }
      else if (uVar4 < 0x1d) {
        if (uVar4 == 0x14) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (iVar6 < 0) goto LAB_800ae538;
          if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
          threadParam->m_state = '\x15';
          local_38[0] = 0xffff;
          uVar9 = Crc16__6JoyBusFiPUcPUs
                            (joyBus,joyBus->m_fileBaseA_dup,joyBus->m_fileBaseA,local_38);
          iVar6 = SendChkCrc__6JoyBusFP11ThreadParamiUsPUi(joyBus,threadParam,0,uVar9,&local_30);
          if (iVar6 == 0) goto LAB_800ae448;
          threadParam->m_altState = threadParam->m_state;
          threadParam->m_recvWriteIdx = local_30;
          threadParam->m_state = 0x84;
        }
        else if (uVar4 < 0x14) {
          if (uVar4 == 3) {
            SetResetFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
            uVar5 = GBAReset(threadParam->m_portIndex,&threadParam->m_unk3);
            threadParam->m_gbaStatus = uVar5;
            if (threadParam->m_gbaStatus != 0) goto LAB_800ae538;
            threadParam->m_state = '\x02';
            threadParam->m_subState = '\0';
            ThreadSleep__6JoyBusFx(joyBus,0x80000000,0,(DAT_800000f8 / 4000) * 0xf);
            OSGetTime();
            threadParam->m_errorRetry = '\0';
            goto LAB_800ae448;
          }
          if (uVar4 < 3) {
            if (uVar4 != 1) {
              if (uVar4 != 0) {
                iVar6 = InitialCode__6JoyBusFP11ThreadParam(joyBus,threadParam);
                if (iVar6 != 1) {
                  if (iVar6 == 2) goto LAB_800ae538;
                  goto LAB_800ae448;
                }
                goto LAB_800ae564;
              }
              threadParam->m_state = '\x01';
            }
            SetChgUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            SetResetFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            threadParam->m_subState = '\0';
            threadParam->m_pposCounter = '\0';
            threadParam->m_counter0x2B = '\0';
            threadParam->m_sentStartFlag = '\0';
            threadParam->m_flags[0] = '\0';
            threadParam->m_flags[1] = '\0';
            threadParam->m_flags[5] = '\0';
            threadParam->m_flags[4] = '\0';
            threadParam->m_flags[2] = '\0';
            threadParam->m_flags[3] = '\0';
            joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\0';
            cVar10 = GetControllerMode__8GbaQueueFv(&GbaQue);
            if (cVar10 == '\0') {
              joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\0';
            }
            else {
              joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\x04';
            }
            ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
            uVar5 = GBAJoyBoot(threadParam->m_portIndex,threadParam->m_portIndex << 1,2,
                               joyBus->m_gbaBootParamA,joyBus->m_gbaBootParamB,&threadParam->m_unk3)
            ;
            threadParam->m_gbaStatus = uVar5;
            uVar5 = threadParam->m_gbaStatus;
            if ((uVar5 == 3) && ((threadParam->m_unk3 & 0x10) != 0)) {
              threadParam->m_flags[0] = '\0';
              threadParam->m_state = '\x04';
              goto LAB_800ae448;
            }
            if (uVar5 == 0) {
              cVar10 = GetControllerMode__8GbaQueueFv(&GbaQue);
              if (cVar10 == '\0') {
                joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\0';
              }
              else {
                joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\x04';
              }
              threadParam->m_state = '\x02';
              threadParam->m_subState = '\0';
              uVar5 = OSGetTick();
              threadParam->m_timestamp = uVar5;
              ThreadSleep__6JoyBusFx(joyBus,0x10624dd3,0,(DAT_800000f8 / 4000) * 0xf);
              goto LAB_800ae448;
            }
            if (uVar5 != 3) goto LAB_800ae538;
            iVar6 = GetGBAStat__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (iVar6 != 0) goto LAB_800aed04;
            threadParam->m_state = '\x02';
            threadParam->m_subState = '\0';
            ThreadSleep__6JoyBusFx(joyBus,0x80000000,0,(DAT_800000f8 / 4000) * 0xf);
            uVar11 = OSGetTime();
            goto LAB_800ae564;
          }
          if (uVar4 == 6) {
            threadParam->m_errorRetry = '\0';
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
              if ((threadParam->m_sentStartFlag != '\0') ||
                 (iVar6 = SendGBAStart__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_30),
                 -1 < iVar6)) {
                uVar4 = GetSPMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                if ((threadParam->m_flags[5] == '\0') ||
                   ((cVar10 = GetSPModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex),
                    cVar10 != '\0' || (-(uVar4 & 0xff) >> 0x1f != (uint)threadParam->m_flags[6]))))
                {
                  iVar6 = SendSPMode__6JoyBusFP11ThreadParam(joyBus,threadParam);
                  if (iVar6 < 0) goto LAB_800ae538;
                  threadParam->m_flags[5] = '\x01';
                  ClrSPModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                }
                uVar4 = GetPauseMode__8GbaQueueFv(&GbaQue);
                if (threadParam->m_flags[4] != uVar4) {
                  iVar6 = SendOpenMenu__6JoyBusFP11ThreadParamc
                                    (joyBus,threadParam,
                                     '\v' - (char)((int)-(uint)threadParam->m_flags[4] >> 0x1f));
                  if (iVar6 < 0) goto LAB_800ae538;
                  uVar4 = countLeadingZeros((uint)threadParam->m_flags[4]);
                  threadParam->m_flags[4] = (uint8_t)(uVar4 >> 5);
                }
                if (joyBus->m_nextModeTypeArr[threadParam->m_portIndex] != '\0') {
                  iVar6 = GetMoneyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  if (iVar6 == 1) {
                    local_30 = GetMoney__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                    iVar6 = SetMoney__6JoyBusFiUi(joyBus,threadParam->m_portIndex,local_30);
                    if (iVar6 == 0) {
                      ClrMoneyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                    }
                  }
                  goto LAB_800ae448;
                }
                iVar6 = SendGBAStop__6JoyBusFP11ThreadParam(joyBus,threadParam);
                if (-1 < iVar6) {
                  threadParam->m_state = '\x14';
                  goto LAB_800ae448;
                }
              }
            }
          }
          else {
            if (5 < uVar4) goto LAB_800b12c4;
            if (uVar4 < 5) {
              ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
              iVar6 = 0;
              do {
                uVar5 = GBAJoyBoot(threadParam->m_portIndex,threadParam->m_portIndex << 1,2,
                                   joyBus->m_gbaBootParamA,joyBus->m_gbaBootParamB,
                                   &threadParam->m_unk3);
                threadParam->m_gbaStatus = uVar5;
                if (threadParam->m_gbaStatus == 1) break;
                iVar6 = iVar6 + 1;
              } while (iVar6 < 100);
              if (threadParam->m_gbaStatus == 1) {
                threadParam->m_state = '\0';
                ThreadSleep__6JoyBusFx(joyBus,0x80000000,0,(DAT_800000f8 / 4000) * 0xf);
                threadParam->m_errorRetry = '\0';
                OSGetTime();
                goto LAB_800ae448;
              }
              threadParam->m_state = 0x86;
            }
            else {
              threadParam->m_errorRetry = '\0';
              iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
              if (iVar6 < 0) goto LAB_800ae538;
              if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
              if ((threadParam->m_sentStartFlag != '\0') ||
                 (iVar6 = SendGBAStart__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_30),
                 -1 < iVar6)) {
                cVar10 = GetPlayModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                if (cVar10 != '\0') {
                  threadParam->m_state = '\x02';
                  goto LAB_800ae448;
                }
                uVar4 = GetSPMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                if (((threadParam->m_flags[5] == '\0') ||
                    (cVar10 = GetSPModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex),
                    cVar10 != '\0')) || (-(uVar4 & 0xff) >> 0x1f != (uint)threadParam->m_flags[6]))
                {
                  iVar6 = SendSPMode__6JoyBusFP11ThreadParam(joyBus,threadParam);
                  if (iVar6 < 0) goto LAB_800ae538;
                  threadParam->m_flags[5] = '\x01';
                  ClrSPModeFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                }
                uVar4 = GetPauseMode__8GbaQueueFv(&GbaQue);
                if (threadParam->m_flags[4] != uVar4) {
                  iVar6 = SendOpenMenu__6JoyBusFP11ThreadParamc
                                    (joyBus,threadParam,
                                     '\v' - (char)((int)-(uint)threadParam->m_flags[4] >> 0x1f));
                  if (iVar6 < 0) goto LAB_800ae538;
                  uVar4 = countLeadingZeros((uint)threadParam->m_flags[4]);
                  threadParam->m_flags[4] = (uint8_t)(uVar4 >> 5);
                }
                cVar10 = GetControllerMode__8GbaQueueFv(&GbaQue);
                if (cVar10 != '\0') {
                  joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\x04';
                }
                if (joyBus->m_nextModeTypeArr[threadParam->m_portIndex] == '\x04') {
                  iVar6 = SendMType__6JoyBusFP11ThreadParami(joyBus,threadParam,4);
                  if (-1 < iVar6) {
                    threadParam->m_state = '\x06';
                    goto LAB_800ae448;
                  }
                }
                else {
                  cVar10 = GetStartBonusFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  if (cVar10 != '\0') {
                    iVar6 = SendStartBonus__6JoyBusFP11ThreadParam(joyBus,threadParam);
                    if (iVar6 < 0) goto LAB_800ae538;
                    ClrStartBonusFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  }
                  uVar4 = GetCmdNumFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  if (uVar4 == 0) {
                    if (((joyBus->m_stateCodeArr[threadParam->m_portIndex] != 0xff) ||
                        (iVar6 = RequestData__6JoyBusFP11ThreadParamii(joyBus,threadParam,0xe,0),
                        -1 < iVar6)) &&
                       ((iVar6 = GetCounter__7CSystemFv(&System), iVar6 != (iVar6 / 3) * 3 ||
                        (iVar6 = SendItemUse__6JoyBusFP11ThreadParam(joyBus,threadParam), -1 < iVar6
                        )))) {
                      iVar6 = GetRadarType__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      iVar8 = GetStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      if ((iVar8 == 0) && (iVar6 == 2)) {
                        iVar6 = GetChgScouFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                        if (iVar6 == 0) {
                          uVar5 = threadParam->m_portIndex;
                          if ((joyBus->m_stateFlagArr[uVar5] == '\0') ||
                             (joyBus->m_stateCodeArr[uVar5] != '\0')) {
                            iVar6 = GetChgHitFlg__8GbaQueueFi(&GbaQue,uVar5);
                            if (iVar6 != 0) {
                              local_34 = GetHitEInfo__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                              iVar6 = SendHitEnemy__6JoyBusFics
                                                (joyBus,threadParam->m_portIndex,
                                                 (char)((uint)local_34 >> 0x10),local_34._2_2_);
                              if (iVar6 < 0) goto LAB_800ae538;
                              ClrChgHitFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                            }
                            goto LAB_800af1c0;
                          }
                        }
                        threadParam->m_state = 'I';
                        goto LAB_800ae448;
                      }
LAB_800af1c0:
                      if ((joyBus->m_stateCodeArr[threadParam->m_portIndex] == '\x02') &&
                         (cVar10 = GetChgUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex),
                         cVar10 != '\0')) {
                        cVar10 = GetUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                        iVar6 = SendUseItem__6JoyBusFic(joyBus,threadParam->m_portIndex,cVar10);
                        if (iVar6 < 0) goto LAB_800ae538;
                        ClrChgUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      }
                      uVar5 = threadParam->m_portIndex;
                      if ((joyBus->m_stateFlagArr[uVar5] != '\0') &&
                         (joyBus->m_stateCodeArr[uVar5] == '\x05')) {
                        threadParam->m_state = 'C';
                        goto LAB_800ae448;
                      }
                      cVar10 = GetStrengthFlg__8GbaQueueFi(&GbaQue,uVar5);
                      if (cVar10 != '\0') {
                        iVar6 = SendStrength__6JoyBusFP11ThreadParam(joyBus,threadParam);
                        if (iVar6 < 0) goto LAB_800ae538;
                        ClrStrengthFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      }
                      cVar10 = GetMemorysFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      if (cVar10 != '\0') {
                        iVar6 = SendMemorys__6JoyBusFP11ThreadParam(joyBus,threadParam);
                        if (iVar6 < 0) goto LAB_800ae538;
                        ClrMemorysFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      }
                      iVar6 = GetChgRadarMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      if (iVar6 != 0) {
                        iVar6 = SendRaderMode__6JoyBusFP11ThreadParam(joyBus,threadParam);
                        if (iVar6 < 0) goto LAB_800ae538;
                        ClrChgRadarMode__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      }
                      iVar6 = SendPlayerHP__6JoyBusFP11ThreadParam(joyBus,threadParam);
                      if (-1 < iVar6) {
                        cVar10 = GetArtifactFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                        if (cVar10 != '\0') {
                          threadParam->m_state = '>';
                          goto LAB_800ae448;
                        }
                        iVar6 = GetStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                        if ((iVar6 == 0) || (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) {
                          uVar5 = threadParam->m_portIndex;
                          if ((joyBus->m_stateFlagArr[uVar5] != '\0') &&
                             (joyBus->m_stateCodeArr[uVar5] == '\x03')) {
                            threadParam->m_state = '2';
                            goto LAB_800ae448;
                          }
                          if ((joyBus->m_stateFlagArr[uVar5] != '\0') &&
                             (joyBus->m_stateCodeArr[uVar5] == '\x01')) {
                            threadParam->m_state = 'L';
                            goto LAB_800ae448;
                          }
                          if ((joyBus->m_stateCodeArr[uVar5] != '\0') ||
                             ((((iVar6 = GetRadarType__8GbaQueueFi(&GbaQue,uVar5), iVar6 != 0 ||
                                (iVar8 = GetCounter__7CSystemFv(&System),
                                iVar6 = iVar8 / 5 + (iVar8 >> 0x1f),
                                iVar8 != (iVar6 - (iVar6 >> 0x1f)) * 5)) ||
                               (iVar6 = SendMapObjDrawFlg__6JoyBusFP11ThreadParam
                                                  (joyBus,threadParam), -1 < iVar6)) &&
                              (((iVar6 = GetCounter__7CSystemFv(&System), iVar6 != (iVar6 / 3) * 3
                                || (iVar6 = SendMBase__6JoyBusFP11ThreadParam(joyBus,threadParam),
                                   -1 < iVar6)) &&
                               (iVar6 = SendPpos__6JoyBusFP11ThreadParam(joyBus,threadParam),
                               -1 < iVar6)))))) {
                            if ((joyBus->m_stateCodeArr[threadParam->m_portIndex] == '\a') &&
                               (iVar6 = GetFavoriteFlg__8GbaQueueFi
                                                  (&GbaQue,threadParam->m_portIndex), iVar6 != 0)) {
                              threadParam->m_state = ',';
                            }
                            else {
                              iVar6 = GetMoneyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                              if (iVar6 == 1) {
                                local_30 = GetMoney__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                                iVar6 = SetMoney__6JoyBusFiUi
                                                  (joyBus,threadParam->m_portIndex,local_30);
                                if (iVar6 == 0) {
                                  ClrMoneyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                                }
                              }
                              iVar6 = GetCompatibilityFlg__8GbaQueueFi
                                                (&GbaQue,threadParam->m_portIndex);
                              if ((iVar6 == 1) &&
                                 (joyBus->m_stateCodeArr[threadParam->m_portIndex] != '\0')) {
                                threadParam->m_state = '/';
                              }
                            }
                            goto LAB_800ae448;
                          }
                        }
                        else {
                          ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
                          threadParam->m_pposCounter = '\0';
                          iVar6 = SendMapNo__6JoyBusFP11ThreadParam(joyBus,threadParam);
                          if ((-1 < iVar6) &&
                             (iVar6 = SendRaderType__6JoyBusFP11ThreadParam(joyBus,threadParam),
                             -1 < iVar6)) {
                            if (threadParam->m_gbaBootFlag == '\0') {
                              iVar6 = SendMBase__6JoyBusFP11ThreadParam(joyBus,threadParam);
                              if (iVar6 < 0) goto LAB_800ae538;
                              ClrStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                            }
                            threadParam->m_state = ';';
                            goto LAB_800ae448;
                          }
                        }
                      }
                    }
                  }
                  else {
                    if ((uVar4 & 2) != 0) {
                      threadParam->m_state = '\x17';
                      goto LAB_800ae448;
                    }
                    iVar6 = SendChgCmdNum__6JoyBusFP11ThreadParam(joyBus,threadParam);
                    if (-1 < iVar6) {
                      ClrCmdNumFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                      goto LAB_800ae448;
                    }
                  }
                }
              }
            }
          }
        }
        else if (uVar4 == 0x19) {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
              if ((local_2c[0] & 0x3f) == 7) {
                threadParam->m_state = '\x17';
              }
              else {
                if (threadParam->m_gbaBootFlag == '\0') {
                  threadParam->m_state = 'F';
                }
                else {
                  threadParam->m_state = '\x1d';
                }
                ClrArtifactFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                ClrCmdNumFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
              }
              iVar6 = SendGBAStart__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_30);
              if (iVar6 != 0) {
                threadParam->m_altState = threadParam->m_state;
                threadParam->m_recvWriteIdx = local_30;
                threadParam->m_state = 0x84;
              }
            }
            goto LAB_800ae448;
          }
        }
        else if (uVar4 < 0x19) {
          if (uVar4 == 0x17) {
            joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if ((threadParam->m_skipProcessingFlag != '\0') ||
                 (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
              threadParam->m_subState = '\0';
              iVar6 = SendItemAll__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (iVar6 == 0) {
                threadParam->m_state = '\x18';
                goto LAB_800ae448;
              }
            }
          }
          else if (uVar4 < 0x17) {
            if (0x15 < uVar4) {
              iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (iVar6 == -1) goto LAB_800ae538;
              if (iVar6 == -2) {
                threadParam->m_state = '\x03';
              }
              if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
                if (joyBus->m_nextModeTypeArr[threadParam->m_portIndex] == '\0') {
                  threadParam->m_state = ';';
                }
                else {
                  threadParam->m_state = '\x06';
                  iVar6 = SendGBAStart__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_30);
                  if (iVar6 != 0) {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = local_30;
                    threadParam->m_state = 0x84;
                  }
                }
              }
              goto LAB_800ae448;
            }
            uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < (int)uVar4) {
              if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
                if ((local_2c[0] & 0x3f) == 7) {
                  threadParam->m_state = '\x16';
                  memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
                  joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\0';
                  iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
                  if (iVar6 != 0) {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = local_30;
                    threadParam->m_state = 0x84;
                    goto LAB_800ae538;
                  }
                }
                else if (joyBus->m_nextModeTypeArr[threadParam->m_portIndex] == '\0') {
                  threadParam->m_state = ';';
                }
                else {
                  threadParam->m_state = '\x06';
                  iVar6 = SendGBAStart__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,&local_30);
                  if (iVar6 != 0) {
                    threadParam->m_altState = threadParam->m_state;
                    threadParam->m_recvWriteIdx = local_30;
                    threadParam->m_state = 0x84;
                  }
                }
                DecRecvQueue__6JoyBusFi(joyBus,threadParam->m_portIndex);
              }
              goto LAB_800ae448;
            }
          }
          else {
            uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (0 < (int)uVar4) {
              if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
              goto LAB_800ae448;
              if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
                threadParam->m_state = '\x17';
                goto LAB_800ae448;
              }
              iVar6 = SendItemAll__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                if (iVar6 == 1) {
                  threadParam->m_state = '\x19';
                }
                goto LAB_800ae448;
              }
            }
          }
        }
        else if (uVar4 == 0x1b) {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
            goto LAB_800ae448;
            if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
              threadParam->m_state = '\x1a';
              goto LAB_800ae448;
            }
            iVar6 = SendPlayerStat__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              if (iVar6 == 1) {
                threadParam->m_state = '\x1c';
              }
              goto LAB_800ae448;
            }
          }
        }
        else if (uVar4 < 0x1b) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag != '\0') ||
               (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
            threadParam->m_subState = '\0';
            iVar6 = SendPlayerStat__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              threadParam->m_state = '\x1b';
              goto LAB_800ae448;
            }
          }
        }
        else {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
              if ((local_2c[0] & 0x3f) == 7) {
                threadParam->m_state = '\x1a';
              }
              else {
                threadParam->m_state = '\x17';
                ClrFavoriteFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                ClrMoneyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                ClrStrengthFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
              }
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 == 0x26) {
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
          threadParam->m_state = '\'';
          memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
          joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\x02';
          iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 == 0) goto LAB_800ae448;
          threadParam->m_altState = threadParam->m_state;
          threadParam->m_recvWriteIdx = local_30;
          threadParam->m_state = 0x84;
        }
      }
      else if (uVar4 < 0x26) {
        if (uVar4 == 0x22) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if (threadParam->m_skipProcessingFlag == '\0') {
              threadParam->m_state = '#';
            }
            goto LAB_800ae448;
          }
        }
        else if (uVar4 < 0x22) {
          if (uVar4 == 0x20) goto LAB_800b12c4;
          if (uVar4 < 0x20) {
            if (uVar4 < 0x1f) {
              uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
              if ((int)uVar4 < 0) goto LAB_800ae538;
              if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 1) == 0))
              goto LAB_800ae448;
              if ((local_2c[0] & 0x3f) != 7) {
                DecRecvQueue__6JoyBusFi(joyBus,threadParam->m_portIndex);
                threadParam->m_state = 'F';
                ClrStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                goto LAB_800ae448;
              }
              threadParam->m_state = '\x1f';
              memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
              joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\x01';
              DecRecvQueue__6JoyBusFi(joyBus,threadParam->m_portIndex);
              iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (iVar6 == 0) goto LAB_800ae448;
              threadParam->m_altState = threadParam->m_state;
              threadParam->m_recvWriteIdx = local_30;
              threadParam->m_state = 0x84;
            }
            else {
              iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (iVar6 != -1) {
                if (iVar6 == -2) {
                  threadParam->m_state = '\x03';
                }
                if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
                  ClrStageFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  threadParam->m_state = 'F';
                }
                goto LAB_800ae448;
              }
            }
          }
          else {
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if ((threadParam->m_skipProcessingFlag == '\0') &&
                 (iVar6 = GetLetterLstFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), iVar6 != 0
                 )) {
                threadParam->m_state = '\"';
              }
              goto LAB_800ae448;
            }
          }
        }
        else if (uVar4 == 0x24) {
          iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 != -1) {
            if (iVar6 == -2) {
              threadParam->m_state = '\x03';
            }
            if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
              threadParam->m_state = '\x05';
            }
            goto LAB_800ae448;
          }
        }
        else if (uVar4 < 0x24) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
            threadParam->m_state = '$';
            memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
            joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\x03';
            DecRecvQueue__6JoyBusFi(joyBus,threadParam->m_portIndex);
            iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (iVar6 == 0) goto LAB_800ae448;
            threadParam->m_altState = threadParam->m_state;
            threadParam->m_recvWriteIdx = local_30;
            threadParam->m_state = 0x84;
          }
        }
        else {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag == '\0') &&
               (iVar6 = GetLetterDatFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), iVar6 != 0))
            {
              threadParam->m_state = '&';
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 == 0x2b) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
            if ((local_2c[0] & 0x3f) == 7) {
              threadParam->m_state = ')';
            }
            else {
              threadParam->m_state = '\x05';
            }
          }
          goto LAB_800ae448;
        }
      }
      else if (uVar4 < 0x2b) {
        if (uVar4 == 0x29) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag != '\0') ||
               (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
            threadParam->m_subState = '\0';
            iVar6 = SendMapObj__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              threadParam->m_state = '*';
              goto LAB_800ae448;
            }
          }
        }
        else if (uVar4 < 0x29) {
          if (0x27 < uVar4) goto LAB_800b12c4;
          iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 != -1) {
            if (iVar6 == -2) {
              threadParam->m_state = '\x03';
            }
            if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
              threadParam->m_state = '\x05';
            }
            goto LAB_800ae448;
          }
        }
        else {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
            goto LAB_800ae448;
            if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
              threadParam->m_state = ')';
              goto LAB_800ae448;
            }
            iVar6 = SendMapObj__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              if (iVar6 == 1) {
                threadParam->m_state = '+';
              }
              goto LAB_800ae448;
            }
          }
        }
      }
      else if (uVar4 == 0x2d) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0)) goto LAB_800ae448;
          if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
            threadParam->m_state = ',';
            goto LAB_800ae448;
          }
          iVar6 = SendFavorite__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            if (iVar6 == 1) {
              threadParam->m_state = '.';
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 < 0x2d) {
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if ((threadParam->m_skipProcessingFlag != '\0') ||
             (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
          threadParam->m_subState = '\0';
          iVar6 = SendFavorite__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            threadParam->m_state = '-';
            goto LAB_800ae448;
          }
        }
      }
      else {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
            if ((local_2c[0] & 0x3f) == 7) {
              threadParam->m_state = ',';
            }
            else {
              threadParam->m_state = '\x05';
              ClrFavoriteFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            }
          }
          goto LAB_800ae448;
        }
      }
    }
    else if (uVar4 == 0x42) {
      iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
      if (iVar6 != -1) {
        if (iVar6 == -2) {
          threadParam->m_state = '\x03';
        }
        if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
          ClrArtiDatFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          threadParam->m_state = '\x05';
        }
        goto LAB_800ae448;
      }
    }
    else if (uVar4 < 0x42) {
      if (uVar4 == 0x39) {
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if ((threadParam->m_skipProcessingFlag != '\0') ||
             (iVar6 = GetMkSmithFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), iVar6 == 0))
          goto LAB_800ae448;
          threadParam->m_state = ':';
          memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
          joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\b';
          iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 == 0) goto LAB_800ae448;
          threadParam->m_altState = threadParam->m_state;
          threadParam->m_recvWriteIdx = local_30;
          threadParam->m_state = 0x84;
        }
      }
      else if (uVar4 < 0x39) {
        if (uVar4 == 0x34) {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
              if ((local_2c[0] & 0x3f) == 7) {
                threadParam->m_state = '2';
              }
              else {
                threadParam->m_state = '\x05';
              }
            }
            goto LAB_800ae448;
          }
        }
        else if (uVar4 < 0x34) {
          if (uVar4 == 0x32) {
            joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if ((threadParam->m_skipProcessingFlag != '\0') ||
                 (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
              threadParam->m_subState = '\0';
              iVar6 = SendEquip__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                threadParam->m_state = '3';
                goto LAB_800ae448;
              }
            }
          }
          else if (uVar4 < 0x32) {
            if (uVar4 < 0x31) {
              uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
              if ((int)uVar4 < 1) goto LAB_800ae538;
              if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
              goto LAB_800ae448;
              if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
                threadParam->m_state = '/';
                goto LAB_800ae448;
              }
              iVar6 = SendCompatibility__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                if (iVar6 == 1) {
                  threadParam->m_state = '1';
                }
                goto LAB_800ae448;
              }
            }
            else {
              uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
              if (0 < (int)uVar4) {
                if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
                  if ((local_2c[0] & 0x3f) == 7) {
                    threadParam->m_state = '/';
                  }
                  else {
                    threadParam->m_state = '\x05';
                    ClrCompatibilityFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                  }
                }
                goto LAB_800ae448;
              }
            }
          }
          else {
            uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (0 < (int)uVar4) {
              if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
              goto LAB_800ae448;
              if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
                threadParam->m_state = '2';
                goto LAB_800ae448;
              }
              iVar6 = SendEquip__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                if (iVar6 == 1) {
                  threadParam->m_state = '4';
                }
                goto LAB_800ae448;
              }
            }
          }
        }
        else if (uVar4 == 0x37) {
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag != '\0') ||
               (iVar6 = GetBuyFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), iVar6 == 0))
            goto LAB_800ae448;
            threadParam->m_state = '8';
            memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
            joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\a';
            iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (iVar6 == 0) goto LAB_800ae448;
            threadParam->m_altState = threadParam->m_state;
            threadParam->m_recvWriteIdx = local_30;
            threadParam->m_state = 0x84;
          }
        }
        else if (uVar4 < 0x37) {
          if (uVar4 < 0x36) {
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if ((threadParam->m_skipProcessingFlag != '\0') ||
                 (iVar6 = GetSellFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), iVar6 == 0))
              goto LAB_800ae448;
              threadParam->m_state = '6';
              memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
              joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\x06';
              iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (iVar6 == 0) goto LAB_800ae448;
              threadParam->m_altState = threadParam->m_state;
              threadParam->m_recvWriteIdx = local_30;
              threadParam->m_state = 0x84;
            }
          }
          else {
            iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (iVar6 != -1) {
              if (iVar6 == -2) {
                threadParam->m_state = '\x03';
              }
              if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
                threadParam->m_state = '\x06';
              }
              goto LAB_800ae448;
            }
          }
        }
        else {
          iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 != -1) {
            if (iVar6 == -2) {
              threadParam->m_state = '\x03';
            }
            if ((threadParam->m_skipProcessingFlag == '\0') && (iVar6 == 1)) {
              threadParam->m_state = '\x06';
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 == 0x3e) {
        joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if ((threadParam->m_skipProcessingFlag != '\0') ||
             (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
          threadParam->m_subState = '\0';
          iVar6 = SendArtifact__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            threadParam->m_state = '?';
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 < 0x3e) {
        if (uVar4 == 0x3c) {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
            goto LAB_800ae448;
            if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
              threadParam->m_state = ';';
              goto LAB_800ae448;
            }
            iVar6 = SendBonusStr__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              if (iVar6 == 1) {
                threadParam->m_state = '=';
              }
              goto LAB_800ae448;
            }
          }
        }
        else if (uVar4 < 0x3c) {
          if (uVar4 < 0x3b) {
            iVar6 = SendDataFile__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (iVar6 != -1) {
              if (iVar6 == -2) {
                threadParam->m_state = '\x03';
              }
              if (threadParam->m_skipProcessingFlag == '\0') {
                if (iVar6 == 1) {
                  threadParam->m_state = '\x06';
                }
                ThreadSleep__6JoyBusFx(joyBus,0x10624dd3,0,DAT_800000f8 / 4000);
                OSGetTime();
              }
              goto LAB_800ae448;
            }
          }
          else {
            joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if ((-1 < iVar6) &&
               (iVar6 = SendGBAStop__6JoyBusFP11ThreadParam(joyBus,threadParam), -1 < iVar6)) {
              if ((threadParam->m_skipProcessingFlag != '\0') ||
                 (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
              threadParam->m_subState = '\0';
              iVar6 = SendBonusStr__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                threadParam->m_state = '<';
                goto LAB_800ae448;
              }
            }
          }
        }
        else {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
              if ((local_2c[0] & 0x3f) == 7) {
                threadParam->m_state = ';';
              }
              else {
                threadParam->m_state = '\x1a';
              }
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 == 0x40) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
            if ((local_2c[0] & 0x3f) == 7) {
              threadParam->m_state = '>';
            }
            else {
              ClrArtifactFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
              threadParam->m_state = '\x05';
            }
          }
          goto LAB_800ae448;
        }
      }
      else if (uVar4 < 0x40) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0)) goto LAB_800ae448;
          if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
            threadParam->m_state = '>';
            goto LAB_800ae448;
          }
          iVar6 = SendArtifact__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            if (iVar6 == 1) {
              threadParam->m_state = '@';
            }
            goto LAB_800ae448;
          }
        }
      }
      else {
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if ((threadParam->m_skipProcessingFlag != '\0') ||
             (cVar10 = GetArtiDatFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex), cVar10 == '\0')
             ) goto LAB_800ae448;
          threadParam->m_state = 'B';
          memset(joyBus->m_perThreadTemp + threadParam->m_portIndex,0,0x18);
          joyBus->m_perThreadTemp[threadParam->m_portIndex][0] = '\t';
          iVar6 = SendCancel__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (iVar6 == 0) goto LAB_800ae448;
          threadParam->m_altState = threadParam->m_state;
          threadParam->m_recvWriteIdx = local_30;
          threadParam->m_state = 0x84;
        }
      }
    }
    else if (uVar4 == 0x4b) {
      uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
      if (0 < (int)uVar4) {
        if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
          if ((local_2c[0] & 0x3f) == 7) {
            threadParam->m_state = 'I';
          }
          else {
            ClrChgScouFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
            threadParam->m_state = '\x05';
          }
        }
        goto LAB_800ae448;
      }
    }
    else if (uVar4 < 0x4b) {
      if (uVar4 == 0x47) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0)) goto LAB_800ae448;
          if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
            threadParam->m_state = 'F';
            goto LAB_800ae448;
          }
          iVar6 = SendMapObjInfo__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            if (iVar6 == 1) {
              threadParam->m_state = 'H';
            }
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 < 0x47) {
        if (uVar4 == 0x45) {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
              if ((local_2c[0] & 0x3f) == 7) {
                threadParam->m_state = 'C';
              }
              else {
                ClrArtifactFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
                threadParam->m_state = '\x05';
              }
            }
            goto LAB_800ae448;
          }
        }
        else if (uVar4 < 0x45) {
          if (uVar4 < 0x44) {
            joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
            iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (-1 < iVar6) {
              if ((threadParam->m_skipProcessingFlag != '\0') ||
                 (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
              threadParam->m_subState = '\0';
              iVar6 = SendTmpArtifact__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                threadParam->m_state = 'D';
                goto LAB_800ae448;
              }
            }
          }
          else {
            uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
            if (0 < (int)uVar4) {
              if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
              goto LAB_800ae448;
              if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
                threadParam->m_state = 'C';
                goto LAB_800ae448;
              }
              iVar6 = SendTmpArtifact__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                if (iVar6 == 1) {
                  threadParam->m_state = 'E';
                }
                goto LAB_800ae448;
              }
            }
          }
        }
        else {
          joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag != '\0') ||
               (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
            iVar6 = SendRaderType__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if ((-1 < iVar6) &&
               (iVar6 = SendRaderMode__6JoyBusFP11ThreadParam(joyBus,threadParam), -1 < iVar6)) {
              threadParam->m_subState = '\0';
              iVar6 = SendMapObjInfo__6JoyBusFP11ThreadParam(joyBus,threadParam);
              if (-1 < iVar6) {
                threadParam->m_state = 'G';
                goto LAB_800ae448;
              }
            }
          }
        }
      }
      else if (uVar4 == 0x49) {
        joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
        iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (-1 < iVar6) {
          if ((threadParam->m_skipProcessingFlag != '\0') ||
             (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
          ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
          threadParam->m_subState = '\0';
          iVar6 = SendScouInfo__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            threadParam->m_state = 'J';
            goto LAB_800ae448;
          }
        }
      }
      else if (uVar4 < 0x49) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
            if ((local_2c[0] & 0x3f) == 7) {
              threadParam->m_state = 'F';
            }
            else {
              threadParam->m_state = ')';
            }
          }
          goto LAB_800ae448;
        }
      }
      else {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0)) goto LAB_800ae448;
          if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
            threadParam->m_state = 'I';
            goto LAB_800ae448;
          }
          iVar6 = SendScouInfo__6JoyBusFP11ThreadParam(joyBus,threadParam);
          if (-1 < iVar6) {
            if (iVar6 == 1) {
              threadParam->m_state = 'K';
            }
            goto LAB_800ae448;
          }
        }
      }
    }
    else if (uVar4 == 900) {
      iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
      if (-1 < iVar6) {
        if (threadParam->m_skipProcessingFlag != '\0') goto LAB_800ae448;
        iVar6 = SetSendQueue__6JoyBusFP11ThreadParamUi
                          (joyBus,threadParam,threadParam->m_recvWriteIdx);
        if (iVar6 == 0) {
          threadParam->m_state = threadParam->m_altState;
          threadParam->m_recvWriteIdx = 0;
          goto LAB_800ae448;
        }
      }
    }
    else if (uVar4 < 900) {
      if (uVar4 == 0x4e) {
        uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
        if (0 < (int)uVar4) {
          if ((threadParam->m_skipProcessingFlag == '\0') && ((uVar4 & 1) != 0)) {
            if ((local_2c[0] & 0x3f) == 7) {
              threadParam->m_state = 'L';
            }
            else {
              threadParam->m_state = '\x05';
            }
          }
          goto LAB_800ae448;
        }
      }
      else {
        if (0x4d < uVar4) goto LAB_800b12c4;
        if (uVar4 < 0x4d) {
          joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\0';
          iVar6 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (-1 < iVar6) {
            if ((threadParam->m_skipProcessingFlag != '\0') ||
               (iVar6 = GetScrFlg__8GbaQueueFv(&GbaQue), iVar6 == 0)) goto LAB_800ae448;
            threadParam->m_subState = '\0';
            iVar6 = SendCmd__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              threadParam->m_state = 'M';
              goto LAB_800ae448;
            }
          }
        }
        else {
          uVar4 = GBARecvSend__6JoyBusFP11ThreadParamPUi(joyBus,threadParam,local_2c);
          if (0 < (int)uVar4) {
            if ((threadParam->m_skipProcessingFlag != '\0') || ((uVar4 & 2) == 0))
            goto LAB_800ae448;
            if (((uVar4 & 1) != 0) && ((local_2c[0] & 0x3f) == 7)) {
              threadParam->m_state = 'L';
              goto LAB_800ae448;
            }
            iVar6 = SendCmd__6JoyBusFP11ThreadParam(joyBus,threadParam);
            if (-1 < iVar6) {
              if (iVar6 == 1) {
                threadParam->m_state = 'N';
              }
              goto LAB_800ae448;
            }
          }
        }
      }
    }
    else {
      if ((uVar4 == 0x386) || (0x385 < uVar4)) {
LAB_800b12c4:
        threadParam->m_flags[4] = '\0';
        SetChgUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
        threadParam->m_sentStartFlag = '\0';
        threadParam->m_flags[1] = '\0';
        threadParam->m_flags[5] = '\0';
        if (threadParam->m_counter0x2B == '\0') {
          SetResetFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
          threadParam->m_counter0x2B = '\x01';
        }
        iVar6 = GetGBAStat__6JoyBusFP11ThreadParam(joyBus,threadParam);
        if (iVar6 == 0) {
          threadParam->m_state = '\0';
        }
        else {
          ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
          joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\x01';
          joyBus->m_stateCodeArr[threadParam->m_portIndex] = 0xff;
          ThreadSleep__6JoyBusFx(joyBus,0x80000000,0,(DAT_800000f8 / 4000) * 0xf);
        }
        goto LAB_800ae448;
      }
      threadParam->m_flags[4] = '\0';
      SetChgUseItemFlg__8GbaQueueFi(&GbaQue,threadParam->m_portIndex);
      threadParam->m_sentStartFlag = '\0';
      threadParam->m_flags[1] = '\0';
      threadParam->m_flags[5] = '\0';
      threadParam->m_errorRetry = threadParam->m_errorRetry + '\x01';
      joyBus->m_ctrlModeArr[threadParam->m_portIndex] = '\0';
      cVar10 = GetControllerMode__8GbaQueueFv(&GbaQue);
      if (cVar10 == '\0') {
        joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\0';
      }
      else {
        joyBus->m_nextModeTypeArr[threadParam->m_portIndex] = '\x04';
      }
      joyBus->m_stateFlagArr[threadParam->m_portIndex] = '\x01';
      joyBus->m_stateCodeArr[threadParam->m_portIndex] = 0xff;
      if (9 < threadParam->m_errorRetry) {
        threadParam->m_state = '\x04';
        goto LAB_800ae448;
      }
      iVar6 = GetGBAStat__6JoyBusFP11ThreadParam(joyBus,threadParam);
      if (iVar6 == 0) {
        ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
        if (threadParam->m_prevState < 3) {
          threadParam->m_subState = '\0';
          threadParam->m_state = '\x01';
          threadParam->m_prevState = '\0';
        }
        else {
          threadParam->m_state = '\x03';
        }
        goto LAB_800ae448;
      }
      uVar11 = OSGetTime();
    }
  }
  else {
    threadParam->m_state = 0x86;
    ResetQueue__6JoyBusFP11ThreadParam(joyBus,threadParam);
    ClrRecvBuffer__6JoyBusFi(joyBus,threadParam->m_portIndex);
  }
LAB_800ae538:
  ThreadSleep__6JoyBusFx(joyBus,0x10624dd3,0,(DAT_800000f8 / 4000) * 0xf);
  goto LAB_800ae564;
LAB_800aed04:
  threadParam->m_flags[0] = '\0';
  goto LAB_800ae448;
}

