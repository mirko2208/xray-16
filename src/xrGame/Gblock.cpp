///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Gblock.h"

CGblock::CGblock() {}
CGblock::~CGblock() {}
BOOL CGblock::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CGblock::Load(LPCSTR section) { inherited::Load(section); }
void CGblock::net_Destroy() { inherited::net_Destroy(); }
void CGblock::UpdateCL() { inherited::UpdateCL(); }
void CGblock::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CGblock::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
