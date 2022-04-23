#pragma once
#include <chrono>
#include <iostream>


namespace GEngine
{
	class Timer
	{
	public:
		Timer() { Reset(); }

		~Timer() { std::cout << ElapsedSeconds() << "s" << std::endl; }

		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float Elapsed() const
		{
			return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Start).count());
		}

		float ElapsedSeconds() const
		{
			return Elapsed() / 1000.f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

#define Timeit(x) std::cout<<#x<<": ";\
Timer timer;

}
