// Function: Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl
// Entry: 8001d838
// Size: 252 bytes

void Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl
               (CAmemCacheSet *amemCacheSet,undefined4 param_2,CStage *stage,int param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11)

{
  undefined4 uVar1;
  int iVar2;
  
  strcpy();
  *(undefined4 *)&amemCacheSet->field_0x40 = param_8;
  *(undefined4 *)&amemCacheSet->field_0x44 = param_9;
  *(undefined4 *)&amemCacheSet->field_0x48 = param_6;
  *(undefined4 *)&amemCacheSet->field_0x4c = param_7;
  *(undefined4 *)&amemCacheSet->field_0x50 = param_10;
  *(undefined4 *)&amemCacheSet->field_0x54 = param_11;
  amemCacheSet->m_stage = stage;
  *(int *)&amemCacheSet->field_0x24 = param_4;
  if (param_4 == 0) {
    *(undefined4 *)&amemCacheSet->field_0x3c = 0;
    *(undefined4 *)&amemCacheSet->field_0x30 = 0;
    *(undefined4 *)&amemCacheSet->field_0x28 = 0;
    *(undefined4 *)&amemCacheSet->field_0x2c = 0;
    *(undefined4 *)&amemCacheSet->field_0x38 = 0;
    *(undefined4 *)&amemCacheSet->field_0x58 = 0;
  }
  else {
    *(undefined4 *)&amemCacheSet->field_0x3c = param_5;
    uVar1 = *(undefined4 *)(param_4 + 8);
    *(undefined4 *)&amemCacheSet->field_0x28 = uVar1;
    *(undefined4 *)&amemCacheSet->field_0x30 = uVar1;
    *(undefined4 *)&amemCacheSet->field_0x2c = *(undefined4 *)(param_4 + 0xc);
    *(undefined4 *)&amemCacheSet->field_0x38 = 0;
    iVar2 = *(int *)&amemCacheSet->field_0x3c;
    uVar1 = alloc__Q27CMemory6CStageFUlPcUli
                      (stage,iVar2 * 0x1c + 0x10,s_memory_cpp_801d6690,0x787,0);
    uVar1 = __construct_new_array(uVar1,__ct__10CAmemCacheFv,__dt__10CAmemCacheFv,0x1c,iVar2);
    *(undefined4 *)&amemCacheSet->field_0x58 = uVar1;
  }
  return;
}

