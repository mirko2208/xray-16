///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Sights.h"

CSights::CSights() {}
CSights::~CSights() {}
bool CSights::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CSights::Load(LPCSTR section) { inherited::Load(section); }
void CSights::net_Destroy() { inherited::net_Destroy(); }
void CSights::UpdateCL() { inherited::UpdateCL(); }
void CSights::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CSights::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
