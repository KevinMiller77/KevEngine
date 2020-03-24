#ifndef __KEV_IMGUI_LOG__
#define __KEV_IMGUI_LOG__

#include <../ext/imgui/imgui.h>

class KevImGuiLog
{
    //Log props
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
    bool                AutoScroll;     // Keep scrolling if already at the bottom

public:
    KevImGuiLog();
    void Clear();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Update(bool& LogOpen);
    void Draw(const char* title, bool* p_open = NULL);
};

#endif