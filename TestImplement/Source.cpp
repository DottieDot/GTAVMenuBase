#include "../GTAVMenuBase/IMenu.h"
#include <synchapi.h>

using namespace ikt::Menu;

void onSelect() {
    printf("Select!\n");
}
void onLeft() {
    printf("Left!\n");
}

void onRight() {
    printf("Right!\n");
}


int main() {
    Submenu mainMenu("Main test", "Subtitle");
    bool myBool;
    mainMenu.AddEntry(std::make_unique<Option>("Simple option", ""));
    mainMenu.AddEntry(std::make_unique<ToggleOption>("Bool option", "", &myBool));
    mainMenu.AddEntry(std::make_unique<Option>("Callbacks option", "", std::bind(onSelect), std::bind(onLeft), std::bind(onRight)));

    Menu menu(&mainMenu);

    while(true) {
        menu.Render();
        Sleep(50);
    }
}
