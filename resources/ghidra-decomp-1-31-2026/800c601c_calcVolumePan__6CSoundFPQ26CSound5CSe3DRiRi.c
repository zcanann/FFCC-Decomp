// Function: calcVolumePan__6CSoundFPQ26CSound5CSe3DRiRi
// Entry: 800c601c
// Size: 780 bytes

/* WARNING: Removing unreachable block (ram,0x800c6300) */
/* WARNING: Removing unreachable block (ram,0x800c602c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcVolumePan__6CSoundFPQ26CSound5CSe3DRiRi(int param_1,int param_2,int *param_3,int *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined auStack_48 [4];
  float local_44;
  Vec local_40 [2];
  
  if (*(char *)(param_2 + 3) < '\0') {
    if ((FLOAT_80330cec == *(float *)(param_2 + 0x10)) &&
       (FLOAT_80330cec == *(float *)(param_2 + 0x14))) {
      *param_3 = 0x7f;
      *param_4 = 0x40;
    }
    else {
      dVar7 = (double)FLOAT_80330cf0;
      if (Game.game.m_gameWork.m_soundOptionFlag != '\0') {
        if ((Game.game.m_gameWork.m_bossArtifactStageIndex == 0xe) ||
           ((Game.game.m_gameWork.m_bossArtifactStageIndex < 0xe &&
            (Game.game.m_gameWork.m_bossArtifactStageIndex == 8)))) {
          dVar7 = (double)FLOAT_80330cf4;
        }
        else {
          dVar7 = (double)FLOAT_80330cf8;
        }
      }
      PSMTXMultVec(&CameraPcs.m_cameraMatrix,(Vec *)(param_2 + 0x18),local_40);
      dVar6 = (double)PSVECSquareDistance((Vec *)&CameraPcs.field_0xd4,(Vec *)(param_2 + 0x18));
      fVar3 = (float)(dVar7 * dVar6);
      fVar1 = (float)(dVar7 * (double)(float)((double)*(float *)(param_2 + 0x14) *
                                             (double)(float)((double)*(float *)(param_2 + 0x14) *
                                                            dVar7)));
      if (fVar1 <= fVar3) {
        *param_3 = 0;
      }
      else {
        fVar2 = (float)(dVar7 * (double)(float)((double)*(float *)(param_2 + 0x10) *
                                               (double)(float)((double)*(float *)(param_2 + 0x10) *
                                                              dVar7)));
        if (fVar2 <= fVar3) {
          *param_3 = 0x7f - (int)(FLOAT_80330ce8 * ((fVar3 - fVar2) / (fVar1 - fVar2)));
        }
        else {
          *param_3 = 0x7f;
        }
      }
      if (Game.game.m_currentMapId == 0x21) {
        iVar4 = (int)(local_40[0].x / FLOAT_80330cfc);
        if (iVar4 < -0x38) {
          iVar5 = -0x38;
        }
        else {
          iVar5 = 0x38;
          if (iVar4 < 0x39) {
            iVar5 = iVar4;
          }
        }
        *param_4 = iVar5 + 0x40;
      }
      else {
        iVar4 = (int)local_40[0].x;
        if (iVar4 < -0x38) {
          iVar5 = -0x38;
        }
        else {
          iVar5 = 0x38;
          if (iVar4 < 0x39) {
            iVar5 = iVar4;
          }
        }
        *param_4 = iVar5 + 0x40;
      }
    }
  }
  else {
    iVar4 = Calc__9CLine((double)*(float *)(param_2 + 0x14),
                         param_1 + *(char *)(param_2 + 3) * 0x1cc + 0x142c,local_40,&local_44,0,
                         auStack_48,0x8026887c);
    if (iVar4 == 0) {
      *param_3 = 0;
      *param_4 = 0x40;
    }
    else {
      PSMTXMultVec(&CameraPcs.m_cameraMatrix,local_40,local_40);
      fVar3 = *(float *)(param_2 + 0x10);
      if (fVar3 <= local_44) {
        *param_3 = 0x7f - (int)(FLOAT_80330ce8 *
                               ((local_44 - fVar3) / (*(float *)(param_2 + 0x14) - fVar3)));
      }
      else {
        *param_3 = 0x7f;
      }
      iVar4 = (int)local_40[0].x;
      if (iVar4 < -0x38) {
        iVar5 = -0x38;
      }
      else {
        iVar5 = 0x38;
        if (iVar4 < 0x39) {
          iVar5 = iVar4;
        }
      }
      *param_4 = iVar5 + 0x40;
    }
  }
  if (*(int *)(param_1 + 0x22b8) < *param_3) {
    *param_3 = *(int *)(param_1 + 0x22b8);
  }
  return;
}

