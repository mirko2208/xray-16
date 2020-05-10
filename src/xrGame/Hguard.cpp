///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Hguard.h"

CHguard::CHguard() {}
CHguard::~CHguard() {}
BOOL CHguard::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CHguard::Load(LPCSTR section) { inherited::Load(section); }
void CHguard::net_Destroy() { inherited::net_Destroy(); }
void CHguard::UpdateCL() { inherited::UpdateCL(); }
void CHguard::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CHguard::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
