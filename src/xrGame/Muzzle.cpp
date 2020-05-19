///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Muzzle.h"

CMuzzle::CMuzzle() {}
CMuzzle::~CMuzzle() {}
bool CMuzzle::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CMuzzle::Load(LPCSTR section) { inherited::Load(section); }
void CMuzzle::net_Destroy() { inherited::net_Destroy(); }
void CMuzzle::UpdateCL() { inherited::UpdateCL(); }
void CMuzzle::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CMuzzle::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
