#pragma once
#include <time.h>
#include <Windows.h>
#include "memory.h"
namespace Hack
{
	extern int keyFingerprintCrack            ;
	extern int keyKeypadCrack                 ;
	extern int keyVaultDoorQuicklyOpen_Normal ;
	extern int keyVaultDoorQuicklyOpen_Hard   ;

	const int pericoPlasmaCutter = 0x373A0;
	const int pericoIncome       = 0x50858;
	const int pericoFingerprint  = 0x2EBF0;
	const int casinoIncome       = 0x2B2D8;
	const int casinoVaultDoor    = 0x133E8;
	const int casinoFingerprint  = 0x68560;
	const int casinoKeypad       = 0x6A690;
	const int arcadeVaultDoor    = 0x3B90;
	const int arcadeFingerprint  = 0x7098;
	const int arcadeKeypad       = 0x8FC0; 

	extern bool isPericoPlasmaCutterAutoFinish;

	bool checkKeyState(int key);
	void checkKeys();

	void pericoPlasmaCutterAutoFinish();
	void setPericoIncome(int value);
	void pericoFingerprintCrack();
	void setCasinoIncome(int value);
	void casinoVaultDoorQuicklyOpen_Normal();
	void casinoVaultDoorQuicklyOpen_Hard();
	void casinoFingerprintCrack();
	void casinoKeypadCrack();
	void arcadeVaultDoorQuicklyOpen_Normal();
	void arcadeVaultDoorQuicklyOpen_Hard();
	void arcadeFingerprintCrack();
	void arcadeKeypadCrack();

	DWORD64 getLocalScript(char* name);
}