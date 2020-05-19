///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Rcievr.h"

CRcievr::CRcievr() {}
CRcievr::~CRcievr() {}
bool CRcievr::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CRcievr::Load(LPCSTR section) { inherited::Load(section); }
void CRcievr::net_Destroy() { inherited::net_Destroy(); }
void CRcievr::UpdateCL() { inherited::UpdateCL(); }
void CRcievr::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CRcievr::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
