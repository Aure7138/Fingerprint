#include "memory.h"

DWORD        g_dwProcessId;
HANDLE       g_hProcess;
ModuleStruct moduleStruct;

DWORD64 LocalScriptsPTR;

DWORD getProcessId(LPCWSTR processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe) == 0)
    {
        CloseHandle(hSnapshot);
        return 0;
    }
    do
    {
        if (lstrcmp(pe.szExeFile, processName) == 0)
        {
            DWORD PID;
            PID = pe.th32ProcessID;
            CloseHandle(hSnapshot);
            return PID;
        }
    } while (Process32Next(hSnapshot, &pe));
    CloseHandle(hSnapshot);
    return 0;
}
ModuleStruct getModuleStruct(DWORD processId, LPCWSTR moduleName)
{
	ModuleStruct a;
    a.addr = 0;
    a.size = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    MODULEENTRY32 me;
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return a;
    }
    me.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &me) == 0)
    {
        CloseHandle(hSnapshot);
        return a;
    }
    do
    {
        if (lstrcmp(me.szModule, moduleName) == 0)
        {
            CloseHandle(hSnapshot);
            ModuleStruct b;
            b.addr = (DWORD64)me.modBaseAddr;
            b.size = (DWORD)me.modBaseSize;
            return b;
        }
    } while (Module32Next(hSnapshot, &me));
    CloseHandle(hSnapshot);
	return a;
}
DWORD64 patternScan(DWORD64 base, DWORD len, char* sig, char* mask)
{
    auto buffer = new char[len + 1];
    memset(buffer, 0, len + 1);
    ReadProcessMemory(g_hProcess, (LPVOID)base, buffer, len, 0);
    for (size_t i = 0; i < len; i++)
    {
        if ((buffer[i] == sig[0] && mask[0] == 'x') || (mask[0] == '?'))
        {
            for (size_t x = 0;; x++)
            {
                if (mask[x] == 'x')
                {
                    if (buffer[i + x] == sig[x])
                        continue;
                    else
                        break;
                }
                else if (mask[x] == 0x00)//'\0'
                {
                    delete[] buffer;
                    return (DWORD64)(base + i);
                }
            }
        }
    }
    delete[] buffer;
	return 0;
}