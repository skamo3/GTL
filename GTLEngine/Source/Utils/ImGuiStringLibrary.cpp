#include "pch.h"
#include "ImGuiStringLibrary.h"

#include "ImGui/imgui.h"

int UImGuiStringLibrary::Stricmp(const char* s1, const char* s2)
{ 
    int d;
    while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
    }
    
    return d;
}
int UImGuiStringLibrary::Strnicmp(const char* s1, const char* s2, int n)
{
    int d = 0;
    while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
    {
        s1++; s2++; n--;
    }

    return d;
}

char* UImGuiStringLibrary::Strdup(const char* s)
{ 
    IM_ASSERT(s);
    size_t len = strlen(s) + 1;
    void* buf = ImGui::MemAlloc(len);
    IM_ASSERT(buf);

    return (char*)memcpy(buf, (const void*)s, len);
}

void  UImGuiStringLibrary::Strtrim(char* s)
{
    char* str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ')
    {
        str_end--;
    }
    *str_end = 0;
}
