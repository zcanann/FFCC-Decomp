// Function: ReplyLetter__8GbaQueueFi
// Entry: 800cd1cc
// Size: 272 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ReplyLetter__8GbaQueueFi(GbaQueue *gbaQueue,int param_2)

{
  uint32_t *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte local_418;
  byte local_417;
  char local_416;
  byte local_415;
  byte local_414;
  byte local_413;
  byte local_412;
  
  GetRecvBuffer__6JoyBusFiPUc(&Joybus,param_2,&local_418);
  uVar4 = 0;
  uVar3 = (uint)local_415 << 0x18 | (uint)local_414 << 0x10 | (uint)local_413 << 8 | (uint)local_412
  ;
  uVar2 = uVar3;
  if (local_416 == '\0') {
    uVar4 = (uint)CONCAT11(local_413,local_412);
    uVar2 = 0;
  }
  puVar1 = Game.game.m_scriptFoodBase + param_2;
  FGLetterReply__12CCaravanWorkFiiii
            ((CCaravanWork *)*puVar1,(uint)local_418,(uint)local_417,uVar4,uVar2);
  ClrRecvBuffer__6JoyBusFi(&Joybus,param_2);
  SendResult__6JoyBusFiiii(&Joybus,param_2,0,0x15,0);
  if (local_416 == '\0') {
    if (uVar4 != 0) {
      DeleteItemIdx__12CCaravanWorkFii((CCaravanWork *)*puVar1,(int)uVar3 >> 0x10,1);
    }
  }
  else {
    AddGil__12CCaravanWorkFi((CCaravanWork *)*puVar1,-uVar2);
  }
  return;
}

