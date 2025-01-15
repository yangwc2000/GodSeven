// Boss.cpp
#include "Boss.h"
#include "DragonVisual.h"
#include <iostream>

Dragon::Dragon()
    : Monster("Dragon", 1000, 50) // 체력, 공격력 설정
{
}

void Dragon::breathAttack() 
{
    showDragonFireAnimation();
    std::cout << "드래곤이 강력한 브레스를 뿜습니다!!\n";
}
