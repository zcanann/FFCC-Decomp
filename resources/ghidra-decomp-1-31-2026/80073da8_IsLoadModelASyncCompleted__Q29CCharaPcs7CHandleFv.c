// Function: IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv
// Entry: 80073da8
// Size: 20 bytes

uint IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv(CCharaPcsCHandle *handle)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(7 - handle->m_asyncState);
  return uVar1 >> 5 & 0xff;
}

