// Function: ResetParticleWork__13CFlatRuntime2Fii
// Entry: 8006a350
// Size: 432 bytes

void ResetParticleWork__13CFlatRuntime2Fii
               (CFlatRuntime2 *flatRuntime2,uint param_2,undefined4 param_3)

{
  float fVar1;
  undefined auStack_5b [3];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  fVar1 = FLOAT_80330140;
  local_48 = 0xffffffff;
  local_58 = 0xffffffff;
  local_50 = 0;
  local_54 = CONCAT12(1,local_54._2_2_) & 0xffff00ff;
  local_4c = 0x1e;
  local_44 = 0;
  local_40 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16cc = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d0 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d4 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16dc = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e0 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e4 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16ec = 0;
  *(float *)&flatRuntime2->field_0x16f0 = fVar1;
  *(float *)&flatRuntime2->field_0x16f4 = fVar1;
  flatRuntime2->field_0x16f8 = 0;
  __copy(&flatRuntime2->field_0x16f9,auStack_5b,3);
  *(undefined4 *)&flatRuntime2->field_0x16fc = local_58;
  *(uint *)&flatRuntime2->field_0x1700 = local_54;
  *(undefined4 *)&flatRuntime2->field_0x1704 = local_50;
  *(undefined4 *)&flatRuntime2->field_0x1708 = local_4c;
  *(undefined4 *)&flatRuntime2->field_0x170c = local_48;
  *(undefined4 *)&flatRuntime2->field_0x1710 = local_44;
  *(undefined4 *)&flatRuntime2->field_0x1714 = local_40;
  *(undefined4 *)&flatRuntime2->field_0x1718 = local_3c;
  *(undefined4 *)&flatRuntime2->field_0x171c = local_38;
  *(undefined4 *)&flatRuntime2->field_0x1720 = local_34;
  *(undefined4 *)&flatRuntime2->field_0x1724 = local_30;
  *(undefined4 *)&flatRuntime2->field_0x1728 = local_2c;
  *(undefined4 *)&flatRuntime2->field_0x172c = local_28;
  *(undefined4 *)&flatRuntime2->field_0x1730 = local_24;
  *(undefined4 *)&flatRuntime2->field_0x1734 = local_20;
  flatRuntime2->field_0x16f8 = 1;
  *(int *)&flatRuntime2->field_0x1738 = (int)param_2 >> 8;
  *(undefined4 *)&flatRuntime2->field_0x16dc = param_3;
  *(uint *)&flatRuntime2->field_0x173c = param_2 & 0xff;
  return;
}

