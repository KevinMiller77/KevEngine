#include "KevImGuiLog.h"

FILE* KevImGuiLog::stdoutFile = (FILE*)nullptr;

KevImGuiLog::KevImGuiLog()
{
    LOG_INF("Moving stdout to ImGui\n");
    
    stdoutFile = fopen(LOG_FILE_PATH, "w");
        
    if (stdoutFile)
    {
        stdoutFile = freopen(LOG_FILE_PATH, "r+a", stdout);
    }
    filePlace = 0;
    
    
    Buf.clear();
    AutoScroll = true;
    Clear();
}

KevImGuiLog::~KevImGuiLog()
{
    if (stdoutFile)
    {
        fclose(stdoutFile);
    }
}

void  KevImGuiLog::Clear()
{
    Buf.clear();
    LineOffsets.clear();
    LineOffsets.push_back(0);
}

void KevImGuiLog::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
    int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);
    Buf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = Buf.size(); old_size < new_size; old_size++)
        if (Buf[old_size] == '\n')
            LineOffsets.push_back(old_size + 1);
}

void KevImGuiLog::Update(bool& LogOpen)
{
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Game Log", &LogOpen);
    
    ImGui::End();
    
    UpdateBuffer();
    Draw("Game Log", &LogOpen);
}

//NOTE: Do not print to stdout from this function!! It will infinite loop
void KevImGuiLog::UpdateBuffer(FILE* InFile)
{
    const unsigned int TIMEOUT_TIME = 500; //MS
    Timer timeout;
    timeout.Reset();
    
    if (InFile)
    {
        fseek(InFile, filePlace, SEEK_SET);
        while(!feof(InFile))
        {
            int oldSize = Buf.size();
            
            //Grab line
            char curLine[256];
            fgets(curLine, 256, InFile);
            Buf.append(curLine);
            
            //Increase base read index
            int new_size = Buf.size();
            filePlace += new_size - oldSize;
            
            for (new_size; oldSize < new_size; oldSize++)
            {
                if (Buf[oldSize] == '\n')
                {
                    LineOffsets.push_back(oldSize + 1);
                }
            }
            
            
            if (timeout.getTimeMS() > TIMEOUT_TIME)
            {
                break;
            }
        }
    }
}

void    KevImGuiLog::Draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &AutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    Filter.Draw("Filter", -100.0f);

    ImGui::Separator();
    ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (clear)
        Clear();
    if (copy)
        ImGui::LogToClipboard();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    const char* buf = Buf.begin();
    const char* buf_end = Buf.end();
    if (Filter.IsActive())
    {
        // In this example we don't use the clipper when Filter is enabled.
        // This is because we don't have a random access on the result on our filter.
        // A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
        // especially if the filtering function is not trivial (e.g. reg-exp).
        for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
        {
            const char* line_start = buf + LineOffsets[line_no];
            const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
            if (Filter.PassFilter(line_start, line_end))
                ImGui::TextUnformatted(line_start, line_end);
        }
    }
    else
    {
        // The simplest and easy way to display the entire buffer:
        //   ImGui::TextUnformatted(buf_begin, buf_end);
        // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
        // Here we instead demonstrate using the clipper to only process lines that are within the visible area.
        // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
        // Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
        // both of which we can handle since we an array pointing to the beginning of each line of text.
        // When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
        // Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
        ImGuiListClipper clipper;
        clipper.Begin(LineOffsets.Size);
        while (clipper.Step())
        {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                ImGui::TextUnformatted(line_start, line_end);
            }
        }
        clipper.End();
    }
    ImGui::PopStyleVar();

    if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}
