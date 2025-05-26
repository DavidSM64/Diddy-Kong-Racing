#pragma once
/*
  TriangulatePolygon.hpp

  C++ Template Class for triangulate a 3D polygon

  Copyright (c) 2024 FalconCoding

  Author: Stefan Falk Johnsen
  Email: stefan.johnsen@outlook.com

  This software is released under the MIT License.
 */

#ifndef TRIANGULATE_POLYGON
#define TRIANGULATE_POLYGON

#include <vector>
#include <cmath>

namespace triangulate
{
	struct Point
	{
		Point() : x(0.0f), y(0.0f), z(0.0f) {}

		Point(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}

		float x;
		float y;
		float z;
        
        bool operator==(const Point& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }

        bool operator!=(const Point& other) const {
            return !operator==(other);
        }
	};

	template <typename T = Point>
	struct Triangle
	{
		Triangle(const T& p0, const T& p1, const T& p2) : p0(p0), p1(p1), p2(p2) {}

		Triangle(const Triangle& t) : p0(t.p0), p1(t.p1), p2(t.p2) {}

		T p0, p1, p2;
	};

	static constexpr float epsilon = 1e-6f;

	inline bool equal(const double& a, const double& b)
	{
		return std::fabs(a - b) <= epsilon;
	}

	inline bool equal(const float& a, const float& b)
	{
		return std::fabs(a - b) <= epsilon;
	}

	inline bool zero(const double& f)
	{
		return equal(f, 0);
	}

	inline bool zero(const float& f)
	{
		return equal(f, 0);
	}

	inline double magnitude(const double& x, const double& y, const double& z)
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	inline float magnitude(const float& x, const float& y, const float& z)
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	template <typename T = Point>
	bool equal(const T& p, const T& q)
	{
		if( !equal(p.x, q.x) ) return false;
		if( !equal(p.y, q.y) ) return false;
		if( !equal(p.z, q.z) ) return false;

		return true;
	}

	template <typename T>
	T subtract(const T& p, const T& q)
	{
		return {p.x - q.x , p.y - q.y , p.z - q.z};
	}

	template <typename T = Point>
	float magnitude(const T& u)
	{
		return magnitude(u.x, u.y, u.z);
	}

	template <typename T = Point>
	float distance(const T& p, const T& q)
	{
		T u = subtract(p, q);

		return std::sqrt(magnitude(u));
	}

	template <typename T = Point>
	T normalize(const T& p)
	{
		const auto m = magnitude(p);

		if( m == 0. ) return {};

		return {p.x / m , p.y / m , p.z / m};
	}

	template <typename T = Point>
	double dot(const T& u, const T& v)
	{
		const auto dx = static_cast<double>(u.x) * static_cast<double>(v.x);
		const auto dy = static_cast<double>(u.y) * static_cast<double>(v.y);
		const auto dz = static_cast<double>(u.z) * static_cast<double>(v.z);

		return dx + dy + dz;
	}

	template <typename T = Point>
	T cross(const T& u, const T& v)
	{
		return {u.y * v.z - u.z * v.y , u.z * v.x - u.x * v.z , u.x * v.y - u.y * v.x};
	}

	enum class TurnDirection
	{
		Right  = 1,
		Left   = -1,
		NoTurn = 0
	};

	template <typename T = Point>
	TurnDirection turn(const T& p, const T& u, const T& n, const T& q)
	{
		const T v = subtract(q, p);

		const auto dot = triangulate::dot(cross(v, u), n);

		return dot > 0. ? TurnDirection::Right : (dot < 0 ? TurnDirection::Left : TurnDirection::NoTurn);
	}

	template <typename T = Point>
	float triangleAreaSquared(const T& a, const T& b, const T& c)
	{
		const T u = subtract(b, a);
		const T v = subtract(c, a);

		const auto cross = triangulate::cross(u, v);

		return static_cast<float>(dot(cross, cross)) / 4.0f;
	}

	//-------------------------------------------------------------------------------------------------------

	template <typename T = Point>
	size_t sizePolygon(const std::vector<T>& polygon)
	{
		const auto n = polygon.size();

		if( n < 2 ) return 0;

		return equal(polygon.front(), polygon.back()) ? n - 1 : n;
	}

	template <typename T = Point>
	T normalPolygon(const std::vector<T>& polygon) //Newel's method
	{
		T normal = T();

		const auto n = sizePolygon(polygon);

		if( n < 3 ) return {};

		for( size_t i = 0; i < n; i++ )
		{
			const auto& item = polygon[i];
			const auto& next = polygon[(i + 1) % n];

			normal.x += (next.y - item.y) * (next.z + item.z);
			normal.y += (next.z - item.z) * (next.x + item.x);
			normal.z += (next.x - item.x) * (next.y + item.y);
		}

		return normalize(normal);
	}

	template <typename T = Point>
	bool convex(const std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n < 3 ) return false;

		if( n == 3 ) return true;

		auto polygonTurn = TurnDirection::NoTurn;

		for( size_t index = 0; index < n; index++ )
		{
			const auto& prev = polygon[(index - 1 + n) % n];
			const auto& item = polygon[index % n];
			const auto& next = polygon[(index + 1) % n];

			const T v = subtract(item, prev);

			const auto u = normalize(v);

			const auto itemTurn = turn(prev, u, normal, next);

			if( itemTurn == TurnDirection::NoTurn )
				continue;

			if( polygonTurn == TurnDirection::NoTurn )
				polygonTurn = itemTurn;

			if( polygonTurn != itemTurn )
				return false;
		}

		return true;
	}

	template <typename T = Point>
	bool clockwiseOriented(const std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n < 3 ) return false;

		double orientationSum(0.0);

		for( size_t index = 0; index < n; index++ )
		{
			const auto& prev = polygon[(index - 1 + n) % n];
			const auto& item = polygon[index % n];
			const auto& next = polygon[(index + 1) % n];

			const T edge        = subtract(item, prev);
			const T toNextPoint = subtract(next, item);

			const auto cross = triangulate::cross(edge, toNextPoint);

			orientationSum += dot(cross, normal);
		}

		return orientationSum < 0.0;
	}

	template <typename T = Point>
	void makeClockwiseOrientation(std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n < 3 ) return;

		if( !clockwiseOriented(polygon, normal) )
			polygon = {polygon.rbegin() , polygon.rend()};
	}

	template <typename T = Point>
	bool pointInsideOrEdgeTriangle(const T& a, const T& b, const T& c, const T& p, bool& edge)
	{
		static double zero = std::numeric_limits<double>::epsilon();

		// Initialize edge to false
		edge = false;

		// Vectors from point p to vertices of the triangle
		const T v0 = subtract(c, a);
		const T v1 = subtract(b, a);
		const T v2 = subtract(p, a);

		const auto dot00 = dot(v0, v0);
		const auto dot01 = dot(v0, v1);
		const auto dot02 = dot(v0, v2);
		const auto dot11 = dot(v1, v1);
		const auto dot12 = dot(v1, v2);

		// Check for degenerate triangle
		const auto denom = dot00 * dot11 - dot01 * dot01;

		if( std::abs(denom) < zero )
		{
			// The triangle is degenerate (i.e., has no area)
			return false;
		}

		// Compute barycentric coordinates
		const auto invDenom = 1.0 / denom;

		const auto u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		const auto v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		// Check for edge condition
		if( std::abs(u) < zero || std::abs(v) < zero || std::abs(u + v - 1) < zero )
			edge = true;

		// Check if point is inside the triangle (including edges)
		return (u >= 0.0) && (v >= 0.0) && (u + v < 1.0);
	}

	template <typename T = Point>
	void removeConsecutiveEqualItems(std::vector<T>& polygon)
	{
		if (sizePolygon(polygon) < 2) return;

	        auto new_end = std::unique(polygon.begin(), polygon.end(), [](const T& a, const T& b) {
	            return equal(a, b);
	            });
	
	        polygon.erase(new_end, polygon.end());
	}

        //-------------------------------------------------------------------------------------------------------

	template <typename T = Point>
	bool isEar(const size_t index, const std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n < 3 ) return false;

		if( n == 3 ) return true;

		bool edge(false);

		const auto prevIndex = (index - 1 + n) % n;
		const auto itemIndex = index % n;
		const auto nextIndex = (index + 1) % n;

		const auto& prev = polygon[prevIndex];
		const auto& item = polygon[itemIndex];
		const auto& next = polygon[nextIndex];

		const T v = subtract(item, prev);

		const auto u = normalize(v);

		if( turn(prev, u, normal, next) != TurnDirection::Right )
			return false;

		for( size_t i = 0; i < n; i++ )
		{
			if( i == prevIndex ) continue;
			if( i == itemIndex ) continue;
			if( i == nextIndex ) continue;

			if( pointInsideOrEdgeTriangle(prev, item, next, polygon[i], edge) )
				return false;
		}

		return true;
	}

	template <typename T = Point>
	int getBiggestEar(const std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n == 3 ) return 0;

		if( n == 0 ) return -1;

		int maxIndex(-1);

		double maxArea(std::numeric_limits<double>::min());

		for( size_t index = 0; index < n; index++ )
		{
			if( isEar(index, polygon, normal) )
			{
				const auto& prev = polygon[(index - 1 + n) % n];
				const auto& item = polygon[index % n];
				const auto& next = polygon[(index + 1) % n];

				const auto area = triangleAreaSquared(prev, item, next);

				if( area > maxArea )
				{
					maxIndex = static_cast<int>(index);

					maxArea = area;
				}
			}
		}

		return maxIndex;
	}

	template <typename T = Point>
	int getOverlappingEar(const std::vector<T>& polygon, const T& normal)
	{
		const auto n = sizePolygon(polygon);

		if( n == 3 ) return 0;

		if( n == 0 ) return -1;

		for( size_t index = 0; index < n; index++ )
		{
			const auto& prev = polygon[(index - 1 + n) % n];
			const auto& item = polygon[index % n];
			const auto& next = polygon[(index + 1) % n];

			const T v_prev = subtract(item, prev);

			const auto n_prev = normalize(v_prev);

			if( turn(prev, n_prev, normal, next) != TurnDirection::NoTurn )
				continue;

			const T v_next = subtract(next, item);

			const auto n_next = normalize(v_next);

			if( dot(n_prev, n_next) < 0.0 ) //Opposite direction -> ear
				return static_cast<int>(index);
		}

		return -1;
	}

	//-------------------------------------------------------------------------------------------------------

	template <typename P = Point, typename T = Triangle<P>>
	std::vector<T> fanTriangulation(std::vector<P>& polygon)
	{
		std::vector<T> triangles;

		const auto n = sizePolygon(polygon);

		if( n < 3 ) return {};

		for( size_t index = 1; index < n - 1; ++index )
			triangles.emplace_back(polygon[0], polygon[index], polygon[index + 1]);

		return triangles;
	}

	template <typename P = Point, typename T = Triangle<P>>
	std::vector<T> cutTriangulation(std::vector<P>& polygon, const P& normal)
	{
		std::vector<T> triangles;

		makeClockwiseOrientation(polygon, normal);

		while( !polygon.empty() )
		{
			int index = getBiggestEar(polygon, normal);

			if( index == -1 )
				index = getOverlappingEar(polygon, normal);

			if( index < 0 )
				return {};

			const auto n = sizePolygon(polygon);
			const auto i = static_cast<size_t>(index);

			const auto& prev = polygon[(i - 1 + n) % n];
			const auto& item = polygon[i % n];
			const auto& next = polygon[(i + 1) % n];

			triangles.emplace_back(prev, item, next);

			polygon.erase(polygon.begin() + index);

			if( polygon.size() < 3 ) break;
		}

		return polygon.size() == 2 ? triangles : std::vector<T>();
	}

	template <typename P = Point, typename T = Triangle<P>>
	std::vector<T> triangulate(const std::vector<P>& polygon)
	{
		std::vector<P> copy(polygon);

		triangulate::removeConsecutiveEqualItems(copy);

		if( copy.size() < 3 ) return {};

		if( copy.size() == 3 )
		{
			std::vector<T> triangle;

			triangle.emplace_back(copy[0], copy[1], copy[2]);

			return triangle;
		}

		const auto normal = triangulate::normalPolygon(copy);

		return convex<P>(copy, normal) ? fanTriangulation<P, T>(copy) : cutTriangulation<P, T>(copy, normal);
	}
}

#endif // TRIANGULATE_POLYGON
