// Function: GetNextOrder__7CSystemFPQ27CSystem6COrder
// Entry: 80021510
// Size: 32 bytes

COrder * GetNextOrder__7CSystemFPQ27CSystem6COrder(CSystem *system,COrder *order)

{
  if (order->mNext == (COrder *)&(system->m_stopwatch).total) {
    return (COrder *)0x0;
  }
  return order->mNext;
}

