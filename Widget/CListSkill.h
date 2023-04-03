#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "CDragWidget.h"
#include "CListSkill.generated.h"

/*
	virtual void NativeOnInitialized(); : 게임시작시에 한번만콜
	virtual void NativeConstruct();     : 세팅마다 콜
*/

UCLASS()
class AI_PORTPOLIO_API UCListSkill 
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* SkillImage;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCDragWidget> DragWidget;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

public:
	FORCEINLINE FVector2D GetImageSize() { return SkillImage->GetDesiredSize(); }
	UTexture2D* GetImage() { return texture; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
		class UCSkill* skill;

	UPROPERTY(Replicated)
		UTexture2D* texture;

	FTimerHandle handle;

	FVector2D Position;
};
