#pragma once
#include <string>

class UUIManager {
public:
	template<typename T>
	std::string ChangeNumToStrWithMargin(int marginNum, T num);
};

template<typename T>
std::string UUIManager::ChangeNumToStrWithMargin(int marginNum, T num)
{
	std::string numToStr = std::to_string(num);

	int digitCount = numToStr.length();
	int paddingSize = std::max(0, marginNum - digitCount / 2);

	std::string strOut(paddingSize, ' ');
	strOut += numToStr;

	return strOut;
}