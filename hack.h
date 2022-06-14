#pragma once
#include <time.h>
#include <Windows.h>
#include "memory.h"
namespace Hack
{
	extern int keyFingerprintCrack;
	extern int keyKeypadCrack;
	extern int keyVaultDoorQuicklyOpen;
	extern int keySewerCutting;

	const int pericoPlasmaCutter     = 8 * (28269 + 3);
	const int pericoPlasmaCutterHeat = 8 * (28269 + 4);
	const int pericoIncome           = 8 * (40004 + 1392 + 53);
	const int pericoFingerprint      = 0x2EBD0;
	const int pericoMissionLife      = 8 * (43059 + 865 + 1);
	const int pericoSewerCutter      = 0x34CE0;
								    
	const int casinoIncome           = 8 * (19652 + 2685);
	const int casinoVaultDoor        = 8 * (10068 + 7);
	const int casinoVaultDoorMax     = 8 * (10068 + 37);
	const int casinoFingerprint      = 0x68CA0;
	const int casinoKeypad           = 0x6ADD0;
	const int casinoMissionLife      = 8 * (26077 + 1322 + 1);
								    
	const int arcadeVaultDoor        = 0x3AE8;
	const int arcadeVaultDoorMax     = 0x3BD8;
	const int arcadeFingerprint      = 0x6FF0;
	const int arcadeKeypad           = 0x8F18;

	extern bool isPericoPlasmaCutterAutoFinish;
	extern bool isPericoPlasmaCutterNeverOverheat;

	bool checkKeyState(int key);
	void checkKeys();

	//
	void pericoFingerprintCrack();
	void casinoFingerprintCrack();
	void arcadeFingerprintCrack();
	//
	void casinoKeypadCrack();
	void arcadeKeypadCrack();
	//
	void casinoVaultDoorQuicklyOpen();
	void arcadeVaultDoorQuicklyOpen();
	//
	void pericoCompleteSewerCuts();
	//
	void pericoPlasmaCutterAutoFinish();
	//
	void pericoPlasmaCutterNeverOverheat();
	//
	void setCasinoIncome(int value);
	//
	void setCasinoMissionLife(int value);
	//
	void setPericoIncome(int value);
	//
	void setPericoMissionLife(int value);

	DWORD64 getLocalScript(char* name);

	extern DWORD_PTR pericoPTR;
	extern DWORD_PTR casinoPTR;
	extern DWORD_PTR arcadePTR;
}