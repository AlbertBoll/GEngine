#pragma once
#include<functional>
#include<algorithm>

namespace GEngine
{

	#define Connect(sender, signal, receiver, slot) (sender)->signal.RegisterSlot(receiver, slot)

	template<typename>class SlotBase;

	template<typename R, typename ... Args>
	class SlotBase<R(Args...)>
	{
	public:
		virtual R CallBackSlot(Args&& ... args) = 0;
		virtual ~SlotBase() = default;

	};


	template<typename Receiver, typename R, typename ... Args>
	class Slot : public SlotBase<R(Args...)>
	{

	public:
		Slot(Receiver* receiver, R(Receiver::* Func)(Args...))
		{
			this->m_Receiver = receiver;
			this->m_Func = Func;
		}

		R CallBackSlot(Args&& ... args)override
		{
			(m_Receiver->*m_Func)(std::forward<Args>(args)...);
		}

	private:
		Receiver* m_Receiver{};
		R(Receiver::* m_Func)(Args...);
	};


	template<typename> class Signal;
	template<typename R, typename ... Args>
	class Signal<R(Args...)>
	{

	public:
		template<typename Receiver>
		void RegisterSlot(Receiver* receiver, R(Receiver::* func)(Args...))
		{
			m_CallBackList.push_back(new Slot<Receiver, R, Args...>(receiver, func));
		}

		R operator()(Args&& ... args)
		{
			for (auto p : m_CallBackList)
			{
				p->CallBackSlot(std::forward<Args>(args)...);
			}
		}

		R Fire(Args&& ... args)
		{
			this->operator()(std::forward<Args>(args)...);
		}

	private:
		std::vector<SlotBase<R(Args...)>*> m_CallBackList;

	};




}