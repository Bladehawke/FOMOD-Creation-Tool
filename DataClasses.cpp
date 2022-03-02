//---------------------------------------------------------------------------

#pragma hdrstop

#include "DataClasses.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

CCondition::CCondition() {}
CCondition::CCondition(UnicodeString name, UnicodeString value) : Name(name), Value(value) {}

CFile::CFile() {}

CDependency::CDependency() {}

CDependencyPattern::CDependencyPattern() {}

CDependencyPattern::~CDependencyPattern()
{
    Dependencies.clear();
}

CPlugin::CPlugin()
{
    DefaultType = _T("Optional");
}
CPlugin::CPlugin(UnicodeString name) : Name(name)
{
    DefaultType = _T("Optional");
}
CPlugin::~CPlugin()
{
    ConditionSet.clear();
    Files.clear();
    DependencyPatterns.clear();
}

CPluginGroup::CPluginGroup() {}
CPluginGroup::CPluginGroup(UnicodeString name, UnicodeString type) : Name(name), Type(type) {}
CPluginGroup::~CPluginGroup()
{
    Plugins.clear();
}

CStep::CStep() {}
CStep::CStep(UnicodeString name) : Name(name) {}
CStep::~CStep()
{
    ConditionSet.clear();
    PluginGroups.clear();
}

CFOMOD::CFOMOD() {}
CFOMOD::CFOMOD(UnicodeString name) : Name(name) {};
CFOMOD::~CFOMOD()
{
    Steps.clear();
}
