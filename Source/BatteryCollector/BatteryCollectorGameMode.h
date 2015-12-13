// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
//#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"


// enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	/** Returns power needed to win */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	/** Sets the current state */
	void SetCurrentState(EBatteryPlayState NewState);
protected:
	/** the rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;

	/** the power needed to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;
	
	/**Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	//**the instance of the HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	/** keeps track of the current playing state */
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/** Handle any function calls that rely upon changing the playing state of our game */
	void HandleCurrentState(EBatteryPlayState NewState);
};



