#pragma once
#include "UICellItem.h"
#include "Weapon.h"

class CUIInventoryCellItem : public CUICellItem
{
    typedef CUICellItem inherited;

public:
    CUIInventoryCellItem(CInventoryItem* itm);
    virtual bool EqualTo(CUICellItem* itm);
    virtual void UpdateItemText();
    CUIDragItem* CreateDragItem();
    virtual bool IsHelper();
    virtual void SetIsHelper(bool is_helper);
    bool IsHelperOrHasHelperChild();
    void Update();
    CInventoryItem* object() { return (CInventoryItem*)m_pData; }
};

class CUIAmmoCellItem : public CUIInventoryCellItem
{
    typedef CUIInventoryCellItem inherited;

protected:
    virtual void UpdateItemText();

public:
    CUIAmmoCellItem(CWeaponAmmo* itm);

    u32 CalculateAmmoCount();
    virtual bool EqualTo(CUICellItem* itm);
    virtual CUIDragItem* CreateDragItem();
    CWeaponAmmo* object() { return (CWeaponAmmo*)m_pData; }
};

class CUIWeaponCellItem : public CUIInventoryCellItem
{
    typedef CUIInventoryCellItem inherited;

public:
    enum eAddonType
    {
        eSilencer = 0,
        eScope,
        eGrip,
        eLauncher,
        eBarrel,
        eBipods,
        eChargs,
        eChargh,
        eFlight,
        eFgrips,
        eGblock,
        eHguard,
        eMagazn,
        eMounts,
        eMuzzle,
        eRcievr,
        eSights,
        eSightf,
        eSightr,
        eSight2,
        eStocks,
        eTacti1,
        eAdapt1,
        eAdapt2,
        eLaserr,
        eMaxAddon
    };

protected:
    CUIStatic* m_addons[eMaxAddon];
    Fvector2 m_addon_offset[eMaxAddon];
    void CreateIcon(eAddonType);
    void DestroyIcon(eAddonType);
    void RefreshOffset();
    CUIStatic* GetIcon(eAddonType);
    void InitAddon(CUIStatic* s, LPCSTR section, Fvector2 offset, bool use_heading);
    bool is_scope();
    bool is_silencer();
    bool is_grip();
    bool is_barrel();
    bool is_bipods();
    bool is_chargh();
    bool is_chargs();
    bool is_flight();
    bool is_fgrips();
    bool is_gblock();
    bool is_hguard();
    bool is_magazn();
    bool is_mounts();
    bool is_muzzle();
    bool is_rcievr();
    bool is_sights();
    bool is_sightf();
    bool is_sightr();
    bool is_sight2();
    bool is_stocks();
    bool is_tacti1();
    bool is_adapt1();
    bool is_adapt2();
    bool is_laserr();
    bool is_launcher();

public:
    CUIWeaponCellItem(CWeapon* itm);
    virtual ~CUIWeaponCellItem();
    virtual void Update();
    virtual void Draw();
    virtual void SetTextureColor(u32 color);

    CWeapon* object() { return (CWeapon*)m_pData; }
    virtual void OnAfterChild(CUIDragDropListEx* parent_list);
    virtual CUIDragItem* CreateDragItem();
    virtual bool EqualTo(CUICellItem* itm);
    CUIStatic* get_addon_static(u32 idx) { return m_addons[idx]; }
};

class CBuyItemCustomDrawCell : public ICustomDrawCellItem
{
    CGameFont* m_pFont;
    string16 m_string;

public:
    CBuyItemCustomDrawCell(LPCSTR str, CGameFont* pFont);
    virtual void OnDraw(CUICellItem* cell);
};
