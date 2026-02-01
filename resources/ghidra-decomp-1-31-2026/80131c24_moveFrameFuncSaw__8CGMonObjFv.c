// Function: moveFrameFuncSaw__8CGMonObjFv
// Entry: 80131c24
// Size: 224 bytes

/* WARNING: Removing unreachable block (ram,0x80131ce4) */
/* WARNING: Removing unreachable block (ram,0x80131c34) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveFrameFuncSaw__8CGMonObjFv(CGMonObj *gMonObj)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar4 = (double)sin((double)(float)SoundBuffer._1264_4_);
  dVar6 = (double)(FLOAT_80331d1c * (FLOAT_80331d18 + (float)dVar4) + FLOAT_80331d30);
  dVar4 = (double)sin((double)(float)SoundBuffer._1260_4_);
  *(float *)&gMonObj->field_0x718 = (float)(dVar6 * (double)(FLOAT_80331dac * (float)dVar4));
  dVar4 = (double)cos((double)(float)SoundBuffer._1260_4_);
  fVar3 = FLOAT_80331db4;
  fVar2 = FLOAT_80331db0;
  fVar1 = FLOAT_80331d60;
  dVar5 = (double)FLOAT_80331d30;
  *(float *)&gMonObj->field_0x720 = (float)(dVar6 * (double)(FLOAT_80331d84 * (float)dVar4));
  SoundBuffer._1260_4_ =
       (float)SoundBuffer._1260_4_ + fVar2 * (float)(dVar5 - (double)(float)(dVar6 - dVar5)) + fVar1
  ;
  SoundBuffer._1264_4_ = (float)SoundBuffer._1264_4_ + fVar3;
  return;
}

