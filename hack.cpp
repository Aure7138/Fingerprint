#include "hack.h"
#include <string>
#include <string.h>
namespace Hack
{
	int keyFingerprintCrack = 116;
	int keyKeypadCrack = 117;
	int keyVaultDoorQuicklyOpen = 118;
	int keySewerCutting = 119;

	bool isPericoPlasmaCutterAutoFinish = false;
	bool isPericoPlasmaCutterNeverOverheat = false;

	bool checkKeyState(int key)
	{
		static clock_t m_keyTmr = clock();

		if (clock() - m_keyTmr > 150 && GetAsyncKeyState(key) & 0x8000)
		{
			m_keyTmr = clock();
			return true;
		}
		return false;
	}
	void checkKeys()
	{
		if (checkKeyState(keyFingerprintCrack))
		{
			pericoFingerprintCrack();
			casinoFingerprintCrack();
			arcadeFingerprintCrack();
		}
		if (checkKeyState(keyKeypadCrack))
		{
			casinoKeypadCrack();
			arcadeKeypadCrack();
		}
		if (checkKeyState(keyVaultDoorQuicklyOpen))
		{
			casinoVaultDoorQuicklyOpen();
			arcadeVaultDoorQuicklyOpen();
		}
		if (checkKeyState(keySewerCutting))
		{
			pericoCompleteSewerCuts();
		}
	}
	//
	void pericoFingerprintCrack()
	{
		if (pericoPTR) wr<int>(pericoPTR + pericoFingerprint - 0x8, 143);
	}
	void casinoFingerprintCrack()
	{
		if (casinoPTR) wr<int>(casinoPTR + casinoFingerprint - 0x8, 11);
	}
	void arcadeFingerprintCrack()
	{
		if (arcadePTR) wr<int>(arcadePTR + arcadeFingerprint - 0x8, 11);
	}
	//
	void casinoKeypadCrack()
	{
		if (casinoPTR) wr<int>(casinoPTR + casinoKeypad - 0x8, 11);
	}
	void arcadeKeypadCrack()
	{
		if (arcadePTR) wr<int>(arcadePTR + arcadeKeypad - 0x8, 11);
	}
	//
	void casinoVaultDoorQuicklyOpen()
	{
		if (casinoPTR) wr<int>(casinoPTR + casinoVaultDoor, re<int>(casinoPTR + casinoVaultDoorMax));
	}
	void arcadeVaultDoorQuicklyOpen()
	{
		if (arcadePTR) wr<int>(arcadePTR + arcadeVaultDoor, re<int>(arcadePTR + arcadeVaultDoorMax));
	}
	//
	void pericoCompleteSewerCuts()
	{
		if (pericoPTR) wr<int>(pericoPTR + pericoSewerCutter, 6);
	}
	//
	void pericoPlasmaCutterAutoFinish()
	{
		if (pericoPTR) wr<float>(pericoPTR + pericoPlasmaCutter, 100.0);
	}
	//
	void pericoPlasmaCutterNeverOverheat()
	{
		if (pericoPTR) wr<float>(pericoPTR + pericoPlasmaCutterHeat, 0.0);
	}
	//
	void setCasinoIncome(int value)
	{
		if (casinoPTR) wr<int>(casinoPTR + casinoIncome, value);
	}
	//
	void setCasinoMissionLife(int value)
	{
		if (casinoPTR) wr<int>(casinoPTR + casinoMissionLife, value);
	}
	//
	void setPericoIncome(int value)
	{
		if (pericoPTR) wr<int>(pericoPTR + pericoIncome, value);
	}
	//
	void setPericoMissionLife(int value)
	{
		if(pericoPTR) wr<int>(pericoPTR + pericoMissionLife, value);
	}

	//void pericoPlasmaCutterAutoFinish()
	//{
	//	if (isPericoPlasmaCutterAutoFinish)
	//	{
	//		DWORD64 p = getLocalScript((char*)"fm_mission_controller_2020");
	//		if (p == 0) return;
	//		p = re<DWORD64>(p);
	//		wr<float>(p + pericoPlasmaCutter, 100.0);
	//	}
	//}
	//void setPericoIncome(int value)
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller_2020");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	wr<int>(p + pericoIncome, value);
	//}
	//void pericoFingerprintCrack()
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller_2020");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	int currentGroup = re<int>(p + pericoFingerprint + 0x10);
	//	for (int i = 0; i < 8; i++)
	//	{
	//		wr<int>(p + pericoFingerprint + 0x78 + 0xC8 * currentGroup + 0x18 * i, i);
	//	}
	//}
	//void setCasinoIncome(int value)
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	wr<int>(p + casinoIncome, value);
	//}
	//void casinoVaultDoorQuicklyOpen()
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	wr<int>(p + casinoVaultDoor, re<int>(p + casinoVaultDoorMax));
	//}
	//void casinoFingerprintCrack()
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	int currentGroup = re<int>(p + casinoFingerprint + 0x10);
	//	//wr<int>(p + casinoFingerprint + 0x10, 3);
	//	wr<int>(p + casinoFingerprint + 0x18, 4);
	//	//currentGroup = 3;
	//	for (int i = 0; i < 8; i++)
	//	{
	//		if (re<int>(p + casinoFingerprint + 0x80 + 0xC8 * currentGroup + 0x18 * i) == 2)
	//		{
	//			wr<int>(p + casinoFingerprint + 0x80 + 0xC8 * currentGroup + 0x18 * i, 3);
	//		}
	//	}
	//}
	//void casinoKeypadCrack()
	//{
	//	DWORD64 p = getLocalScript((char*)"fm_mission_controller");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	int currentGroup = re<int>(p + casinoKeypad + 0x10);
	//	if (currentGroup < 2)
	//	{
	//		wr<int>(p + casinoKeypad + 0x10, 2);
	//		currentGroup = 2;
	//	}
	//	wr<int>(p + casinoKeypad + 0x18, 5);
	//	for (int i = 0; i < 5; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (re<int>(p + casinoKeypad + 0x38 + 0x128 * currentGroup + 0x30 * i + 0x8 * j) == 1)
	//			{
	//				wr<int>(p + casinoKeypad + 0x38 + 0x128 * currentGroup + 0x30 * i + 0x8 * j, 3);
	//			}
	//		}
	//	}
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (re<int>(p + casinoKeypad + 0x38 + 0x128 * currentGroup + 0x30 * 5 + 0x8 * i) == 1)
	//		{
	//			wr<int>(p + casinoKeypad, i);
	//		}
	//	}
	//}
	//void arcadeVaultDoorQuicklyOpen()
	//{
	//	DWORD64 p = getLocalScript((char*)"am_mp_arc_cab_manager");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	wr<int>(p + arcadeVaultDoor, re<int>(p + arcadeVaultDoorMax));
	//}
	//void arcadeFingerprintCrack()
	//{
	//	DWORD64 p = getLocalScript((char*)"am_mp_arc_cab_manager");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	int currentGroup = re<int>(p + arcadeFingerprint + 0x10);
	//	wr<int>(p + arcadeFingerprint + 0x10, 3);
	//	wr<int>(p + arcadeFingerprint + 0x18, 4);
	//	currentGroup = 3;
	//	for (int i = 0; i < 8; i++)
	//	{
	//		if (re<int>(p + arcadeFingerprint + 0x80 + 0xC8 * currentGroup + 0x18 * i) == 2)
	//		{
	//			wr<int>(p + arcadeFingerprint + 0x80 + 0xC8 * currentGroup + 0x18 * i, 3);
	//		}
	//	}
	//}
	//void arcadeKeypadCrack()
	//{
	//	DWORD64 p = getLocalScript((char*)"am_mp_arc_cab_manager");
	//	if (p == 0) return;
	//	p = re<DWORD64>(p);
	//	int currentGroup = re<int>(p + arcadeKeypad + 0x10);
	//	wr<int>(p + arcadeKeypad + 0x10, 3);
	//	wr<int>(p + arcadeKeypad + 0x18, 5);
	//	currentGroup = 3;
	//	for (int i = 0; i < 5; i++)
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (re<int>(p + arcadeKeypad + 0x38 + 0x128 * currentGroup + 0x30 * i + 0x8 * j) == 1)
	//			{
	//				wr<int>(p + arcadeKeypad + 0x38 + 0x128 * currentGroup + 0x30 * i + 0x8 * j, 3);
	//			}
	//		}
	//	}
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (re<int>(p + arcadeKeypad + 0x38 + 0x128 * currentGroup + 0x30 * 5 + 0x8 * i) == 1)
	//		{
	//			wr<int>(p + arcadeKeypad, i);
	//		}
	//	}
	//}
	DWORD64 getLocalScript(char* name)
	{
		for (int i = 0; i < 54; i++)
		{
			DWORD64 p = re<DWORD64>(LocalScriptsPTR);
			p = re<DWORD64>(p + i * 0x8);
			DWORD64 lc_p = re<DWORD64>(p + 0xB0);
			if (lc_p == 0) continue;
			char lc_n[MAX_PATH];
			ReadProcessMemory(g_hProcess, (void*)(p + 0xD0), lc_n, MAX_PATH, 0);
			if (strcmp(name, lc_n) == 0) return lc_p;
		}
		return 0;
	}
	DWORD_PTR pericoPTR;
	DWORD_PTR casinoPTR;
	DWORD_PTR arcadePTR;
}