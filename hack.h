#pragma once
#include <time.h>
#include <Windows.h>
#include "memory.h"
namespace Hack
{
	extern int keyFingerprintCrack            ;
	extern int keyKeypadCrack                 ;
	extern int keyVaultDoorQuicklyOpen;

	const int pericoPlasmaCutter = 8 * (28269 + 3);
	const int pericoIncome       = 8 * (40004 + 1392 + 53);
	const int pericoFingerprint  = 0x2EBD0;

	const int casinoIncome       = 8 * (19652 + 2685);
	const int casinoVaultDoor    = 8 * (10068 + 7);
	const int casinoVaultDoorMax = 8 * (10068 + 37);
	const int casinoFingerprint  = 0x68CA0;
	const int casinoKeypad       = 0x6ADD0;

	const int arcadeVaultDoor    = 0x3AE8;
	const int arcadeVaultDoorMax = 0x3BD8;
	const int arcadeFingerprint  = 0x6FF0;
	const int arcadeKeypad       = 0x8F18;

	extern bool isPericoPlasmaCutterAutoFinish;

	bool checkKeyState(int key);
	void checkKeys();

	void pericoPlasmaCutterAutoFinish();
	void setPericoIncome(int value);
	void pericoFingerprintCrack();
	void setCasinoIncome(int value);
	void casinoVaultDoorQuicklyOpen();
	void casinoFingerprintCrack();
	void casinoKeypadCrack();
	void arcadeVaultDoorQuicklyOpen();
	void arcadeFingerprintCrack();
	void arcadeKeypadCrack();

	DWORD64 getLocalScript(char* name);
}