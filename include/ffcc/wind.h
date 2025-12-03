#ifndef _FFCC_PPP_WIND_H_
#define _FFCC_PPP_WIND_H_

struct Vec;

class CWind
{
public:
    void ClearAll();
    void Frame();
    void Draw();
    void Calc(Vec *, const Vec *, int);
    void searchFreeObj();
    void getObj(int);
    void AddAmbient(float, float);
    void AddDiffuse(const Vec *, float, float, float);
    void AddSphere(const Vec *, float, float, int);
    void ChangePower(int, float);
};

#endif // _FFCC_PPP_WIND_H_
