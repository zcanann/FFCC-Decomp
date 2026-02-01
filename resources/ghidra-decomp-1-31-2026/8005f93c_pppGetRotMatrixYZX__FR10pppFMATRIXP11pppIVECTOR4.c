// Function: pppGetRotMatrixYZX__FR10pppFMATRIXP11pppIVECTOR4
// Entry: 8005f93c
// Size: 120 bytes

void pppGetRotMatrixYZX__FR10pppFMATRIXP11pppIVECTOR4(pppFMATRIX *pppFMtx,pppIVECTOR4 *pppIVector4)

{
  undefined4 angle;
  undefined4 angle_00;
  undefined4 angle_01;
  pppFMATRIX pStack_c8;
  Mtx MStack_98;
  pppFMATRIX pStack_68;
  pppFMATRIX pStack_38;
  
  angle._0_2_ = pppIVector4->x;
  angle._2_2_ = pppIVector4->y;
  pppGetRotMatrixX__FR10pppFMATRIXl(&pStack_38,angle);
  angle_00._0_2_ = pppIVector4[1].x;
  angle_00._2_2_ = pppIVector4[1].y;
  pppGetRotMatrixZ__FR10pppFMATRIXl(&pStack_68,angle_00);
  PSMTXConcat(&pStack_68,&pStack_38,&MStack_98);
  angle_01._0_2_ = pppIVector4->z;
  angle_01._2_2_ = pppIVector4->w;
  pppGetRotMatrixY__FR10pppFMATRIXl(&pStack_c8,angle_01);
  PSMTXConcat(&pStack_c8,&MStack_98,pppFMtx);
  return;
}

