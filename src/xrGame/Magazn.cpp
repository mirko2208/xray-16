///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Magazn.h"

CMagazn::CMagazn() {}
CMagazn::~CMagazn() {}
bool CMagazn::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CMagazn::Load(LPCSTR section) { inherited::Load(section); }
void CMagazn::net_Destroy() { inherited::net_Destroy(); }
void CMagazn::UpdateCL() { inherited::UpdateCL(); }
void CMagazn::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CMagazn::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
