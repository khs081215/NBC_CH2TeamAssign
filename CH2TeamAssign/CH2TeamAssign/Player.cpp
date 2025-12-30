// 김태우_테스트용 플레이어 cpp
//#include <iostream>
//#include <string>
//#include "Player.h"
//
//using namespace std;
//
//void Player::RestoreHP(int restore) {
//    if (currentHealth < maxHealth)
//    {
//        cout << "체력 회복" << endl;
//        currentHealth += restore;
//
//        if(currentHealth > maxHealth) {
//            currentHealth = maxHealth;
//            cout << "현재체력을 최대체력과 맞게 보정" << endl;
//        }
//        cout << "현재 체력 : " << currentHealth << endl;
//    }
//    else 
//    {
//        cout << "체력이 가득차있습니다." << endl;
//    }
//}
//
//void Player::IncreaseATK(int bounsAtk) {
//    cout << "공격력 " << bounsAtk << "만큼 증가" << endl;
//    bonusAttack = bounsAtk;
//}
//
//void Player::TakeDamage(int damage) {
//    cout << damage << " 만큼 데미지 입음!!" << endl;
//    currentHealth -= damage;
//    
//    cout << "남은 체력 : " << currentHealth << endl;
//}
//
//void Player::EndBuff() {
//    cout << "전투 종료시 호출 : 버프 종료" << endl;
//    bonusAttack = 0;
//}
//
//void Player::ViewATK() {
//    cout << "현재 공격력 : " << attack + bonusAttack << endl;
//}