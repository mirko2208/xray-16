///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Adapt2.h"

CAdapt2::CAdapt2() {}
CAdapt2::~CAdapt2() {}
bool CAdapt2::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CAdapt2::Load(LPCSTR section) { inherited::Load(section); }
void CAdapt2::net_Destroy() { inherited::net_Destroy(); }
void CAdapt2::UpdateCL() { inherited::UpdateCL(); }
void CAdapt2::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CAdapt2::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
