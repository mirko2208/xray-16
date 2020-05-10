///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Adapt1.h"

CAdapt1::CAdapt1() {}
CAdapt1::~CAdapt1() {}
BOOL CAdapt1::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CAdapt1::Load(LPCSTR section) { inherited::Load(section); }
void CAdapt1::net_Destroy() { inherited::net_Destroy(); }
void CAdapt1::UpdateCL() { inherited::UpdateCL(); }
void CAdapt1::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CAdapt1::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
