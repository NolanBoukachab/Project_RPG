// Copyright Underflow Studios 2017
#pragma once
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "CoreMinimal.h"
#include "Dialogue.generated.h"

class UDialogue;
// Extend this class to add custom events
UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class DIALOGUEPLUGIN_API UDialogueEvents : public UObject
{
	GENERATED_BODY()
	
public:
	UDialogueEvents();

	//Called when the event is triggered. 
	//Return bool if you're on 4.16, because void crashes.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dialogue Events")
	void RecieveEventTriggered(APlayerController* ConsideringPlayer, AActor* NPCActor);

	virtual class UWorld* GetWorld() const override;
};

// Extend this class to add custom conditions.
UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class DIALOGUEPLUGIN_API UDialogueConditions : public UObject
{
	GENERATED_BODY()
	
public:
	UDialogueConditions();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue Conditions")
	bool IsConditionMet(APlayerController* ConsideringPlayer, AActor* NPCActor);

	// It is assigned in DialogueUserWidget.cpp just before calling IsConditionMet()
	UPROPERTY(Transient)
	UWorld * World;

	virtual class UWorld* GetWorld() const override;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	int32 id = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	bool isPlayer;

	//Todo: Make this more adjustable, allow variables in text. Allow text to be colored differently, etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	TArray<int32> Links;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	FVector2D Coordinates;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Dialogue Node")
	TArray<UDialogueEvents*> Events;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "Dialogue Node")
	TArray<UDialogueConditions*> Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	class USoundBase* Sound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
	class UDialogueWave* DialogueWave = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class DIALOGUEPLUGIN_API UDialogue : public UDataAsset
{
	GENERATED_BODY()

public:

	UDialogue(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	FDialogueNode GetFirstNode();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	TArray<FDialogueNode> GetNextNodes(FDialogueNode Node);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	static void CallFunctionByName(UObject* Object, FString FunctionName);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	bool DisplayIdleSplines = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	TArray<FDialogueNode> Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	int32 NextNodeId;

	UPROPERTY(Transient)
	class UGameInstance * PersistentGameInstance;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AssignPersistentOuter(class UGameInstance * inGameInstance);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void CleanOuter();

	virtual UWorld* GetWorld() const override;	

	FDialogueNode GetNodeById(int32 id, int32 &index);
	FDialogueNode GetNodeById(int32 id);

	int32 CurrentNodeId;
	bool isLinking;
	FVector2D LinkingCoords;
	int32 LinkingFromIndex;
	//FSlateImageBrush* bgStyle;
};
