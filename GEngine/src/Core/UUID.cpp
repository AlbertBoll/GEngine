#include"gepch.h"
#include"Core/UUID.h"
#include<random>
#include <unordered_map>

static std::unordered_map<GEngine::UUID, std::string> m_Map;

namespace GEngine
{

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID(): m_UUID(s_UniformDistribution(s_Engine))
	{

	}

	UUID::UUID(uint64_t id): m_UUID(id)
	{

	}
}

