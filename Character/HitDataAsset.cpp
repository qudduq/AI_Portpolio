#include "HitDataAsset.h"
#include "Utillities/CLog.h"

UHitDataAsset::UHitDataAsset()
{

}

FHitData UHitDataAsset::GetHitData(EDamageType Type)
{
	if (HitDataMap.Find(Type) == nullptr)
	{
		CLog::Log("not Setting HitData");
		return FHitData();
	}

	return HitDataMap[Type];
}