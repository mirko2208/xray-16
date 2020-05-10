///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Sight2.h"

CSight2::CSight2() {}
CSight2::~CSight2() {}
BOOL CSight2::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CSight2::Load(LPCSTR section) { inherited::Load(section); }
void CSight2::net_Destroy() { inherited::net_Destroy(); }
void CSight2::UpdateCL() { inherited::UpdateCL(); }
void CSight2::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CSight2::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
