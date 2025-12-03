#ifndef _FFCC_GOBJWORK_H_
#define _FFCC_GOBJWORK_H_

class CRomWork;
class CRomLetterWork;

class CGObjWork
{
public:
    CGObjWork();
    ~CGObjWork();

    void Init(int, CRomWork *, int);
    void CalcStatus();
};

class CMonWork
{
public:
    CMonWork();
    ~CMonWork();

    void Init(int, CRomWork *, int);
    void CalcStatus();
};

class CCaravanWork
{
public:
    CCaravanWork();
    ~CCaravanWork();

    void clearCaravanWork();
    void LoadInit();
    void ClearEvtWork();
    void LoadFinished();
    void Init(int, CRomWork *, int);
    void SetBonusCondition(int);
    void IsOutOfShouki();
    void AddLetter(int, int, int, int, int, int, int, int, int);

    class CLetterWork
    {
    public:
        void operator=(const CLetterWork &);
    };

    void FGLetterOpen(int);
    void FGLetterReply(int, int, int, int);
    void FGUseItem(int, int);
    void FGPutItem(int, int);
    void FGPutGil(int);
    void ChgCmdLst(int, int);
    void ChgEquipPos(int, int);
    void CanAddComList(int);
    void AddComList(int, int *);
    void DeleteCmdList(int, int);
    void AddItem(int, int *);
    void SetArtifact(int, int);
    void FGAddItemIdx(int, int);
    void ChkNumItem(char *, int);
    void CanAddTmpArtifact(int);
    void FindItem(int);
    void DeleteItemIdx(int, int);
    void DeleteItem(int, int);
    void AddTmpArtifact(int, int *);
    void CanAddGil(int);
    void AddGil(int);
    void GetFoodRank(int);
    void SearchRomLetterWork(CRomLetterWork **, int);
    void ShopRequest(int, int, int, int, int, int, int);
    void CallShop(int, int, int, int, int);
    void SafeDeleteTempItem();
    void ClampStatus(short &, unsigned short &);
    void CalcArtifactStatus(int, int, int &, int &, int &, int &, int &);
    void CalcStatus();
    void CanPlayerUseItem();
    void ValidCmdList(int);
    void GetIdxCmdList();
    void SetIdxCmdList(int);
    void IsUseCmdList(int);
    void IsSelectedCmdList(int);
    void GetMagicCharge(int, int &, int &);
    void GetCmdListItemName(int);
    void GetWeaponAttrib(int);
    void GetCmdListItem(int);
    void DelCmdListAndItem(int, int);
    void SearchCombiTop(int);
    void GetNumCombi(int);
    void GetNextCmdListIdx(int, int);
    void CanPlayerPutItem();
    void GetCurrentWeaponItem(int &, int &);
    void SetCurrentWeaponIdx(int);
    void CheckAndResetCurrentWeaponIdx(int);
    void SortBeforeReturnWorldMap();
    void BackupTutorialItem(int);
    void UniteComList(int, int, int);
    void UnuniteComList(int, int);
};

#endif // _FFCC_GOBJWORK_H_
