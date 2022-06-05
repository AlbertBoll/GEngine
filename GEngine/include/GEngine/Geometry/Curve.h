#pragma once
#include<vector>
#include"Math/Math.h"
#include"Math/Matrix.h"

namespace GEngine
{
	using namespace Math;

	template<typename Func>
	class Curve
	{
	public:
		Func m_Func;
		float m_Tmin{ 0.f };
		float m_Tmax{ 1.f };
		float m_TotalArcLength{ 0.f };
		int m_Divisions = 4;
		int m_ArcLengthDivisions = 256;
		std::vector<float> m_ArcLengths{0.f};


	public:
		Curve(Func&& func, float tmin = 0.f, float tmax = 1.f, int div = 4, int arcDiv = 256): 
			m_Func(func), m_Tmin(tmin), m_Tmax(tmax), m_Divisions(div), m_ArcLengthDivisions(arcDiv){}

		void CalculateArcLengths();

		Vec3f GetPointAt(float t);

		float ConvertUToT(float u);

		Vec3f GetPoint(float u);

		Vec3f GetTangentAt(float t, float delta = 0.00005f);

		Vec3f GetTangent(float u);

		std::vector<Vec3f> GetPoints();

		std::unordered_map<std::string, std::vector<Vec3f>>GetFrames();


	};

	template<typename Func>
	inline void Curve<Func>::CalculateArcLengths()
	{
		std::vector<Vec3f> arcLengthPoints;
		float deltaT = (m_Tmax - m_Tmin) / (m_ArcLengthDivisions - 1);
		for (int index = 0; index < m_ArcLengthDivisions; ++index)
		{
			float t = m_Tmin + index * deltaT;
			auto point = GetPointAt(t);
			arcLengthPoints.push_back(point);
		}

		for (int index = 1; index < m_ArcLengthDivisions; ++index)
		{
			auto arcLength = glm::length(arcLengthPoints[index] - arcLengthPoints[index - 1]);
			m_ArcLengths.push_back(arcLength + m_ArcLengths[index - 1]);

		}

		m_TotalArcLength = m_ArcLengths[m_ArcLengthDivisions - 1];
	}


	template<typename Func>
	inline Vec3f Curve<Func>::GetPointAt(float t)
	{
		return m_Func(t);
	}

	template<typename Func>
	inline float Curve<Func>::ConvertUToT(float u)
	{
		float arcLength = u * m_TotalArcLength;
		int index = std::lower_bound(m_ArcLengths.begin(), m_ArcLengths.end(), arcLength) - m_ArcLengths.begin();
		float arcStart = m_ArcLengths[index - 1];
		float arcEnd = m_ArcLengths[index];
		float segmentLength = arcEnd - arcStart;
		float percent = (arcLength - arcStart) / segmentLength;
		float deltaT = (m_Tmax - m_Tmin) / (m_ArcLengthDivisions - 1);
		float Ta = m_Tmin + (index - 1) * deltaT;
		return Ta + percent * deltaT;

	}

	template<typename Func>
	inline Vec3f Curve<Func>::GetPoint(float u)
	{
		float t = ConvertUToT(u);
		return GetPointAt(t);
	}

	template<typename Func>
	inline Vec3f Curve<Func>::GetTangentAt(float t, float delta)
	{
		
		Vec3f tangent = (GetPointAt(t + delta) - GetPointAt(t))/delta;
		tangent /= glm::length(tangent);
		return tangent;

	}

	template<typename Func>
	inline Vec3f Curve<Func>::GetTangent(float u)
	{
		float t = ConvertUToT(u);
		return GetTangentAt(t);
	}

	template<typename Func>
	inline std::vector<Vec3f> Curve<Func>::GetPoints()
	{
		std::vector<Vec3f> points;
		points.reserve((size_t)m_Divisions);
		float deltaU = 1.f / (m_Divisions - 1);
		for (auto index = 0; index < m_Divisions; ++index)
		{
			float u = index * deltaU;
			points.push_back(GetPoint(u));
		}

		return points;
	}

	template<typename Func>
	inline std::unordered_map<std::string, std::vector<Vec3f>> Curve<Func>::GetFrames()
	{
		std::vector<Vec3f> tangents;
		std::vector<Vec3f> normals;
		std::vector<Vec3f> binormals;

		float deltaU = 1 / (m_Divisions - 1);
		float u;

		for (auto index = 0; index < m_Divisions; ++index)
		{
			u = index * deltaU;
			auto tangent = GetTangent(u);
			tangents.push_back(tangent);
		}

		Vec3f arbitaryVector = { 1.f, 1.f, 1.f };

		auto normal = glm::cross(tangents[0], arbitaryVector);

		normals.push_back(normal);

		for (auto n = 0; n < m_Divisions; ++n)
		{
			normal = normals[n - 1];
			auto crossProduct = glm::cross(tangents[n-1], tangents[n]);

			if (auto magnitude = glm::length(crossProduct); magnitude > 0.0001f)
			{
				crossProduct /= magnitude;
				auto theta = glm::acos(glm::dot(tangents[n - 1], tangents[n]));
				auto rotationMatrix = Matrix::MakeRotationFromArbitaryAxis(crossProduct, theta);
				normal = Mat3(rotationMatrix) * normal;

			}

			normals.push_back(normal);

		}

		Vec3f binormal;
		for (auto index = 0; index < m_Divisions; ++index)
		{
			binormal = glm::cross(tangents[index], normals[index]);
			binormals.push_back(binormal);
		}

		return std::unordered_map<std::string, std::vector<Vec3f>>({ "tangents", tangents }, { "normals", normals }, { "binormals", binormals });

	}



}
