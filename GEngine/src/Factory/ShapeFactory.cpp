#include "gepch.h"
#include "Factory/ShapeFactory.h"
#include "Shapes/Box.h"



//namespace GEngine::Factory
//{
//	void ShapeFactory::RegisterShape(const std::string& shape_name, Geometry* new_shape)
//	{
//		if (auto it = m_Shapes.find(shape_name); it == m_Shapes.end())
//		{
//			m_Shapes.emplace(shape_name, new_shape);
//		}
//	}
//	Geometry* ShapeFactory::GetShape(const std::string& shape_name)
//	{
//		if (auto it = m_Shapes.find(shape_name); it != m_Shapes.end())
//			return it->second;
//
//		return nullptr;
//	}
//
//	ShapeFactory::~ShapeFactory()
//	{
//		for (auto& [name, instance] : m_Shapes)
//		{
//			if (instance)
//			{
//				delete instance;
//				instance = nullptr;
//			}
//		}
//	}
//}