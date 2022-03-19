//---------------------------------------------------------------------------

#ifndef FOMODClassH
#define FOMODClassH

#include <vcl.h>
#include <vector>

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
        unsigned int  Priority;
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
		std::vector <CDependency> Dependencies;
};

class CPlugin
{
    public:
        CPlugin();
        explicit CPlugin(UnicodeString name);
        ~CPlugin();

        UnicodeString Name;
        UnicodeString Description;
        UnicodeString ImagePath;
        UnicodeString DefaultType = _T("Optional");
        std::vector <CCondition> ConditionSet;
        std::vector <CFile> Files;
        std::vector <CDependencyPattern> DependencyPatterns;
};

class CPluginGroup
{
    public:
        CPluginGroup();
        CPluginGroup(UnicodeString name, UnicodeString type);
        ~CPluginGroup();

        UnicodeString Name;
        UnicodeString Type;
        std::vector <CPlugin> Plugins;
};

class CStep
{
    public:
        CStep();
        explicit CStep(UnicodeString name);
        ~CStep();

        UnicodeString Name;
        UnicodeString VisibilityOperator = _T("And");
        std::vector <CDependency>  VisibilityDependencies;
        std::vector <CPluginGroup> PluginGroups;
};

class CConditionalFile
{
    public:
        CConditionalFile();
        ~CConditionalFile();

        UnicodeString Operator;
        std::vector <CDependency> Dependencies;
        std::vector <CFile> Files;
};

class CFOMOD
{
    public:
        CFOMOD();
        explicit CFOMOD(UnicodeString name);
        ~CFOMOD();

        UnicodeString Name;
        UnicodeString AuthorName;
        UnicodeString Version;
        UnicodeString ModCategory;
        UnicodeString URL;
        UnicodeString HeaderImagePath;
        UnicodeString Description;
        std::vector <CStep> Steps;
        std::vector <CFile> RequiredFiles;
		std::vector <CConditionalFile> ConditionalFiles;
};

//---------------------------------------------------------------------------
#endif
