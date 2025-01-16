// Boss.cpp
#include "Boss.h"
#include "Item.h"

Dragon::Dragon()
    : Monster("드래곤(해츨링)", 550, 80) {
}

void Dragon::breathAttack() {
    // 드래곤의 브레스 공격 로직
}

Item* Dragon::dropItem() const {
    return new Treasure("해츨링의 비늘", 1000); // 드래곤이 드랍하는 환금용 아이템
}
