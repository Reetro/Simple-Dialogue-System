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

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UCameraComponent* DialogueCamera;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Blend Settings", meta = (MakeEditWidget = true))
  FTransform CameraTransform;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  FText NPCName;

  /* This is where dialogue is stored a new index will equal a new dialogue screen */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  TArray<FText> DialogueToSay;

  /* The delay between each screen of dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings", meta = (EditCondition = "!bRequireInput"))
  float DialogueScreenDelay;

  /* The speed of each letter being printed to screen */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Settings")
  float TextSpeed;

  /* Whether to require input from player to continue dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "!bStartOnOverlap"))
  bool bRequireInput;

  UPROPERTY(BlueprintReadWrite, Category = "Dialogue Settings")
  bool bInputKeyPressed;

  UPROPERTY(BlueprintReadOnly, Category = "Dialogue Settings")
  float DefaultTextSpeed;

  /* Whether or not dialogue should start when overlapping the dialogue trigger or should wait for a given input */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "!bRequireInput"))
  bool bStartOnOverlap;

  UPROPERTY(BlueprintReadOnly, Category = "Dialogue Settings")
  float DefaultScreenDelay;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UBoxComponent* DialogueTrigger;

  /* This key used to continue dialogue if RequireInput is true if no controller is detected this key is used*/
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bRequireInput"))
  FKey InputKeyKeyboard;

  /* This key used to continue dialogue if RequireInput is true*/
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings", meta = (EditCondition = "bRequireInput"))
  FKey InputKeyController;

  /* These are the keys used to skip dialogue */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Settings")
  TArray<FKey> SkipKeys;

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void StartDialogue();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void EndDialogue();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void SkipDialogue();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void ContinueDialogue();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void UpdateKeyToController();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue Events")
  void UpdateKeyToKeyboard();

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
