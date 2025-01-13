// GameManager.h
#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Character.h"
#include "Monster.h"

class GameManager
{
public:
    GameManager();
    void startGame();

    // 일반 몬스터 전투
    void battle(Character* player);

    // 보스(드래곤) 전투
    void battleBoss(Character* player);

    // 몬스터 생성
    Monster* generateMonster(int level);

    // 인벤토리 열기
    void displayInventory(Character* player);

    // 타이틀 화면
    void displayTitleScreen();

    // 상점 방문
    void visitShop(Character* player);
};

#endif
