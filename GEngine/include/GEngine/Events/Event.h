#pragma once

#include<functional>


namespace GEngine
{

#define BIND_EVENT_FN(fn) [this](auto&& ... args)->decltype(auto){return this->fn(std::forward<decltype(args)>(args)...); }


	template<typename... Args>
	class Events

	{

		using Callbacks = std::vector<std::function<void(Args...)>>;

		using iterator = typename Callbacks::iterator;

		using const_iterator = typename Callbacks::const_iterator;


	public:


		void subscribe(const std::function<void(Args...)>& function) { m_Callbacks.push_back(function); }

		void unsubscribe(const std::function<void(Args...)>& function)

		{

			m_Callbacks.erase(std::remove_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const std::function<void(Args...)>& f)

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

		Callbacks m_Callbacks;

	};

}