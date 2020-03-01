// Copyright 2020, Justin Wells, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Super_NPC.generated.h"

class UBoxComponent;
class USoundCue;
class UWidgetComponent;
class UCameraComponent;

UCLASS()
class SIMPLEDIALOGUESYSTEM_API ASuper_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASuper_NPC();

  /* Sound that plays during dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  USoundCue* DialogueSound;

  /* The camera that is used during dialogue */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UCameraComponent* DialogueCamera;

  /* The transform of the Dialogue Camera relative to the NPC */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Blend Settings", meta = (MakeEditWidget = true))
  FTransform CameraTransform;

  /* The name of the NPC shown on the dialogue widget */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  FText NPCName;

  /* This is where dialogue is stored a new index will equal a new dialogue screen */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  TArray<FText> DialogueToSay;

  /* The delay between each screen of dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings", meta = (EditCondition = "!bRequireInput"))
  float DialogueScreenDelay;

  /* The delay between each letter being printed to the screen */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
  float TextSpeed;

  /* Default value of TextSpeed */
  UPROPERTY(BlueprintReadWrite, Category = "Dialogue Settings")
  float DefaultTextSpeed;

  /* Default value of DialogueScreenDelay */
  UPROPERTY(BlueprintReadWrite, Category = "Dialogue Settings")
  float DefaultDialogueScreenDelay;

  /* Weather or not the NPC is currently talking */
  UPROPERTY(BlueprintReadWrite, Category = "Dialogue Settings")
  bool bCurrentlyTalking;

  /* Whether or not to require input from the player to continue dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "!bStartOnOverlap"))
  bool bRequireInput;

  /* Whether or not dialogue should start when overlapping the dialogue trigger or should wait for a given input */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "!bRequireInput"))
  bool bStartOnOverlap;

  /* Whether or not the last dialogue screen should ask the player a question this will make the choice 1 and choice 2 button's appear next the dialogue widget */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  bool bIsQuestText;
  /* What the NPC will say if the player chose dialogue option 1 if blank dialogue will end */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bIsQuestText"))
  FText NPCDialogueOption1;
  /* What the NPC will say if the player chose dialogue option 2 if blank dialogue will end */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bIsQuestText"))
  FText NPCDialogueOption2;
  /* The first dialogue option the player has */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bIsQuestText"))
  FText PlayerDialogueOption1;
  /* The second dialogue option the player has */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bIsQuestText"))
  FText PlayerDialogueOption2;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UBoxComponent* DialogueTrigger;

  /* This key used to continue dialogue if RequireInput is true if no controller is detected this key is used */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bRequireInput"))
  FKey InputKeyKeyboard;

  /* This key used to continue dialogue if RequireInput is true and a gamepad is connected */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bRequireInput"))
  FKey InputKeyController;

  /* These are the keys used to skip dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  TArray<FKey> SkipKeys;

  UPROPERTY(BlueprintReadWrite, Category = "Dialogue Settings")
  bool bInputKeyPressed;

  /* This will create a dialogue widget and play text from the dialogue to say array until it reaches the end of the array will also disable player movement */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void StartDialogue();

  /* Stop's dialogue and removes the widget from the screen */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void EndDialogue();
  /* If player chose the first option then this event is called */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ChoseOption1();
  /* If player chose the second option this event is called */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ChoseOption2();

  /* Sets the textspeed to 0 so there is no delay between letters being printed then sets the dialogue screen to 0.5 if RequireInput player will still need to press the input key to continue to the next dialogue screen */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void SkipDialogue();
  /* First event called if player chose dialogue option 1 */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ContinueToOption1();
  /* First event called if player chose dialogue option 2 */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ContinueToOption2();

  /* Moves dialogue to the screen either waits for play input or pause and the specified time set in DialogueScreenDelay */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ContinueDialogue();

  /* Sends updates to NPC that player is using a gamepad so updates UI */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void UpdateKeyToController();

  /* Sends updates to NPC that player is not using a gamepad so update UI this is also the default state of an NPC */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void UpdateKeyToKeyboard();

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
