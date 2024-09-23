#define _WIN32_WINNT 0x0600 
#include <windows.h>
#include <Sysinfoapi.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <fileapi.h>
#include <psapi.h>
#include <ntverp.h>

char* getAvailableDrives(unsigned int bitmask) {
	const int NUM_DRIVES = 26;									// Assuming drives from A to Z
	char* available_drives = (char*)malloc(NUM_DRIVES + 1);
	int index = 0;
	for (int i = 0; i < NUM_DRIVES; ++i) {
																// Check if the ith bit is set
		if (bitmask & (1 << i)) {
																// Print the corresponding drive letter
			available_drives[index++] = 'A' + i;
		}
	}
	return(available_drives);
}

int main() {
																// Get Local system time
	SYSTEMTIME local_time;
	GetLocalTime(&local_time);

																// Setup Buffer and the size of buffer
	char buf[256];
	DWORD bufSize = sizeof(buf);

	GetComputerNameExA(ComputerNameNetBIOS, buf, &bufSize); 
																/* According to the doccumentation GetComputerNameExA and ComputerNameNetBIOS
																   gives the true name of the comptuer as seen in Windows NETBIOS.
																*/
	size_t len = 0;
	while (buf[len] != '\0') {                                  // Get length of the buffer up to the \0 (null) terminator
		len++;
	}

	char* computerName = (char*)malloc((len+1) * sizeof(char)); // size the computer name to what was stored in the buffer the +1 is for the null terminator \0

	if (computerName == NULL) {									// If computer name is NULL then their is either no name or the Memory Allocation failed.
		std::ofstream sysError("sysError.txt");
		sysError << "[*] Memory allocation failed.";
		return 1;
	}
	for (size_t i = 0; i < len; i++) {							// Copy the buffer into the computer name.
		computerName[i] = buf[i];
	}

																// Get Processor Architecture
	SYSTEM_INFO myInfo;
	GetSystemInfo(&myInfo);
	const char* arch = nullptr;
	switch (myInfo.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		arch = "AMD64";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		arch = "ARM";
		break;
	case PROCESSOR_ARCHITECTURE_ARM64:
		arch = "ARM64";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		arch = "IA64";
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		arch = "INTEL";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		arch = "UNKNOWN";
		break;
	default:
		arch = "UNKNOWN";
		break;
	}

	// Get Type of processor
	DWORD processorType = myInfo.dwProcessorType;
	const char* pType = nullptr;
	switch (processorType) {
	case PROCESSOR_INTEL_386:
		pType = "Intel 386";
		break;
	case PROCESSOR_INTEL_486:
		pType = "Intel 486";
		break;
	case PROCESSOR_INTEL_PENTIUM:
		pType = "Intel Pentium";
		break;
	case PROCESSOR_INTEL_IA64:
		pType = "Intel Itanium";
		break;
	case PROCESSOR_AMD_X8664:
		pType = "AMD x86-64";
		break;
	default:
		pType = "Unknown or Reserved";
		break;
	}

	// Get Logical Drives
	DWORD drive_bitmask = GetLogicalDrives();
	char* available_drives;
	available_drives = getAvailableDrives(drive_bitmask);
	char* drives_string;
	for (int i = 0; i < sizeof(available_drives); i++) {
				
	}

	ULONGLONG memTotal = 0;
	GetPhysicallyInstalledSystemMemory(&memTotal);

	char date_time[23]; // 18 characters + 5 extra bytes
	snprintf(date_time, sizeof(date_time), "%02d:%02d:%02d %02d%02d%04d",
		local_time.wHour, local_time.wMinute, local_time.wSecond,
		local_time.wDay, local_time.wMonth, local_time.wYear);

	std::ofstream sysInfo("sysInfo.txt");
	sysInfo << "-- Run At " << date_time << " --\n";
	sysInfo << "Computer Name: " << computerName << "\n";
	sysInfo << "Processor Type: " << pType << "\n";
	sysInfo << "Processor Arch: " << arch << "\n";
	sysInfo << "Available Mem: " << memTotal << "\n";
	sysInfo << "Available Drives: " << available_drives << "\n";


	free(computerName);
	return 0;
}