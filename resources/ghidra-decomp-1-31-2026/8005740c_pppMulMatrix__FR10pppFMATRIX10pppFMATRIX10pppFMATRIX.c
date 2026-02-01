// Function: pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX
// Entry: 8005740c
// Size: 52 bytes

void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX
               (pppFMATRIX *ab,pppFMATRIX *a,pppFMATRIX *b)

{
  PSMTXConcat(a,b,ab);
  return;
}

