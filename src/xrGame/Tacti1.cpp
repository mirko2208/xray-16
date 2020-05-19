///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Tacti1.h"

CTacti1::CTacti1() {}
CTacti1::~CTacti1() {}
bool CTacti1::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CTacti1::Load(LPCSTR section) { inherited::Load(section); }
void CTacti1::net_Destroy() { inherited::net_Destroy(); }
void CTacti1::UpdateCL() { inherited::UpdateCL(); }
void CTacti1::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CTacti1::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }

