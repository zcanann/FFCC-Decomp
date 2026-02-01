// Function: pppConstructYmMoveParabola
// Entry: 800d4558
// Size: 292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMoveParabola(pppYmMoveParabola *pppYmMoveParabola,UnkC *param_2)

{
  _pppMngSt *p_Var1;
  float fVar2;
  float *pfVar3;
  Vec local_48;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  Vec local_24;
  float local_18;
  float local_14;
  float local_10;
  
  fVar2 = FLOAT_80330e1c;
  p_Var1 = pppMngStPtr;
  pfVar3 = (float *)((int)(&pppYmMoveParabola->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  pfVar3[2] = FLOAT_80330e1c;
  pfVar3[1] = fVar2;
  *pfVar3 = fVar2;
  *(undefined2 *)(pfVar3 + 3) = 1;
  if (Game.game.m_currentSceneId == 7) {
    local_24.x = (p_Var1->m_savedPosition).x;
    local_24.y = (p_Var1->m_savedPosition).y;
    local_24.z = (p_Var1->m_savedPosition).z;
    pppCopyVector__FR3Vec3Vec((Vec *)(pfVar3 + 4),&local_24);
    local_3c = (pppMngStPtr->m_matrix).value[0][3];
    local_38 = (pppMngStPtr->m_matrix).value[1][3];
    local_34 = (pppMngStPtr->m_matrix).value[2][3];
    local_30 = pfVar3[4];
    local_2c = pfVar3[5];
    local_28 = pfVar3[6];
    local_18 = local_3c;
    local_14 = local_38;
    local_10 = local_34;
    pppAddVector__FR3Vec3Vec3Vec(pfVar3 + 4,&local_30,&local_3c);
    local_48.x = pfVar3[4];
    local_48.y = pfVar3[5];
    local_48.z = pfVar3[6];
    pppCopyVector__FR3Vec3Vec(&p_Var1->m_paramVec0,&local_48);
    (p_Var1->m_paramVec0).x = (p_Var1->m_paramVec0).x + FLOAT_80330e18;
  }
  return;
}

