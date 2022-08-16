#include "gepch.h"
#include "Managers/ShapeManager.h"
#include <Shapes/Box.h>
#include <Shapes/Circle.h>
#include <Shapes/Cone.h>
#include <Shapes/Ellipsoid.h>
#include <Shapes/Hexagon.h>
#include <Shapes/Icosahedron.h>
#include <Shapes/Plane.h>
#include <Shapes/Prism.h>
#include <Shapes/Pyramid.h>
#include <Shapes/Ring.h>
#include <Shapes/SmoothSphere.h>
#include <Shapes/Torus.h>
#include <Shapes/Cylinder.h>
#include <Shapes/Sphere.h>
#include <Shapes/Quad.h>

namespace GEngine::Manager
{
	void ShapeManager::Initialize()
	{
		using namespace Shape;

		RegisterShape(Quad);
		RegisterShape(Box);
		RegisterShape(Circle);
		RegisterShape(Cone);
		RegisterShape(Ellipsoid);
		RegisterShape(Hexagon);
		RegisterShape(Icosahedron);
		RegisterShape(Plane);
		RegisterShape(Prism);
		RegisterShape(Pyramid);
		RegisterShape(Ring);
		RegisterShape(SmoothSphere);
		RegisterShape(Torus);
		RegisterShape(Cylinder);
		RegisterShape(Sphere);
		_RegisterShape(SmoothSphere, EnvironmentSphere, 200.f);
	}

	void ShapeManager::Register(const std::string& shape_name, Geometry* new_shape)
	{
		if (auto it = m_Shapes.find(shape_name); it == m_Shapes.end())
		{
			m_Shapes.emplace(shape_name, new_shape);
		}
	}

	void ShapeManager::UnRegister(const std::string& shape_name)
	{
		if (auto it = m_Shapes.find(shape_name); it != m_Shapes.end())
		{
			delete it->second;
			m_Shapes.erase(it->first);
		}
	}

	Geometry* ShapeManager::GetShape(const std::string& shape_name)
	{
		if (auto it = m_Shapes.find(shape_name); it != m_Shapes.end())
			return it->second;

		return nullptr;
	}

	void ShapeManager::FreeShape()
	{
		for (auto& [name, instance] : m_Shapes)
		{
			if (instance)
			{
				delete instance;
				instance = nullptr;
			}
		}

		m_Shapes.clear();
	}

	
}
