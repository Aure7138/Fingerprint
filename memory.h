#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

struct ModuleStruct
{
    DWORD64 addr;
	DWORD   size;
};

extern DWORD        g_dwProcessId;
extern HANDLE       g_hProcess;
extern ModuleStruct moduleStruct;

extern DWORD64 GlobalPTR;
extern DWORD64 LocalScriptsPTR;

DWORD        getProcessId(LPCWSTR processName);
ModuleStruct getModuleStruct(DWORD processId, LPCWSTR moduleName);
DWORD64      patternScan(DWORD64 base, DWORD len, char* sig, char* mask);

template<typename T> T re(DWORD64 address)
{
    T ret;
    ReadProcessMemory(g_hProcess, (void*)address, &ret, sizeof(T), 0);
    return ret;
};

template<typename T> void wr(DWORD64 address, T value)
{
    T ret = value;
    WriteProcessMemory(g_hProcess, (void*)address, &ret, sizeof(T), 0);
};

template<typename T> T res(DWORD64 address, std::vector<int> offsets)
{
    T ret;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(g_hProcess, (void*)address, &address, sizeof(address), 0);
        address = address + offsets[i];
    }
    ReadProcessMemory(g_hProcess, (void*)address, &ret, sizeof(T), 0);
    return ret;
};

template<typename T> void wrs(DWORD64 address, std::vector<int> offsets, T value)
{
    T ret = value;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(g_hProcess, (void*)address, &address, sizeof(address), 0);
        address = address + offsets[i];
    }
    WriteProcessMemory(g_hProcess, (void*)address, &ret, sizeof(T), 0);
};