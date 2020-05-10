///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Flight.h"

CFlight::CFlight() {}
CFlight::~CFlight() {}
BOOL CFlight::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CFlight::Load(LPCSTR section) { inherited::Load(section); }
void CFlight::net_Destroy() { inherited::net_Destroy(); }
void CFlight::UpdateCL() { inherited::UpdateCL(); }
void CFlight::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CFlight::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
