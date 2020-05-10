///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Mounts.h"

CMounts::CMounts() {}
CMounts::~CMounts() {}
BOOL CMounts::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CMounts::Load(LPCSTR section) { inherited::Load(section); }
void CMounts::net_Destroy() { inherited::net_Destroy(); }
void CMounts::UpdateCL() { inherited::UpdateCL(); }
void CMounts::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CMounts::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
