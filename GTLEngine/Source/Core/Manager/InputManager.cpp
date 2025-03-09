
#include "pch.h"
#include "InputManager.h"

UInputManager::UInputManager()
    : currentKeyStates(TArray<bool>(256, false))
    , prevKeyStates(TArray<bool>(256, false))
{}

UInputManager::~UInputManager()
{}

void UInputManager::Update(HWND hWnd, int Width, int Height)
{
    // 현재 키 상태를 이전 상태에 복사
    prevKeyStates = currentKeyStates;
    // 0~255 범위의 가상키에 대해 GetAsyncKeyState를 호출하여 현재 상태 업데이트
    for (int i = 0; i < 256; ++i)
    {
        currentKeyStates[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }

    // 현재 마우스 상태를 이전 상태에 복사
    prevMouseState = currentMouseState;
    // 마우스 버튼 상태 업데이트
    currentMouseState.leftButton = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    currentMouseState.rightButton = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    currentMouseState.middleButton = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    // 마우스 커서 위치 업데이트
    POINT pt;
    if (GetCursorPos(&pt))
    {
        currentMouseState.ScreenX = pt.x;
        currentMouseState.ScreenY = pt.y;

        if (ScreenToClient(hWnd, &pt))
        {
            currentMouseState.ClientX = pt.x;
            currentMouseState.ClientY = pt.y;

            ConvertMouseToNDC(hWnd, Width, Height);
        }
    }
}

bool UInputManager::GetKey(int key) const
{
    return currentKeyStates[key];
}

bool UInputManager::GetKeyDown(int key) const
{
    return currentKeyStates[key] && !prevKeyStates[key];
}

bool UInputManager::GetKeyUp(int key) const
{
    return !currentKeyStates[key] && prevKeyStates[key];
}

void UInputManager::ConvertMouseToNDC(HWND hWnd, int Width, int Height)
{
    // 마우스 커서 위치를 NCD 좌표로 변환
    float HalfWidth = Width / 2.f;
    float HalfHeight = Height / 2.f;
    float MaxHalfLength = max(HalfWidth, HalfHeight);
    currentMouseState.ndcX = (currentMouseState.ScreenX - HalfWidth) / HalfWidth;
    currentMouseState.ndcY = (currentMouseState.ScreenY - HalfHeight) / HalfWidth * -1.f;
}

bool UInputManager::GetMouseButton(int button) const
{
    if (button == 0)
        return currentMouseState.leftButton;
    if (button == 1)
        return currentMouseState.rightButton;
    if (button == 2)
        return currentMouseState.middleButton;
    return false;
}

bool UInputManager::GetMouseDown(int button) const
{
    if (button == 0)
        return currentMouseState.leftButton && !prevMouseState.leftButton;
    if (button == 1)
        return currentMouseState.rightButton && !prevMouseState.rightButton;
    if (button == 2)
        return currentMouseState.middleButton && !prevMouseState.middleButton;
    return false;
}

bool UInputManager::GetMouseUp(int button) const
{
    if (button == 0)
        return !currentMouseState.leftButton && prevMouseState.leftButton;
    if (button == 1)
        return !currentMouseState.rightButton && prevMouseState.rightButton;
    if (button == 2)
        return !currentMouseState.middleButton && prevMouseState.middleButton;
    return false;
}
