#ifndef FFCC_PPP_CONSTANTS_H
#define FFCC_PPP_CONSTANTS_H

extern float ppvSinTbl[];

extern float gPppPointRApRandomAngleRange;
extern float gPppPointRApRandomAngleBias;
extern const float gPppPointRApSpinScale[2];

extern const float gPppScaleLoopAutoZero;

extern const float gPppYmMoveParabolaYOffsetStep;
extern const float gPppYmMoveParabolaZero;
extern const float gPppYmMoveParabolaAngleScale;
extern const float gPppYmMoveParabolaAngleDivisor;
extern const float gPppYmMoveParabolaGravityScale;

extern const float gPppParMoveMatrixZero;
extern const float gPppParMoveMatrixOne;

extern float gPppYmLookOnZero;
extern float gPppYmLookOnOne;

extern float kPppZero;
extern float kPppOne;
extern const float kPppGetRotMatrixXOne;
extern const float kPppGetRotMatrixXZero;
extern const float kPppGetRotMatrixYZero;
extern const float kPppGetRotMatrixYOne;
extern const float kPppGetRotMatrixZZero;
extern const float kPppGetRotMatrixZOne;
extern const float kPppAcceleZero;
extern float kPppBreathModelZero;
extern const float kPppChangeTexInit[2];
extern const float kPppKeLnsZero[2];
extern const float kPppMoveZero[2];
extern float kPppSclAcceleZero;
extern float kPppSclMoveZero;
extern const float kPppVtMimeZero[2];

extern float kPppSRandCVSingleSampleScale;
extern float kPppSRandDownCVDualSampleScale;
extern float kPppSRandDownFVDualSampleScale;
extern float kPppSRandDownHCVDualSampleScale;
extern float kPppSRandFVSingleSampleScale;
extern float kPppSRandHCVSingleSampleScale;
extern float kPppSRandUpCVDualSampleScale;
extern float kPppSRandUpFVDualSampleScale;
extern float kPppSRandUpHCVDualSampleScale;

#endif
