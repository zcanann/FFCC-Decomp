// Function: pppConstructLaser
// Entry: 801766ec
// Size: 336 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructLaser(pppLaser *pppLaser,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  undefined4 local_28;
  int local_24;
  Vec VStack_20;
  Vec local_14;
  
  fVar1 = FLOAT_80333428;
  dVar4 = (double)FLOAT_8033345c;
  pfVar3 = (float *)((int)(&pppLaser->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  *pfVar3 = FLOAT_80333428;
  pfVar3[6] = fVar1;
  pfVar3[5] = fVar1;
  pfVar3[4] = fVar1;
  pfVar3[3] = fVar1;
  pfVar3[2] = fVar1;
  pfVar3[1] = fVar1;
  pfVar3[7] = 0.0;
  pfVar3[10] = fVar1;
  pfVar3[9] = fVar1;
  pfVar3[8] = fVar1;
  *(undefined *)(pfVar3 + 0xb) = 0;
  *(undefined *)((int)pfVar3 + 0x2d) = 0;
  *(undefined *)((int)pfVar3 + 0x2e) = 0;
  *(undefined2 *)(pfVar3 + 0xc) = 0;
  *(undefined2 *)(pfVar3 + 0xd) = 0;
  *(undefined2 *)((int)pfVar3 + 0x32) = 0;
  dVar4 = (double)RandF__5CMathFf(dVar4,&Math);
  pfVar3[0xe] = (float)dVar4;
  *(undefined *)(pfVar3 + 0x13) = 1;
  iVar2 = GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi
                    (&Game.game,&pppMngStPtr->m_hitParams,&local_24,&local_28);
  if (iVar2 == 0) {
    pfVar3[0xf] = FLOAT_80333448;
    pppMngStPtr->m_endRequested = '\x01';
    pppStopSe__FP9_pppMngStP7PPPSEST(pppMngStPtr,&pppMngStPtr->m_soundEffectData);
  }
  else {
    GetTargetCursor__5CGameFiR3VecR3Vec(&Game.game,local_28,(Vec *)(pfVar3 + 0x10),&VStack_20);
    iVar2 = GetPartyObj__5CGameFi(&Game.game,local_28);
    local_14.x = *(float *)(iVar2 + 0x15c);
    local_14.y = *(float *)(iVar2 + 0x160);
    local_14.z = *(float *)(iVar2 + 0x164);
    if (local_24 == 0x200) {
      dVar4 = (double)PSVECDistance((Vec *)(pfVar3 + 0x10),&local_14);
      pfVar3[0xf] = (float)dVar4;
    }
    else {
      pfVar3[0xf] = FLOAT_80333448;
    }
  }
  return;
}

