#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>


//just for color
void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void color_text(int c1, int c2, std::string text) {
    color(c1);
    std::cout << text << std::endl;
    color(c2);
}

/*
FindDMAAddy:
1.Dereference the localPlayer pointer to get the dynamic address of the object
2.Add offset to get to the name pointer
3.Dereference the name pointer to get the dynamic address of the name value
*/
uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }
    return addr;
}

void menu() {
    system("title hax haha");
    color_text(6, 7, "https://github.com/Agustony0");
    color_text(6, 7, "v0.1 03.08.2021");
    std::cout << std::endl;
    color_text(2, 7, "[+] The dll was successfully injected\n");
    color_text(3, 7, "[INTERN] F8 for exit the intern cheat.");
    color_text(3, 7, "[INTERN] F9 for $16,000.");
    color_text(3, 7, "[INTERN] F10 for 100 bullets [ak-47]. \n");
    color_text(2, 1, "[INTERN] Keyboard commands are expected\n");
}

void injected_thread() {

    menu();
    
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle("hw.dll");
    //moduleBase = (uintptr_t)GetModuleHandle(NULL);
    while (true) {

        if (GetAsyncKeyState(VK_F8)) {
            break;
        }

        if (GetAsyncKeyState(VK_F9)) {  
            // money
            
            uintptr_t money = FindDMAAddy(moduleBase + 0x007AF55C, { 0x74, 0x1CC });
            int* moneyy = (int*)money;
            *moneyy = 16000;
            color_text(6, 7, "[INTERN] $16,000 was added");
            std::cout << "[INTERN] Address for money:" <<std::hex << moneyy << std::endl;
            std::cout << std::endl;
            Sleep(1000);
            
        }
        if (GetAsyncKeyState(VK_F10)) {
            //ammo on ak
            
            uintptr_t ammo = FindDMAAddy(moduleBase + 0x007AF55C, { 0x74, 0x5D4, 0xCC });
            int* ammo0 = (int*)ammo;
            *ammo0 = 100;
            color_text(6, 7, "[INTERN] 100 bullets were added [ak-47]");
            std::cout << "[INTERN] Address for ammo:" << std::hex << ammo << std::endl;
            std::cout << std::endl;
            Sleep(1000);
        }          

        // So our thread doesn't constantly run, we have it pause execution for a millisecond.
        // This allows the processor to schedule other tasks.
        Sleep(1);
    }


}

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    //calling it with NULL also gives you the address of the .exe module
    //moduleBase = (uintptr_t)GetModuleHandle(NULL);

    injected_thread();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, nullptr));
    }

    return true;
}


