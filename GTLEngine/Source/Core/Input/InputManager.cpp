
#include "pch.h"
#include "InputManager.h"

#include "Engine.h"

UInputManager::UInputManager()
    : CurrentKeyStates(TArray<bool>(256, false))
    , PrevKeyStates(TArray<bool>(256, false))
{}

UInputManager::~UInputManager()
{
    CurrentKeyStates.clear();
    PrevKeyStates.clear();
}

void UInputManager::Tick(float TickTime)
{
    // 현재 키 상태를 이전 상태에 복사
    PrevKeyStates = CurrentKeyStates;
    // 0~255 범위의 가상키에 대해 GetAsyncKeyState를 호출하여 현재 상태 업데이트
    for (int i = 0; i < 256; ++i)
    {
        CurrentKeyStates[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }

    // 현재 마우스 상태를 이전 상태에 복사
    PrevMouseState = CurrentMouseState;
    // 마우스 버튼 상태 업데이트
    CurrentMouseState.LeftButton = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    CurrentMouseState.RightButton = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    CurrentMouseState.MiddleButton = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    // 마우스 커서 위치 업데이트
    POINT pt;
    if (GetCursorPos(&pt))
    {
        CurrentMouseState.ScreenX = pt.x;
        CurrentMouseState.ScreenY = pt.y;

        
        if (ScreenToClient(UEngine::GetEngine().GetWindowInfo().WindowHandle, &pt))
        {
            CurrentMouseState.ClientX = pt.x;
            CurrentMouseState.ClientY = pt.y;
            FWindowInfo WindowInfo = UEngine::GetEngine().GetWindowInfo();
            ConvertMouseToNDC(WindowInfo.WindowHandle, WindowInfo.Width, WindowInfo.Height);
        }
    }
}

void UInputManager::Destroy()
{
}

bool UInputManager::GetKey(int key) const
{
    return CurrentKeyStates[key];
}

bool UInputManager::GetKeyDown(int key) const
{
    return CurrentKeyStates[key] && !PrevKeyStates[key];
}

bool UInputManager::GetKeyUp(int key) const
{
    return !CurrentKeyStates[key] && PrevKeyStates[key];
}

void UInputManager::ConvertMouseToNDC(HWND hWnd, int Width, int Height)
{
    // 마우스 커서 위치를 NCD 좌표로 변환
    float HalfWidth = Width / 2.f;
    float HalfHeight = Height / 2.f;
    CurrentMouseState.NdcX = (CurrentMouseState.ScreenX - HalfWidth) / HalfWidth;
    CurrentMouseState.NdcY = (CurrentMouseState.ScreenY - HalfHeight) / HalfHeight * -1.f;
}

bool UInputManager::GetMouseButton(EMouseButton button) const
{
    if (button == EMouseButton::LEFT)
        return CurrentMouseState.LeftButton;
    if (button == EMouseButton::RIGHT)
        return CurrentMouseState.RightButton;
    if (button == EMouseButton::MIDDLE)
        return CurrentMouseState.MiddleButton;
    return false;
}

bool UInputManager::GetMouseDown(EMouseButton button) const
{
    if (button == EMouseButton::LEFT)
        return CurrentMouseState.LeftButton && !PrevMouseState.LeftButton;
    if (button == EMouseButton::RIGHT)
        return CurrentMouseState.RightButton && !PrevMouseState.RightButton;
    if (button == EMouseButton::MIDDLE)
        return CurrentMouseState.MiddleButton && !PrevMouseState.MiddleButton;
    return false;
}

bool UInputManager::GetMouseUp(EMouseButton button) const
{
    if (button == EMouseButton::LEFT)
        return !CurrentMouseState.LeftButton && PrevMouseState.LeftButton;
    if (button == EMouseButton::RIGHT)
        return !CurrentMouseState.RightButton && PrevMouseState.RightButton;
    if (button == EMouseButton::MIDDLE)
        return !CurrentMouseState.MiddleButton && PrevMouseState.MiddleButton;
    return false;
}
