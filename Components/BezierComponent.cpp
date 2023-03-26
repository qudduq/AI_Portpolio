#include "Components//BezierComponent.h"
#include "Math/Vector.h"
#include "Utillities/CLog.h"

UBezierComponent::UBezierComponent()
{

}

void UBezierComponent::ShootBezierCurve(const FVector EndPostion,const FVector OwnerPosition)
{
	//곡선을 만들수있는 제어점생성
	const FVector ControlPosition = SetControlPosition(GetOwner()->GetActorLocation(), EndPostion, OwnerPosition);

	//타이머함수를 통하여 각비율의 점들을 전부 지나 곡선을 이룰수있도록 해줍니다.
	GetWorld()->GetTimerManager().SetTimer
	(
		handle,
		FTimerDelegate::CreateLambda
		(
			[=]()
			{
				if (Rate >= 1.0f)
				{
					Rate = 0.0f;
					GetWorld()->GetTimerManager().ClearTimer(handle);
					return;
				}

				Rate += GetWorld()->DeltaTimeSeconds * Speed;
				const FVector Location = GetLocationBezier(GetOwner()->GetActorLocation(), EndPostion, ControlPosition, Rate);
				GetOwner()->SetActorLocation(Location);
			}
		),
		0.01f,
		true
	);
}

const FVector UBezierComponent::GetLocationBezier(const FVector start,const FVector end,const FVector adj,const float rate)
{
	/*배지어곡선을 만들기 위한 식
	 *베지어곡선은 각 점들의 비율의 끝점을 모아서 만들어집니다.*/
	FVector sa = FMath::Lerp(start, adj, rate);
	FVector ea = FMath::Lerp(adj, end, rate);

	return FMath::Lerp(sa, ea, rate);
}

const FVector UBezierComponent::SetControlPosition(const FVector Start,const FVector End, const FVector OwerPosition)
{
	//외적을 사용한 좌우판별 Z축사용
	float left_right = FVector::CrossProduct((Start - OwerPosition), (End- OwerPosition)).Z;

	FVector ControlPosition = FVector();
	if(left_right < 0) //오른쪽
	{
		ControlPosition = End + FVector(0, SpaceHorizontal, SpaceVertical);
	}
	else // 왼쪽
	{
		ControlPosition = End + FVector(0, -SpaceHorizontal, SpaceVertical);
	}

	return ControlPosition;
}




