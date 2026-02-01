// Function: pppDestructConstrainCameraForLoc
// Entry: 80167dd4
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructConstrainCameraForLoc
               (pppConstrainCameraForLoc *pppConstrainCameraForLoc,undefined4 *param_2,UnkC *param_3
               )

{
  int iVar1;
  undefined *value;
  
  if (DAT_8032ed70 == 0) {
    value = (undefined *)
            ((int)(&pppConstrainCameraForLoc->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2])
    ;
    iVar1 = GetModelPtr__FP8CGObject((CGObject *)(pppMngStPtr->m_velocity).x);
    *(undefined **)(iVar1 + 0xe4) = value;
    *(undefined4 **)(iVar1 + 0xe8) = param_2;
    *(code **)(iVar1 + 0xec) = CC_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv;
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2[1],&pppConstrainCameraForLoc->field0_0x0,*param_2,value,value + 4,
               value + 8,param_2 + 2,param_2 + 3);
  }
  return;
}

