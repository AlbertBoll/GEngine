#pragma once

#include <memory>


#define NONCOPYABLE(className) className(const className&) = delete;\
							   className& operator=(const className&) = delete

#define NONMOVABLE(className) className(className&&) = delete;\
							   className& operator=(className&&) = delete

#define NONCOPYMOVABLE(className)  NONCOPYABLE(className);\
								   NONMOVABLE(className)


#ifdef GENGINE_CONFIG_DEBUG
	#if defined(GENGINE_PLATFORM_WINDOWS)
		#define GENGINE_DEBUGBREAK() __debugbreak()

	#elif defined(GENGINE_PLATFORM_LINUX)
		//#include<signal.h>
		//#define GENGINE_DEBUGBREAK() raise(SIGTRAP)
		#define GENGINE_DEBUGBREAK() __builtin_trap();
	
	#elif defined(GENGINE_PLATFORM_MAC)
		#define GENGINE_DEBUGBREAK() __builtin_debugtrap();

	//not yet support any other platforms
	#else
		#error "Platform doesn't support debugbreak yet!"
	
	#endif
	#define GENGINE_ENABLE_ASSERTS
	
#else
	#define GENGINE_DEBUGBREAK()

#endif

#define GENGINE_EXPAND_MACRO(str) str
#define GENGINE_STRINGIFY_MACRO(str) #str

#define BIT(x) (1 << x)

#define BENGINE_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace GEngine
{
	template<typename T, typename deleter = std::default_delete<T>>
	using ScopedPtr = std::unique_ptr<T, deleter>;

	//using default deleter
	template<typename T, typename ... Args>
	constexpr ScopedPtr<T> CreateScopedPtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	//using custom deleter
	template<typename T, typename deleter, typename ... Args>
	constexpr ScopedPtr<T, deleter> CreateScopedPtr(Args&& ... args)
	{
		return std::unique_ptr<T, deleter>(new T{ std::forward<Args>(args)... }, deleter{});
	}


	template<typename T>
	using RefPtr = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr RefPtr<T> CreateRefPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename deleter, typename... Args>
	constexpr RefPtr<T> CreateRefPtr(Args&& ... args)
	{
		return std::shared_ptr<T>(new T{ std::forward<Args>(args)... }, deleter{});
	}

	template<typename Enum, typename Value, typename = std::enable_if_t<std::is_enum_v<Enum>>>
	class BitFlags
	{
	public:
		template<typename ... Args>
		constexpr BitFlags(Args&& ... args) : m_Value{ Create<Enum>(std::forward<Args>(args)...) } {}

		template<typename T, typename ... Args>
		constexpr Value Create(T t, Args&&... args) const {
			return Create(t) | Create(std::forward<Args>(args)...);
		}

		template<typename T>
		constexpr Value Create(T t) const {
			return static_cast<Value>(t);
		}

		template<typename T>
		constexpr Value Create() const { return 0; }

		constexpr bool IsSet(Enum e) const
		{
			return (m_Value & static_cast<Value>(e)) != 0;
		}

		void Combine(const BitFlags& other)
		{
			m_Value |= other.m_Value;
		}

		operator Value()const { return m_Value; }


	private:
		Value m_Value;
	};





}

#include "Core/Log.h"
#include "Core/Assert.h"