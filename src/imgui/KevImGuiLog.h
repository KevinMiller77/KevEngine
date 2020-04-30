#ifndef __KEV_IMGUI_LOG__
#define __KEV_IMGUI_LOG__

#include <../ext/imgui/imgui.h>
#include <utils/Logging.h>
#include <utils/Timer.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define LOG_FILE_PATH "console.txt"

class KevImGuiLog
{
    //Log props
    int filePlace;
    
    Timer refreshRate;
    
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;    // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
    bool                AutoScroll;     // Keep scrolling if already at the bottom

public:
    static FILE* stdoutFile;
    KevImGuiLog();
    ~KevImGuiLog();
    void Clear();
    void AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void UpdateBuffer(FILE* InFile = stdoutFile);
    void Update(bool& LogOpen);
    void Draw(const char* title, bool* p_open = NULL);
};

#endif
