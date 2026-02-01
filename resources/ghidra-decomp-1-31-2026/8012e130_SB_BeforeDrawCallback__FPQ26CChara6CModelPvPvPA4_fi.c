// Function: SB_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi
// Entry: 8012e130
// Size: 296 bytes

void SB_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi(void)

{
  undefined4 *puVar1;
  double dVar2;
  undefined auStack_58 [4];
  undefined4 local_54;
  Vec local_50;
  undefined auStack_44 [68];
  
  local_50.x = (float)CameraPcs._236_4_ - (FLOAT_80331ce8 + (float)CameraPcs._224_4_);
  local_50.y = (float)CameraPcs._240_4_ - (FLOAT_80331ce8 + (float)CameraPcs._228_4_);
  local_50.z = (float)CameraPcs._244_4_ - (FLOAT_80331ce8 + (float)CameraPcs._232_4_);
  PSVECNormalize(&local_50,&local_50);
  GXInitSpecularDirHA((double)local_50.x,(double)local_50.y,(double)local_50.z,
                      (double)FLOAT_80331cc4,(double)FLOAT_80331cd0,(double)FLOAT_80331cc4,
                      auStack_44);
  dVar2 = (double)FLOAT_80331cc4;
  GXInitLightAttn(dVar2,dVar2,(double)FLOAT_80331cd0,(double)FLOAT_80331cec,dVar2,
                  (double)FLOAT_80331cf0,auStack_44);
  puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_58,0xff,0xff,0xff,0xff);
  local_54 = *puVar1;
  GXInitLightColor(auStack_44,&local_54);
  GXLoadLightObjImm(auStack_44,1);
  GXSetChanCtrl(0,1,0,1,1,2,0);
  GXSetChanCtrl(2,0,0,1,0,0,2);
  return;
}

