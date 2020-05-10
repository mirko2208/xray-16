#include "pch_script.h"
#include "Scope.h"
#include "Silencer.h"
#include "Grip.h"
#include "Barrel.h"
#include "Chargs.h"
#include "Bipods.h"
#include "Chargh.h"
#include "Flight.h"
#include "Fgrips.h"
#include "Gblock.h"
#include "Hguard.h"
#include "Magazn.h"
#include "Mounts.h"
#include "Muzzle.h"
#include "Rcievr.h"
#include "Sights.h"
#include "Sightf.h"
#include "Sightr.h"
#include "Sight2.h"
#include "Stocks.h"
#include "Tacti1.h"
#include "Adapt1.h"
#include "Adapt2.h"
#include "Laserr.h"
#include "GrenadeLauncher.h"
#include "xrScriptEngine/ScriptExporter.hpp"

CScope::CScope() {}
CScope::~CScope() {}
using namespace luabind;

SCRIPT_EXPORT(CScope, (CGameObject), {
    module(luaState)[class_<CScope, CGameObject>("CScope").def(constructor<>()),

        class_<CSilencer, CGameObject>("CSilencer").def(constructor<>()),
        class_<CGrip, CGameObject>("CGrip").def(constructor<>()),
        class_<CBarrel, CGameObject>("CBarrel").def(constructor<>()),
        class_<CChargs, CGameObject>("CChargs").def(constructor<>()),
        class_<CBipods, CGameObject>("CBipods").def(constructor<>()),
        class_<CChargh, CGameObject>("CChargh").def(constructor<>()),
        class_<CFlight, CGameObject>("CFlight").def(constructor<>()),
        class_<CFgrips, CGameObject>("CFgrips").def(constructor<>()),
        class_<CGblock, CGameObject>("CGblock").def(constructor<>()),
        class_<CHguard, CGameObject>("CHguard").def(constructor<>()),
        class_<CMagazn, CGameObject>("CMagazn").def(constructor<>()),
        class_<CMounts, CGameObject>("CMounts").def(constructor<>()),
        class_<CMuzzle, CGameObject>("CMuzzle").def(constructor<>()),
        class_<CRcievr, CGameObject>("CRcievr").def(constructor<>()),
        class_<CSights, CGameObject>("CSights").def(constructor<>()),
        class_<CSightf, CGameObject>("CSightf").def(constructor<>()),
        class_<CSightr, CGameObject>("CSightr").def(constructor<>()),
        class_<CSight2, CGameObject>("CSight2").def(constructor<>()),
        class_<CStocks, CGameObject>("CStocks").def(constructor<>()),
        class_<CTacti1, CGameObject>("CTacti1").def(constructor<>()),
        class_<CAdapt2, CGameObject>("CAdapt2").def(constructor<>()),
        class_<CAdapt1, CGameObject>("CAdapt1").def(constructor<>()),
        class_<CGrenadeLauncher, CGameObject>("CGrenadeLauncher").def(constructor<>())];
});
