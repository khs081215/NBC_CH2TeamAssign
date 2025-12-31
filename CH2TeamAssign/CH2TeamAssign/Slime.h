#pragma once
#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster {
public:
    // 생성자를 public으로 선언해야 밖에서 만들 수 있습니다.
    Slime();
};

#endif