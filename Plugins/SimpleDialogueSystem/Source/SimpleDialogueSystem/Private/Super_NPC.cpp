// Copyright 2020, Justin Wells, All rights reserved.

#include "Super_NPC.h"
#include "Components/BoxComponent.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASuper_NPC::ASuper_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  DialogueTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Dialogue Trigger"));
  if (!ensure(DialogueTrigger != nullptr)) { return; }
  DialogueTrigger->SetupAttachment(RootComponent);

  bRequireInput = false;
  bStartOnOverlap = true;

  TextSpeed = 0.07f;
  DialogueScreenDelay = 2.0f;

  if (bRequireInput)
  {
    bStartOnOverlap = false;
  }
  else if (bStartOnOverlap)
  {
    bRequireInput = false;
  }

  InputKeyKeyboard = EKeys::E;
  InputKeyController = EKeys::Gamepad_FaceButton_Left;

  SkipKeys.Add(EKeys::SpaceBar);
  SkipKeys.Add(EKeys::Gamepad_FaceButton_Bottom);

  NPCName = FText::FromString(ANSI_TO_TCHAR("Dave"));

  DialogueToSay.Add(FText::FromString(ANSI_TO_TCHAR("Welcome to Simple Dialogue System!")));
  
  DialogueCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Dialogue Camera"));
  if (!ensure(DialogueCamera != nullptr)) { return; }
  DialogueCamera->SetupAttachment(RootComponent);
}

void ASuper_NPC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  auto Player = UGameplayStatics::GetPlayerPawn(this, 0);

  if (bStartOnOverlap && OtherActor == Player)
  {
    StartDialogue();
  }
}

// Called when the game starts or when spawned
void ASuper_NPC::BeginPlay()
{
	Super::BeginPlay();
  
  // if bStartOnOverlap and bRequireInput are false default npc to require input
  if (!bRequireInput && !bStartOnOverlap)
  {
    bRequireInput = true;
  }

  DialogueTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASuper_NPC::OnOverlapBegin);
 
  if (!DialogueSound)
  {
    return;
  }
}
