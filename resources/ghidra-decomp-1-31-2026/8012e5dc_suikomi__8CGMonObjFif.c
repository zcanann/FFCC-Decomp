// Function: suikomi__8CGMonObjFif
// Entry: 8012e5dc
// Size: 992 bytes

/* WARNING: Removing unreachable block (ram,0x8012e9a0) */
/* WARNING: Removing unreachable block (ram,0x8012e5ec) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void suikomi__8CGMonObjFif(double param_1,CGCharaObj *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  uint32_t uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  
  if ((param_2->gPrgObj).m_stateFrame == 0) {
    playSe3D__8CGPrgObjFiiiiP3Vec(&param_2->gPrgObj,0xdec0,0x32,0x1c2,0,0);
    iVar8 = 0;
    iVar9 = -0x7fde1140;
    do {
      iVar7 = *(int *)(iVar9 + 0xc5b0);
      if (iVar7 != 0) {
        ResetParticleWork__13CFlatRuntime2Fii
                  ((CFlatRuntime2 *)&CFlat,0x26,*(undefined4 *)&param_2->field_0x58c);
        SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                  ((CFlatRuntime2 *)&CFlat,param_2);
        SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                  ((CFlatRuntime2 *)&CFlat,iVar7);
        PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      }
      iVar8 = iVar8 + 1;
      iVar9 = iVar9 + 4;
    } while (iVar8 < 4);
  }
  if ((param_2->gPrgObj).m_stateFrame <= param_3) {
    iVar8 = -0x7fde1140;
    iVar9 = 4;
    do {
      iVar7 = *(int *)(iVar8 + 0xc5b0);
      if (iVar7 != 0) {
        fVar2 = (param_2->gPrgObj).object.m_worldPosition.x - *(float *)(iVar7 + 0x15c);
        fVar1 = (float)(param_1 +
                       (double)((param_2->gPrgObj).object.m_worldPosition.z -
                               *(float *)(iVar7 + 0x164)));
        fVar3 = fVar2 * fVar2 + fVar1 * fVar1;
        dVar11 = (double)fVar3;
        if (dVar11 <= (double)FLOAT_80331cf8) {
          if (DOUBLE_80331d10 <= dVar11) {
            uVar4 = (uint)fVar3 & 0x7f800000;
            if (uVar4 == 0x7f800000) {
              if (((uint)fVar3 & 0x7fffff) == 0) {
                iVar6 = 2;
              }
              else {
                iVar6 = 1;
              }
            }
            else if ((uVar4 < 0x7f800000) && (uVar4 == 0)) {
              if (((uint)fVar3 & 0x7fffff) == 0) {
                iVar6 = 3;
              }
              else {
                iVar6 = 5;
              }
            }
            else {
              iVar6 = 4;
            }
            if (iVar6 == 1) {
              dVar11 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar11 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar10 = 1.0 / SQRT(dVar11);
          dVar10 = DOUBLE_80331d00 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08);
          dVar10 = DOUBLE_80331d00 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08);
          dVar11 = (double)(float)(dVar11 * DOUBLE_80331d00 * dVar10 *
                                            -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08));
        }
        if ((double)FLOAT_80331cf8 < dVar11) {
          fVar3 = (float)((double)FLOAT_80331d18 / dVar11) *
                  FLOAT_80331d1c * (float)(dVar11 / (double)FLOAT_80331d20);
          *(float *)(iVar7 + 0x104) = *(float *)(iVar7 + 0x104) + fVar2 * fVar3;
          *(float *)(iVar7 + 0x10c) = *(float *)(iVar7 + 0x10c) + fVar1 * fVar3;
        }
      }
      uVar5 = Game.game.unk_flat3_0xc7d0;
      iVar8 = iVar8 + 4;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    if ((Game.game.unk_flat3_0xc7d0 != 0) && (*(int *)(Game.game.unk_flat3_0xc7d0 + 0x550) == 0)) {
      fVar2 = (param_2->gPrgObj).object.m_worldPosition.x -
              *(float *)(Game.game.unk_flat3_0xc7d0 + 0x15c);
      fVar1 = (float)(param_1 +
                     (double)((param_2->gPrgObj).object.m_worldPosition.z -
                             *(float *)(Game.game.unk_flat3_0xc7d0 + 0x164)));
      fVar3 = fVar2 * fVar2 + fVar1 * fVar1;
      dVar11 = (double)fVar3;
      if (dVar11 <= (double)FLOAT_80331cf8) {
        if (DOUBLE_80331d10 <= dVar11) {
          uVar4 = (uint)fVar3 & 0x7f800000;
          if (uVar4 == 0x7f800000) {
            if (((uint)fVar3 & 0x7fffff) == 0) {
              iVar8 = 2;
            }
            else {
              iVar8 = 1;
            }
          }
          else if ((uVar4 < 0x7f800000) && (uVar4 == 0)) {
            if (((uint)fVar3 & 0x7fffff) == 0) {
              iVar8 = 3;
            }
            else {
              iVar8 = 5;
            }
          }
          else {
            iVar8 = 4;
          }
          if (iVar8 == 1) {
            dVar11 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar11 = (double)DAT_8032ec20;
        }
      }
      else {
        dVar10 = 1.0 / SQRT(dVar11);
        dVar10 = DOUBLE_80331d00 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08);
        dVar10 = DOUBLE_80331d00 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08);
        dVar11 = (double)(float)(dVar11 * DOUBLE_80331d00 * dVar10 *
                                          -(dVar11 * dVar10 * dVar10 - DOUBLE_80331d08));
      }
      if ((double)FLOAT_80331cf8 < dVar11) {
        fVar3 = (float)((double)FLOAT_80331d18 / dVar11) *
                FLOAT_80331d1c * (float)(dVar11 / (double)FLOAT_80331d20);
        *(float *)(Game.game.unk_flat3_0xc7d0 + 0x104) =
             *(float *)(Game.game.unk_flat3_0xc7d0 + 0x104) + fVar2 * fVar3;
        *(float *)(uVar5 + 0x10c) = *(float *)(uVar5 + 0x10c) + fVar1 * fVar3;
      }
    }
    if ((param_2->gPrgObj).m_stateFrame == param_3) {
      endPSlotBit__10CGCharaObjFi(param_2,0x400);
    }
  }
  _statAttack__10CGCharaObjFv(param_2);
  return;
}

