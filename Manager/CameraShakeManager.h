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
	// �����Ҵ�� �ν��Ͻ��� �ڵ����� ���������ֵ��� ����Ʈ������ Ȱ��
	static TSharedPtr<CameraShakeManager> Instance;

	//����Ʈ�����Ϳ� ���ؼ� �Ҹ��ڸ� �ҷ���������� private�� �ִ°�� �ҷ���������
	//Deleter��� ����ü�� �����Ͽ� ����Ʈ �ɼ��ֵ��� ����
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
