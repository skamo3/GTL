#include "pch.h"
#include "UIManager.h"

template<typename T>
string UUIManager::ChangeNumToStrWithMargin(int marginNum, T num)
{
	std::string numToStr = std::to_string(num);

	int digitCount = numToStr.length();
	int paddingSize = max(0, marginNum - digitCount / 2);

	string strOut(paddingSize, ' ');
	strOut += numToStr;

	return strOut;
}
