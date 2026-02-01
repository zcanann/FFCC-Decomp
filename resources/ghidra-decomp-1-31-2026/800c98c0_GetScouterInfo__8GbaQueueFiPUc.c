// Function: GetScouterInfo__8GbaQueueFiPUc
// Entry: 800c98c0
// Size: 816 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 GetScouterInfo__8GbaQueueFiPUc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  undefined2 uVar1;
  ushort uVar2;
  short sVar3;
  OSSemaphore *pOVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined local_218;
  undefined uStack_217;
  char local_214 [4];
  undefined2 local_210 [258];
  
  memset(local_214,0xff,0x200);
  pOVar4 = gbaQueue->accessSemaphores;
  OSWaitSemaphore(pOVar4 + param_2);
  iVar6 = -0x7fde1140;
  pcVar5 = local_214;
  iVar9 = 0x40;
  do {
    *pcVar5 = gbaQueue->field_0xb37;
    if (*pcVar5 != '\0') {
      uVar1 = *(undefined2 *)(*(int *)(iVar6 + 0xc6d0) + 0x1a);
      iVar8 = Game.game.unkCFlatData0[1] + (uint)(byte)gbaQueue->field_0xb37 * 0x1d0;
      uStack_217 = (undefined)uVar1;
      local_218 = (undefined)((ushort)uVar1 >> 8);
      *(ushort *)(pcVar5 + 4) = CONCAT11(uStack_217,local_218);
      if (*(short *)&gbaQueue->field_0xb42 < 1) {
        if (*(short *)&gbaQueue->field_0xb40 < 1) {
          pcVar5[6] = '\0';
          pcVar5[7] = '\0';
        }
        else if (((int)*(short *)&gbaQueue->field_0xb40 & 0xc000U) == 0x4000) {
          pcVar5[6] = '\0';
          pcVar5[7] = '\0';
        }
        else {
          *(ushort *)(pcVar5 + 6) = CONCAT11(gbaQueue->field_0xb41,gbaQueue->field_0xb40);
        }
      }
      else {
        pcVar5[6] = -1;
        pcVar5[7] = -1;
      }
      uVar2 = *(ushort *)(iVar8 + 0x10e);
      if ((uVar2 & 5) == 5) {
        pcVar5[1] = '\0';
      }
      else if ((uVar2 & 4) == 0) {
        if ((uVar2 & 1) == 0) {
          sVar3 = *(short *)(iVar8 + 0xf0);
          if (((sVar3 == 0) && (*(short *)(iVar8 + 0xf2) == 0)) && (*(short *)(iVar8 + 0xf4) == 0))
          {
            pcVar5[1] = '\x03';
          }
          else if (((sVar3 == 3) && (*(short *)(iVar8 + 0xf2) == 3)) &&
                  (*(short *)(iVar8 + 0xf4) == 3)) {
            if (*(short *)(iVar8 + 0xc) == 0x10) {
              pcVar5[1] = '\x0e';
            }
            else {
              pcVar5[1] = '\x04';
            }
          }
          else {
            if (sVar3 == 0) {
              pcVar5[1] = '\x05';
            }
            uVar7 = (uint)(sVar3 == 0);
            if ((*(short *)(iVar8 + 0xf0) == 3) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\x06';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf2) == 0) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\a';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf2) == 3) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\b';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf4) == 0) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\t';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf4) == 3) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\n';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf6) == 0) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\v';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xf8) == 0) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\f';
              uVar7 = uVar7 + 1;
            }
            if ((*(short *)(iVar8 + 0xfa) == 3) && (uVar7 < 3)) {
              pcVar5[uVar7 + 1] = '\r';
            }
          }
        }
        else {
          pcVar5[1] = '\x02';
        }
      }
      else {
        pcVar5[1] = '\x01';
      }
    }
    gbaQueue = (GbaQueue *)&gbaQueue->accessSemaphores[1].queue.tail;
    pcVar5 = pcVar5 + 8;
    iVar6 = iVar6 + 4;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  OSSignalSemaphore(pOVar4 + param_2);
  memcpy(param_3,local_214,0x200);
  return 0x200;
}

