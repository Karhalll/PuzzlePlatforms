// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	const bool Success = Super::Initialize();
	if (!Success) return false;

	if (!Host) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MMenuInterface)
{
	this->MenuInterface = MMenuInterface;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}
