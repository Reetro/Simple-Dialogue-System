// Copyright 2020, Justin Wells, All rights reserved.


#include "Gamepad_Controller.h"
#include "Super_NPC.h"


AGamepad_Controller::AGamepad_Controller()
{
  bIsUsingGamepad = false;
  bResetGamepadDetectionAfterNoInput = true;
  GamepadTimeout = 5.f;
}

bool AGamepad_Controller::InputAxis(const FKey Key, const float Delta, const float DeltaTime, const int32 NumSamples, const bool bGamepad)
{
  const bool bRet = Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
  _UpdateGamepad(bGamepad);
  return bRet;
}

bool AGamepad_Controller::InputKey(const FKey Key, const EInputEvent EventType, const float AmountDepressed, const bool bGamepad)
{
  const bool bRet = Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
  _UpdateGamepad(bGamepad);
  return bRet;
}

void AGamepad_Controller::PlayerTick(float DeltaTime)
{
  Super::PlayerTick(DeltaTime);
  if (IsLocalController() && bResetGamepadDetectionAfterNoInput && bIsUsingGamepad)
  {
    const float Now = GetWorld()->TimeSeconds;
    if (Now > LastGamepadInputTime + GamepadTimeout)
    {
      bIsUsingGamepad = false;
      ControllerDisconnected(); 
    }
  }
}
