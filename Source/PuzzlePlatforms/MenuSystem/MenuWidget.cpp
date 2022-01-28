// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* MMenuInterface)
{
	this->MenuInterface = MMenuInterface;
}

void UMenuWidget::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!World) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!PlayerController) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!PlayerController) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	
	PlayerController->bShowMouseCursor = false;
}

