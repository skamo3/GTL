#pragma once

#include "Object.h"

class UInputManager : public UObject
{
public:
    enum class MOUSE_BUTTON
    {
        LEFT = 0,
        RIGHT,
        MIDDLE,
    };

    UInputManager();
    ~UInputManager();

    // 매 프레임 호출하여 입력 상태를 업데이트
    void Update(HWND hWnd, int Width, int Height);

    // 키보드 입력 함수
    bool GetKey(int key) const;
    bool GetKeyDown(int key) const;
    bool GetKeyUp(int key) const;

    // 마우스 상태 구조체
    struct MouseState
    {
        bool leftButton = false;
        bool rightButton = false;
        bool middleButton = false;
        int ScreenX = 0;
        int ScreenY = 0;
        int ClientX = 0;
        int ClientY = 0;
        float ndcX = 0.f;
        float ndcY = 0.f;
    };

    // 마우스 입력 관련 함수

    // 0: Left Button, 1: Right Button, 2: Middle Button
    bool GetMouseButton(MOUSE_BUTTON button) const;
    // 0: Left Button, 1: Right Button, 2: Middle Button    
    bool GetMouseDown(MOUSE_BUTTON button) const;
    // 0: Left Button, 1: Right Button, 2: Middle Button    
    bool GetMouseUp(MOUSE_BUTTON button) const;
    int GetMouseClientX() const { return currentMouseState.ScreenX;};
    int GetMouseClient() const { return currentMouseState.ScreenY;};
    int GetMouseScreenX() const { return currentMouseState.ClientX;};
    int GetMouseScreenY() const { return currentMouseState.ClientY;};
    float GetMouseNDCX() const { return currentMouseState.ndcX;};
    float GetMouseNDCY() const { return currentMouseState.ndcY;};
    int GetMouseDeltaX() const { return currentMouseState.ClientX - prevMouseState.ClientX; };
    int GetMouseDeltaY() const { return currentMouseState.ClientY - prevMouseState.ClientY; };


protected:
    void ConvertMouseToNDC(HWND hWnd, int Width, int Height);

private:
    // 복사 및 대입 금지
    UInputManager(const UInputManager&) = delete;
    UInputManager& operator=(const UInputManager&) = delete;
    UInputManager(UInputManager&&) = delete;
    UInputManager& operator=(UInputManager&&) = delete;

    TArray<bool> currentKeyStates;
    TArray<bool> prevKeyStates;

    MouseState currentMouseState;
    MouseState prevMouseState;
};
