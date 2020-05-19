///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Barrel.h"

CBarrel::CBarrel() {}
CBarrel::~CBarrel() {}
bool CBarrel::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CBarrel::Load(LPCSTR section) { inherited::Load(section); }
void CBarrel::net_Destroy() { inherited::net_Destroy(); }
void CBarrel::UpdateCL() { inherited::UpdateCL(); }
void CBarrel::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CBarrel::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
