///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Chargh.h"

CChargh::CChargh() {}
CChargh::~CChargh() {}
BOOL CChargh::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CChargh::Load(LPCSTR section) { inherited::Load(section); }
void CChargh::net_Destroy() { inherited::net_Destroy(); }
void CChargh::UpdateCL() { inherited::UpdateCL(); }
void CChargh::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CChargh::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
