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

        AnsiString Type;
        UnicodeString SrcPath;
        UnicodeString DstPath;
};

class CPlugin
{
    public:
        CPlugin();
        CPlugin(UnicodeString name);
        ~CPlugin();

        UnicodeString Name;
        UnicodeString Description;
        AnsiString ImagePath;
        vector <CCondition> ConditionSet;
        vector <CFile> Files;
};

class CPluginGroup
{
    public:
        CPluginGroup();
        CPluginGroup(UnicodeString name, AnsiString type);
        ~CPluginGroup();

        UnicodeString Name;
        AnsiString Type;
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
        AnsiString ModCategory;
        AnsiString URL;
        UnicodeString Description;
        vector <CStep> Steps;
};

//---------------------------------------------------------------------------
#endif
