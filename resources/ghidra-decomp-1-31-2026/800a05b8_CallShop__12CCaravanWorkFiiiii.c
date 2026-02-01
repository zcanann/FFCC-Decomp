// Function: CallShop__12CCaravanWorkFiiiii
// Entry: 800a05b8
// Size: 112 bytes

void CallShop__12CCaravanWorkFiiiii
               (CCaravanWork *caravanWork,int param_2,int param_3,int param_4,int param_5,
               int param_6)

{
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_2 == 0) || (param_2 == 1)) {
    caravanWork->m_shopRequestState = '\0';
  }
  local_18 = param_2;
  local_14 = param_3;
  local_10 = param_4;
  local_c = param_5;
  local_8 = param_6;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,(caravanWork->gObjWork).m_ownerObj,2,0x12,5,&local_18,(CStack *)0x0);
  return;
}

