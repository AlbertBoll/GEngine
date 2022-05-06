#pragma once

#include<functional>


namespace GEngine
{

#define BIND_EVENT_FN(fn) [this](auto&& ... args)->decltype(auto){return this->fn(std::forward<decltype(args)>(args)...); }



	class IEvent
	{

	public:
		virtual const std::string& GetName() const = 0;
		virtual ~IEvent(){}

	};


	template<typename> class Events;

	template<typename R, typename... Args>
	class Events<R(Args...)>: public IEvent

	{

		using Callbacks = std::vector<std::function<R(Args...)>>;

		using iterator = typename Callbacks::iterator;

		using const_iterator = typename Callbacks::const_iterator;


	public:
		Events() = default;

		Events(const std::string& eventName): m_EventName(eventName){}

		const std::string& GetName() const override { return m_EventName; }

		void Reserve(size_t size) { m_Callbacks.reserve(size); }

		auto& Subscribe(const std::function<R(Args...)>& function) { m_Callbacks.push_back(function); return function; }

		void Unsubscribe(const std::function<R(Args...)>& function)

		{

			m_Callbacks.erase(std::remove_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const std::function<R(Args...)>& f)

				{

					return function.target_type().hash_code() == f.target_type().hash_code();

				}), m_Callbacks.end());

		}


		iterator begin() { return m_Callbacks.begin(); }

		iterator end() { return m_Callbacks.end(); }

		[[nodiscard]] const_iterator begin() const { return m_Callbacks.begin(); }

		[[nodiscard]] const_iterator end() const { return m_Callbacks.end(); }

		[[nodiscard]] const_iterator cbegin() const { return m_Callbacks.cbegin(); }

		[[nodiscard]] const_iterator cend() const { return m_Callbacks.cend(); }


		template<typename ... Args>
		void Fire(Args&&... args)const
		{

			this->operator()(std::forward<Args>(args)...);

		}

		void operator()(Args&&... args)const
		{

			for (auto&& event_func : m_Callbacks)
			{
				event_func(std::forward<Args>(args)...);
			}

		}


	private:
		std::string m_EventName;
		Callbacks m_Callbacks;

	};


	class EventDispatcher
	{

	public:

		~EventDispatcher() 
		{
			
			for (auto& eventList : m_EventCallBackList)
			{
				delete eventList.second;
			}
		};
		
		void UnregisterEvent(const std::string& eventName)
		{
			m_EventCallBackList.erase(eventName);
		}


		void RegisterEvent(IEvent* callBackList)
		{
			if (auto p = m_EventCallBackList.find(callBackList->GetName()); p == m_EventCallBackList.end())
			{
				m_EventCallBackList[callBackList->GetName()] = callBackList;
			}

			
		}

		template <typename R = void, typename ... Args>
		void DispatchEvent(const std::string& eventName, Args&&...args)
		{
			if (auto p = m_EventCallBackList.find(eventName); p != m_EventCallBackList.end())
			{
				if (Events<R(Args...)>* events = dynamic_cast<Events<R(Args...)>*>(p->second))
				{
					events->Fire(std::forward<Args>(args)...);
				}
			}

		}



	private:
		std::unordered_map<std::string, IEvent*> m_EventCallBackList;
	};


}