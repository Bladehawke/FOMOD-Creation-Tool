//---------------------------------------------------------------------------

#ifndef DataClassesH
#define DataClassesH

#include <vcl.h>
#include <vector.h>

class CCondition
{
    public:
        CCondition();
        CCondition(UnicodeString name, UnicodeString value);

        UnicodeString Name;
        UnicodeString Value;
};

class CFile
{
    public:
        CFile();

        UnicodeString Type;
        UnicodeString SrcPath;
        UnicodeString DstPath;
};

class CDependency
{
    public:
        CDependency();

        UnicodeString Type;
        UnicodeString Name;
        UnicodeString Value;
};

class CDependencyPattern
{
    public:
        CDependencyPattern();
        ~CDependencyPattern();

        UnicodeString Operator;
        UnicodeString Type;
        vector <CDependency> Dependencies;
};

class CPlugin
{
    public:
        CPlugin();
        CPlugin(UnicodeString name);
        ~CPlugin();

        UnicodeString Name;
        UnicodeString Description;
        UnicodeString ImagePath;
        UnicodeString DefaultType;
        vector <CCondition> ConditionSet;
        vector <CFile> Files;
        vector <CDependencyPattern> DependencyPatterns;
};

class CPluginGroup
{
    public:
        CPluginGroup();
        CPluginGroup(UnicodeString name, UnicodeString type);
        ~CPluginGroup();

        UnicodeString Name;
        UnicodeString Type;
        vector <CPlugin> Plugins;
};

class CStep
{
    public:
        CStep();
        CStep(UnicodeString name);
        ~CStep();

        UnicodeString Name;
        vector <CCondition> ConditionSet;
        vector <CPluginGroup> PluginGroups;
};

class CFOMOD
{
    public:
        CFOMOD();
        CFOMOD(UnicodeString name);
        ~CFOMOD();

        UnicodeString Name;
        UnicodeString AuthorName;
        UnicodeString Version;
        UnicodeString ModCategory;
        UnicodeString URL;
        UnicodeString Description;
        vector <CStep> Steps;
};

//---------------------------------------------------------------------------
#endif
