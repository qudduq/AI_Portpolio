#include "CameraShakeManager.h"

#include "Camera/CameraShakeBase.h"

TSharedPtr<CameraShakeManager> CameraShakeManager::Instance = nullptr;
int CameraShakeManager::count = 0;

TSharedRef<CameraShakeManager> CameraShakeManager::GetInstance()
{
	if(Instance == nullptr)
	{
		Instance = MakeShareable(new CameraShakeManager(),Deleter{});
	}

	return Instance.ToSharedRef();
}

bool CameraShakeManager::IsCameraShaking()
{
	if (CameraShake->OscillationDuration < 0.001f || CameraShake->IsFinished())
		return false;

	return true;
}

void CameraShakeManager::SaveCameraShake(UMatineeCameraShake* matineeCamera)
{
	if (CameraShake->OscillationDuration < 0.001f || CameraShake->GetName() != matineeCamera->GetName())
	{
		CLog::Log(count);
		count++;
		CameraShake = (matineeCamera);
	}
}

CameraShakeManager::CameraShakeManager()
{

}

CameraShakeManager::~CameraShakeManager()
{

}
