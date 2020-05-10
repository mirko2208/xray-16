///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Laserr.h"

CLaserr::CLaserr() {}
CLaserr::~CLaserr() {}
BOOL CLaserr::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CLaserr::Load(LPCSTR section) { inherited::Load(section); }
void CLaserr::net_Destroy() { inherited::net_Destroy(); }
void CLaserr::UpdateCL() { inherited::UpdateCL(); }
void CLaserr::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CLaserr::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
