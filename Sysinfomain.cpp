#include <windows.h>
#include <Sysinfoapi.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

int main(){
	
	char buf[256];
	DWORD bufSize = sizeof(buf);
	
	GetComputerNameExA(ComputerNameNetBIOS, buf, &bufSize);
	size_t len = 0;
	while(buf[len] != '\0'){
		len++;
	}
	
	char *computerName = (char *)malloc(len * sizeof(char));
	
	if(computerName == NULL){
		std::ofstream sysError("sysError.txt");
		sysError << "[*] Memory allocation failed.";
		return 1;
	}
	
	for(size_t i = 0; i < len; i++){
		computerName[i] = buf[i];
	}
	
	// Get Processor Type
	SYSTEM_INFO myInfo;
	GetSystemInfo(&myInfo);
	const char *arch = nullptr;
	switch(myInfo.wProcessorArchitecture){
		case PROCESSOR_ARCHITECTURE_AMD64:
			arch="AMD64";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
    		arch="ARM";
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
    		arch="ARM64";
            break;
        case PROCESSOR_ARCHITECTURE_IA64:
    		arch="IA64";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
    		arch="INTEL";
            break;
        case PROCESSOR_ARCHITECTURE_UNKNOWN:
    		arch="UNKNOWN";
            break;
        default:
    		arch="UNKNOWN";
            break;
	}
	DWORD processorType = myInfo.dwProcessorType;
	const char *pType = nullptr;
	switch(processorType){
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
	
	std::ofstream sysInfo("sysInfo.txt");
	sysInfo << "Computer Name: " << computerName << "\n";
	sysInfo << "Processor Type: " << pType << "\n";
	sysInfo << "Processor: " << arch;
	free(computerName);
	return 0;
}