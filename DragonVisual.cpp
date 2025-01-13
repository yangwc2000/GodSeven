#include "DragonVisual.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> // system("cls")

// 콘솔 화면 지우기 (Windows 전용)
void clearScreen() {
    system("cls");
}

// 드래곤 ASCII 아트 + 단계별 불길 출력
void printDragonAndFire(int step) {
    // 1) 드래곤 ASCII 아트
    std::cout << R"(
                       ZZ    ZZZ     Z Z     ZZ   ZZ
                    Z ZZZ  ZZZ  ZZZ ZZZ     ZZZ
                  ZZZZZZZZZZZZZZZZZZZZ     ZZ  Z
                  ZZZZZZZZZZZZZZZZZZZZZZZZZZ
                 ZZZZZZZZZZZZZ    ZZZZZZZZZZZZ
                 ZZZZZZZZZZZ         ZZZZZZZ  Z
               ZZZZZ ZZZZZZZ           ZZZZZZ
              ZZZZZZZZZZZZ              ZZZZZZZ
           ZZZZZZZZZZZZZZZZZ             ZZZZZZZ
           ZZZZZZ  ZZZZZZZ                ZZZZZZZ
                   ZZZZ                   ZZZZZZZ
                ZZZZZ                     ZZZZ ZZ
                 ZZ                       ZZZZ  Z
                                          ZZZZZ
                       ZZZZZZZZ          ZZZZZZ
                    ZZZZZZZZZZZZZZZZZZZZZZZZZZZ
ZZZZ             ZZZZZZZZZZZZZZZZZZZZZZZZZZZ ZZ
   ZZZZZZ      ZZZZZZZZZZZZZZZZZZZZZZZZZZZZ  Z
 ZZZZZZZZZZZZZZZZZZZZZZZZZ    ZZZZZ  ZZ  Z
Z     ZZ   ZZZZZZZZZZZZ        ZZZZ   Z
Z  ZZ  ZZ   ZZZZZZZZZZZ      ZZZ  Z
 Z  Z       ZZZZZZZZZ       ZZZ               ZZZZZZZZ
     ZZ    ZZZZZZZZZ   Z   ZZZ            ZZZZZZZZZZZZZZZ
           ZZZZZZZZZ  ZZZZZZZZZZ        ZZZZZZZZZZZZZZZZZZ
          ZZZZZZZZZ  Z ZZZZ   Z      ZZZZZZZZZZZZZZZZZZZZZZ
           ZZZZZZZZZZ   ZZZZZ        ZZZZZZZZZZZZZZZZZZZZZZZ
           ZZZZZZZZZ   ZZ  Z        ZZZZZZZZZZZZZZZZZZZZZZZZ
           ZZZZZZZZZZ  Z   ZZ      ZZZZZZZZZZZZZZZZZZZZZZZZZ
           ZZZZZZZZZZZ            ZZZZZZZZZZZ         ZZZZZZ
           ZZZZZZZZZZZZ          ZZZZZZZZZ            ZZZZZZ
           ZZZZZZZZZZZZZZZ      ZZZZZZZZZ             ZZZZZZ
           ZZZZZZZZZZZZZZZZZ  ZZZZZZZZZ   Z           ZZZZZ
            Z  ZZZZZZZZZZZZZZZZZZZZZZZZZZZ            ZZZZZ
               ZZZZZZZZZZZZZZZZZZZZ                   ZZZZ
                Z  ZZZZZZZZZZZZZZZZZ  Z              ZZZZ
                 Z  ZZZZZZZZZZZZ  ZZZZ               ZZZZ
                     ZZZ    ZZZ                      ZZZ
                       ZZZ    ZZ                    ZZZZ
                                                    ZZZ
                                                   ZZZ
                                                   ZZZ
                                                    ZZZZ
                                                       ZZZZ    Z
                                                           ZZZZZZ
                                                             ZZZZZ
                                                             ZZZ
)" << std::endl;

    // 2) 불길(브레스) 단계별 출력
    switch (step) {
    case 1:
        // 불길 거의 없음(빈 공간)
        std::cout << R"(                    )" << std::endl;
        break;
    case 2:
        // 2단계: ~~~~~~  + ~~~~~~~~
        // 들여쓰기를 살짝 조정해 더 자연스럽게 할 수 있음
        std::cout << R"(
            ~~~~~~
                                   ~~~~~~~~
)" << std::endl;
        break;
    case 3:
        // 3단계: 2단계 + ~~~~~~~~~~~~~ 
        std::cout << R"(
            ~~~~~~
                                   ~~~~~~~~
                                 ~~~~~~~~~~~~~
)" << std::endl;
        break;
    case 4:
        // 4단계: + ~~~~~~~~~~~~~~~~~~~~~
        std::cout << R"(
            ~~~~~~
                                   ~~~~~~~~
                                 ~~~~~~~~~~~~~
                             ~~~~~~~~~~~~~~~~~~~~~
)" << std::endl;
        break;
    case 5:
        // 5단계: + ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::cout << R"(
            ~~~~~~
                                   ~~~~~~~~
                                 ~~~~~~~~~~~~~
                             ~~~~~~~~~~~~~~~~~~~~~
                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
)" << std::endl;
        break;
    default:
        break;
    }
}

// 드래곤 브레스 애니메이션 (1~5단계)
void showDragonFireAnimation() {
    for (int step = 1; step <= 5; ++step) {
        clearScreen();                // 매 단계 콘솔 지우기
        printDragonAndFire(step);     // 드래곤 아트 + 불길 출력
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
