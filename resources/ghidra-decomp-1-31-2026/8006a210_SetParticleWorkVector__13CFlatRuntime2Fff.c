// Function: SetParticleWorkVector__13CFlatRuntime2Fff
// Entry: 8006a210
// Size: 200 bytes

/* WARNING: Removing unreachable block (ram,0x8006a2bc) */
/* WARNING: Removing unreachable block (ram,0x8006a2b4) */
/* WARNING: Removing unreachable block (ram,0x8006a2ac) */
/* WARNING: Removing unreachable block (ram,0x8006a230) */
/* WARNING: Removing unreachable block (ram,0x8006a228) */
/* WARNING: Removing unreachable block (ram,0x8006a220) */

void SetParticleWorkVector__13CFlatRuntime2Fff
               (undefined8 param_1,undefined8 param_2,CFlatRuntime2 *flatRuntime2)

{
  double dVar1;
  double dVar2;
  
  dVar1 = (double)cos(param_2);
  dVar2 = (double)(float)dVar1;
  dVar1 = (double)sin(param_1);
  *(float *)&flatRuntime2->field_0x1764 =
       (float)((double)(float)dVar1 * dVar2 + (double)*(float *)&flatRuntime2->field_0x1740);
  dVar1 = (double)sin(param_2);
  *(float *)&flatRuntime2->field_0x1768 = *(float *)&flatRuntime2->field_0x1744 + (float)dVar1;
  dVar1 = (double)cos(param_2);
  dVar2 = (double)(float)dVar1;
  dVar1 = (double)cos(param_1);
  *(float *)&flatRuntime2->field_0x176c =
       (float)((double)(float)dVar1 * dVar2 + (double)*(float *)&flatRuntime2->field_0x1748);
  *(undefined **)&flatRuntime2->field_0x16d8 = &flatRuntime2->field_0x1764;
  return;
}

