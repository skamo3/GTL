#pragma once

class UImGuiStringLibrary 
{
public:
    static int   Stricmp(const char* s1, const char* s2);

    static int   Strnicmp(const char* s1, const char* s2, int n);

    static char* Strdup(const char* s);

    static void  Strtrim(char* s);
};