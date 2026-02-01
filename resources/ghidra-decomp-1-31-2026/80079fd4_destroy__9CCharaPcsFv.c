// Function: destroy__9CCharaPcsFv
// Entry: 80079fd4
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void destroy__9CCharaPcsFv(CCharaPcs *param_1)

{
  Reset__9CCharaPcsFQ29CCharaPcs5RESET(param_1,1);
  DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs,0);
  DAT_8032edc0 = 0;
  if (*(int *)&param_1->field_0x4c != 0) {
    __dt__Q29CCharaPcs7CHandleFv(*(int *)&param_1->field_0x4c,1);
    *(undefined4 *)&param_1->field_0x4c = 0;
  }
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xcc);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xd0);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xd8);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xdc);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xe0);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)&param_1->field_0xd4);
  Destroy__6CCharaFv(&Chara);
  return;
}

