// Function: pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
// Entry: 8005810c
// Size: 60 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
          (CPartMng *partMng,undefined4 pdtSlotIndex,undefined4 param_3,
          PPPCREATEPARAM *pppCreateParam,undefined4 param_5)

{
  undefined4 uVar1;
  
  if (PartPcs.m_usbStreamData.m_disableShokiDraw == '\0') {
    uVar1 = pppCreate0__8CPartMngFiiP14PPPCREATEPARAMi
                      (partMng,pdtSlotIndex,param_3,pppCreateParam,param_5);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

