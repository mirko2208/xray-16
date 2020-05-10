///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Fgrips.h"

CFgrips::CFgrips() {}
CFgrips::~CFgrips() {}
BOOL CFgrips::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CFgrips::Load(LPCSTR section) { inherited::Load(section); }
void CFgrips::net_Destroy() { inherited::net_Destroy(); }
void CFgrips::UpdateCL() { inherited::UpdateCL(); }
void CFgrips::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CFgrips::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
