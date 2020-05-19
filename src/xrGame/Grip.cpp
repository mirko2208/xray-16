///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Grip.h"

CGrip::CGrip() {}
CGrip::~CGrip() {}
bool CGrip::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CGrip::Load(LPCSTR section) { inherited::Load(section); }
void CGrip::net_Destroy() { inherited::net_Destroy(); }
void CGrip::UpdateCL() { inherited::UpdateCL(); }
void CGrip::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CGrip::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
