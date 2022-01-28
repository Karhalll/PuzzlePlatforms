// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowPBClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if(!ensure(ServerRowPBClass.Class != nullptr)) return;
	ServerRowClass = ServerRowPBClass.Class;
}

bool UMainMenu::Initialize()
{
	const bool Success = Super::Initialize();
	if (!Success) return false;

	if (!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (!JoinMenuButton) return false;
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!QuitGame) return false;
	QuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);
	
	if (!JoinButton) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (!BackButton) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	
	
	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		// if (!IPAddressField) return;
		// const FString& IPAddress = IPAddressField->GetText().ToString();
		//
		// MenuInterface->Join(IPAddress);

		UWorld* World = this->GetWorld();
		
		if(!ServerRowClass || !World) return;
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if(!Row) return;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!MenuSwitcher) return;
	if (!JoinMenu) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!MenuSwitcher) return;
	if (!MainMenu) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!PlayerController) return;

	PlayerController->ConsoleCommand("quit");
}
