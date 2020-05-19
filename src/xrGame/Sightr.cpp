///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Sightr.h"

CSightr::CSightr() {}
CSightr::~CSightr() {}
bool CSightr::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CSightr::Load(LPCSTR section) { inherited::Load(section); }
void CSightr::net_Destroy() { inherited::net_Destroy(); }
void CSightr::UpdateCL() { inherited::UpdateCL(); }
void CSightr::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CSightr::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
