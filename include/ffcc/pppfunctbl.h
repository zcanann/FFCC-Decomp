#ifndef _FFCC_FUNCTBL_H_
#define _FFCC_FUNCTBL_H_

#include "ffcc/partMng.h"

pppProg* pppGetSysProgTable();

#ifdef FFCC_PPPFUNCTBL_IMPLEMENTATION
#include "ffcc/LocationTitle2.h"
#include "ffcc/pppAccele.h"
#include "ffcc/pppAlignmentScale.h"
#include "ffcc/pppAngAccele.h"
#include "ffcc/pppAngle.h"
#include "ffcc/pppAngMove.h"
#include "ffcc/pppBindOnlyPos.h"
#include "ffcc/pppBlurChara.h"
#include "ffcc/pppBreathModel.h"
#include "ffcc/pppCallBackDistance.h"
#include "ffcc/pppChangeBGColor.h"
#include "ffcc/pppChangeTex.h"
#include "ffcc/pppCharaBreak.h"
#include "ffcc/pppCharaZEnvCtrl.h"
#include "ffcc/pppColAccele.h"
#include "ffcc/pppColMove.h"
#include "ffcc/pppColor.h"
#include "ffcc/pppColum.h"
#include "ffcc/pppConformBGNormal.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/pppCorona.h"
#include "ffcc/pppCrystal.h"
#include "ffcc/pppCrystal2.h"
#include "ffcc/pppDrawMatrix.h"
#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/pppDrawMatrixFrontLnr.h"
#include "ffcc/pppDrawMatrixLoc.h"
#include "ffcc/pppDrawMatrixNoRot.h"
#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppDrawMdlTs.h"
#include "ffcc/pppDrawShape.h"
#include "ffcc/pppDrawShape2.h"
#include "ffcc/pppEmission.h"
#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/pppFilter.h"
#include "ffcc/pppFovAdjustMatrix.h"
#include "ffcc/pppKeDMat.h"
#include "ffcc/pppKeLns.h"
#include "ffcc/pppKeShpTail.h"
#include "ffcc/pppKeShpTail2X.h"
#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/pppLaser.h"
#include "ffcc/pppLensFlare.h"
#include "ffcc/pppLerpPos.h"
#include "ffcc/pppLight.h"
#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppMana2.h"
#include "ffcc/pppMatrixLoc.h"
#include "ffcc/pppMatrixScl.h"
#include "ffcc/pppMatrixXYZ.h"
#include "ffcc/pppMatrixXZY.h"
#include "ffcc/pppMatrixYXZ.h"
#include "ffcc/pppMatrixYZX.h"
#include "ffcc/pppMatrixZXY.h"
#include "ffcc/pppMatrixZYX.h"
#include "ffcc/pppMiasma.h"
#include "ffcc/pppMove.h"
#include "ffcc/pppParHitSph.h"
#include "ffcc/pppParHitSphMat.h"
#include "ffcc/pppParMatrix.h"
#include "ffcc/pppParMoveLine.h"
#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPObjPoint.h"
#include "ffcc/pppPoint.h"
#include "ffcc/pppPointAp.h"
#include "ffcc/pppPointApMtx.h"
#include "ffcc/pppPointRAp.h"
#include "ffcc/pppRain.h"
#include "ffcc/pppRandChar.h"
#include "ffcc/pppRandCV.h"
#include "ffcc/pppRandDownChar.h"
#include "ffcc/pppRandDownCV.h"
#include "ffcc/pppRandDownFloat.h"
#include "ffcc/pppRandDownFV.h"
#include "ffcc/pppRandDownHCV.h"
#include "ffcc/pppRandDownInt.h"
#include "ffcc/pppRandDownIV.h"
#include "ffcc/pppRandDownShort.h"
#include "ffcc/pppRandFloat.h"
#include "ffcc/pppRandFV.h"
#include "ffcc/pppRandHCV.h"
#include "ffcc/pppRandInt.h"
#include "ffcc/pppRandIV.h"
#include "ffcc/pppRandShort.h"
#include "ffcc/pppRandUpChar.h"
#include "ffcc/pppRandUpCV.h"
#include "ffcc/pppRandUpFloat.h"
#include "ffcc/pppRandUpFV.h"
#include "ffcc/pppRandUpHCV.h"
#include "ffcc/pppRandUpInt.h"
#include "ffcc/pppRandUpIV.h"
#include "ffcc/pppRandUpShort.h"
#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/pppScale.h"
#include "ffcc/pppScaleLoopAuto.h"
#include "ffcc/pppSclAccele.h"
#include "ffcc/pppSclMove.h"
#include "ffcc/pppScreenBlur.h"
#include "ffcc/pppScreenBreak.h"
#include "ffcc/pppScreenQuake.h"
#include "ffcc/pppSDrawMatrix.h"
#include "ffcc/pppSpMatrix.h"
#include "ffcc/pppSRandCV.h"
#include "ffcc/pppSRandDownCV.h"
#include "ffcc/pppSRandDownFV.h"
#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/pppSRandFV.h"
#include "ffcc/pppSRandHCV.h"
#include "ffcc/pppSRandUpCV.h"
#include "ffcc/pppSRandUpFV.h"
#include "ffcc/pppSRandUpHCV.h"
#include "ffcc/pppVertexAp.h"
#include "ffcc/pppVertexApAt.h"
#include "ffcc/pppVertexApLc.h"
#include "ffcc/pppVertexApMtx.h"
#include "ffcc/pppVertexAttend.h"
#include "ffcc/pppVtMime.h"
#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/pppWDrawMatrixFront.h"
#include "ffcc/pppWDrawMatrixFrontLoop.h"
#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/pppYmBreath.h"
#include "ffcc/pppYmCallBack.h"
#include "ffcc/pppYmChangeTex.h"
#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/pppYmDeformationShp.h"
#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "ffcc/pppYmLaser.h"
#include "ffcc/pppYmLookOn.h"
#include "ffcc/pppYmMana.h"
#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/pppYmMelt.h"
#include "ffcc/pppYmMiasma.h"
#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppYmTraceMove.h"
#include "ffcc/pppYmTracer.h"
#include "ffcc/pppYmTracer2.h"

#define PPP_FN(fn) ((pppProgAnyCallback)(fn))

struct _pppSysProgTbl
{
    pppProg* m_progs;
};

static pppProg s_pppSysProgTable[159] = {
    {
        (char*)"pppDummyFunc",
        0,
        0,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppAccele",
        0,
        PPP_FN(pppAccele),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAcceleCon),
        PPP_FN(pppAcceleCon),
        0,
        0
    },
    {
        (char*)"pppAngAccele",
        0,
        PPP_FN(pppAngAccele),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAngAcceleCon),
        PPP_FN(pppAngAcceleCon),
        0,
        0
    },
    {
        (char*)"pppAngle",
        0,
        PPP_FN(pppAngle),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAngleCon),
        PPP_FN(pppAngleCon),
        0,
        0
    },
    {
        (char*)"pppAngMove",
        0,
        PPP_FN(pppAngMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAngMoveCon),
        PPP_FN(pppAngMoveCon),
        0,
        0
    },
    {
        (char*)"pppColAccele",
        0,
        PPP_FN(pppColAccele),
        0,
        { 0, 0, 0 },
        PPP_FN(pppColAcceleCon),
        PPP_FN(pppColAcceleCon),
        0,
        0
    },
    {
        (char*)"pppColMove",
        0,
        PPP_FN(pppColMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppColMoveCon),
        PPP_FN(pppColMoveCon),
        0,
        0
    },
    {
        (char*)"pppColor",
        0,
        PPP_FN(pppColor),
        0,
        { 0, 0, 0 },
        PPP_FN(pppColorCon),
        PPP_FN(pppColorCon),
        0,
        0
    },
    {
        (char*)"pppMatrix",
        0,
        PPP_FN(pppMatrixXYZ),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixLoc",
        0,
        PPP_FN(pppMatrixLoc),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixScl",
        0,
        PPP_FN(pppMatrixScl),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixXYZ",
        0,
        PPP_FN(pppMatrixXYZ),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixXZY",
        0,
        PPP_FN(pppMatrixXZY),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixYXZ",
        0,
        PPP_FN(pppMatrixYXZ),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixYZX",
        0,
        PPP_FN(pppMatrixYZX),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixZXY",
        0,
        PPP_FN(pppMatrixZXY),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMatrixZYX",
        0,
        PPP_FN(pppMatrixZYX),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppMove",
        0,
        PPP_FN(pppMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppMoveCon),
        PPP_FN(pppMoveCon),
        0,
        0
    },
    {
        (char*)"pppParMatrix",
        0,
        PPP_FN(pppParMatrix),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppPObjPoint",
        0,
        PPP_FN(pppPObjPoint),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppPoint",
        0,
        PPP_FN(pppPoint),
        0,
        { 0, 0, 0 },
        PPP_FN(pppPointCon),
        PPP_FN(pppPointCon),
        0,
        0
    },
    {
        (char*)"pppPointAp",
        0,
        PPP_FN(pppPointAp),
        0,
        { 0, 0, 0 },
        PPP_FN(pppPointApCon),
        0,
        0,
        0
    },
    {
        (char*)"pppPointRAp",
        0,
        PPP_FN(pppPointRAp),
        0,
        { 0, 0, 0 },
        PPP_FN(pppPointRApCon),
        0,
        0,
        0
    },
    {
        (char*)"pppRandChar",
        0,
        PPP_FN(pppRandChar),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandCV",
        0,
        PPP_FN(pppRandCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownChar",
        0,
        PPP_FN(pppRandDownChar),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownCV",
        0,
        PPP_FN(pppRandDownCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownFloat",
        0,
        PPP_FN(pppRandDownFloat),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownFV",
        0,
        PPP_FN(pppRandDownFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownHCV",
        0,
        PPP_FN(pppRandDownHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownInt",
        0,
        PPP_FN(pppRandDownInt),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownIV",
        0,
        PPP_FN(pppRandDownIV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandDownShort",
        0,
        PPP_FN(pppRandDownShort),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandFloat",
        0,
        PPP_FN(pppRandFloat),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandFV",
        0,
        PPP_FN(pppRandFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandHCV",
        0,
        PPP_FN(pppRandHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandInt",
        0,
        PPP_FN(pppRandInt),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandIV",
        0,
        PPP_FN(pppRandIV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandShort",
        0,
        PPP_FN(pppRandShort),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpChar",
        0,
        PPP_FN(pppRandUpChar),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpCV",
        0,
        PPP_FN(pppRandUpCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpFloat",
        0,
        PPP_FN(pppRandUpFloat),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpFV",
        0,
        PPP_FN(pppRandUpFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpHCV",
        0,
        PPP_FN(pppRandUpHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpInt",
        0,
        PPP_FN(pppRandUpInt),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpIV",
        0,
        PPP_FN(pppRandUpIV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppRandUpShort",
        0,
        PPP_FN(pppRandUpShort),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppScale",
        0,
        PPP_FN(pppScale),
        0,
        { 0, 0, 0 },
        PPP_FN(pppScaleCon),
        PPP_FN(pppScaleCon),
        0,
        0
    },
    {
        (char*)"pppSclAccele",
        0,
        PPP_FN(pppSclAccele),
        0,
        { 0, 0, 0 },
        PPP_FN(pppSclAcceleCon),
        PPP_FN(pppSclAcceleCon),
        0,
        0
    },
    {
        (char*)"pppSclMove",
        0,
        PPP_FN(pppSclMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppSclMoveCon),
        PPP_FN(pppSclMoveCon),
        0,
        0
    },
    {
        (char*)"pppSMatrix",
        0,
        0,
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandCV",
        0,
        PPP_FN(pppSRandCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownCV",
        0,
        PPP_FN(pppSRandDownCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownFV",
        0,
        PPP_FN(pppSRandDownFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandDownHCV",
        0,
        PPP_FN(pppSRandDownHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandFV",
        0,
        PPP_FN(pppSRandFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandHCV",
        0,
        PPP_FN(pppSRandHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpCV",
        0,
        PPP_FN(pppSRandUpCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpFV",
        0,
        PPP_FN(pppSRandUpFV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppSRandUpHCV",
        0,
        PPP_FN(pppSRandUpHCV),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppVertexAp",
        0,
        PPP_FN(pppVertexAp),
        0,
        { 0, 0, 0 },
        PPP_FN(pppVertexApCon),
        0,
        0,
        0
    },
    {
        (char*)"pppVertexApAt",
        0,
        PPP_FN(pppVertexApAt),
        0,
        { 0, 0, 0 },
        PPP_FN(pppVertexApAtCon),
        PPP_FN(pppVertexApAtCon),
        0,
        0
    },
    {
        (char*)"pppVertexApLc",
        0,
        PPP_FN(pppVertexApLc),
        0,
        { 0, 0, 0 },
        PPP_FN(pppVertexApLcCon),
        PPP_FN(pppVertexApLcCon),
        0,
        0
    },
    {
        (char*)"pppVertexAttend",
        0,
        PPP_FN(pppVertexAttend),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppVtMime",
        0,
        PPP_FN(pppVtMime),
        PPP_FN(pppDrawVtMime),
        { 0, 0, 0 },
        PPP_FN(pppVtMimeCon),
        PPP_FN(pppVtMimeCon2),
        0,
        PPP_FN(pppVtMimeDes)
    },
    {
        (char*)"pppDrawMatrix",
        0,
        0,
        PPP_FN(pppDrawMatrix),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixFront",
        0,
        0,
        PPP_FN(pppDrawMatrixFront),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMdl",
        0,
        0,
        PPP_FN(pppDrawMdl),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawShape",
        0,
        PPP_FN(pppCalcShape),
        PPP_FN(pppDrawShape),
        { 0, 0, 0 },
        PPP_FN(pppDrawShapeConstruct),
        PPP_FN(pppDrawShapeConstruct),
        0,
        0
    },
    {
        (char*)"pppRyjMegaBirth",
        0,
        PPP_FN(pppRyjMegaBirth),
        PPP_FN(pppRyjDrawMegaBirth),
        { 0, 0, 0 },
        PPP_FN(pppRyjMegaBirthCon),
        0,
        0,
        PPP_FN(pppRyjMegaBirthDes)
    },
    {
        (char*)"pppRyjMegaBirthModel",
        0,
        PPP_FN(pppRyjMegaBirthModel),
        PPP_FN(pppRyjDrawMegaBirthModel),
        { 0, 0, 0 },
        PPP_FN(pppRyjMegaBirthModelCon),
        0,
        0,
        PPP_FN(pppRyjMegaBirthModelDes)
    },
    {
        (char*)"pppDrawMdlTs",
        0,
        PPP_FN(pppDrawMdlTs),
        PPP_FN(pppDrawDrawMdlTs),
        { 0, 0, 0 },
        PPP_FN(pppDrawMdlTsCon),
        PPP_FN(pppDrawMdlTsCon),
        0,
        0
    },
    {
        (char*)"pppKeShpTail",
        0,
        PPP_FN(pppKeShpTail),
        PPP_FN(pppKeShpTailDraw),
        { 0, 0, 0 },
        PPP_FN(pppKeShpTailCon),
        0,
        0,
        0
    },
    {
        (char*)"pppKeShpTail2X",
        0,
        PPP_FN(pppKeShpTail2X),
        PPP_FN(pppKeShpTail2XDraw),
        { 0, 0, 0 },
        PPP_FN(pppKeShpTail2XCon),
        0,
        0,
        PPP_FN(pppKeShpTail2XDes)
    },
    {
        (char*)"pppKeZCrctShp",
        0,
        0,
        PPP_FN(pppKeZCrctShpDraw),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppKeShpTail3X",
        0,
        PPP_FN(pppKeShpTail3X),
        PPP_FN(pppKeShpTail3XDraw),
        { 0, 0, 0 },
        PPP_FN(pppKeShpTail3XCon),
        0,
        0,
        PPP_FN(pppKeShpTail3XDes)
    },
    {
        (char*)"pppMoveLoop",
        0,
        PPP_FN(pppMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppMoveCon),
        0,
        0,
        0
    },
    {
        (char*)"pppAngMoveLoop",
        0,
        PPP_FN(pppAngMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAngMoveCon),
        0,
        0,
        0
    },
    {
        (char*)"pppSclMoveLoop",
        0,
        PPP_FN(pppSclMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppSclMoveCon),
        0,
        0,
        0
    },
    {
        (char*)"pppPointLoop",
        0,
        PPP_FN(pppPoint),
        0,
        { 0, 0, 0 },
        PPP_FN(pppPointCon),
        0,
        0,
        0
    },
    {
        (char*)"pppAngleLoop",
        0,
        PPP_FN(pppAngle),
        0,
        { 0, 0, 0 },
        PPP_FN(pppAngleCon),
        0,
        0,
        0
    },
    {
        (char*)"pppScaleLoop",
        0,
        PPP_FN(pppScale),
        0,
        { 0, 0, 0 },
        PPP_FN(pppScaleCon),
        0,
        0,
        0
    },
    {
        (char*)"pppColorLoop",
        0,
        PPP_FN(pppColor),
        0,
        { 0, 0, 0 },
        PPP_FN(pppColorCon),
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMdlLoop",
        0,
        PPP_FN(pppDrawMdlTs),
        PPP_FN(pppDrawDrawMdlTs),
        { 0, 0, 0 },
        PPP_FN(pppDrawMdlTsCon),
        0,
        PPP_FN(pppDrawMdlTsCon3),
        0
    },
    {
        (char*)"pppYmDrawMdlTexAnm",
        0,
        PPP_FN(pppFrameYmDrawMdlTexAnm),
        PPP_FN(pppRenderYmDrawMdlTexAnm),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmDrawMdlTexAnm),
        0,
        0,
        PPP_FN(pppDestructYmDrawMdlTexAnm)
    },
    {
        (char*)"pppDrawMatrixWood",
        0,
        0,
        PPP_FN(pppDrawMatrixWood),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixNoRot",
        0,
        0,
        PPP_FN(pppDrawMatrixNoRot),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMegaBirthShpTail2",
        0,
        PPP_FN(pppFrameYmMegaBirthShpTail2),
        PPP_FN(pppRenderYmMegaBirthShpTail2),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMegaBirthShpTail2),
        0,
        0,
        PPP_FN(pppDestructYmMegaBirthShpTail2)
    },
    {
        (char*)"pppYmMegaBirthShpTail3",
        0,
        PPP_FN(pppFrameYmMegaBirthShpTail3),
        PPP_FN(pppRenderYmMegaBirthShpTail3),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMegaBirthShpTail3),
        0,
        0,
        PPP_FN(pppDestructYmMegaBirthShpTail3)
    },
    {
        (char*)"pppKeLnsFls",
        0,
        0,
        PPP_FN(pppKeLnsFlsDraw),
        { 0, 0, 0 },
        PPP_FN(pppKeLnsFlsCon),
        0,
        0,
        0
    },
    {
        (char*)"pppKeLnsLp",
        0,
        0,
        PPP_FN(pppKeLnsLpDraw),
        { 0, 0, 0 },
        PPP_FN(pppKeLnsLpCon),
        PPP_FN(pppKeLnsLpCon2),
        0,
        0
    },
    {
        (char*)"pppKeDMat",
        0,
        0,
        PPP_FN(pppKeDMatDraw),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmDeformationShp",
        0,
        PPP_FN(pppFrameYmDeformationShp),
        PPP_FN(pppRenderYmDeformationShp),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmDeformationShp),
        PPP_FN(pppConstruct2YmDeformationShp),
        0,
        PPP_FN(pppDestructYmDeformationShp)
    },
    {
        (char*)"pppWDrawMatrix",
        0,
        0,
        PPP_FN(pppWDrawMatrix),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppWDrawMatrixFront",
        0,
        0,
        PPP_FN(pppWDrawMatrixFront),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppParMoveLine",
        0,
        PPP_FN(pppParMoveLine),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMiasma",
        0,
        PPP_FN(pppFrameYmMiasma),
        PPP_FN(pppRenderYmMiasma),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMiasma),
        PPP_FN(pppConstruct2YmMiasma),
        0,
        PPP_FN(pppDestructYmMiasma)
    },
    {
        (char*)"pppYmDeformationScreen",
        0,
        PPP_FN(pppFrameYmDeformationScreen),
        PPP_FN(pppRenderYmDeformationScreen),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmDeformationScreen),
        PPP_FN(pppConstruct2YmDeformationScreen),
        0,
        PPP_FN(pppDestructYmDeformationScreen)
    },
    {
        (char*)"pppYmTracer",
        0,
        PPP_FN(pppFrameYmTracer),
        PPP_FN(pppRenderYmTracer),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmTracer),
        PPP_FN(pppConstruct2YmTracer),
        0,
        PPP_FN(pppDestructYmTracer)
    },
    {
        (char*)"pppParHitSph",
        0,
        PPP_FN(pppParHitSph),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMelt",
        0,
        PPP_FN(pppFrameYmMelt),
        PPP_FN(pppRenderYmMelt),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMelt),
        0,
        0,
        PPP_FN(pppDestructYmMelt)
    },
    {
        (char*)"pppYmCallBack",
        0,
        PPP_FN(pppFrameYmCallBack),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmCallBack),
        0,
        0,
        PPP_FN(pppDestructYmCallBack)
    },
    {
        (char*)"pppYmBreath",
        0,
        PPP_FN(pppFrameYmBreath),
        PPP_FN(pppRenderYmBreath),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmBreath),
        PPP_FN(pppConstruct2YmBreath),
        0,
        PPP_FN(pppDestructYmBreath)
    },
    {
        (char*)"pppWDrawMatrixLoop",
        0,
        0,
        PPP_FN(pppWDrawMatrixLoop),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppWDrawMatrixFrontLoop",
        0,
        0,
        PPP_FN(pppWDrawMatrixFrontLoop),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmMoveCircle",
        0,
        PPP_FN(pppFrameYmMoveCircle),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMoveCircle),
        0,
        0,
        0
    },
    {
        (char*)"pppDrawMatrixFrontLnr",
        0,
        0,
        PPP_FN(pppDrawMatrixFrontLnr),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmDeformationMdl",
        0,
        PPP_FN(pppFrameYmDeformationMdl),
        PPP_FN(pppRenderYmDeformationMdl),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmDeformationMdl),
        PPP_FN(pppConstruct2YmDeformationMdl),
        0,
        PPP_FN(pppDestructYmDeformationMdl)
    },
    {
        (char*)"pppPointApMtx",
        0,
        PPP_FN(pppPointApMtx),
        0,
        { 0, 0, 0 },
        PPP_FN(pppPointApMtxCon),
        0,
        0,
        0
    },
    {
        (char*)"pppVertexApMtx",
        0,
        PPP_FN(pppVertexApMtx),
        0,
        { 0, 0, 0 },
        PPP_FN(pppVertexApMtxCon),
        0,
        0,
        0
    },
    {
        (char*)"pppSDrawMatrix",
        0,
        0,
        PPP_FN(pppSDrawMatrix),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmLaser",
        0,
        PPP_FN(pppFrameYmLaser),
        PPP_FN(pppRenderYmLaser),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmLaser),
        PPP_FN(pppConstruct2YmLaser),
        0,
        PPP_FN(pppDestructYmLaser)
    },
    {
        (char*)"pppSpMatrix",
        0,
        PPP_FN(pppSpMatrix),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmChangeTex",
        0,
        PPP_FN(pppFrameYmChangeTex),
        PPP_FN(pppRenderYmChangeTex),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmChangeTex),
        0,
        0,
        PPP_FN(pppDestructYmChangeTex)
    },
    {
        (char*)"pppYmMoveParabola",
        0,
        PPP_FN(pppFrameYmMoveParabola),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMoveParabola),
        0,
        0,
        0
    },
    {
        (char*)"pppParMoveMatrix",
        0,
        PPP_FN(pppParMoveMatrix),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppYmTraceMove",
        0,
        PPP_FN(pppFrameYmTraceMove),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmTraceMove),
        0,
        0,
        0
    },
    {
        (char*)"pppYmMana",
        0,
        PPP_FN(pppFrameYmMana),
        PPP_FN(pppRenderYmMana),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmMana),
        0,
        0,
        PPP_FN(pppDestructYmMana)
    },
    {
        (char*)"pppYmLookOn",
        0,
        PPP_FN(pppFrameYmLookOn),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmLookOn),
        0,
        0,
        0
    },
    {
        (char*)"pppYmCheckBGHeight",
        0,
        PPP_FN(pppFrameYmCheckBGHeight),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructYmCheckBGHeight),
        0,
        0,
        0
    },
    {
        (char*)"pppLocationTitle",
        0,
        PPP_FN(pppFrameLocationTitle),
        PPP_FN(pppRenderLocationTitle),
        { 0, 0, 0 },
        PPP_FN(pppConstructLocationTitle),
        0,
        0,
        PPP_FN(pppDestructLocationTitle)
    },
    {
        (char*)"pppLocationTitle2",
        0,
        PPP_FN(pppFrameLocationTitle2),
        PPP_FN(pppRenderLocationTitle2),
        { 0, 0, 0 },
        PPP_FN(pppConstructLocationTitle2),
        0,
        0,
        PPP_FN(pppDestructLocationTitle2)
    },
    {
        (char*)"pppDrawShape2",
        0,
        PPP_FN(pppCalcShape2),
        PPP_FN(pppDrawShape2),
        { 0, 0, 0 },
        PPP_FN(pppDrawShape2Construct),
        PPP_FN(pppDrawShape2Construct),
        0,
        0
    },
    {
        (char*)"pppLight",
        0,
        PPP_FN(pppLight),
        0,
        { 0, 0, 0 },
        PPP_FN(pppLightCon),
        PPP_FN(pppLightCon),
        0,
        0
    },
    {
        (char*)"pppBreathModel",
        0,
        PPP_FN(pppFrameBreathModel),
        PPP_FN(pppRenderBreathModel),
        { 0, 0, 0 },
        PPP_FN(pppConstructBreathModel),
        0,
        0,
        PPP_FN(pppDestructBreathModel)
    },
    {
        (char*)"pppCrystal",
        0,
        PPP_FN(pppFrameCrystal),
        PPP_FN(pppRenderCrystal),
        { 0, 0, 0 },
        PPP_FN(pppConstructCrystal),
        0,
        0,
        PPP_FN(pppDestructCrystal)
    },
    {
        (char*)"pppRain",
        0,
        PPP_FN(pppFrameRain),
        PPP_FN(pppRenderRain),
        { 0, 0, 0 },
        PPP_FN(pppConstructRain),
        0,
        0,
        PPP_FN(pppDestructRain)
    },
    {
        (char*)"pppBlurChara",
        0,
        PPP_FN(pppFrameBlurChara),
        PPP_FN(pppRenderBlurChara),
        { 0, 0, 0 },
        PPP_FN(pppConstructBlurChara),
        0,
        0,
        PPP_FN(pppDestructBlurChara)
    },
    {
        (char*)"pppLensFlare",
        0,
        PPP_FN(pppFrameLensFlare),
        PPP_FN(pppRenderLensFlare),
        { 0, 0, 0 },
        PPP_FN(pppConstructLensFlare),
        0,
        0,
        PPP_FN(pppDestructLensFlare)
    },
    {
        (char*)"pppCorona",
        0,
        PPP_FN(pppFrameCorona),
        PPP_FN(pppRenderCorona),
        { 0, 0, 0 },
        PPP_FN(pppConstructCorona),
        0,
        0,
        PPP_FN(pppDestructCorona)
    },
    {
        (char*)"pppColum",
        0,
        PPP_FN(pppFrameColum),
        PPP_FN(pppRenderColum),
        { 0, 0, 0 },
        PPP_FN(pppConstructColum),
        0,
        0,
        PPP_FN(pppDestructColum)
    },
    {
        (char*)"pppLightLoop",
        0,
        PPP_FN(pppLight),
        0,
        { 0, 0, 0 },
        PPP_FN(pppLightCon),
        PPP_FN(pppLightCon),
        PPP_FN(pppLightCon3),
        0
    },
    {
        (char*)"pppEmission",
        0,
        PPP_FN(pppFrameEmission),
        PPP_FN(pppRenderEmission),
        { 0, 0, 0 },
        PPP_FN(pppConstructEmission),
        PPP_FN(pppConstruct2Emission),
        0,
        PPP_FN(pppDestructEmission)
    },
    {
        (char*)"pppEraseCharaParts",
        0,
        PPP_FN(pppFrameEraseCharaParts),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructEraseCharaParts),
        0,
        0,
        PPP_FN(pppDestructEraseCharaParts)
    },
    {
        (char*)"pppYmTracer2",
        0,
        PPP_FN(pppFrameYmTracer2),
        PPP_FN(pppRenderYmTracer2),
        { 0, 0, 0 },
        PPP_FN(pppConstructYmTracer2),
        PPP_FN(pppConstruct2YmTracer2),
        0,
        PPP_FN(pppDestructYmTracer2)
    },
    {
        (char*)"pppMana2",
        0,
        PPP_FN(pppFrameMana2),
        PPP_FN(pppRenderMana2),
        { 0, 0, 0 },
        PPP_FN(pppConstructMana2),
        0,
        0,
        PPP_FN(pppDestructMana2)
    },
    {
        (char*)"pppConformBGNormal",
        0,
        PPP_FN(pppFrameConformBGNormal),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructConformBGNormal),
        0,
        0,
        0
    },
    {
        (char*)"pppAlignmentScale",
        0,
        PPP_FN(pppFrameAlignmentScale),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructAlignmentScale),
        0,
        0,
        0
    },
    {
        (char*)"pppMiasma",
        0,
        PPP_FN(pppFrameMiasma),
        PPP_FN(pppRenderMiasma),
        { 0, 0, 0 },
        PPP_FN(pppConstructMiasma),
        PPP_FN(pppConstruct2Miasma),
        0,
        PPP_FN(pppDestructMiasma)
    },
    {
        (char*)"pppBindOnlyPos",
        0,
        PPP_FN(pppFrameBindOnlyPos),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructBindOnlyPos),
        0,
        0,
        0
    },
    {
        (char*)"pppLerpPos",
        0,
        PPP_FN(pppFrameLerpPos),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructLerpPos),
        0,
        0,
        PPP_FN(pppDestructLerpPos)
    },
    {
        (char*)"pppScaleLoopAuto",
        0,
        PPP_FN(pppScaleLoopAuto),
        0,
        { 0, 0, 0 },
        PPP_FN(pppScaleLoopAutoCon),
        0,
        0,
        0
    },
    {
        (char*)"pppChangeBGColor",
        0,
        PPP_FN(pppFrameChangeBGColor),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConChangeBGColor),
        0,
        0,
        PPP_FN(pppDesChangeBGColor)
    },
    {
        (char*)"pppScreenBreak",
        0,
        PPP_FN(pppFrameScreenBreak),
        PPP_FN(pppRenderScreenBreak),
        { 0, 0, 0 },
        PPP_FN(pppConScreenBreak),
        PPP_FN(pppCon2ScreenBreak),
        0,
        PPP_FN(pppDesScreenBreak)
    },
    {
        (char*)"pppScreenBlur",
        0,
        PPP_FN(pppFrameScreenBlur),
        PPP_FN(pppRenderScreenBlur),
        { 0, 0, 0 },
        PPP_FN(pppConScreenBlur),
        PPP_FN(pppCon2ScreenBlur),
        0,
        PPP_FN(pppDesScreenBlur)
    },
    {
        (char*)"pppScreenQuake",
        0,
        PPP_FN(pppFrameScreenQuake),
        PPP_FN(pppRenderScreenQuake),
        { 0, 0, 0 },
        PPP_FN(pppConScreenQuake),
        PPP_FN(pppCon2ScreenQuake),
        0,
        PPP_FN(pppDesScreenQuake)
    },
    {
        (char*)"pppCrystal2",
        0,
        PPP_FN(pppFrameCrystal2),
        PPP_FN(pppRenderCrystal2),
        { 0, 0, 0 },
        PPP_FN(pppConstructCrystal2),
        0,
        0,
        PPP_FN(pppDestructCrystal2)
    },
    {
        (char*)"pppChangeTex",
        0,
        PPP_FN(pppFrameChangeTex),
        PPP_FN(pppRenderChangeTex),
        { 0, 0, 0 },
        PPP_FN(pppConstructChangeTex),
        PPP_FN(pppConstruct2ChangeTex),
        0,
        PPP_FN(pppDestructChangeTex)
    },
    {
        (char*)"pppCharaBreak",
        0,
        PPP_FN(pppFrameCharaBreak),
        PPP_FN(pppRenderCharaBreak),
        { 0, 0, 0 },
        PPP_FN(pppConstructCharaBreak),
        PPP_FN(pppConstruct2CharaBreak),
        0,
        PPP_FN(pppDestructCharaBreak)
    },
    {
        (char*)"pppCallBackDistance",
        0,
        PPP_FN(pppFrameCallBackDistance),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructCallBackDistance),
        0,
        0,
        PPP_FN(pppDestructCallBackDistance)
    },
    {
        (char*)"pppParHitSphMat",
        0,
        PPP_FN(pppParHitSphMat),
        0,
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppConstrainCameraDir",
        0,
        PPP_FN(pppFrameConstrainCameraDir),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructConstrainCameraDir),
        PPP_FN(pppConstruct2ConstrainCameraDir),
        0,
        PPP_FN(pppDestructConstrainCameraDir)
    },
    {
        (char*)"pppFilter",
        0,
        PPP_FN(pppFrameFilter),
        PPP_FN(pppRenderFilter),
        { 0, 0, 0 },
        PPP_FN(pppConstructFilter),
        0,
        0,
        PPP_FN(pppDestructFilter)
    },
    {
        (char*)"pppConstrainCameraForLoc",
        0,
        PPP_FN(pppFrameConstrainCameraForLoc),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructConstrainCameraForLoc),
        PPP_FN(pppConstruct2ConstrainCameraForLoc),
        PPP_FN(fn_80167EC4),
        PPP_FN(pppDestructConstrainCameraForLoc)
    },
    {
        (char*)"pppDrawMatrixLoc",
        0,
        0,
        PPP_FN(pppDrawMatrixLoc),
        { 0, 0, 0 },
        0,
        0,
        0,
        0
    },
    {
        (char*)"pppCharaZEnvCtrl",
        0,
        PPP_FN(pppFrameCharaZEnvCtrl),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConCharaZEnvCtrl),
        0,
        0,
        PPP_FN(pppDesCharaZEnvCtrl)
    },
    {
        (char*)"pppConstrainCameraDir2",
        0,
        PPP_FN(pppFrameConstrainCameraDir2),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructConstrainCameraDir),
        PPP_FN(pppConstruct2ConstrainCameraDir),
        0,
        PPP_FN(pppDestructConstrainCameraDir)
    },
    {
        (char*)"pppFovAdjustMatrix",
        0,
        PPP_FN(pppFrameFovAdjustMatrix),
        0,
        { 0, 0, 0 },
        PPP_FN(pppConstructFovAdjustMatrix),
        0,
        0,
        PPP_FN(pppDestructFovAdjustMatrix)
    },
    {
        (char*)"pppLaser",
        0,
        PPP_FN(pppFrameLaser),
        PPP_FN(pppRenderLaser),
        { 0, 0, 0 },
        PPP_FN(pppConstructLaser),
        PPP_FN(pppConstruct2Laser),
        0,
        PPP_FN(pppDestructLaser)
    },
};

static _pppSysProgTbl pppSysProgTbl = {
    s_pppSysProgTable,
};

pppProg* pppGetSysProgTable()
{
    return pppSysProgTbl.m_progs;
}
#endif // FFCC_PPPFUNCTBL_IMPLEMENTATION

#endif // _FFCC_FUNCTBL_H_
