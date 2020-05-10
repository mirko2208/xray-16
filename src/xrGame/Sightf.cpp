///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Sightf.h"

CSightf::CSightf() {}
CSightf::~CSightf() {}
BOOL CSightf::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CSightf::Load(LPCSTR section) { inherited::Load(section); }
void CSightf::net_Destroy() { inherited::net_Destroy(); }
void CSightf::UpdateCL() { inherited::UpdateCL(); }
void CSightf::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CSightf::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
