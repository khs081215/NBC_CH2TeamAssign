#include "Store.h"
#include "CityData.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

// ✅ 테스트용 함수
void testStoreSystem() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); //한글출력용 설정
#endif

    // --- 플레이어 인벤토리와 골드 초기화 ---
    std::vector<std::unique_ptr<ItemBase>> playerInventory;
    int playerGold = 2000;

    // --- 도시 목록 불러오기 ---
    std::vector<City> cities = getCities();

    // --- 현재 도시 설정 ---
    City& currentCity = cities[0];
    
    //rand()함수를사용하기위한 초기화
    srand(static_cast<unsigned int>(time(nullptr)));

    // --- 상점 진입 ---
    goToStore(currentCity, playerInventory, playerGold);
}
