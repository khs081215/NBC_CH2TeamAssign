#pragma once
#include <vector>
#include <memory>
#include "ItemBase.h"

std::vector<std::unique_ptr<ItemBase>> getMasterItems();
