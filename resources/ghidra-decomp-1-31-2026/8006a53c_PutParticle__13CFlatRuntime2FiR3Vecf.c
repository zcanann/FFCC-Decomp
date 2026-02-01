// Function: PutParticle__13CFlatRuntime2FiR3Vecf
// Entry: 8006a53c
// Size: 552 bytes

/* WARNING: Removing unreachable block (ram,0x8006a740) */
/* WARNING: Removing unreachable block (ram,0x8006a54c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void PutParticle__13CFlatRuntime2FiR3Vecf
               (double param_1,int param_2,uint param_3,undefined4 *param_4)

{
  float fVar1;
  undefined auStack_6b [3];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
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
  
  fVar1 = FLOAT_80330140;
  local_58 = 0xffffffff;
  local_68 = 0xffffffff;
  local_60 = 0;
  local_64 = CONCAT12(1,local_64._2_2_) & 0xffff00ff;
  local_5c = 0x1e;
  local_54 = 0;
  local_50 = 0;
  *(undefined4 *)(param_2 + 0x16cc) = 0;
  *(undefined4 *)(param_2 + 0x16d0) = 0;
  *(undefined4 *)(param_2 + 0x16d4) = 0;
  *(undefined4 *)(param_2 + 0x16d8) = 0;
  *(undefined4 *)(param_2 + 0x16dc) = 0;
  *(undefined4 *)(param_2 + 0x16e0) = 0;
  *(undefined4 *)(param_2 + 0x16e4) = 0;
  *(undefined4 *)(param_2 + 0x16e8) = 0;
  *(undefined4 *)(param_2 + 0x16ec) = 0;
  *(float *)(param_2 + 0x16f0) = fVar1;
  *(float *)(param_2 + 0x16f4) = fVar1;
  *(undefined *)(param_2 + 0x16f8) = 0;
  __copy(param_2 + 0x16f9,auStack_6b,3);
  *(undefined4 *)(param_2 + 0x16fc) = local_68;
  fVar1 = FLOAT_80330144;
  *(uint *)(param_2 + 0x1700) = local_64;
  *(undefined4 *)(param_2 + 0x1704) = local_60;
  *(undefined4 *)(param_2 + 0x1708) = local_5c;
  *(undefined4 *)(param_2 + 0x170c) = local_58;
  *(undefined4 *)(param_2 + 0x1710) = local_54;
  *(undefined4 *)(param_2 + 0x1714) = local_50;
  *(undefined4 *)(param_2 + 0x1718) = local_4c;
  *(undefined4 *)(param_2 + 0x171c) = local_48;
  *(undefined4 *)(param_2 + 0x1720) = local_44;
  *(undefined4 *)(param_2 + 0x1724) = local_40;
  *(undefined4 *)(param_2 + 0x1728) = local_3c;
  *(undefined4 *)(param_2 + 0x172c) = local_38;
  *(undefined4 *)(param_2 + 0x1730) = local_34;
  *(undefined4 *)(param_2 + 0x1734) = local_30;
  *(undefined *)(param_2 + 0x16f8) = 1;
  *(int *)(param_2 + 0x1738) = (int)param_3 >> 8;
  *(undefined4 *)(param_2 + 0x16dc) = 0;
  *(uint *)(param_2 + 0x173c) = param_3 & 0xff;
  *(undefined4 *)(param_2 + 0x1740) = *param_4;
  *(undefined4 *)(param_2 + 0x1744) = param_4[1];
  *(undefined4 *)(param_2 + 0x1748) = param_4[2];
  *(float *)(param_2 + 0x1750) = fVar1;
  *(int *)(param_2 + 0x16cc) = param_2 + 0x1740;
  *(int *)(param_2 + 0x16d0) = param_2 + 0x174c;
  *(float *)(param_2 + 0x1760) = (float)param_1;
  *(float *)(param_2 + 0x175c) = (float)param_1;
  *(float *)(param_2 + 0x1758) = (float)param_1;
  *(int *)(param_2 + 0x16d4) = param_2 + 0x1758;
  pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
            (&PartMng,*(undefined4 *)(param_2 + 0x1738),*(undefined4 *)(param_2 + 0x173c),
             param_2 + 0x16cc,1);
  return;
}

