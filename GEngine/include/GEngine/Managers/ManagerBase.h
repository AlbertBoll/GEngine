#pragma once
#include "Core/Utility.h"

namespace GEngine::Manager
{

	//CRTP......Any concreate manager class derived from ManagerBase template class will be singleton and using CRTP to Get unique instance of T
	template<typename T>
	class ManagerBase
	{
	public:
	
		static T& Get();

	protected:
		ManagerBase(){}
		~ManagerBase(){}

	public:
		NONCOPYABLE(ManagerBase);
	};


	template<typename T>
	inline T& ManagerBase<T>::Get()
	{
		static T Manager;
		return Manager;
	}

	
}
