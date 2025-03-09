#pragma once
#include "pch.h"
#include <string>

class UUIManager {
public:
	template<typename T>
	std::string ChangeNumToStrWithMargin(int marginNum, T num);
};
