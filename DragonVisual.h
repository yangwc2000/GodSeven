#pragma once
#ifndef DRAGON_VISUAL_H
#define DRAGON_VISUAL_H

// 드래곤과 불길을 출력하는 함수들

// 콘솔 화면을 지우는 함수
void clearScreen();

// 드래곤 + 단계별 불길 아트를 출력
void printDragonAndFire(int step);

// 실제로 애니메이션을 재생하는 함수를 만들어
// GameManager 등에서 간단히 호출할 수 있도록 제공
void showDragonFireAnimation();

#endif // DRAGON_VISUAL_H

