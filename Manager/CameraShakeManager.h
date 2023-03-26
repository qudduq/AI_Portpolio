#pragma once

#include "CoreMinimal.h"
#include "Utillities/CLog.h"

class AI_PORTPOLIO_API CameraShakeManager
{
public:
	static TSharedRef<CameraShakeManager> GetInstance();

	bool IsCameraShaking();
	void SaveCameraShake(UMatineeCameraShake* matineeCamera);

private:
	// 동적할당된 인스턴스가 자동으로 지워질수있도록 스마트포인터 활용
	static TSharedPtr<CameraShakeManager> Instance;

	//스마트포인터에 의해서 소멸자를 불러줘야하지만 private에 있는경우 불려지지않음
	//Deleter라는 구조체로 래핑하여 딜리트 될수있도록 세팅
	struct Deleter
	{
		void operator()(CameraShakeManager* Ptr)
		{
			delete Ptr;
		}
	};
	friend Deleter;

	CameraShakeManager();
	~CameraShakeManager();

	class UMatineeCameraShake* CameraShake;
	static int count;
};
