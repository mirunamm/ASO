#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    SC_HANDLE hSCManager;
    DWORD bytesNeeded = 0;
    DWORD servicesCount = 0;
    DWORD resumeHandle = 0;
    DWORD runningCount = 0;

    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (hSCManager == NULL) {
        printf("Eroare OpenSCManager\n");
        return 1;
    }

    EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_STATE_ALL,
        NULL,
        0,
        &bytesNeeded,
        &servicesCount,
        &resumeHandle,
        NULL
    );

    LPBYTE buffer = (LPBYTE)malloc(bytesNeeded);
    if (buffer == NULL) {
        printf("Eroare la alocare\n");
        CloseServiceHandle(hSCManager);
        return 1;
    }

    if (!EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_STATE_ALL,
        buffer,
        bytesNeeded,
        &bytesNeeded,
        &servicesCount,
        &resumeHandle,
        NULL
    )) {
        printf("EroareEnumServicesStatusEx\n");
        free(buffer);
        CloseServiceHandle(hSCManager);
        return 1;
    }

    ENUM_SERVICE_STATUS_PROCESS* services;
    services = (ENUM_SERVICE_STATUS_PROCESS*)buffer;

    printf("Servicii care ruleaza\n\n");

    for (DWORD i = 0; i < servicesCount; i++) {
        if (services[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING) {
            runningCount++;

            wprintf(L"Nume serviciu: %s\n", services[i].lpServiceName);
            wprintf(L"Display Name: %s\n", services[i].lpDisplayName);
            wprintf(L"PID: %lu\n\n", services[i].ServiceStatusProcess.dwProcessId);
        }
    }

    printf("Total servicii active: %lu\n", runningCount);

    free(buffer);
    CloseServiceHandle(hSCManager);

    return 0;
}
