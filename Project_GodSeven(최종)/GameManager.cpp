﻿// GameManager.cpp
#define NOMINMAX
#include "GameManager.h"
#include "DragonVisual.h"
#include "DragonAnimation.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <conio.h>   // Windows 전용 (_getch)
#include <limits>    // numeric_limits
#include <thread>
#include <chrono>
#include <random>
#include <map>
#include "Boss.h"    // 드래곤(boss) 사용
#include "Monster.h"
#include "character.h"
#pragma comment(lib, "winmm.lib")


// 간단 예시: 보스 처치 여부를 전역/정적 변수로 관리
bool bossDefeated = false;

GameManager::GameManager() {
    // 랜덤 시드 초기화
    srand(static_cast<unsigned int>(time(nullptr)));
}

void GameManager::playMusic(const std::string& filePath, bool loop) {
    DWORD flags = SND_FILENAME | SND_ASYNC;
    if (loop) {
        flags |= SND_LOOP; // 반복 재생
    }
    if (!PlaySoundA(filePath.c_str(), 0, flags)) {
        std::cerr << "Error: Failed to play sound: " << filePath << std::endl;
    }
}

void GameManager::playEffectWithPause(const std::string& effectFilePath, const std::string& backgroundMusicPath, int effectDurationMs)
{
    // 1. 현재 재생 중인 배경음악 중단
    PlaySoundA(nullptr, 0, 0); // 중단

    // 2. 효과음 재생
    if (!PlaySoundA(effectFilePath.c_str(), 0, SND_FILENAME | SND_ASYNC)) {
        std::cerr << "Error: Failed to play effect: " << effectFilePath << std::endl;
    }

    // 3. 효과음 길이만큼 대기
    std::this_thread::sleep_for(std::chrono::milliseconds(effectDurationMs));

    // 4. 배경음악 재개
    playMusic(backgroundMusicPath, true); // 배경음악 반복 재생
}


void printWithDelay(const std::string& text, int delay = 50) { // delay 기본값 50ms
    for (char c : text) {
        std::cout << c << std::flush; // std::flush 추가
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}

void GameManager::startGame() {

    playMusic("C:\\MyFolder\\02Story.wav", true);
    // 타이틀 화면
    displayTitleScreen();

    playMusic("C:\\MyFolder\\01background_music.wav", true);
    // 캐릭터 생성
    std::string playerName;
    std::cout << "캐릭터의 이름을 입력하세요: ";
    std::getline(std::cin, playerName);

    Character* player = new Character(playerName);

    printWithDelay("\n게임을 시작합니다!\n", 20);
    player->displayStatus();

    // ──────────── 메인 게임 루프 ────────────
    while (true) {
        // 1) 플레이어 사망 체크
        if (player->getHealth() <= 0) {
            std::cout << "\n게임 오버! 캐릭터가 사망했습니다.\n";

            // 사망 음악 재생
            playMusic("C:\\MyFolder\\20GameOver.wav", false);

            // 대기 시간 추가
            std::this_thread::sleep_for(std::chrono::seconds(31));

            break;
        }
        // 2) 보스 처치(게임 클리어) 체크
        if (bossDefeated) {
            std::cout << "\n축하합니다! 드래곤의 비늘을 손에 넣었습니다!\n";

            break;
        }

        playMusic("C:\\MyFolder\\01background_music.wav", true);
        // 행동 메뉴
        printWithDelay("\n어떤 행동을 하시겠습니까?\n", 20);
        std::cout << "1. 전투하기\n"
            << "2. 인벤토리 열기\n"
            << "3. 스탯창 보기\n"
            << "4. 상점 방문\n"
            << "5. 몬스터 서식지 탐험\n"
            << "6. 야바위 게임\n" // 새로운 기능 추가
            << "0. 게임 종료\n";
        std::cout << "선택 > ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            // 잘못된 입력 방지
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
        case 1:
            // 전투하기
            // → 레벨10 이상 & 보스 안 잡았으면 보스전
            if (player->getLevel() >= 10 && !bossDefeated) {
                battleBoss(player);
            }
            else {
                battle(player, -1); // 랜덤 전투
            }
            break;
        case 2:
            // 인벤토리 열기
            displayInventory(player);
            break;
        case 3:
            // 스탯창 보기
            player->displayStatus();
            break;
        case 4:
            // 상점 방문
            visitShop(player);
            break;
        case 5:
            // 몬스터 서식지 탐험
            exploreHabitat(player);
            break;
        case 6:
            // 야바위 게임
            playShellGame(player);
            break;
        case 0:
            // 게임 종료
            printWithDelay("게임을 종료합니다.\n", 20);
            delete player;
            return;
        default:
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
    }

    // 루프 탈출 후 정리
    delete player;
}



void GameManager::displayTitleScreen() {
    system("cls");

    std::cout << "\033[1;33m" << R"(
 =============================================================================
 |  ######   ######  #######      ####### ####### ##    ## ####### ###    ## | 
 | ##       ##    ## ##    ##     ##      ##      ##    ## ##      ####   ## |
 | ##   ### ##    ## ##     #     ####### #####   ##    ## #####   ## ##  ## |
 | ##    ## ##    ## ##    ##          ## ##       ##  ##  ##      ##  ## ## |
 |  ######   ######  #######      ####### #######   ####   ####### ##   #### |
 =============================================================================
  )" << "\033[0m" << "\n"; // 색상 리셋

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 타이틀 잠시 보여주기

    printWithDelay(
        "먼 옛날...\n"
        "Unreal 이라는 마을에 내려오는 전설이 있다.\n"
        "그 전설은 현재까지도 구전되어 내려오고 있다.\n\n",
        30
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    printWithDelay(
        "드래곤이라는 신비한 고대종을 쓰러트리면 \"GOD Seven\" 이라는\n"
        "전설의 아이템들을 얻을 수 있다고 하는데\n"
        "부를 축적하는 금화\n"
        "명예를 불러오는 갑옷\n"
        "권력을 얻게 해 주는 왕관\n"
        "지혜롭게 해 주는 구슬\n"
        "평화를 가져오는 깃털\n"
        "용기를 부여하는 검\n"
        "존경심을 일으키는 망토가 있다고 한다.\n"
        "그러나, 지금까지 \"GOD Seven\"을 본 사람은 아무도 없었다.\n\n",
        30
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    printWithDelay("하지만...\n", 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    printWithDelay(
        "그 전설에 도전했던 수 많은 용사들이 있었으니\n"
        "첫번째 용사, \"어지니우스, 재미니우스, 주히디스\"\n"
        "두번째 용사, \"케르호스, 창미니다스, 하니우스, 호여디다스\"\n"
        "하지만, 모험을 떠난 그들을 본 사람은 아무도 없다고 한다.\n\n",
        30
    );

    printWithDelay(
        "그러나, 우리는 끊임없이 도전하여 \"GOD Seven\"을 향해 나아가리라.\n"
        "새로운 용사는 지금 바로 전설을 향해 도전하라!\n",
        30
    );
    std::this_thread::sleep_for(std::chrono::milliseconds(50));


    printWithDelay("Press Start...", 30);
    printWithDelay("아무 키나 눌러서 시작하세요!", 10);

    _getch();
    system("cls");
}

// ────────────── 일반 전투 (몬스터) ──────────────
void GameManager::battle(Character* player, int habitat) {
    system("cls"); // 화면 클리어
    Monster* monster = nullptr;

    if (habitat == 0) {
        monster = new Slime(player->getLevel());
    }
    else if (habitat == 1) {
        monster = new Goblin(player->getLevel());
    }
    else if (habitat == 2) {
        monster = new Orc(player->getLevel());
    }
    else if (habitat == 3) {
        monster = new Troll(player->getLevel());
    }
    else {
        // 랜덤 몬스터 생성 (기존 로직 유지)
        int playerLevel = player->getLevel();
        if (playerLevel >= 1 && playerLevel <= 3) {
            monster = new Slime(playerLevel);
        }
        else if (playerLevel >= 4 && playerLevel <= 5) {
            monster = new Goblin(playerLevel);
        }
        else if (playerLevel >= 6 && playerLevel <= 7) {
            monster = new Orc(playerLevel);
        }
        else if (playerLevel >= 8 && playerLevel <= 9) {
            monster = new Troll(playerLevel);
        }
        else {
            monster = generateMonster(player->getExperience() / 100 + 1, habitat);
        }
    }

    printWithDelay("\n=== 전투 시작! ===\n", 20);
    printWithDelay("몬스터 " + monster->getName()
        + " (체력: " + std::to_string(monster->getHealth())
        + ", 공격력: " + std::to_string(monster->getAttack())
        + ") 이(가) 등장했습니다!\n\n", 20);

    // 몬스터 아트 출력
    if (monster->getName() == "Slime") {
        playMusic("C:\\MyFolder\\13Fight.wav", true);
        std::cout << R"(
     #######        
    ########## 
   ############ 
    # #%%%%%### 
  #########%##%%# 
   #%###%###%#%#%## 
# ################%#
####%%%###%###%%%#%#
	)" << "\n\n";
    }
    if (monster->getName() == "Goblin") {
        playMusic("C:\\MyFolder\\13Fight.wav", true);
        std::cout << R"(
           ###%     
          #####%    
           ###%%%%  
       %%########   
 %%%%%%%#% ######   
 %%%%      %%%%%    
          #%%%%#%   
          %%%  #%   
         ##%   %##  
               %##  
)" << "\n\n";
    }
    if (monster->getName() == "Orc") {
        playMusic("C:\\MyFolder\\13Fight.wav", true);
        std::cout << R"(
                      .=####+   
                  *#####*.##  
                .#########+   
               :##*  ######.  
                  .##* :+##-  
                .######+:  .  
            .#############=#: 
           .################:.
         :##+#############:.. 
     :####*##*############*:. 
     ###################:.+   
  *##:   =#############=      
  #*        ############:#    
  =##*:    #############      
   :++#+. ############.       
     ..::###############      
          ##############      
          .+:-#########..:    
     -####################+-. 
 :.=#######################*=.
.+###########################:
 ..:-+==+**##################.
)" << "\n\n";
    }
    if (monster->getName() == "Troll") {
        playMusic("C:\\MyFolder\\13Fight.wav", true);
        std::cout << R"(
                    *@@-                
                   =@@@@-               
                   +@@@@#               
               .*@@@@@@@@@:             
             %@@@@%%@@@@@@@@*           
            -@@@@*+*@@@@@@@@@@:         
            =@@@@@@%@@@@@@@@@@=         
            #@@@%%*#@@@@@@@@@@*         
            #@@@@#**##%@@@@@@@@.        
           +@@@%=#*#%%@@@+*@@@@:        
          .@@@@%%@%%@@@@@@=*@@@+        
          .@@@%*@@@@@@@@@@%%@@@@.       
          .@@@*@@@@@@@@@@@@@@@@+        
          =@@#@@@@@@##@@@@@@@@@.        
         :@@@=@@@@@*  *@@@@@@@@-        
        .@@@@-@@@@#    %@@@@@@@@-       
        .@@@@=@@@@*    =@@@@@@@@*       
         -@:-@@@@@#    +@@@@@=@@:       
            :@@@@@.    .@@@@@@+         
           -@@@@@%      +@@@@@:         
          -@@@@@@@      *@@@@@@.        
          .+*@@@*:      .+@@%#*         
)" << "\n\n";
    }

    // 전투 루프
    while (monster->getHealth() > 0 && player->getHealth() > 0) {
        printWithDelay("\n어떤 행동을 하시겠습니까?\n", 20);
        std::cout << "1. 공격하기\n"
            << "2. 아이템 사용\n"
            << "3. 도망가기\n" // 도망가기 옵션 추가
            << "선택 > "
            << "\n\n";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
        case 1: 
        {
            // 플레이어 공격
            int damage = player->performRandomAttack(monster); // 반환값 저장

            // 배경음(13Fight.wav)을 일시 중단 후 효과음(attack.wav) 재생
            playEffectWithPause("C:\\MyFolder\\attack.wav", "C:\\MyFolder\\13Fight.wav", 1000); // 효과음 길이 1초


            if (monster->getHealth() > 0)
                std::cout << "[플레이어] " << player->getName()
                << " → [몬스터] " << monster->getName()
                << " (피해: " << damage << ")\n"; // 저장된 값 출력
            break;
        }
        case 2:
            // 인벤토리 열기 및 아이템 사용
            displayInventory(player);
            break;
        case 3:
            // 도망가기
            printWithDelay("[플레이어]" + player->getName() + "이(가) 추하게 도망쳤습니다!\n", 20);
            delete monster;
            return; // 전투 종료
        default:
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        // 몬스터 사망?
        if (monster->getHealth() <= 0) {
            printWithDelay(monster->getName() + "를 처치했습니다!\n", 20);
            // 보상
            player->addExperience(30);
            player->addGold(50);
            player->levelUp();
            player->addMonsterKill();
            // 몬스터가 아이템 드랍
            Item* droppedItem = monster->dropItem();
            if (droppedItem) {
                player->addItem(droppedItem);
                std::cout << "몬스터가 " << droppedItem->getName() << "을(를) 드랍했습니다!\n";
            }
            delete monster;
            return;
        }

        // 몬스터 반격
        player->takeDamage(monster->getAttack());
        std::cout << "[몬스터] " << monster->getName()
            << " → [플레이어] " << player->getName()
            << " (피해: " << monster->getAttack() << ")\n";
        std::cout << "[몬스터의 남은 체력] " << monster->getHealth() << "\n";
        std::cout << "[플레이어 남은 체력] " << player->getHealth() << "\n";

        // 플레이어 사망?
        if (player->getHealth() <= 0) {
            printWithDelay(player->getName() + "이(가) 사망했습니다...\n", 50);
            delete monster;
            return;
        }

        std::cout << "\n";
    }
    delete monster;
}

// ────────────── 보스전 (드래곤) ──────────────
void displayCredit(const std::string& line) {
    std::cout << line << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 스크롤 속도 조절 (100ms)
}

void GameManager::battleBoss(Character* player) {
    playMusic("C:\\MyFolder\\03Boss", true);
    // 드래곤 객체 생성
    showDragon2LinesAnimation();
    Monster* boss = new Dragon();

    if (boss == nullptr) {
        std::cout << "Error보스 생성에 실패했습니다.\n";
        return;
    }

    printWithDelay("\n===== 보스전 돌입! 드래곤이 나타났습니다! =====\n", 20);
    // 드래곤 ASCII 아트

    int step = 0; // step 변수 정의 및 초기화
    printDragonAndFire(step); // 드래곤 브레스 애니메이션

    while (boss->getHealth() > 0 && player->getHealth() > 0) {
        printWithDelay("\n어떤 행동을 하시겠습니까?\n", 20);
        std::cout << "1. 공격하기\n"
            << "2. 아이템 사용\n"
            << "선택 > ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        switch (choice) {
        case 1:
            player->performRandomAttack(boss);
            if (boss->getHealth() > 0)
                std::cout << "[보스 남은 체력] " << boss->getHealth() << "\n";
            break;
        case 2:
            displayInventory(player);
            break;
        default:
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (boss->getHealth() <= 0) {
            printWithDelay("드래곤을 쓰러뜨렸습니다!\n", 20);
            bossDefeated = true;
            Item* droppedItem = boss->dropItem();
            if (droppedItem) {
                player->addItem(droppedItem);
                printWithDelay("보스가 " + droppedItem->getName() + "을(를) 드랍했습니다!\n", 20);
            }
            delete boss;

            // 엔딩 크레딧 출력
            system("cls"); // 엔딩 전 화면 클리어

            // 클리어 음악 재생
            playMusic("C:\\MyFolder\\25Finale.wav", false);

            // 엔딩 스토리 출력
            printWithDelay("드래곤을 물리친 " + player->getName() + "의 앞에 나타난 것은 전설 속의 GOD Seven이 아닌, 나풀거리는 종이 한 장이었다.\n"
                "당황하며 나풀거리며 떨어진 종이를 주워들자, 써진 글자들이 보였다.\n"
                "일어나... 공부하러 가야지...\n"
                "환한 빛이 퍼져 나왔고, 자신도 모르게 감았던 눈을 뜬 " + player->getName() + "의 앞에 보인 건\n"
                "켜져 있는 자신의 컴퓨터 화면과, 작성하다 만 코드였다.\n"
                "이제 공부하러 가자!\n\n", 30);

            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 짧은 대기

            // ASCII 아트 출력
            std::cout << "\033[1;33m" << R"(
====================================================================
| ########  ###   ###  ########      ########  ###    ##  #######  |
|    ##     ###   ###  ###           ###       ####   ##  ##    ## |
|    ##     #########  #######       #######   ## ##  ##  ##    ## |
|    ##     ###   ###  ###           ###       ##  ## ##  ##    ## |
|    ##     ###   ###  ########      ########  ##   ####  #######  |
====================================================================
)" << "\033[0m" << "\n"; // 색상 리셋
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // 엔딩 크레딧 출력
            std::vector<std::string> credits = {
                "=== 엔딩 크레딧 ===",
                "",
                "프로젝트명 : GOD SEVEN",
                "제작 by Unreal 1기 매출 7조",
                "팀장 : 양우창",
                "총괄 : 정완훈",
                "몬스터 디자인 : 양우창, 정완훈",
                "전투 밸런싱 : 이재",
                "아이템, 디테일 : 송현우",
                "몬스터 생성 로직 : 김태완",
                "스토리 : 이재, 김태완",
                "잡기술 : 정완훈",
                "",
                "Special Thanks to " + player->getName() + "!",
            };

            for (const auto& line : credits) {
                displayCredit(line); // 한 줄씩 출력하며 대기
            }
            // 대기 시간 추가
            std::this_thread::sleep_for(std::chrono::seconds(31));

            return; // 엔딩 크레딧 출력 후 함수 종료
        }

        // 보스 반격
        if (Dragon* dragon = dynamic_cast<Dragon*>(boss)) {
            dragon->breathAttack();
        }
        player->takeDamage(boss->getAttack() + 20);
        std::cout << "[보스] " << boss->getName()
            << " → [플레이어] " << player->getName()
            << " (피해: " << boss->getAttack() + 20 << ")\n";
        std::cout << "[보스 남은 체력] " << boss->getHealth() << "\n";
        std::cout << "[플레이어 남은 체력] " << player->getHealth() << "\n";

        if (player->getHealth() <= 0) {
            printWithDelay(player->getName() + "이(가) 드래곤에게 패배했습니다...\n", 20);
            delete boss;
            return;
        }
        std::cout << "\n";

    }
    delete boss; // 전투 루프 종료 후 몬스터 삭제 (플레이어 사망 후에도)
}

// ────────────── 몬스터 서식지 탐험 ──────────────
void GameManager::exploreHabitat(Character* player) {
    system("cls"); // 화면 클리어
    printWithDelay("\n어떤 서식지로 탐험하시겠습니까?\n", 20);
    std::cout << "1. 숲 (슬라임)\n"
        << "2. 동굴 (고블린)\n"
        << "3. 늪지대 (오크)\n"
        << "4. 산 (트롤)\n"
        << "선택 > ";

    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = -1;
    }

    switch (choice) {
    case 1:
        printWithDelay("숲으로 탐험을 떠납니다...\n", 20);
        // 숲에서 슬라임과 전투
        battle(player, 0);
        break;
    case 2:
        printWithDelay("동굴로 탐험을 떠납니다...\n", 20);
        // 동굴에서 고블린과 전투
        battle(player, 1);
        break;
    case 3:
        printWithDelay("늪지대로 탐험을 떠납니다...\n", 20);
        // 늪지대에서 오크와 전투
        battle(player, 2);
        break;
    case 4:
        printWithDelay("산으로 탐험을 떠납니다...\n", 20);
        // 산에서 트롤과 전투
        battle(player, 3);
        break;
    default:
        printWithDelay("잘못된 입력입니다.\n", 20);
        break;
    }
}

// ────────────── 야바위 게임 ──────────────
void GameManager::playShellGame(Character* player) {
    system("cls"); // 화면 클리어
    playMusic("C:\\MyFolder\\Yabawi.wav", true);
    printWithDelay("\n야바위꾼 : 돈 먹고 돈 먹기! 자자, 어서 걸어보라고! 이기면 두배로 돌려주겠네!\n", 10);
    std::cout << "배팅할 금액을 입력하세요: ";
    int betAmount;
    std::cin >> betAmount;

    if (std::cin.fail() || betAmount <= 0 || betAmount > player->getGold()) {
        printWithDelay("야바위꾼 : 자네 그게 무슨 소리인가?\n", 10);
        playMusic("C:\\MyFolder\\wrong.wav", false);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    // 컵 선택
    playMusic("C:\\MyFolder\\shuffle.wav", false);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int winningCup = rand() % 3 + 1; // 1, 2, 3 중 하나
    printWithDelay("야바위꾼 : 1, 2, 3번 컵 중 하나를 선택해봐: ", 10);
    int playerChoice;
    std::cin >> playerChoice;

    if (std::cin.fail() || playerChoice < 1 || playerChoice > 3) {
        printWithDelay("야바위꾼 : 자네 그게 무슨 소리인가?.\n", 10);
        playMusic("C:\\MyFolder\\wrong.wav", false);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    if (playerChoice == winningCup) {
        printWithDelay("야바위꾼 : 쳇, 축하하네.\n", 10);
        playMusic("C:\\MyFolder\\victory.wav", false);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        player->addGold(betAmount * 1);
    }
    else {
        printWithDelay("야바위꾼 : 흐흐, 내가 이겼구만. 어라, 벌써 끝인가?\n", 10);
        playMusic("C:\\MyFolder\\lose.wav", false);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        player->spendGold(betAmount);
    }

    // 현재 골드 표시
    std::cout << "현재 보유 골드: " << player->getGold() << " G\n";
}

// ────────────── 몬스터 생성 함수 ──────────────
Monster* GameManager::generateMonster(int level, int habitat) {
    if (habitat == -1) {
        // 랜덤 몬스터 생성
        int monsterType = rand() % 4; // 0~3
        switch (monsterType) {
        case 0:  return new Goblin(level);
        case 1:  return new Orc(level);
        case 2:  return new Troll(level);
        default: return new Slime(level);
        }
    }
    else {
        // 서식지별 몬스터 생성
        switch (habitat) {
        case 0:  return new Slime(level); // 숲
        case 1:  return new Goblin(level); // 동굴
        case 2:  return new Orc(level); // 늪지대
        case 3:  return new Troll(level); // 산
        default: return new Slime(level);
        }
    }
}

// ────────────── 인벤토리 열기 ──────────────
void GameManager::displayInventory(Character* player) {
    system("cls"); // 화면 클리어
    printWithDelay("\n=== 인벤토리 확인 ===\n", 20);
    player->printInventory(); // 실제로 아이템 목록을 보여주도록 수정

    std::cout << "\n사용할 아이템 번호(취소=음수) > ";
    int choice;
    std::cin >> choice;
    if (choice >= 0) {
        player->useItem(choice);
    }
    // 이후 player->displayStatus(); 등으로 상태 확인 가능
}

void GameManager::visitShop(Character* player) { //------- 명칭 수정
    playMusic("C:\\MyFolder\\07Store.wav", true);
    system("cls"); // 화면 클리어
    printWithDelay("\n===== 상점 입장 =====\n", 20);
    bool shopping = true;
    while (shopping) {
        std::cout << "\n[보유 골드] " << player->getGold() << " G\n"
            << "1. 체력 회복 포션 (150G)\n"
            << "2. 영고항력의 신단(공격력 증가) (70G)\n"
            << "3. 아이템 판매\n"
            << "0. 상점 나가기\n"
            << "선택 > ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
        case 1:
            // 체력포션 구매
            if (player->getGold() >= 150) {
                player->spendGold(150);
                player->addItem(new HealthPotion());
                std::cout << "체력 회복 포션 구매 완료!\n";
            }
            else {
                std::cout << "골드가 부족합니다!\n";
            }
            break;
        case 2:
            // 공격력 증가 포션 구매
            if (player->getGold() >= 70) {
                player->spendGold(70);
                player->addItem(new AttackBoost());
                std::cout << "영고항력의 신단(공격력 증가) 구매 완료!\n";
            }
            else {
                std::cout << "골드가 부족합니다!\n";
            }
            break;
        case 3:
            // 아이템 판매
            printWithDelay("\n=== 인벤토리 확인 ===\n", 20);
            player->printInventory();
            std::cout << "\n판매할 아이템 번호(취소=음수) > ";
            int sellChoice;
            std::cin >> sellChoice;
            if (sellChoice >= 0) {
                Item* item = player->getItem(sellChoice);
                if (item) {
                    int sellPrice = static_cast<int>(item->getPrice() * 0.6); // 원가의 60%
                    player->addGold(sellPrice);
                    player->removeItem(sellChoice);
                    std::cout << item->getName() << "을(를) " << sellPrice << "G에 판매했습니다!\n";
                }
            }
            break;
        case 0:
            printWithDelay("상점을 나갑니다.\n", 20);
            shopping = false;
            break;
        default:
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
    }
}
