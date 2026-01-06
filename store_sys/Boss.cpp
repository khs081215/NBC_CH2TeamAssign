#include "Boss.h"
#define COLOR_REV_RED "\033[41m"
#define COLOR_RESET "\033[0m"

// 부모 생성자 Monster(L, N)를 호출하여 기본 랜덤 스탯을 먼저 생성합니다.
Boss::Boss(int playerLevel) : Monster(playerLevel, "★심연의 군주 발록★") {
    // 조건: 기존 몬스터 스탯의 1.5배로 재설정
    this->Hp = (int)(this->getcurHealth() * 1.5);
    this->Atk = (int)(this->GetAttack() * 1.5);


}

void Boss::showInfo() {
    cout << COLOR_REV_RED;
    cout << "\n==================================================" << endl;
    cout << " [WARNING] 대지가 흔들리며 강력한 기운이 느껴집니다..." << endl;
    cout << "==================================================" << endl;

    // 부모의 showInfo를 활용하여 기본 스탯 출력
    Monster::showInfo();

    cout << " >> 특이사항: 모든 일반 몬스터의 정점에 선 존재 <<" << endl;
    cout << "==================================================\n" << endl;
    //cout << COLOR_RESET;
}

void Boss::display()
{
    cout << COLOR_REV_RED;
    char print_temp[256];
    FILE* fp;
    errno_t err= fopen_s(&fp, "Boss.tmg", "rt");
    system("mode con cols=80");

    if (err != 0)return;
    while (fgets(print_temp, 255, fp) != NULL) {
        cout << print_temp;
    }
    fclose(fp);
    cout << COLOR_RESET;
}