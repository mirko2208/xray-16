#include "StdAfx.h"
#include "UICellCustomItems.h"
#include "UIInventoryUtilities.h"
#include "Weapon.h"
#include "UIDragDropListEx.h"
#include "xrUICore/ProgressBar/UIProgressBar.h"

#define INV_GRID_WIDTHF 50.0f
#define INV_GRID_HEIGHTF 50.0f

namespace detail
{
struct is_helper_pred
{
    bool operator()(CUICellItem* child) { return child->IsHelper(); }
}; // struct is_helper_pred

} // namespace detail

CUIInventoryCellItem::CUIInventoryCellItem(CInventoryItem* itm)
{
    m_pData = (void*)itm;

    inherited::SetShader(InventoryUtilities::GetEquipmentIconsShader());

    m_grid_size.set(itm->GetInvGridRect().rb);
    Frect rect;
    rect.lt.set(INV_GRID_WIDTHF * itm->GetInvGridRect().x1, INV_GRID_HEIGHTF * itm->GetInvGridRect().y1);

    rect.rb.set(rect.lt.x + INV_GRID_WIDTHF * m_grid_size.x, rect.lt.y + INV_GRID_HEIGHTF * m_grid_size.y);

    inherited::SetTextureRect(rect);
    inherited::SetStretchTexture(true);
}

bool CUIInventoryCellItem::EqualTo(CUICellItem* itm)
{
    CUIInventoryCellItem* ci = smart_cast<CUIInventoryCellItem*>(itm);
    if (!itm)
    {
        return false;
    }
    if (object()->object().cNameSect() != ci->object()->object().cNameSect())
    {
        return false;
    }
    if (!fsimilar(object()->GetCondition(), ci->object()->GetCondition(), 0.01f))
    {
        return false;
    }
    if (!object()->equal_upgrades(ci->object()->upgardes()))
    {
        return false;
    }
    return true;
}

bool CUIInventoryCellItem::IsHelperOrHasHelperChild()
{
    return std::count_if(m_childs.begin(), m_childs.end(), detail::is_helper_pred()) > 0 || IsHelper();
}

CUIDragItem* CUIInventoryCellItem::CreateDragItem()
{
    return IsHelperOrHasHelperChild() ? NULL : inherited::CreateDragItem();
}

bool CUIInventoryCellItem::IsHelper() { return object()->is_helper_item(); }
void CUIInventoryCellItem::SetIsHelper(bool is_helper) { object()->set_is_helper(is_helper); }
void CUIInventoryCellItem::Update()
{
    inherited::Update();
    UpdateConditionProgressBar(); // Alundaio
    UpdateItemText();

    u32 color = GetTextureColor();
    if (IsHelper() && !ChildsCount())
    {
        color = 0xbbbbbbbb;
    }
    else if (IsHelperOrHasHelperChild())
    {
        color = 0xffffffff;
    }

    SetTextureColor(color);
}

void CUIInventoryCellItem::UpdateItemText()
{
    const u32 helper_count =
        (u32)std::count_if(m_childs.begin(), m_childs.end(), detail::is_helper_pred()) + IsHelper() ? 1 : 0;

    const u32 count = ChildsCount() + 1 - helper_count;

    string32 str;

    if (count > 1 || helper_count)
    {
        xr_sprintf(str, "x%d", count);
        m_text->TextItemControl()->SetText(str);
        m_text->Show(true);
    }
    else
    {
        xr_sprintf(str, "");
        m_text->TextItemControl()->SetText(str);
        m_text->Show(false);
    }
}

CUIAmmoCellItem::CUIAmmoCellItem(CWeaponAmmo* itm) : inherited(itm) {}
bool CUIAmmoCellItem::EqualTo(CUICellItem* itm)
{
    if (!inherited::EqualTo(itm))
        return false;

    CUIAmmoCellItem* ci = smart_cast<CUIAmmoCellItem*>(itm);
    if (!ci)
        return false;

    return ((object()->cNameSect() == ci->object()->cNameSect()));
}

CUIDragItem* CUIAmmoCellItem::CreateDragItem() { return IsHelper() ? NULL : inherited::CreateDragItem(); }
u32 CUIAmmoCellItem::CalculateAmmoCount()
{
    xr_vector<CUICellItem*>::iterator it = m_childs.begin();
    xr_vector<CUICellItem*>::iterator it_e = m_childs.end();

    u32 total = IsHelper() ? 0 : object()->m_boxCurr;
    for (; it != it_e; ++it)
    {
        CUICellItem* child = *it;

        if (!child->IsHelper())
        {
            total += ((CUIAmmoCellItem*)(*it))->object()->m_boxCurr;
        }
    }

    return total;
}

void CUIAmmoCellItem::UpdateItemText()
{
    m_text->Show(false);
    if (!m_custom_draw)
    {
        const u32 total = CalculateAmmoCount();

        string32 str;
        xr_sprintf(str, "%d", total);
        m_text->TextItemControl()->SetText(str);
        m_text->Show(true);
    }
}

CUIWeaponCellItem::CUIWeaponCellItem(CWeapon* itm) : inherited(itm)
{
    m_addons[eSilencer] = NULL;
    m_addons[eScope] = NULL;
    m_addons[eLauncher] = NULL;
    m_addons[eGrip] = NULL;
    m_addons[eBarrel] = NULL;
    m_addons[eBipods] = NULL;
    m_addons[eChargs] = NULL;
    m_addons[eChargh] = NULL;
    m_addons[eFlight] = NULL;
    m_addons[eFgrips] = NULL;
    m_addons[eGblock] = NULL;
    m_addons[eHguard] = NULL;
    m_addons[eMagazn] = NULL;
    m_addons[eMounts] = NULL;
    m_addons[eMuzzle] = NULL;
    m_addons[eRcievr] = NULL;
    m_addons[eSights] = NULL;
    m_addons[eSightf] = NULL;
    m_addons[eSightr] = NULL;
    m_addons[eSight2] = NULL;
    m_addons[eStocks] = NULL;
    m_addons[eTacti1] = NULL;
    m_addons[eAdapt1] = NULL;
    m_addons[eAdapt2] = NULL;
    m_addons[eLaserr] = NULL;

    if (itm->SilencerAttachable())
        m_addon_offset[eSilencer].set(object()->GetSilencerX(), object()->GetSilencerY());

    if (itm->GripAttachable())
        m_addon_offset[eGrip].set(object()->GetGripX(), object()->GetGripY());

    if (itm->BarrelAttachable())
        m_addon_offset[eBarrel].set(object()->GetBarrelX(), object()->GetBarrelY());

    if (itm->BipodsAttachable())
        m_addon_offset[eBipods].set(object()->GetBipodsY(), object()->GetBipodsX());

    if (itm->ChargsAttachable())
        m_addon_offset[eChargs].set(object()->GetChargsX(), object()->GetChargsY());

    if (itm->CharghAttachable())
        m_addon_offset[eChargh].set(object()->GetCharghX(), object()->GetCharghY());

    if (itm->FlightAttachable())
        m_addon_offset[eFlight].set(object()->GetFlightX(), object()->GetFlightY());

    if (itm->FgripsAttachable())
        m_addon_offset[eFgrips].set(object()->GetFgripsX(), object()->GetFgripsY());

    if (itm->GblockAttachable())
        m_addon_offset[eGblock].set(object()->GetGblockX(), object()->GetGblockY());

    if (itm->HguardAttachable())
        m_addon_offset[eHguard].set(object()->GetHguardX(), object()->GetHguardY());

    if (itm->MagaznAttachable())
        m_addon_offset[eMagazn].set(object()->GetMagaznX(), object()->GetMagaznY());

    if (itm->MountsAttachable())
        m_addon_offset[eMounts].set(object()->GetMountsX(), object()->GetMountsY());

    if (itm->MuzzleAttachable())
        m_addon_offset[eMuzzle].set(object()->GetMuzzleX(), object()->GetMuzzleY());

    if (itm->RcievrAttachable())
        m_addon_offset[eRcievr].set(object()->GetRcievrX(), object()->GetRcievrY());

    if (itm->SightsAttachable())
        m_addon_offset[eSights].set(object()->GetSightsX(), object()->GetSightsY());

    if (itm->SightfAttachable())
        m_addon_offset[eSightf].set(object()->GetSightfX(), object()->GetSightfY());

    if (itm->SightrAttachable())
        m_addon_offset[eSightr].set(object()->GetSightrX(), object()->GetSightrY());

    if (itm->Sight2Attachable())
        m_addon_offset[eSight2].set(object()->GetSight2X(), object()->GetSight2Y());

    if (itm->StocksAttachable())
        m_addon_offset[eStocks].set(object()->GetStocksX(), object()->GetStocksY());

    if (itm->Tacti1Attachable())
        m_addon_offset[eTacti1].set(object()->GetTacti1X(), object()->GetTacti1Y());

    if (itm->Adapt1Attachable())
        m_addon_offset[eAdapt1].set(object()->GetAdapt1X(), object()->GetAdapt1Y());

    if (itm->Adapt2Attachable())
        m_addon_offset[eAdapt2].set(object()->GetAdapt2X(), object()->GetAdapt2Y());

    if (itm->LaserrAttachable())
        m_addon_offset[eLaserr].set(object()->GetLaserrX(), object()->GetLaserrY());

    if (itm->ScopeAttachable())
        m_addon_offset[eScope].set(object()->GetScopeX(), object()->GetScopeY());

    if (itm->GrenadeLauncherAttachable())
        m_addon_offset[eLauncher].set(object()->GetGrenadeLauncherX(), object()->GetGrenadeLauncherY());
}

#include "Common/object_broker.h"
CUIWeaponCellItem::~CUIWeaponCellItem() {}
bool CUIWeaponCellItem::is_scope() { return object()->ScopeAttachable() && object()->IsScopeAttached(); }
bool CUIWeaponCellItem::is_silencer() { return object()->SilencerAttachable() && object()->IsSilencerAttached(); }
bool CUIWeaponCellItem::is_barrel() { return object()->BarrelAttachable() && object()->IsBarrelAttached(); }
bool CUIWeaponCellItem::is_bipods() { return object()->BipodsAttachable() && object()->IsBipodsAttached(); }
bool CUIWeaponCellItem::is_chargs() { return object()->ChargsAttachable() && object()->IsChargsAttached(); }
bool CUIWeaponCellItem::is_chargh() { return object()->CharghAttachable() && object()->IsCharghAttached(); }
bool CUIWeaponCellItem::is_grip() { return object()->GripAttachable() && object()->IsGripAttached(); }
bool CUIWeaponCellItem::is_flight() { return object()->FlightAttachable() && object()->IsFlightAttached(); }
bool CUIWeaponCellItem::is_fgrips() { return object()->FgripsAttachable() && object()->IsFgripsAttached(); }
bool CUIWeaponCellItem::is_gblock() { return object()->GblockAttachable() && object()->IsGblockAttached(); }
bool CUIWeaponCellItem::is_hguard() { return object()->HguardAttachable() && object()->IsHguardAttached(); }
bool CUIWeaponCellItem::is_magazn() { return object()->MagaznAttachable() && object()->IsMagaznAttached(); }
bool CUIWeaponCellItem::is_mounts() { return object()->MountsAttachable() && object()->IsMountsAttached(); }
bool CUIWeaponCellItem::is_muzzle() { return object()->MuzzleAttachable() && object()->IsMuzzleAttached(); }
bool CUIWeaponCellItem::is_rcievr() { return object()->RcievrAttachable() && object()->IsRcievrAttached(); }
bool CUIWeaponCellItem::is_sights() { return object()->SightsAttachable() && object()->IsSightsAttached(); }
bool CUIWeaponCellItem::is_sightf() { return object()->SightfAttachable() && object()->IsSightfAttached(); }
bool CUIWeaponCellItem::is_sightr() { return object()->SightrAttachable() && object()->IsSightrAttached(); }
bool CUIWeaponCellItem::is_sight2() { return object()->Sight2Attachable() && object()->IsSight2Attached(); }
bool CUIWeaponCellItem::is_stocks() { return object()->StocksAttachable() && object()->IsStocksAttached(); }
bool CUIWeaponCellItem::is_tacti1() { return object()->Tacti1Attachable() && object()->IsTacti1Attached(); }
bool CUIWeaponCellItem::is_adapt1() { return object()->Adapt1Attachable() && object()->IsAdapt1Attached(); }
bool CUIWeaponCellItem::is_adapt2() { return object()->Adapt2Attachable() && object()->IsAdapt2Attached(); }
bool CUIWeaponCellItem::is_laserr() { return object()->LaserrAttachable() && object()->IsLaserrAttached(); }
bool CUIWeaponCellItem::is_launcher()
{
    return object()->GrenadeLauncherAttachable() && object()->IsGrenadeLauncherAttached();
}

void CUIWeaponCellItem::CreateIcon(eAddonType t)
{
    if (m_addons[t])
        return;
    m_addons[t] = xr_new<CUIStatic>();
    m_addons[t]->SetAutoDelete(true);
    AttachChild(m_addons[t]);
    m_addons[t]->SetShader(InventoryUtilities::GetEquipmentIconsShader());

    u32 color = GetTextureColor();
    m_addons[t]->SetTextureColor(color);
}

void CUIWeaponCellItem::DestroyIcon(eAddonType t)
{
    DetachChild(m_addons[t]);
    m_addons[t] = NULL;
}

CUIStatic* CUIWeaponCellItem::GetIcon(eAddonType t) { return m_addons[t]; }
void CUIWeaponCellItem::RefreshOffset()
{
    if (object()->SilencerAttachable())
        m_addon_offset[eSilencer].set(object()->GetSilencerX(), object()->GetSilencerY());

    if (object()->BarrelAttachable())
        m_addon_offset[eBarrel].set(object()->GetBarrelX(), object()->GetBarrelY());

    if (object()->BipodsAttachable())
        m_addon_offset[eBipods].set(object()->GetBipodsX(), object()->GetBipodsY());

    if (object()->ChargsAttachable())
        m_addon_offset[eChargs].set(object()->GetChargsX(), object()->GetChargsY());

    if (object()->CharghAttachable())
        m_addon_offset[eChargh].set(object()->GetCharghX(), object()->GetCharghY());

    if (object()->FlightAttachable())
        m_addon_offset[eFlight].set(object()->GetFlightX(), object()->GetFlightY());

    if (object()->FgripsAttachable())
        m_addon_offset[eFgrips].set(object()->GetFgripsX(), object()->GetFgripsY());

    if (object()->GblockAttachable())
        m_addon_offset[eGblock].set(object()->GetGblockX(), object()->GetGblockY());

    if (object()->HguardAttachable())
        m_addon_offset[eHguard].set(object()->GetHguardX(), object()->GetHguardY());

    if (object()->MagaznAttachable())
        m_addon_offset[eMagazn].set(object()->GetMagaznX(), object()->GetMagaznY());

    if (object()->MountsAttachable())
        m_addon_offset[eMounts].set(object()->GetMountsX(), object()->GetMountsY());

    if (object()->MuzzleAttachable())
        m_addon_offset[eMuzzle].set(object()->GetMuzzleX(), object()->GetMuzzleY());

    if (object()->RcievrAttachable())
        m_addon_offset[eRcievr].set(object()->GetRcievrX(), object()->GetRcievrY());

    if (object()->SightsAttachable())
        m_addon_offset[eSights].set(object()->GetSightsX(), object()->GetSightsY());

    if (object()->SightfAttachable())
        m_addon_offset[eSightf].set(object()->GetSightfX(), object()->GetSightfY());

    if (object()->SightrAttachable())
        m_addon_offset[eSightr].set(object()->GetSightrX(), object()->GetSightrY());

    if (object()->Sight2Attachable())
        m_addon_offset[eSight2].set(object()->GetSight2X(), object()->GetSight2Y());

    if (object()->StocksAttachable())
        m_addon_offset[eStocks].set(object()->GetStocksX(), object()->GetStocksY());

    if (object()->Tacti1Attachable())
        m_addon_offset[eTacti1].set(object()->GetTacti1X(), object()->GetTacti1Y());

    if (object()->Adapt1Attachable())
        m_addon_offset[eAdapt1].set(object()->GetAdapt1X(), object()->GetAdapt1Y());

    if (object()->Adapt2Attachable())
        m_addon_offset[eAdapt2].set(object()->GetAdapt2X(), object()->GetAdapt2Y());

    if (object()->LaserrAttachable())
        m_addon_offset[eLaserr].set(object()->GetLaserrX(), object()->GetLaserrY());

    if (object()->GripAttachable())
        m_addon_offset[eGrip].set(object()->GetGripX(), object()->GetGripY());

    if (object()->ScopeAttachable())
        m_addon_offset[eScope].set(object()->GetScopeX(), object()->GetScopeY());

    if (object()->GrenadeLauncherAttachable())
        m_addon_offset[eLauncher].set(object()->GetGrenadeLauncherX(), object()->GetGrenadeLauncherY());
}

void CUIWeaponCellItem::Draw()
{
    inherited::Draw();

    if (m_upgrade && m_upgrade->IsShown())
        m_upgrade->Draw();
};

void CUIWeaponCellItem::Update()
{
    bool b = Heading();
    inherited::Update();

    bool bForceReInitAddons = (b != Heading());

    if (object()->SilencerAttachable())
    {
        if (object()->IsSilencerAttached())
        {
            if (!GetIcon(eSilencer) || bForceReInitAddons)
            {
                CreateIcon(eSilencer);
                RefreshOffset();
                InitAddon(GetIcon(eSilencer), *object()->GetSilencerName(), m_addon_offset[eSilencer], Heading());
            }
        }
        else
        {
            if (m_addons[eSilencer])
                DestroyIcon(eSilencer);
        }
    }

    if (object()->GripAttachable())
    {
        if (object()->IsGripAttached())
        {
            if (!GetIcon(eGrip) || bForceReInitAddons)
            {
                CreateIcon(eGrip);
                RefreshOffset();
                InitAddon(GetIcon(eGrip), *object()->GetGripName(), m_addon_offset[eGrip], Heading());
            }
        }
        else
        {
            if (m_addons[eGrip])
                DestroyIcon(eGrip);
        }
    }
    if (object()->BarrelAttachable())
    {
        if (object()->IsBarrelAttached())
        {
            if (!GetIcon(eBarrel) || bForceReInitAddons)
            {
                CreateIcon(eBarrel);
                RefreshOffset();
                InitAddon(GetIcon(eBarrel), *object()->GetBarrelName(), m_addon_offset[eBarrel], Heading());
            }
        }
        else
        {
            if (m_addons[eBarrel])
                DestroyIcon(eBarrel);
        }
    }
    if (object()->BipodsAttachable())
    {
        if (object()->IsBipodsAttached())
        {
            if (!GetIcon(eBipods) || bForceReInitAddons)
            {
                CreateIcon(eBipods);
                RefreshOffset();
                InitAddon(GetIcon(eBipods), *object()->GetBipodsName(), m_addon_offset[eBipods], Heading());
            }
        }
        else
        {
            if (m_addons[eBipods])
                DestroyIcon(eBipods);
        }
    }
    if (object()->ChargsAttachable())
    {
        if (object()->IsChargsAttached())
        {
            if (!GetIcon(eChargs) || bForceReInitAddons)
            {
                CreateIcon(eChargs);
                RefreshOffset();
                InitAddon(GetIcon(eChargs), *object()->GetChargsName(), m_addon_offset[eChargs], Heading());
            }
        }
        else
        {
            if (m_addons[eChargs])
                DestroyIcon(eChargs);
        }
    }
    if (object()->ChargsAttachable())
    {
        if (object()->IsChargsAttached())
        {
            if (!GetIcon(eChargs) || bForceReInitAddons)
            {
                CreateIcon(eChargs);
                RefreshOffset();
                InitAddon(GetIcon(eChargs), *object()->GetChargsName(), m_addon_offset[eChargs], Heading());
            }
        }
        else
        {
            if (m_addons[eChargs])
                DestroyIcon(eChargs);
        }
    }
    if (object()->FlightAttachable())
    {
        if (object()->IsFlightAttached())
        {
            if (!GetIcon(eFlight) || bForceReInitAddons)
            {
                CreateIcon(eFlight);
                RefreshOffset();
                InitAddon(GetIcon(eFlight), *object()->GetFlightName(), m_addon_offset[eFlight], Heading());
            }
        }
        else
        {
            if (m_addons[eFlight])
                DestroyIcon(eFlight);
        }
    }
    if (object()->FgripsAttachable())
    {
        if (object()->IsFgripsAttached())
        {
            if (!GetIcon(eFgrips) || bForceReInitAddons)
            {
                CreateIcon(eFgrips);
                RefreshOffset();
                InitAddon(GetIcon(eFgrips), *object()->GetFgripsName(), m_addon_offset[eFgrips], Heading());
            }
        }
        else
        {
            if (m_addons[eFgrips])
                DestroyIcon(eFgrips);
        }
    }
    if (object()->GblockAttachable())
    {
        if (object()->IsGblockAttached())
        {
            if (!GetIcon(eGblock) || bForceReInitAddons)
            {
                CreateIcon(eGblock);
                RefreshOffset();
                InitAddon(GetIcon(eGblock), *object()->GetGblockName(), m_addon_offset[eGblock], Heading());
            }
        }
        else
        {
            if (m_addons[eGblock])
                DestroyIcon(eGblock);
        }
    }
    if (object()->HguardAttachable())
    {
        if (object()->IsHguardAttached())
        {
            if (!GetIcon(eHguard) || bForceReInitAddons)
            {
                CreateIcon(eHguard);
                RefreshOffset();
                InitAddon(GetIcon(eHguard), *object()->GetHguardName(), m_addon_offset[eHguard], Heading());
            }
        }
        else
        {
            if (m_addons[eHguard])
                DestroyIcon(eHguard);
        }
    }
    if (object()->MagaznAttachable())
    {
        if (object()->IsMagaznAttached())
        {
            if (!GetIcon(eMagazn) || bForceReInitAddons)
            {
                CreateIcon(eMagazn);
                RefreshOffset();
                InitAddon(GetIcon(eMagazn), *object()->GetMagaznName(), m_addon_offset[eMagazn], Heading());
            }
        }
        else
        {
            if (m_addons[eMagazn])
                DestroyIcon(eMagazn);
        }
    }
    if (object()->MountsAttachable())
    {
        if (object()->IsMountsAttached())
        {
            if (!GetIcon(eMounts) || bForceReInitAddons)
            {
                CreateIcon(eMounts);
                RefreshOffset();
                InitAddon(
                    GetIcon(eMounts), *object()->GetMountsName(), m_addon_offset[eMounts], Heading());
            }
        }
        else
        {
            if (m_addons[eMounts])
                DestroyIcon(eMounts);
        }
    }
    if (object()->MuzzleAttachable())
    {
        if (object()->IsMuzzleAttached())
        {
            if (!GetIcon(eMuzzle) || bForceReInitAddons)
            {
                CreateIcon(eMuzzle);
                RefreshOffset();
                InitAddon(GetIcon(eMuzzle), *object()->GetMuzzleName(), m_addon_offset[eMuzzle], Heading());
            }
        }
        else
        {
            if (m_addons[eMuzzle])
                DestroyIcon(eMuzzle);
        }
    }
    if (object()->RcievrAttachable())
    {
        if (object()->IsRcievrAttached())
        {
            if (!GetIcon(eRcievr) || bForceReInitAddons)
            {
                CreateIcon(eRcievr);
                RefreshOffset();
                InitAddon(GetIcon(eRcievr), *object()->GetRcievrName(), m_addon_offset[eRcievr], Heading());
            }
        }
        else
        {
            if (m_addons[eRcievr])
                DestroyIcon(eRcievr);
        }
    }
    if (object()->SightsAttachable())
    {
        if (object()->IsSightsAttached())
        {
            if (!GetIcon(eSights) || bForceReInitAddons)
            {
                CreateIcon(eSights);
                RefreshOffset();
                InitAddon(GetIcon(eSights), *object()->GetSightsName(), m_addon_offset[eSights], Heading());
            }
        }
        else
        {
            if (m_addons[eSights])
                DestroyIcon(eSights);
        }
    }
    if (object()->SightfAttachable())
    {
        if (object()->IsSightfAttached())
        {
            if (!GetIcon(eSightf) || bForceReInitAddons)
            {
                CreateIcon(eSightf);
                RefreshOffset();
                InitAddon(GetIcon(eSightf), *object()->GetSightfName(), m_addon_offset[eSightf], Heading());
            }
        }
        else
        {
            if (m_addons[eSightf])
                DestroyIcon(eSightf);
        }
    }
    if (object()->SightrAttachable())
    {
        if (object()->IsSightrAttached())
        {
            if (!GetIcon(eSightr) || bForceReInitAddons)
            {
                CreateIcon(eSightr);
                RefreshOffset();
                InitAddon(GetIcon(eSightr), *object()->GetSightrName(), m_addon_offset[eSightr], Heading());
            }
        }
        else
        {
            if (m_addons[eSightr])
                DestroyIcon(eSightr);
        }
    }
    if (object()->Sight2Attachable())
    {
        if (object()->IsSight2Attached())
        {
            if (!GetIcon(eSight2) || bForceReInitAddons)
            {
                CreateIcon(eSight2);
                RefreshOffset();
                InitAddon(GetIcon(eSight2), *object()->GetSight2Name(), m_addon_offset[eSight2], Heading());
            }
        }
        else
        {
            if (m_addons[eSight2])
                DestroyIcon(eSight2);
        }
    }
    if (object()->StocksAttachable())
    {
        if (object()->IsStocksAttached())
        {
            if (!GetIcon(eStocks) || bForceReInitAddons)
            {
                CreateIcon(eStocks);
                RefreshOffset();
                InitAddon(GetIcon(eStocks), *object()->GetStocksName(), m_addon_offset[eStocks], Heading());
            }
        }
        else
        {
            if (m_addons[eStocks])
                DestroyIcon(eStocks);
        }
    }
    if (object()->Tacti1Attachable())
    {
        if (object()->IsTacti1Attached())
        {
            if (!GetIcon(eTacti1) || bForceReInitAddons)
            {
                CreateIcon(eTacti1);
                RefreshOffset();
                InitAddon(GetIcon(eTacti1), *object()->GetTacti1Name(), m_addon_offset[eTacti1], Heading());
            }
        }
        else
        {
            if (m_addons[eTacti1])
                DestroyIcon(eTacti1);
        }
    }
    if (object()->Adapt1Attachable())
    {
        if (object()->IsAdapt1Attached())
        {
            if (!GetIcon(eAdapt1) || bForceReInitAddons)
            {
                CreateIcon(eAdapt1);
                RefreshOffset();
                InitAddon(GetIcon(eAdapt1), *object()->GetAdapt1Name(), m_addon_offset[eAdapt1], Heading());
            }
        }
        else
        {
            if (m_addons[eAdapt1])
                DestroyIcon(eAdapt1);
        }
    }
    if (object()->Adapt2Attachable())
    {
        if (object()->IsAdapt2Attached())
        {
            if (!GetIcon(eAdapt2) || bForceReInitAddons)
            {
                CreateIcon(eAdapt2);
                RefreshOffset();
                InitAddon(GetIcon(eAdapt2), *object()->GetAdapt2Name(), m_addon_offset[eAdapt2], Heading());
            }
        }
        else
        {
            if (m_addons[eAdapt2])
                DestroyIcon(eAdapt2);
        }
    }
    if (object()->LaserrAttachable())
    {
        if (object()->IsLaserrAttached())
        {
            if (!GetIcon(eLaserr) || bForceReInitAddons)
            {
                CreateIcon(eLaserr);
                RefreshOffset();
                InitAddon(GetIcon(eLaserr), *object()->GetLaserrName(), m_addon_offset[eLaserr], Heading());
            }
        }
        else
        {
            if (m_addons[eLaserr])
                DestroyIcon(eLaserr);
        }
    }

    if (object()->ScopeAttachable())
    {
        if (object()->IsScopeAttached())
        {
            if (!GetIcon(eScope) || bForceReInitAddons)
            {
                CreateIcon(eScope);
                RefreshOffset();
                InitAddon(GetIcon(eScope), *object()->GetScopeName(), m_addon_offset[eScope], Heading());
            }
        }
        else
        {
            if (m_addons[eScope])
                DestroyIcon(eScope);
        }
    }

    if (object()->GrenadeLauncherAttachable())
    {
        if (object()->IsGrenadeLauncherAttached())
        {
            if (!GetIcon(eLauncher) || bForceReInitAddons)
            {
                CreateIcon(eLauncher);
                RefreshOffset();
                InitAddon(
                    GetIcon(eLauncher), *object()->GetGrenadeLauncherName(), m_addon_offset[eLauncher], Heading());
            }
        }
        else
        {
            if (m_addons[eLauncher])
                DestroyIcon(eLauncher);
        }
    }
}

void CUIWeaponCellItem::SetTextureColor(u32 color)
{
    inherited::SetTextureColor(color);
    if (m_addons[eSilencer])
    {
        m_addons[eSilencer]->SetTextureColor(color);
    }
    if (m_addons[eGrip])
    {
        m_addons[eGrip]->SetTextureColor(color);
    }
    if (m_addons[eBarrel])
    {
        m_addons[eBarrel]->SetTextureColor(color);
    }
    if (m_addons[eBipods])
    {
        m_addons[eBipods]->SetTextureColor(color);
    }
    if (m_addons[eScope])
    {
        m_addons[eScope]->SetTextureColor(color);
    }
    if (m_addons[eFlight])
    {
        m_addons[eFlight]->SetTextureColor(color);
    }
    if (m_addons[eChargs])
    {
        m_addons[eChargs]->SetTextureColor(color);
    }
    if (m_addons[eFgrips])
    {
        m_addons[eFgrips]->SetTextureColor(color);
    }
    if (m_addons[eGblock])
    {
        m_addons[eGblock]->SetTextureColor(color);
    }
    if (m_addons[eSightf])
    {
        m_addons[eSightf]->SetTextureColor(color);
    }
    if (m_addons[eMagazn])
    {
        m_addons[eMagazn]->SetTextureColor(color);
    }
    if (m_addons[eHguard])
    {
        m_addons[eHguard]->SetTextureColor(color);
    }
    if (m_addons[eSightr])
    {
        m_addons[eSightr]->SetTextureColor(color);
    }
    if (m_addons[eMounts])
    {
        m_addons[eMounts]->SetTextureColor(color);
    }
    if (m_addons[eMuzzle])
    {
        m_addons[eMuzzle]->SetTextureColor(color);
    }
    if (m_addons[eRcievr])
    {
        m_addons[eRcievr]->SetTextureColor(color);
    }
    if (m_addons[eSights])
    {
        m_addons[eSights]->SetTextureColor(color);
    }
    if (m_addons[eSight2])
    {
        m_addons[eSight2]->SetTextureColor(color);
    }
    if (m_addons[eStocks])
    {
        m_addons[eStocks]->SetTextureColor(color);
    }
    if (m_addons[eLauncher])
    {
        m_addons[eLauncher]->SetTextureColor(color);
    }
    if (m_addons[eTacti1])
    {
        m_addons[eTacti1]->SetTextureColor(color);
    }
    if (m_addons[eAdapt1])
    {
        m_addons[eAdapt1]->SetTextureColor(color);
    }
    if (m_addons[eAdapt2])
    {
        m_addons[eAdapt2]->SetTextureColor(color);
    }
    if (m_addons[eLaserr])
    {
        m_addons[eLaserr]->SetTextureColor(color);
    }
}

void CUIWeaponCellItem::OnAfterChild(CUIDragDropListEx* parent_list)
{
    if (is_silencer() && GetIcon(eSilencer))
        InitAddon(GetIcon(eSilencer), *object()->GetSilencerName(), m_addon_offset[eSilencer],
            parent_list->GetVerticalPlacement());

    if (is_grip() && GetIcon(eGrip))
        InitAddon(GetIcon(eGrip), *object()->GetGripName(), m_addon_offset[eGrip],
            parent_list->GetVerticalPlacement());

    if (is_scope() && GetIcon(eScope))
        InitAddon(
            GetIcon(eScope), *object()->GetScopeName(), m_addon_offset[eScope], parent_list->GetVerticalPlacement());

    if (is_launcher() && GetIcon(eLauncher))
        InitAddon(GetIcon(eLauncher), *object()->GetGrenadeLauncherName(), m_addon_offset[eLauncher],
            parent_list->GetVerticalPlacement());

    if (is_barrel() && GetIcon(eBarrel))
        InitAddon(GetIcon(eBarrel), *object()->GetBarrelName(), m_addon_offset[eBarrel],
            parent_list->GetVerticalPlacement());

    if (is_bipods() && GetIcon(eBipods))
        InitAddon(GetIcon(eBipods), *object()->GetBipodsName(), m_addon_offset[eBipods],
            parent_list->GetVerticalPlacement());

    if (is_chargs() && GetIcon(eChargs))
        InitAddon(GetIcon(eChargs), *object()->GetChargsName(), m_addon_offset[eChargs],
            parent_list->GetVerticalPlacement());

    if (is_chargh() && GetIcon(eChargh))
        InitAddon(GetIcon(eChargh), *object()->GetCharghName(), m_addon_offset[eChargh],
            parent_list->GetVerticalPlacement());

    if (is_flight() && GetIcon(eFlight))
        InitAddon(GetIcon(eFlight), *object()->GetFlightName(), m_addon_offset[eFlight],
            parent_list->GetVerticalPlacement());

    if (is_fgrips() && GetIcon(eFgrips))
        InitAddon(GetIcon(eFgrips), *object()->GetFgripsName(), m_addon_offset[eFgrips],
            parent_list->GetVerticalPlacement());

    if (is_gblock() && GetIcon(eGblock))
        InitAddon(GetIcon(eGblock), *object()->GetGblockName(), m_addon_offset[eGblock],
            parent_list->GetVerticalPlacement());

    if (is_hguard() && GetIcon(eHguard))
        InitAddon(GetIcon(eHguard), *object()->GetHguardName(), m_addon_offset[eHguard],
            parent_list->GetVerticalPlacement());

    if (is_magazn() && GetIcon(eMagazn))
        InitAddon(GetIcon(eMagazn), *object()->GetMagaznName(), m_addon_offset[eMagazn],
            parent_list->GetVerticalPlacement());

    if (is_mounts() && GetIcon(eMounts))
        InitAddon(GetIcon(eMounts), *object()->GetMountsName(), m_addon_offset[eMounts],
            parent_list->GetVerticalPlacement());

    if (is_muzzle() && GetIcon(eMuzzle))
        InitAddon(GetIcon(eMuzzle), *object()->GetMuzzleName(), m_addon_offset[eMuzzle],
            parent_list->GetVerticalPlacement());

    if (is_rcievr() && GetIcon(eRcievr))
        InitAddon(GetIcon(eRcievr), *object()->GetRcievrName(), m_addon_offset[eRcievr],
            parent_list->GetVerticalPlacement());

    if (is_sights() && GetIcon(eSights))
        InitAddon(GetIcon(eSights), *object()->GetSightsName(), m_addon_offset[eSights],
            parent_list->GetVerticalPlacement());

    if (is_sightf() && GetIcon(eSightf))
        InitAddon(GetIcon(eSightf), *object()->GetSightfName(), m_addon_offset[eSightf],
            parent_list->GetVerticalPlacement());

    if (is_sightr() && GetIcon(eSightr))
        InitAddon(GetIcon(eSightr), *object()->GetSightrName(), m_addon_offset[eSightr],
            parent_list->GetVerticalPlacement());

    if (is_sight2() && GetIcon(eSight2))
        InitAddon(GetIcon(eSight2), *object()->GetSight2Name(), m_addon_offset[eSight2],
            parent_list->GetVerticalPlacement());

    if (is_stocks() && GetIcon(eStocks))
        InitAddon(GetIcon(eStocks), *object()->GetStocksName(), m_addon_offset[eStocks],
            parent_list->GetVerticalPlacement());

    if (is_tacti1() && GetIcon(eTacti1))
        InitAddon(GetIcon(eTacti1), *object()->GetTacti1Name(), m_addon_offset[eTacti1],
            parent_list->GetVerticalPlacement());

    if (is_adapt1() && GetIcon(eAdapt1))
        InitAddon(GetIcon(eAdapt1), *object()->GetAdapt1Name(), m_addon_offset[eAdapt1],
            parent_list->GetVerticalPlacement());

    if (is_adapt2() && GetIcon(eAdapt2))
        InitAddon(GetIcon(eAdapt2), *object()->GetAdapt2Name(), m_addon_offset[eAdapt2],
            parent_list->GetVerticalPlacement());

    if (is_laserr() && GetIcon(eLaserr))
        InitAddon(GetIcon(eLaserr), *object()->GetLaserrName(), m_addon_offset[eLaserr],
            parent_list->GetVerticalPlacement());







}

void CUIWeaponCellItem::InitAddon(CUIStatic* s, LPCSTR section, Fvector2 addon_offset, bool b_rotate)
{
    Frect tex_rect;
    Fvector2 base_scale;

    if (Heading())
    {
        base_scale.x = GetHeight() / (INV_GRID_WIDTHF * m_grid_size.x);
        base_scale.y = GetWidth() / (INV_GRID_HEIGHTF * m_grid_size.y);
    }
    else
    {
        base_scale.x = GetWidth() / (INV_GRID_WIDTHF * m_grid_size.x);
        base_scale.y = GetHeight() / (INV_GRID_HEIGHTF * m_grid_size.y);
    }
    Fvector2 cell_size;
    cell_size.x = pSettings->r_u32(section, "inv_grid_width") * INV_GRID_WIDTHF;
    cell_size.y = pSettings->r_u32(section, "inv_grid_height") * INV_GRID_HEIGHTF;

    tex_rect.x1 = pSettings->r_u32(section, "inv_grid_x") * INV_GRID_WIDTHF;
    tex_rect.y1 = pSettings->r_u32(section, "inv_grid_y") * INV_GRID_HEIGHTF;

    tex_rect.rb.add(tex_rect.lt, cell_size);

    cell_size.mul(base_scale);

    if (b_rotate)
    {
        s->SetWndSize(Fvector2().set(cell_size.y, cell_size.x));
        Fvector2 new_offset;
        new_offset.x = addon_offset.y * base_scale.x;
        new_offset.y = GetHeight() - addon_offset.x * base_scale.x - cell_size.x;
        addon_offset = new_offset;
        addon_offset.x *= UI().get_current_kx();
    }
    else
    {
        s->SetWndSize(cell_size);
        addon_offset.mul(base_scale);
    }

    s->SetWndPos(addon_offset);
    s->SetTextureRect(tex_rect);
    s->SetStretchTexture(true);

    s->EnableHeading(b_rotate);

    if (b_rotate)
    {
        s->SetHeading(GetHeading());
        Fvector2 offs;
        offs.set(0.0f, s->GetWndSize().y);
        s->SetHeadingPivot(Fvector2().set(0.0f, 0.0f), /*Fvector2().set(0.0f,0.0f)*/ offs, true);
    }
}

CUIDragItem* CUIWeaponCellItem::CreateDragItem()
{
    CUIDragItem* i = inherited::CreateDragItem();
    CUIStatic* s = NULL;

    if (GetIcon(eSilencer))
    {
        s = xr_new<CUIStatic>();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetSilencerName(), m_addon_offset[eSilencer], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }

    if (GetIcon(eGrip))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetGripName(), m_addon_offset[eGrip], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eBarrel))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetBarrelName(), m_addon_offset[eBarrel], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eBipods))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetBipodsName(), m_addon_offset[eBipods], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eChargs))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetChargsName(), m_addon_offset[eChargs], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eChargh))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetCharghName(), m_addon_offset[eChargh], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eFlight))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetFlightName(), m_addon_offset[eFlight], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eFgrips))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetFgripsName(), m_addon_offset[eFgrips], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eGblock))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetGblockName(), m_addon_offset[eGblock], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eHguard))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetHguardName(), m_addon_offset[eHguard], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eMagazn))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetMagaznName(), m_addon_offset[eMagazn], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eMounts))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetMountsName(), m_addon_offset[eMounts], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eMuzzle))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetMuzzleName(), m_addon_offset[eMuzzle], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eRcievr))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetRcievrName(), m_addon_offset[eRcievr], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eSights))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetSightsName(), m_addon_offset[eSights], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eSightf))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetSightfName(), m_addon_offset[eSightf], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eSightr))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetSightrName(), m_addon_offset[eSightr], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eSight2))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetSight2Name(), m_addon_offset[eSight2], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eStocks))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetStocksName(), m_addon_offset[eStocks], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eTacti1))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetTacti1Name(), m_addon_offset[eTacti1], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eAdapt1))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetAdapt1Name(), m_addon_offset[eAdapt1], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eAdapt2))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetAdapt2Name(), m_addon_offset[eAdapt2], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    if (GetIcon(eLaserr))
    {
        s = new CUIStatic();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetLaserrName(), m_addon_offset[eLaserr], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }

    if (GetIcon(eScope))
    {
        s = xr_new<CUIStatic>();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetScopeName(), m_addon_offset[eScope], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }

    if (GetIcon(eLauncher))
    {
        s = xr_new<CUIStatic>();
        s->SetAutoDelete(true);
        s->SetShader(InventoryUtilities::GetEquipmentIconsShader());
        InitAddon(s, *object()->GetGrenadeLauncherName(), m_addon_offset[eLauncher], false);
        s->SetTextureColor(i->wnd()->GetTextureColor());
        i->wnd()->AttachChild(s);
    }
    return i;
}

bool CUIWeaponCellItem::EqualTo(CUICellItem* itm)
{
    if (!inherited::EqualTo(itm))
        return false;

    CUIWeaponCellItem* ci = smart_cast<CUIWeaponCellItem*>(itm);
    if (!ci)
        return false;

    //	bool b_addons					= ( (object()->GetAddonsState() == ci->object()->GetAddonsState()) );
    if (object()->GetAddonsState() != ci->object()->GetAddonsState())
    {
        return false;
    }
    if (this->is_scope() && ci->is_scope())
    {
        if (object()->GetScopeName() != ci->object()->GetScopeName())
        {
            return false;
        }
    }
    //	bool b_place					= ( (object()->m_eItemCurrPlace == ci->object()->m_eItemCurrPlace) );

    return true;
}

CBuyItemCustomDrawCell::CBuyItemCustomDrawCell(LPCSTR str, CGameFont* pFont)
{
    m_pFont = pFont;
    VERIFY(xr_strlen(str) < 16);
    xr_strcpy(m_string, str);
}

void CBuyItemCustomDrawCell::OnDraw(CUICellItem* cell)
{
    Fvector2 pos;
    cell->GetAbsolutePos(pos);
    UI().ClientToScreenScaled(pos, pos.x, pos.y);
    m_pFont->Out(pos.x, pos.y, m_string);
    m_pFont->OnRender();
}
