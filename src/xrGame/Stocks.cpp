///////////////////////////////////////////////////////////////
// Silencer.cpp
// Silencer - апгрейд оружия глушитель
///////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Stocks.h"

CStocks::CStocks() {}
CStocks::~CStocks() {}
bool CStocks::net_Spawn(CSE_Abstract* DC) { return (inherited::net_Spawn(DC)); }
void CStocks::Load(LPCSTR section) { inherited::Load(section); }
void CStocks::net_Destroy() { inherited::net_Destroy(); }
void CStocks::UpdateCL() { inherited::UpdateCL(); }
void CStocks::OnH_A_Chield() { inherited::OnH_A_Chield(); }
void CStocks::OnH_B_Independent(bool just_before_destroy) { inherited::OnH_B_Independent(just_before_destroy); }
