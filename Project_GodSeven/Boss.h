// Boss.h
#pragma once

#include "Monster.h"

class Dragon : public Monster {
public:
    Dragon();
    void breathAttack();
    Item* dropItem() const override; // dropItem 메서드 선언
};
