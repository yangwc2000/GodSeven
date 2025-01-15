// DragonAnimation.cpp
#include "DragonAnimation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>  // system("cls") (필요시)
using namespace std;

void showDragon2LinesAnimation() {
    vector<string> dragonLines = {
        // 드래곤 아트 줄단위...
    };

    for (int i = 0; i < (int)dragonLines.size(); i += 2) {
        // clearScreen(); // (B안) 원한다면 주석 해제
        cout << dragonLines[i] << "\n";
        if (i + 1 < (int)dragonLines.size()) {
            cout << dragonLines[i + 1] << "\n";
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n드래곤이 브레스를 발사했다!\n";
}
