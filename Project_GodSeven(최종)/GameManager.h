#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include "Character.h"
#include "Monster.h"

class GameManager
{
public:
    GameManager();

    // 게임 시작
    void startGame();

    // 배경음악 재생
    void playMusic(const std::string& filePath, bool loop = false);

    // 효과음 재생 및 배경음악 일시 중지 후 재개
    void playEffectWithPause(const std::string& effectFilePath, const std::string& backgroundMusicPath, int effectDurationMs);

    // 일반 몬스터 전투
    void battle(Character* player, int habitat); // 서식지 인자 추가

    // 보스(드래곤) 전투
    void battleBoss(Character* player);

    // 몬스터 생성
    Monster* generateMonster(int level, int habitat); // 서식지 인자 추가

    // 인벤토리 열기
    void displayInventory(Character* player);

    // 타이틀 화면
    void displayTitleScreen();

    // 상점 방문
    void visitShop(Character* player);

    // 몬스터 서식지 탐험
    void exploreHabitat(Character* player);

    // 야바위 게임
    void playShellGame(Character* player);

private:
    Character* player; // 플레이어 캐릭터 포인터
};

#endif // GAMEMANAGER_H
