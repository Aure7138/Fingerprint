#include <iostream>
#include <cstdio>
#include "memory.h"
#include "hack.h"
#include <conio.h>
#include <assert.h>
#include "resource.h"
#include <fstream>

DWORD WINAPI threadHotKeys(LPVOID lpParam);
DWORD WINAPI threadScriptLoad(LPVOID lpParam);

std::wstring getProgramDir()
{
	wchar_t exeFullPath[MAX_PATH]; // Full path 
	std::wstring strPath = L"";
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);

	strPath = (std::wstring)exeFullPath;    // Get full path of the file 

	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos+1);  // Return the directory without the file name 
}

void showMenu()
{
	std::cout << "ModuleBaseAddr :" << std::hex << moduleStruct.addr << std::endl;
	std::cout << "ModuleBaseSize :" << std::hex << moduleStruct.size << std::endl;
	std::cout << "LocalScriptsPTR:" << std::hex << LocalScriptsPTR << std::endl;
	std::cout << "\n";

	std::cout << "\n";
	std::cout << "Fingerprint Crack                    :" << std::dec << Hack::keyFingerprintCrack << std::endl;
	std::cout << "Keypad Crack                         :" << std::dec << Hack::keyKeypadCrack << std::endl;
	std::cout << "Vault Door Quickly Open              :" << std::dec << Hack::keyVaultDoorQuicklyOpen << std::endl;
	std::cout << "Finish Perico sewer cutting          :" << std::dec << Hack::keySewerCutting << std::endl;
	std::cout << "\n";

	std::cout << "\n";
	std::cout << " 1) Perico Plasma Cutter Auto Finish   :" << (Hack::isPericoPlasmaCutterAutoFinish    ? "ON\n\n" : "OFF\n\n");
	std::cout << " 2) Perico Plasma Cutter Never Overheat:" << (Hack::isPericoPlasmaCutterNeverOverheat ? "ON\n\n" : "OFF\n\n");
	std::cout << " 3) Set Casino Income\n\n";
	std::cout << " 4) Set Casino Mission Life\n\n";
	std::cout << " 5) Set Perico Income\n\n";
	std::cout << " 6) Set Perico Mission Life\n\n";
	std::cout << " 7) Open Unknowncheats Url\n\n";
	std::cout << " 8) Open Github Url\n\n";
	std::cout << " 9) Exit Program\n";
	std::cout << "\n";
}

int main()
{
	SetConsoleTitle(L"GTA5 External Fingerprint Menu By Aure");
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	std::wstring str = L"Fingerprint.ini";
	str = getProgramDir() + str;
	std::ifstream f(str.c_str());
	if (f.good())
	{
		f.close();
		Hack::keyFingerprintCrack            = GetPrivateProfileInt(L"HotKeys", L"FingerprintCrack", 116, str.c_str());
		Hack::keyKeypadCrack                 = GetPrivateProfileInt(L"HotKeys", L"KeypadCrack", 117, str.c_str());
		Hack::keyVaultDoorQuicklyOpen        = GetPrivateProfileInt(L"HotKeys", L"VaultDoorQuicklyOpen", 118, str.c_str());
		Hack::keySewerCutting                = GetPrivateProfileInt(L"HotKeys", L"SewerCutting", 119, str.c_str());
	}
	else
	{
		WritePrivateProfileString(L"HotKeys", L"FingerprintCrack", L"116", str.c_str());
		WritePrivateProfileString(L"HotKeys", L"KeypadCrack", L"117", str.c_str());
		WritePrivateProfileString(L"HotKeys", L"VaultDoorQuicklyOpen", L"118", str.c_str());
		WritePrivateProfileString(L"HotKeys", L"SewerCutting", L"119", str.c_str());
	}

	g_dwProcessId   = getProcessId(L"GTA5.exe");
	if (g_dwProcessId == 0)
	{
		MessageBox(GetConsoleWindow(), L"Please run GTA5 first", L"Can't find GTA5.exe", MB_OK);
		return 0;
	}
	g_hProcess      = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_dwProcessId);
	moduleStruct    = getModuleStruct(g_dwProcessId, L"GTA5.exe");
	
	LocalScriptsPTR = patternScan(moduleStruct.addr, moduleStruct.size, (char*)"\x48\x8B\x05\x00\x00\x00\x00\x8B\xCF\x48\x8B\x0C\xC8\x39\x59\x68", (char*)"xxx????xxxxxxxxx");

	LocalScriptsPTR = LocalScriptsPTR + re<int>(LocalScriptsPTR + 3) + 7;

	CreateThread(NULL, 0, threadHotKeys   , NULL, 0, nullptr);
	CreateThread(NULL, 0, threadScriptLoad, NULL, 0, nullptr);

	showMenu();

	while (getProcessId(L"GTA5.exe") != 0)
	{
		int n;
		n = _getch();
		switch (n)
		{
			case '1':
			{
				Hack::isPericoPlasmaCutterAutoFinish = !Hack::isPericoPlasmaCutterAutoFinish;
				break;
			}
			case '2':
			{
				Hack::isPericoPlasmaCutterNeverOverheat = !Hack::isPericoPlasmaCutterNeverOverheat;
				break;
			}
			case '3':
			{
				system("cls");
				std::cout << "Enter Casino Income:";
				int m;
				std::cin >> m;
				Hack::setCasinoIncome(m);
				break;
			}
			case '4':
			{
				system("cls");
				std::cout << "Enter Casino Mission Life:";
				int m;
				std::cin >> m;
				Hack::setCasinoMissionLife(m);
				break;
			}
			case '5':
			{
				system("cls");
				std::cout << "Enter Perico Income:";
				int m;
				std::cin >> m;
				Hack::setPericoIncome(m);
				break;
			}
			case '6':
			{
				system("cls");
				std::cout << "Enter Perico Mission Life:";
				int m;
				std::cin >> m;
				Hack::setPericoMissionLife(m);
				break;
			}
			case '7':
			{
				const WCHAR szOperation[] = L"open";
				const WCHAR szAddress[] = L"https://www.unknowncheats.me/forum/grand-theft-auto-v/492935-gta5-external-fingerprint-menu.html#post3389282";
				HINSTANCE hRslt = ShellExecute(NULL, szOperation,
					szAddress, NULL, NULL, SW_SHOWNORMAL);
				assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
				break;
			}
			case '8':
			{
				const WCHAR szOperation[] = L"open";
				const WCHAR szAddress[] = L"https://github.com/Aure7138/Fingerprint";
				HINSTANCE hRslt = ShellExecute(NULL, szOperation,
					szAddress, NULL, NULL, SW_SHOWNORMAL);
				assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
				break;
			}
			case '9':
			{
				exit(0);
				break;
			}
			default:
			{
				break;
			}
		}
		system("cls");
		showMenu();
	}
	return 0;
}

DWORD WINAPI threadHotKeys(LPVOID lpParam)
{
	while (true)
	{
		Hack::checkKeys();
		Sleep(1);
	}
}

DWORD WINAPI threadScriptLoad(LPVOID lpParam)
{
	while (true)
	{
		if (getProcessId(L"GTA5.exe") == 0) exit(0);
		Hack::arcadePTR = Hack::getLocalScript((char*)"am_mp_arc_cab_manager");
		Hack::casinoPTR = Hack::getLocalScript((char*)"fm_mission_controller");
		Hack::pericoPTR = Hack::getLocalScript((char*)"fm_mission_controller_2020");
		if (Hack::isPericoPlasmaCutterAutoFinish) Hack::pericoPlasmaCutterAutoFinish();
		if (Hack::isPericoPlasmaCutterNeverOverheat) Hack::pericoPlasmaCutterNeverOverheat();
		Sleep(100);
	}
}