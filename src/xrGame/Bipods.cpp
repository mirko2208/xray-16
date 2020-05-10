///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Bipods.h"

CBipods::CBipods() {}
CBipods::~CBipods() {}
BOOL CBipods::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CBipods::Load(LPCSTR section) { inherited::Load(section); }
void CBipods::net_Destroy() { inherited::net_Destroy(); }
void CBipods::UpdateCL() { inherited::UpdateCL(); }
void CBipods::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CBipods::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
