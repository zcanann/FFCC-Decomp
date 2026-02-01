// Function: onSetSystemVal__13CFlatRuntime2FiPQ212CFlatRuntime6CStacki
// Entry: 800b28f0
// Size: 1680 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onSetSystemVal__13CFlatRuntime2FiPQ212CFlatRuntime6CStacki
               (undefined4 param_1,int param_2,CStack *cstack,int param_4)

{
  int8_t *piVar1;
  uint16_t *puVar2;
  uint8_t *puVar3;
  int16_t *piVar4;
  byte bVar5;
  int iVar6;
  uint32_t uVar7;
  uint uVar8;
  
  if (-0x1000 < param_2) {
    if (param_2 < -499) {
      uVar8 = param_2 + 0x9f3;
      iVar6 = (int)uVar8 >> 0x1f;
      piVar1 = Game.game.m_gameWork.m_eventFlags +
               ((int)uVar8 >> 3) + (uint)((int)uVar8 < 0 && (uVar8 & 7) != 0) + 8;
      uVar8 = 1 << (iVar6 * 8 | uVar8 * 0x20000000 + iVar6 >> 0x1d) - iVar6;
      uVar7 = -((int)-((byte)*piVar1 & uVar8) >> 0x1f);
      cstack[-1].m_arg = uVar7;
      if (param_4 == 0) {
        uVar7 = cstack->m_arg;
      }
      else if (param_4 < 0) {
        if (-2 < param_4) {
          uVar7 = uVar7 - cstack->m_arg;
        }
      }
      else if (param_4 < 2) {
        uVar7 = uVar7 + cstack->m_arg;
      }
      bVar5 = (byte)uVar8;
      if (uVar7 == 0) {
        *piVar1 = *piVar1 & ~bVar5;
      }
      else {
        *piVar1 = *piVar1 | bVar5;
      }
    }
    else if (param_2 < -199) {
      puVar2 = Game.game.m_caravanWorkArr[0].m_artifacts + param_2 + 0x1e;
      cstack[-1].m_arg = (int)(short)*puVar2;
      if (param_4 == 0) {
        *puVar2 = (uint16_t)cstack->m_arg;
      }
      else if (param_4 < 0) {
        if (-2 < param_4) {
          *puVar2 = *puVar2 - (short)cstack->m_arg;
        }
      }
      else if (param_4 < 2) {
        *puVar2 = *puVar2 + (short)cstack->m_arg;
      }
    }
    else {
      switch(param_2) {
      case -0x79:
        cstack[-1].m_arg = (int)(short)Game.game.m_gameWork.m_optionValue;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_optionValue = (uint16_t)cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_optionValue =
                 Game.game.m_gameWork.m_optionValue - (short)cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_optionValue =
               Game.game.m_gameWork.m_optionValue + (short)cstack->m_arg;
        }
        break;
      case -0x77:
        cstack[-1].m_arg = (uint)Game.game.m_gameWork.m_soundOptionFlag;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_soundOptionFlag = (uint8_t)cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_soundOptionFlag =
                 Game.game.m_gameWork.m_soundOptionFlag - (char)cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_soundOptionFlag =
               Game.game.m_gameWork.m_soundOptionFlag + (char)cstack->m_arg;
        }
        break;
      case -0x76:
        uVar8 = (uint)Game.game.m_gameWork.m_menuStageMode;
        cstack[-1].m_arg = uVar8;
        if (param_4 == 0) {
          uVar8 = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            uVar8 = uVar8 - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          uVar8 = uVar8 + cstack->m_arg;
        }
        ChgPlayModeFromScript__8CMenuPcsFb
                  (&MenuPcs,(byte)((byte)(-uVar8 >> 0x18) | (byte)(uVar8 >> 0x18)) >> 7);
        break;
      case -0x75:
        cstack[-1].m_arg = (int)Game.game.m_gameWork.m_bossArtifactStageIndex;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_bossArtifactStageIndex = (int16_t)cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_bossArtifactStageIndex =
                 Game.game.m_gameWork.m_bossArtifactStageIndex - (short)cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_bossArtifactStageIndex =
               Game.game.m_gameWork.m_bossArtifactStageIndex + (short)cstack->m_arg;
        }
        break;
      case -0x6b:
      case -0x6a:
      case -0x69:
      case -0x68:
      case -0x67:
        piVar4 = Game.game.m_gameWork.m_eventWork + param_2 * 2 + 0x50;
        cstack[-1].m_arg = *(uint32_t *)piVar4;
        if (param_4 == 0) {
          *(uint32_t *)piVar4 = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            *(uint32_t *)piVar4 = *(int *)piVar4 - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          *(uint32_t *)piVar4 = *(int *)piVar4 + cstack->m_arg;
        }
        break;
      case -0x66:
        cstack[-1].m_arg = Game.game.m_gameWork.m_chaliceElement;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_chaliceElement = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_chaliceElement =
                 Game.game.m_gameWork.m_chaliceElement - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_chaliceElement =
               Game.game.m_gameWork.m_chaliceElement + cstack->m_arg;
        }
        break;
      case -0x65:
      case -100:
      case -99:
      case -0x62:
      case -0x61:
      case -0x60:
      case -0x5f:
      case -0x5e:
      case -0x5d:
      case -0x5c:
      case -0x5b:
      case -0x5a:
      case -0x59:
      case -0x58:
      case -0x57:
        puVar3 = Game.game.m_gameWork.m_linkTable[0][5][3] + param_2 * 4;
        cstack[-1].m_arg = *(uint32_t *)puVar3;
        if (param_4 == 0) {
          *(uint32_t *)puVar3 = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            *(uint32_t *)puVar3 = *(int *)puVar3 - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          *(uint32_t *)puVar3 = *(int *)puVar3 + cstack->m_arg;
        }
        break;
      case -0x56:
      case -0x55:
      case -0x54:
      case -0x53:
      case -0x52:
      case -0x51:
      case -0x50:
      case -0x4f:
      case -0x4e:
      case -0x4d:
      case -0x4c:
      case -0x4b:
      case -0x4a:
      case -0x49:
      case -0x48:
        puVar3 = Game.game.m_gameWork.m_linkTable[0][3][4] + param_2 * 4;
        cstack[-1].m_arg = *(uint32_t *)puVar3;
        if (param_4 == 0) {
          *(uint32_t *)puVar3 = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            *(uint32_t *)puVar3 = *(int *)puVar3 - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          *(uint32_t *)puVar3 = *(int *)puVar3 + cstack->m_arg;
        }
        break;
      case -0x47:
      case -0x46:
      case -0x45:
      case -0x44:
        puVar3 = Game.game.m_gameWork.m_linkTable[0][2][2] + param_2 * 4 + 4;
        cstack[-1].m_arg = *(uint32_t *)puVar3;
        if (param_4 == 0) {
          *(uint32_t *)puVar3 = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            *(uint32_t *)puVar3 = *(int *)puVar3 - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          *(uint32_t *)puVar3 = *(int *)puVar3 + cstack->m_arg;
        }
        break;
      case -0x43:
        cstack[-1].m_arg = Game.game.m_gameWork.m_frameCounter;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_frameCounter = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_frameCounter =
                 Game.game.m_gameWork.m_frameCounter - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_frameCounter = Game.game.m_gameWork.m_frameCounter + cstack->m_arg;
        }
        break;
      case -0x42:
        cstack[-1].m_arg = Game.game.m_gameWork.m_scriptGlobalTime;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_scriptGlobalTime = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_scriptGlobalTime =
                 Game.game.m_gameWork.m_scriptGlobalTime - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_scriptGlobalTime =
               Game.game.m_gameWork.m_scriptGlobalTime + cstack->m_arg;
        }
        break;
      case -0x41:
        cstack[-1].m_arg = Game.game.m_gameWork.m_timerA;
        if (param_4 == 0) {
          Game.game.m_gameWork.m_timerA = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork.m_timerA = Game.game.m_gameWork.m_timerA - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork.m_timerA = Game.game.m_gameWork.m_timerA + cstack->m_arg;
        }
        break;
      case -0x40:
        cstack[-1].m_arg = Game.game.m_gameWork._8_4_;
        if (param_4 == 0) {
          Game.game.m_gameWork._8_4_ = cstack->m_arg;
        }
        else if (param_4 < 0) {
          if (-2 < param_4) {
            Game.game.m_gameWork._8_4_ = Game.game.m_gameWork._8_4_ - cstack->m_arg;
          }
        }
        else if (param_4 < 2) {
          Game.game.m_gameWork._8_4_ = Game.game.m_gameWork._8_4_ + cstack->m_arg;
        }
      }
    }
  }
  return;
}

