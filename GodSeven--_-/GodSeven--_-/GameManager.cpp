//GameManager.cpp
#include "GameManager.h"
#include "DragonVisual.h"
#include "DragonAnimation.h"
#include <iostream>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <conio.h>   // Windows 전용 (_getch)
#include <limits>    // numeric_limits
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
            std::cout << "\n축하합니다! 드래곤을 물리치고 게임을 클리어했습니다!\n";
            break;
        }

        // 행동 메뉴
        std::cout << "\n어떤 행동을 하시겠습니까?\n";
        std::cout << "1. 전투하기\n"
            << "2. 인벤토리 열기\n"
            << "3. 스탯창 보기\n"
            << "4. 상점 방문\n"
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
                battle(player);
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
void GameManager::battle(Character* player) {
    // 몬스터 생성 (레벨 기반)
    Monster* monster = generateMonster(player->getExperience() / 100 + 1);

    std::cout << "\n=== 전투 시작! ===\n";
    std::cout << "몬스터 " << monster->getName()
        << " (체력: " << monster->getHealth()
        << ", 공격력: " << monster->getAttack()
        << ") 이(가) 등장했습니다!\n\n";

    // 전투 루프
    while (monster->getHealth() > 0 && player->getHealth() > 0) {
        // 플레이어 공격
        monster->takeDamage(player->getAttack());
        std::cout << "[플레이어] " << player->getName()
            << " → [몬스터] " << monster->getName()
            << " (피해: " << player->getAttack() << ")\n";

        // 몬스터 사망?
        if (monster->getHealth() <= 0) {
            std::cout << monster->getName() << "를 처치했습니다!\n";
            // 보상
            player->addExperience(30);
            player->addGold(50);
            player->levelUp();
            delete monster;
            return;
        }

        // 몬스터 반격
        player->takeDamage(monster->getAttack());
        std::cout << "[몬스터] " << monster->getName()
            << " → [플레이어] " << player->getName()
            << " (피해: " << monster->getAttack() << ")\n";

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
void GameManager::battleBoss(Character* player) {
    // 드래곤 객체 생성
    showDragon2LinesAnimation();
    Monster* boss = new Dragon();

    std::cout << "\n===== 보스전 돌입! 드래곤이 나타났습니다! =====\n";
    // 드래곤 ASCII 아트
    std::cout << R"(

        DRAGON
    )" << "\n\n";

    while (boss->getHealth() > 0 && player->getHealth() > 0) {
        // 플레이어 공격
        boss->takeDamage(player->getAttack());
        std::cout << "[플레이어] " << player->getName()
            << " → [보스] " << boss->getName()
            << " (피해: " << player->getAttack() << ")\n";

        // 보스 사망?
        if (boss->getHealth() <= 0) {
            std::cout << "드래곤을 쓰러뜨렸습니다!\n";
            bossDefeated = true;
            break;
        }

        // 보스 반격 (브레스 공격)
        // Dragon 타입이라면 breathAttack()도 함께 사용 가능
        if (Dragon* dragon = dynamic_cast<Dragon*>(boss)) {
            dragon->breathAttack();
        }
        player->takeDamage(boss->getAttack() + 20);

        // 플레이어 사망?
        if (player->getHealth() <= 0) {
            std::cout << player->getName() << "이(가) 드래곤에게 패배했습니다...\n";
            break;
        }

        std::cout << "\n";
    }
    delete boss;
}

// ────────────── 몬스터 생성 함수 ──────────────
Monster* GameManager::generateMonster(int level) {
    int monsterType = rand() % 4; // 0~3
    switch (monsterType) {
    case 0:  return new Goblin(level);
    case 1:  return new Orc(level);
    case 2:  return new Troll(level);
    default: return new Slime(level);
    }
}

// ────────────── 인벤토리 열기 ──────────────
void GameManager::displayInventory(Character* player) {
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

// ────────────── 상점 방문 (4번 기능) ──────────────
void GameManager::visitShop(Character* player) {
    std::cout << "\n===== 상점 입장 =====\n";
    bool shopping = true;
    while (shopping) {
        std::cout << "\n[보유 골드] " << player->getGold() << " G\n"
            << "1. 체력포션 (50G)\n"
            << "2. 공격력 증가 포션 (70G)\n"
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
                // 실제로 포션 아이템을 인벤토리에 추가
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
                // 실제로 공격력 증가 포션을 인벤토리에 추가
                player->addItem(new AttackBoost());
                std::cout << "공격력 증가 포션 구매 완료!\n";
            }
            else {
                std::cout << "골드가 부족합니다!\n";
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
