#include "Components//BezierComponent.h"
#include "Math/Vector.h"
#include "Utillities/CLog.h"

UBezierComponent::UBezierComponent()
{

}

void UBezierComponent::ShootBezierCurve(const FVector EndPostion,const FVector OwnerPosition)
{
	//��� ������ִ� ����������
	const FVector ControlPosition = SetControlPosition(GetOwner()->GetActorLocation(), EndPostion, OwnerPosition);

	//Ÿ�̸��Լ��� ���Ͽ� �������� ������ ���� ���� ��� �̷���ֵ��� ���ݴϴ�.
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
	/*�������� ����� ���� ��
	 *�������� �� ������ ������ ������ ��Ƽ� ��������ϴ�.*/
	FVector sa = FMath::Lerp(start, adj, rate);
	FVector ea = FMath::Lerp(adj, end, rate);

	return FMath::Lerp(sa, ea, rate);
}

const FVector UBezierComponent::SetControlPosition(const FVector Start,const FVector End, const FVector OwerPosition)
{
	//������ ����� �¿��Ǻ� Z����
	float left_right = FVector::CrossProduct((Start - OwerPosition), (End- OwerPosition)).Z;

	FVector ControlPosition = FVector();
	if(left_right < 0) //������
	{
		ControlPosition = End + FVector(0, SpaceHorizontal, SpaceVertical);
	}
	else // ����
	{
		ControlPosition = End + FVector(0, -SpaceHorizontal, SpaceVertical);
	}

	return ControlPosition;
}




