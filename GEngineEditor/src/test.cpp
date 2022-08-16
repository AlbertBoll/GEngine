#include <iostream>
#include <GEngine/Core/BaseApp.h>
#include <GEngine/Events/Signal.h>
#include <GEngine/Events/Event.h>
#include <GEngine/Core/Timer.h>
#include <GEngine/Core/Actor.h>
#include <GEngine/Events/Property.h>
#include <GEngine/Container/Array1D.h>
#include <GEngine/Container/Array2D.h>
#include <GEngine/Container/Array3D.h>
#include <GEngine/Core/Parallel.h>
#include <GEngine/Core/ThreadPool.h>
//#include <reflect/Reflect.hpp>


using namespace GEngine;







struct A
{
	Property<int> m_Int{0};
	
	Property<const char*> m_String{"Cai"};
	
public:
	GetterAndSetter(m_Int);
	GetterAndSetter(m_String);
	


};


struct B
{
	Property<int> m_Int{0};
	Property<const char*> m_String{"Cai"};

public:
	GetterAndSetter(m_Int);
	GetterAndSetter(m_String);

};


struct GoalScoredInfo
{
	std::string playerName;
	int Goal{};
};


class Player
{

private:
	std::string Name;
	int Goal{};

public:
	Player(const std::string& name): Name{name}{}
	Signal<void(const GoalScoredInfo&)> ScoreSignal;

	void Score()
	{
		Goal++;
		if (Goal <= 3)
			ScoreSignal(GoalScoredInfo{ Name, Goal });
	}

};

class Coach
{
public:
	void RespondToScore(const GoalScoredInfo& info)
	{
		std::cout << "Congratulations, " << info.playerName << "!" << " You score a goal." << std::endl;
	}
};

template<typename T>
class PropertyChange
{
public:
	PropertyChange(T x) : m_val{ x } {};
	virtual void SetProperty(T x) = 0;
	Signal<void(PropertyChange*, T)> PropertyChanged;
	T m_val{ };

};

template<typename T>
class PropertyMediator
{

public:

	PropertyMediator(const std::initializer_list<PropertyChange<T>*>& receivers): Receivers{receivers}
	{
		for (auto& p : Receivers)
		{
			Connection(*p, PropertyChanged, *this, PropertyMediator, &PropertyMediator::OnAnyChange);
		}

	}

	void OnPropertyChange(PropertyChange<T>* obj, T value)
	{
		for (auto& p : Receivers)
		{
			if (p != obj) p->SetProperty(value);
		}
	}

	void OnAnyChange(PropertyChange<T>* obj, T value)const
	{
		std::cout << "Hello" << std::endl;
	}

public:

	std::vector<PropertyChange<T>*> Receivers;


};


class Obj1: public PropertyChange<int>
{
	using PropertyChange::PropertyChange;
public:

	//Obj1(int x): PropertyChange(x){};
	void SetProperty(int x) override
	{
		if (m_val == x)return;
		m_val = x;
		std::cout << "Obj1's value change to " << x << std::endl;
		PropertyChanged(this, x);
	}

	//int m_val{};
	//GEngine::Signal<void(int)> valueChanged;
};

class Obj2: public PropertyChange<int>
{
	using PropertyChange::PropertyChange;
public:
	//Obj2(int x) : PropertyChange(x) {};
	void SetProperty(int x)
	{
		if (m_val == x)return;
		m_val = x;
		std::cout << "Obj2's value change to " << x << std::endl;
		PropertyChanged(this, x);
	}

	//int m_val{};
	//GEngine::Signal<void(int)> valueChanged;
};

class Obj3: public PropertyChange<int>
{
	using PropertyChange::PropertyChange;
public:
	//Obj3(int x) : PropertyChange(x) {};
	void SetProperty(int x)
	{
		if (m_val == x)return;
		m_val = x;
		std::cout << "Obj3's value change to " << x << std::endl;
		PropertyChanged(this, x);
	}

	//int m_val{};
	//GEngine::Signal<void(int)> valueChanged;
};


struct Vector3D
{
	float x;
	float y;
	float z;
};


class Player_
{
public:
	Player_() : id(10), name("Luke") {}
	Player_(int id) : id(id), name("Luke") {}
	Player_(int id, const std::string& name) : id(id), name(name) {}
	Player_(Vector3D const& position) : position(position) {}

	void SetId(int id) { Player_::id = id; }
	int GetId() const { return id; }

	void SetName(const std::string& name) { this->name = name; }
	std::string GetName() const { return name; }

	void SetPosition(Vector3D position) { this->position = position; }
	Vector3D GetPosition() const { return position; }

	void Print(const std::string& s) const
	{
		std::cout << s << '\n';
		std::cout << "player id: " << id << ", name: " << name << ", health: " << health << '\n';
		std::cout << "position: " << position.x << ", y: " << position.y << ", z: " << position.z << std::endl;
	}

	std::string SayHello() const { return "hello from " + name + "!"; }

	float health = 100.0f;

private:
	int id = 11;
	std::string name;;
	Vector3D position;
};

//int main(int argc, char* args[])
//{
// 
// 
// GridBasedContainer::DomainParams domain{.Start = 0.0f, .End = 4.0f, .Interval = 0.00000005f};
	//size_t n = 1 << 16;

//GridBasedContainer::Array1D<float> array_1d_X;
//GridBasedContainer::Array1D<float> array_1d_Y;
//
//
////array_1d_X.Reserve(n);
////array_1d_Y.Reserve(n);
//array_1d_X.Resize(domain.N, 0.f);
//array_1d_Y.Resize(domain.N, 0.f);
//
//
//{
//	Timeit(Aggregation)
//		array_1d_X.ParallelForIndexRange([&](size_t Begin, size_t End)
//			{
//				auto temp = 0.f;
//				for (auto index = Begin; index < End; ++index)
//				{
//					temp = array_1d_X[index] = domain.Start + domain.Interval * index;
//					array_1d_Y[index] = std::exp(-temp) * std::cos(2 * Math::Pi * temp);
//				}
//			});
//
//}

//	size_t n = 1 << 16;
//	//GridBasedContainer::Array1D<float> array_1d(n, 0.f);
//
//	//GridBasedContainer::Array2D<float> array_2d1({ n, n }, 1.f);
//
//	//GridBasedContainer::Array2D<float> array_2d1_copy({ n, n }, 1.f);
//
//	GridBasedContainer::Array1D<float> array_1d(n, 1.f);
//
//  	{
//Timeit(FLOAT);
//std::vector<float> Data_(100000000, 1.f);
//
//	}
//
//	{
//	Timeit(POD);
//	std::vector<Pod<float>> Data(100000000);
//	}
//
//	{
//		Timeit(Array);
//		GridBasedContainer::Array1D<float> array_1d_X(100000000, 1.f);
//
//	}
//
//	//{
//		//Timeit(ParallelReduce)
//	auto val = array_1d.ParallelReduce({ 0, n, 64 }, 0.f, [&](size_t Begin, size_t End, float local_res)
//		{
//			for (auto index = Begin; index < End; ++index)
//			{
//				local_res += array_1d[index];
//			}
//
//			return local_res;
//		}, [](float x, float y) {return x + y; });
//
//	std::cout << val << std::endl;
//	//}
//
//
//
//
//
//	/*{
//
//		Timeit(TBB_ParallelRangeFor);
//
//		array_2d1.ParallelForIndexRange([&](size_t xBegin, size_t xEnd, size_t yBegin, size_t yEnd)
//			{
//				for (auto index_y = yBegin; index_y < yEnd; ++index_y)
//				{
//					for (auto index_x = xBegin; index_x < xEnd; ++index_x)
//					{
//						array_2d1(index_x, index_y) = std::sin(index_x) * std::sin(index_y);
//					}
//				}
//
//			});
//
//	}*/
//
//
//
//	/*{
//
//		Timeit(TBB_ParallelRangeForPartition);
//		array_2d1_copy.ParallelForIndexRange({ 0, n, 32 }, { 0, n, 32 }, [&](size_t xBegin, size_t xEnd, size_t yBegin, size_t yEnd)
//			{
//				for (auto index_y = yBegin; index_y < yEnd; ++index_y)
//				{
//					for (auto index_x = xBegin; index_x < xEnd; ++index_x)
//					{
//						array_2d1_copy(index_x, index_y) = std::sin(index_x) * std::sin(index_y);;
//					}
//				}
//
//			});
//
//	}*/
//
//
//
//
//	//{
//	//	Timeit(Parallel);
//	//	array_1d.ParallelForIndexRange([&](size_t i, size_t j)
//	//		{
//	//			for (auto index = i; index < j; ++index)
//	//			{
//	//				array_1d[index] = std::sin(index);
//	//			}
//	//		}
//	//	);
//
//	//}
//
//	//Reflect::Reflect<int>("int");
//
//	//Reflect::Reflect<double>("double")
//	//	.AddConversion<int>();
//
//	//Reflect::Reflect<const char*>("cstring")
//	//	.AddConversion<std::string>();
//
//	//Reflect::Reflect<Player_>("Player")
//	//	.AddConstructor<>()
//	//	.AddConstructor<int>()
//	//	.AddConstructor<int, const std::string&>()
//	//	.AddConstructor<Vector3D const&>()
//	//	.AddDataMember<&Player_::SetId, &Player_::GetId>("id")
//	//	.AddDataMember<&Player_::SetName, &Player_::GetName>("name")
//	//	.AddDataMember(&Player_::health, "health")
//	//	.AddDataMember <&Player_::SetPosition, &Player_::GetPosition>("position")
//	//	.AddMemberFunction(&Player_::Print, "Print")
//	//	.AddMemberFunction(&Player_::SayHello, "SayHello");
//
//	//auto a = Reflect::Resolve("Player")->GetConstructor<int, const std::string&>()->NewInstance(1, "Mario");
//	//Reflect::Resolve("Player")->GetDataMember("position")->Set(a, Vector3D{ 13.4f, 15.0f, 11.1f });
//	//Reflect::Resolve("Player")->GetDataMember("id")->Set(a, 1.7);
//	//Reflect::Resolve("Player")->GetDataMember("name")->Set(a, "Luigi");
//	//Reflect::Resolve("Player")->GetDataMember("health")->Set(a, 20.0f);
//	//Reflect::Resolve("Player")->GetMemberFunction("Print")->Invoke(a, Reflect::Any("player stats:"));
//	//std::cout << *Reflect::Resolve("Player")->GetMemberFunction("SayHello")->Invoke(a).TryCast<std::string>() << std::endl;
//	//for (auto& meth : t.get_methods())
//		//std::cout << "name: " << meth.get_name();
//	//GridBasedContainer::Array1D<size_t> array_1d(100000000, 5);
//	//GridBasedContainer::Array1D<size_t> array_1d_(100000000, 5);
//	//GridBasedContainer::Array2D<double> array_2d({ 10000, 10000 }, 1.);
//	//GridBasedContainer::Array2D<double> array_2d_({ 10000, 10000 }, 1.);
//
//
//	//{
//	//	Timeit(TBB_ParallelRangeFor);
//	//	array_2d.ParallelForIndexRange([&](size_t xBegin, size_t xEnd, size_t yBegin, size_t yEnd)
//	//		{
//	//			for (auto index_y = yBegin; index_y < yEnd; ++index_y)
//	//			{
//	//				for (auto index_x = xBegin; index_x < xEnd; ++index_x)
//	//				{
//	//					array_2d(index_x, index_y) = std::sin((double)index_x) * std::sin((double)index_y);
//	//				}
//	//			}
//	//			
//	//		});
//
//	//}
//
//	//{
//	//	Timeit(TBB_ParallelIndexFor);
//	//	array_2d_.ParallelForEachIndex([&](size_t i, size_t j)
//	//		{
//	//			//for (auto index_y = yBegin; index_y < yEnd; ++index_y)
//	//			{
//	//				//for (auto index_x = xBegin; index_x < xEnd; ++index_x)
//	//				//{
//	//				array_2d_(i, j) = std::sin((double)i) * std::sin((double)j);
//	//				//}
//	//			//}
//	//			}
//	//		});
//
//	//}
//
//
//
//
//	int j = 10;
//	/*{
//		thread_pool pool;
//		Timeit(Pool);
//		pool.parallelize_loop(0, 100000000,
//			[&array_1d](size_t a, size_t b)
//			{
//				for (size_t i = a; i < b; i++)
//					array_1d[i] = i * i;
//			});
//	}
//
//	{
//		Timeit(TBB_ParallelFor);
//		array_1d_.ParallelForIndexRange([&](size_t i, size_t j)
//			{
//				for(auto index = i; index < j; ++index)
//				array_1d_[index] = index * index;
//			});
//
//	}*/
//	//std::cout << squares[10] << std::endl;
//	//GridBasedContainer::Array1D<int> array_1d(10000000, 5);
//
//	//array_1d.ForEach([&](int& i) {i *= i; });
//
//	int i = 0;
//
//
//	/*A a;
//	A b = a;
//	Connection(a, m_Int.m_PropertySignal, b, A, &A::SetProperty);
//	Connection(a, m_String.m_PropertySignal, b, A, &A::SetProperty);
//
//	a.m_Int = 5;
//	a.m_String = "Hello";
//
//	std::cout << b.m_Int << std::endl;
//	std::cout << b.m_String << std::endl;*/
//
//	/*GEngine::BaseApp app;
//
//
//	GEngine::WindowProperties winProp1{ .m_Title = "GEngine Editor App1",
//										.m_WinPos = GEngine::WindowPos::TopLeft,
//										.m_XPaddingToCenterY = 5,
//										.m_YPaddingToCenterX = 20,
//									 };
//
//	GEngine::WindowProperties winProp2{ .m_Title = "GEngine Editor App2",
//										.m_WinPos = GEngine::WindowPos::TopRight,
//										.m_XPaddingToCenterY = 5,
//										.m_YPaddingToCenterX = 20,
//	};
//
//	app.Initialize();
//	auto& engine = app.GetEngine();
//	engine.GetWindowManager()->AddWindows(winProp1, winProp2);
//
//	app.Run();
//
//	std::cout << "Finish" << std::endl;*/
//
//	return 0;
//
//}