#pragma once
#include "BaseGui.h"
#include "ImGuiColorTextEdit/TextEditor.h"

class FileBrowserNode
{
public:
    FileBrowserNode() = default;
    FileBrowserNode(const std::filesystem::path& Path_) : Path(Path_) {}
    ~FileBrowserNode() { Children.clear(); }

    std::vector<FileBrowserNode> Children;

    std::filesystem::path Path;

    bool IsSelected = false;
    bool IsOpen = false;
    bool IsFolder = false; //Is a file if true and a folder if false.
    bool IsEmpty = true;

    int Index = 0;

    std::string Label = {};

    ImGuiTreeNodeFlags Flags = 0;
};

class TextEditorWrapper : public BaseGui
{
public:
    TextEditorWrapper(bool* OpenState_, std::string Title_);
    ~TextEditorWrapper() = default;

    void Draw() override;

    void DrawMenuBar();
    void DrawToolbar();

    void DrawFileBrowserNodes();
    void DrawFileBrowserNode(FileBrowserNode& Node);

    void GenerateFileBrowserNodes();
    void GenerateFileBrowserNode(FileBrowserNode& Node);

    void TryOpenBrowserNode(FileBrowserNode& Node);
    bool ScriptBeenEdited() const;

    ImGuiWindowFlags MainOverlayWindowFlags = 0;

    void RunCurrentScript();
    void ClearErrorMarkers();

    bool LoadScript(std::string FullPath, std::string NewScriptName);
    bool SaveScript();
    std::string FixScriptExtension(std::string CurrentScriptName);
    void ClearScript();

    void ProcessPopups();
    void DrawNewScriptPopup();
    void DrawOpenScriptPopup();
    void DrawSaveScriptPopup();
    void DrawSaveAsScriptPopup();
    void DrawConfirmSaveChangesPopup();

    std::string GetCurrentScriptString();
    void LoadLanguageDefinitions();

    std::string ScriptName = "NewScript.lua";
    const std::string DefaultScriptName = "NewScript.lua";
    //ScriptManager* Scripts = nullptr;

    bool ShowNewScriptPopup = false;
    bool ShowOpenScriptPopup = false;
    bool ShowSaveScriptPopup = false;
    bool ShowSaveAsScriptPopup = false;
    bool ShowConfirmSaveChangesPopup = false;

    std::string NewNameBuffer;

private:
    TextEditor Editor;
    nlohmann::json LanguageConfig;

    int NodeIndex = 0;
    int SelectedIndex = -1;
    FileBrowserNode FileBrowserRootNode;

    std::string InitialScript;
    FileBrowserNode* PendingOpenNode = nullptr;
};