///////////////////////////////////////////////////////////////
// Silencer.h
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#pragma once
#include "inventory_item_object.h"

class CRcievr : public CInventoryItemObject
{
private:
    typedef CInventoryItemObject inherited;

public:
    CRcievr(void);
    virtual ~CRcievr(void);

    virtual bool net_Spawn(CSE_Abstract* DC);
    virtual void Load(LPCSTR section);
    virtual void net_Destroy();

    virtual void OnH_A_Chield();
    virtual void OnH_B_Independent(bool just_before_destroy);

    virtual void UpdateCL();
};
#pragma once
#pragma once
