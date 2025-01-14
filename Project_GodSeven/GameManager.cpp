// GameManager.cpp
#include "GameManager.h"
#include "DragonVisual.h"
#include "DragonAnimation.h"
#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <conio.h>   // Windows 전용 (_getch)
#include <limits>    // numeric_limits
#include <thread>
#include <chrono>
#include "Boss.h"    // 드래곤(boss) 사용

// 간단 예시: 보스 처치 여부를 전역/정적 변수로 관리
bool bossDefeated = false;

GameManager::GameManager() {
    // 랜덤 시드 초기화
    srand(static_cast<unsigned int>(time(nullptr)));
}

void GameManager::startGame() {
    // 타이틀 화면
    displayTitleScreen();

    // 캐릭터 생성
    std::string playerName;
    std::cout << "캐릭터의 이름을 입력하세요: ";
    std::getline(std::cin, playerName);

    Character* player = new Character(playerName);

    std::cout << "\n게임을 시작합니다!\n";
    player->displayStatus();

    // ──────────── 메인 게임 루프 ────────────
    while (true) {
        // 1) 플레이어 사망 체크
        if (player->getHealth() <= 0) {
            std::cout << "\n게임 오버! 캐릭터가 사망했습니다.\n";
            break;
        }
        // 2) 보스 처치(게임 클리어) 체크
        if (bossDefeated) {
            std::cout << "\n축하합니다! 드래곤의 비늘을 손에 넣었습니다!\n";
            break;
        }

        // 행동 메뉴
        std::cout << "\n어떤 행동을 하시겠습니까?\n";
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
            std::cout << "게임을 종료합니다.\n";
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
    system("cls"); // Windows 전용 화면 클리어
    std::cout << R"(
   ######   ######  #######      ####### ####### ##    ## ####### ###    ##
  ##       ##    ## ##    ##     ##      ##      ##    ## ##      ####   ##
  ##   ### ##    ## ##     #     ####### #####   ##    ## #####   ## ##  ##
  ##    ## ##    ## ##    ##          ## ##       ##  ##  ##      ##  ## ##
   ######   ######  #######      ####### #######   ####   ####### ##   ####

    )" << "\n";
    std::cout << "Press Start...\n\n";
    std::cout << "아무 키나 눌러서 시작하세요!\n";

    _getch(); // 아무 키 입력 대기 (Windows)
    system("cls"); // 화면 클리어
}

// ────────────── 일반 전투 (몬스터) ──────────────
void GameManager::battle(Character* player, int habitat) {
    system("cls"); // 화면 클리어
    // 몬스터 생성 (레벨 기반)
    Monster* monster = generateMonster(player->getExperience() / 100 + 1, habitat); // 서식지 인자 추가

    std::cout << "\n=== 전투 시작! ===\n";
    std::cout << "몬스터 " << monster->getName()
        << " (체력: " << monster->getHealth()
        << ", 공격력: " << monster->getAttack()
        << ") 이(가) 등장했습니다!\n\n";

    // 몬스터 아트 출력
    if (monster->getName() == "Slime") {
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
        std::cout << "\n어떤 행동을 하시겠습니까?\n";
        std::cout << "1. 공격하기\n"
            << "2. 아이템 사용\n"
            << "3. 도망가기\n" // 도망가기 옵션 추가
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
            // 플레이어 공격
            monster->takeDamage(player->getAttack());
            std::cout << "[플레이어] " << player->getName()
                << " → [몬스터] " << monster->getName()
                << " (피해: " << player->getAttack() << ")\n";
            break;
        case 2:
            // 인벤토리 열기 및 아이템 사용
            displayInventory(player);
            break;
        case 3:
            // 도망가기
            std::cout << "[플레이어]" << player->getName() << "이(가) 추하게 도망쳤습니다!\n";
            return; // 전투 종료
        default:
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        // 몬스터 사망?
        if (monster->getHealth() <= 0) {
            std::cout << monster->getName() << "를 처치했습니다!\n";
            // 보상
            player->addExperience(30);
            player->addGold(50);
            player->levelUp();
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
            std::cout << player->getName() << "이(가) 사망했습니다...\n";
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
    // 드래곤 객체 생성
    showDragon2LinesAnimation();
    Monster* boss = new Dragon();

    if (boss == nullptr) {
        std::cout << "Error보스 생성에 실패했습니다.\n";
        return;
    }

    std::cout << "\n===== 보스전 돌입! 드래곤이 나타났습니다! =====\n";
    // 드래곤 ASCII 아트

    int step = 0; // step 변수 정의 및 초기화
    printDragonAndFire(step); // 드래곤 브레스 애니메이션

    while (boss->getHealth() > 0 && player->getHealth() > 0) {
        std::cout << "\n어떤 행동을 하시겠습니까?\n";
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
            boss->takeDamage(player->getAttack()); // player 포인터 전달
            std::cout << "[플레이어] " << player->getName()
                << " → [보스] " << boss->getName()
                << " (피해: " << player->getAttack() << ")\n";
            break;
        case 2:
            displayInventory(player);
            break;
        default:
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (boss->getHealth() <= 0) {
            std::cout << "드래곤을 쓰러뜨렸습니다!\n";
            bossDefeated = true;
            Item* droppedItem = boss->dropItem();
            if (droppedItem) {
                player->addItem(droppedItem);
                std::cout << "보스가 " << droppedItem->getName() << "을(를) 드랍했습니다!\n";
            }
            delete boss;

            // 엔딩 크레딧 출력
            system("cls"); // 엔딩 전 화면 클리어
            std::vector<std::string> credits = {
                "=== 엔딩 크레딧 ===",
                "",
                "프로젝트명 : GOD SEVEN",
                "제작 by Unreal 1기 매출 7조",
                "팀장 : 양우창",
                "몬스터 디자인 : 양우창, 정완훈",
                "전투 밸런싱 : 이재",
                "잡기술 : 정완훈",
                "",
                "Special Thanks to " + player->getName() + "!",
            };

            for (const auto& line : credits) {
                displayCredit(line);
            }
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
            std::cout << player->getName() << "이(가) 드래곤에게 패배했습니다...\n";
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
    std::cout << "\n어떤 서식지로 탐험하시겠습니까?\n";
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
        std::cout << "숲으로 탐험을 떠납니다...\n";
        // 숲에서 슬라임과 전투
        battle(player, 0);
        break;
    case 2:
        std::cout << "동굴로 탐험을 떠납니다...\n";
        // 동굴에서 고블린과 전투
        battle(player, 1);
        break;
    case 3:
        std::cout << "늪지대로 탐험을 떠납니다...\n";
        // 늪지대에서 오크와 전투
        battle(player, 2);
        break;
    case 4:
        std::cout << "산으로 탐험을 떠납니다...\n";
        // 산에서 트롤과 전투
        battle(player, 3);
        break;
    default:
        std::cout << "잘못된 입력입니다.\n";
        break;
    }
}

// ────────────── 야바위 게임 ──────────────
void GameManager::playShellGame(Character* player) {
    system("cls"); // 화면 클리어
    std::cout << "\n야바위꾼 : 돈 먹고 돈 먹기! 자자, 어서 걸어보라고!\n";
    std::cout << "배팅할 금액을 입력하세요: ";
    int betAmount;
    std::cin >> betAmount;

    if (std::cin.fail() || betAmount <= 0 || betAmount > player->getGold()) {
        std::cout << "야바위꾼 : 자네 그게 무슨 소리인가?\n";
        return;
    }

    // 컵 선택
    int winningCup = rand() % 3 + 1; // 1, 2, 3 중 하나
    std::cout << "야바위꾼 : 1, 2, 3번 컵 중 하나를 선택해봐: ";
    int playerChoice;
    std::cin >> playerChoice;

    if (std::cin.fail() || playerChoice < 1 || playerChoice > 3) {
        std::cout << "야바위꾼 : 자네 그게 무슨 소리인가?.\n";
        return;
    }

    if (playerChoice == winningCup) {
        std::cout << "야바위꾼 : 쳇, 축하하네.\n";
        player->addGold(betAmount * 2);
    }
    else {
        std::cout << "야바위꾼 : 흐흐, 내가 이겼구만. 어라, 벌써 끝인가?\n";
        player->addGold(-betAmount);
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
    std::cout << "\n=== 인벤토리 확인 ===\n";
    player->printInventory(); // 실제로 아이템 목록을 보여주도록 수정

    std::cout << "\n사용할 아이템 번호(취소=음수) > ";
    int choice;
    std::cin >> choice;
    if (choice >= 0) {
        player->useItem(choice);
    }
    // 이후 player->displayStatus(); 등으로 상태 확인 가능
}

void GameManager::visitShop(Character* player) {
    system("cls"); // 화면 클리어
    std::cout << "\n===== 상점 입장 =====\n";
    bool shopping = true;
    while (shopping) {
        std::cout << "\n[보유 골드] " << player->getGold() << " G\n"
            << "1. 체력포션 (50G)\n"
            << "2. 공격력 증가 포션 (70G)\n"
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
            if (player->getGold() >= 50) {
                player->addGold(-50);
                player->addItem(new HealthPotion());
                std::cout << "체력포션 구매 완료!\n";
            }
            else {
                std::cout << "골드가 부족합니다!\n";
            }
            break;
        case 2:
            // 공격력 증가 포션 구매
            if (player->getGold() >= 70) {
                player->addGold(-70);
                player->addItem(new AttackBoost());
                std::cout << "공격력 증가 포션 구매 완료!\n";
            }
            else {
                std::cout << "골드가 부족합니다!\n";
            }
            break;
        case 3:
            // 아이템 판매
            std::cout << "\n=== 인벤토리 확인 ===\n";
            player->printInventory();
            std::cout << "\n판매할 아이템 번호(취소=음수) > ";
            int sellChoice;
            std::cin >> sellChoice;
            if (sellChoice >= 0) {
                Item* item = player->getItem(sellChoice);
                if (item) {
                    int sellPrice = static_cast<int>(item->getPrice() * 0.6);
                    player->addGold(sellPrice);
                    player->removeItem(sellChoice);
                    std::cout << item->getName() << "을(를) " << sellPrice << "G에 판매했습니다!\n";
                }
            }
            break;
        case 0:
            std::cout << "상점을 나갑니다.\n";
            shopping = false;
            break;
        default:
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
    }
}
