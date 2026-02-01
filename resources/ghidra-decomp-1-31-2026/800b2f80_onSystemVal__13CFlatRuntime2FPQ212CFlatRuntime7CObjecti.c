// Function: onSystemVal__13CFlatRuntime2FPQ212CFlatRuntime7CObjecti
// Entry: 800b2f80
// Size: 912 bytes

/* WARNING: Removing unreachable block (ram,0x800b32c4) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint32_t *
onSystemVal__13CFlatRuntime2FPQ212CFlatRuntime7CObjecti
          (CFlatRuntime2 *flatRuntime2,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  uint32_t uVar5;
  
  if (param_3 < -0xfff) {
    iVar3 = -0x1000 - param_3;
    uVar5 = 0;
    iVar1 = iVar3 / 0x600 + (iVar3 >> 0x1f);
    puVar4 = (ushort *)
             (Game.game.unkCFlatData0[2] +
             (0x5ff - (iVar3 + (iVar1 - (iVar1 >> 0x1f)) * -0x600)) * 0x48);
    switch(iVar1 - (iVar1 >> 0x1f)) {
    case 0:
      uVar5 = (uint32_t)*puVar4;
      break;
    case 1:
      uVar5 = (uint32_t)puVar4[1];
      break;
    case 2:
      uVar5 = (uint32_t)puVar4[2];
      break;
    case 3:
      uVar5 = (uint32_t)puVar4[3];
      break;
    case 4:
      uVar5 = (uint32_t)puVar4[4];
      break;
    case 5:
      uVar5 = (uint32_t)puVar4[5];
      break;
    case 6:
      uVar5 = (uint32_t)puVar4[6];
      break;
    case 7:
      uVar5 = (uint32_t)puVar4[7];
      break;
    case 8:
      uVar5 = (uint32_t)puVar4[8];
      break;
    case 9:
      uVar5 = (uint32_t)puVar4[9];
      break;
    case 10:
      uVar5 = (uint32_t)puVar4[10];
      break;
    case 0xb:
      uVar5 = (uint32_t)puVar4[0xb];
      break;
    case 0xc:
      uVar5 = (uint32_t)puVar4[0xc];
      break;
    case 0xd:
      uVar5 = (uint32_t)puVar4[0xd];
      break;
    case 0xe:
      uVar5 = (uint32_t)puVar4[0xe];
      break;
    case 0xf:
      uVar5 = (uint32_t)puVar4[0xf];
      break;
    case 0x10:
      uVar5 = (uint32_t)puVar4[0x10];
      break;
    case 0x11:
      uVar5 = (uint32_t)puVar4[0x11];
      break;
    case 0x12:
      uVar5 = (uint32_t)puVar4[0x12];
      break;
    case 0x13:
      uVar5 = (uint32_t)puVar4[0x13];
      break;
    case 0x14:
      uVar5 = (uint32_t)puVar4[0x14];
      break;
    case 0x15:
      uVar5 = (uint32_t)puVar4[0x15];
      break;
    case 0x16:
      uVar5 = (uint32_t)puVar4[0x16];
      break;
    case 0x17:
      uVar5 = (uint32_t)puVar4[0x17];
      break;
    case 0x18:
      uVar5 = (uint32_t)puVar4[0x18];
      break;
    case 0x19:
      uVar5 = (uint32_t)puVar4[0x19];
      break;
    case 0x1a:
      uVar5 = (uint32_t)puVar4[0x1a];
      break;
    case 0x1b:
      uVar5 = (uint32_t)puVar4[0x1b];
      break;
    case 0x1c:
      uVar5 = (uint32_t)puVar4[0x1c];
      break;
    case 0x1d:
      uVar5 = (uint32_t)puVar4[0x1d];
      break;
    case 0x1e:
      uVar5 = (uint32_t)puVar4[0x1e];
      break;
    case 0x1f:
      uVar5 = (uint32_t)puVar4[0x1f];
      break;
    case 0x20:
      uVar5 = (uint32_t)puVar4[0x20];
      break;
    case 0x21:
      uVar5 = (uint32_t)puVar4[0x21];
      break;
    case 0x22:
      uVar5 = (uint32_t)puVar4[0x22];
      break;
    case 0x23:
      uVar5 = (uint32_t)puVar4[0x23];
    }
    (flatRuntime2->flatRuntimeBase).m_lastResult = uVar5;
  }
  else if (param_3 < -499) {
    uVar2 = param_3 + 0x9f3;
    iVar1 = (int)uVar2 >> 0x1f;
    (flatRuntime2->flatRuntimeBase).m_lastResult =
         -((uint)(byte)Game.game.m_gameWork.m_eventFlags
                       [((int)uVar2 >> 3) + (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0) + 8] &
          1 << (iVar1 * 8 | uVar2 * 0x20000000 + iVar1 >> 0x1d) - iVar1) >> 0x1f;
  }
  else if (param_3 < -199) {
    (flatRuntime2->flatRuntimeBase).m_lastResult =
         (int)(short)Game.game.m_caravanWorkArr[0].m_artifacts[param_3 + 0x1e];
  }
  else {
    switch(param_3) {
    case -0x7a:
      uVar5 = 1;
      if (Game.game.m_gameWork.m_languageId == '\x03') {
        uVar5 = 6;
      }
      else if (Game.game.m_gameWork.m_languageId < 3) {
        if (Game.game.m_gameWork.m_languageId == '\x01') {
          uVar5 = 3;
        }
        else if (Game.game.m_gameWork.m_languageId == '\0') {
          uVar5 = 1;
        }
        else {
          uVar5 = 5;
        }
      }
      else if (Game.game.m_gameWork.m_languageId == '\x05') {
        uVar5 = 7;
      }
      else if (Game.game.m_gameWork.m_languageId < 5) {
        uVar5 = 4;
      }
      (flatRuntime2->flatRuntimeBase).m_lastResult = uVar5;
      break;
    case -0x78:
      (flatRuntime2->flatRuntimeBase).m_lastResult = (uint)Game.game.m_gameWork.m_gameOverFlag;
      break;
    case -0x76:
      (flatRuntime2->flatRuntimeBase).m_lastResult = (uint)Game.game.m_gameWork.m_menuStageMode;
      break;
    case -0x73:
    case -0x72:
    case -0x71:
    case -0x70:
    case -0x6f:
    case -0x6e:
    case -0x6d:
    case -0x6c:
      if (*(int *)(PartMng.m_usbEdit + param_3 * 0xc30 + 0x190c) == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = (uint)*(ushort *)(PartMng.m_usbEdit + param_3 * 0xc30 + 0x157c);
      }
      (flatRuntime2->flatRuntimeBase).m_lastResult = uVar2;
      break;
    case -0x6b:
    case -0x6a:
    case -0x69:
    case -0x68:
    case -0x67:
      (flatRuntime2->flatRuntimeBase).m_lastResult =
           *(uint32_t *)(Game.game.m_gameWork.m_eventWork + param_3 * 2 + 0x50);
      break;
    case -0x66:
      (flatRuntime2->flatRuntimeBase).m_lastResult = Game.game.m_gameWork.m_chaliceElement;
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
      (flatRuntime2->flatRuntimeBase).m_lastResult =
           *(uint32_t *)(Game.game.m_gameWork.m_linkTable[0][5][3] + param_3 * 4);
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
      (flatRuntime2->flatRuntimeBase).m_lastResult =
           *(uint32_t *)(Game.game.m_gameWork.m_linkTable[0][3][4] + param_3 * 4);
      break;
    case -0x47:
    case -0x46:
    case -0x45:
    case -0x44:
      (flatRuntime2->flatRuntimeBase).m_lastResult =
           *(uint32_t *)(Game.game.m_gameWork.m_linkTable[0][2][2] + param_3 * 4 + 4);
      break;
    case -0x43:
      (flatRuntime2->flatRuntimeBase).m_lastResult = Game.game.m_gameWork.m_frameCounter;
      break;
    case -0x42:
      (flatRuntime2->flatRuntimeBase).m_lastResult = Game.game.m_gameWork.m_scriptGlobalTime;
      break;
    case -0x41:
      (flatRuntime2->flatRuntimeBase).m_lastResult = Game.game.m_gameWork.m_timerA;
      break;
    case -0x40:
      (flatRuntime2->flatRuntimeBase).m_lastResult = Game.game.m_gameWork._8_4_;
    }
  }
  return &(flatRuntime2->flatRuntimeBase).m_lastResult;
}

