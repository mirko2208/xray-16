///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Chargs.h"

CChargs::CChargs() {}
CChargs::~CChargs() {}
BOOL CChargs::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CChargs::Load(LPCSTR section) { inherited::Load(section); }
void CChargs::net_Destroy() { inherited::net_Destroy(); }
void CChargs::UpdateCL() { inherited::UpdateCL(); }
void CChargs::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CChargs::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
