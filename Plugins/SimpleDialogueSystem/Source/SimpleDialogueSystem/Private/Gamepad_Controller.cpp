// Copyright 2020, Justin Wells, All rights reserved.


#include "Gamepad_Controller.h"
#include "Super_NPC.h"

AGamepad_Controller::AGamepad_Controller()
{
  bIsUsingGamepad = false;
  bResetGamepadDetectionAfterNoInput = true;
  GamepadTimeout = 5.f;
}

bool AGamepad_Controller::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
  bool ret = Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
  _UpdateGamepad(bGamepad);
  return ret;
}

bool AGamepad_Controller::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
  bool ret = Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
  _UpdateGamepad(bGamepad);
  return ret;
}

void AGamepad_Controller::PlayerTick(float DeltaTime)
{
  Super::PlayerTick(DeltaTime);
  if (IsLocalController() && bResetGamepadDetectionAfterNoInput && bIsUsingGamepad)
  {
    float now = GetWorld()->TimeSeconds;
    if (now > LastGamepadInputTime + GamepadTimeout)
    {
      bIsUsingGamepad = false;
      ControllerDisconnected(); 
    }
  }
}
