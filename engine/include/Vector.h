
// CODESTYLE: v2.0

// Vector.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: 2D and 3D vector classes

/**
 * \file Vector.h
 * \brief A Good Ole Game Programmer Math Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>

namespace ENGINE
{
	/**
	 * \class Vector2D
	 * \brief A template class that implements basic 2D vector operations
	 * \ingroup MathGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */

	template <typename T> 
	class Vector2D
	{
	public:
	
		Vector2D() : 
			x_(0.0f),
			y_(0.0f)
		{
		};
		
		/**********************************************************************/
		
		Vector2D(T x, T y) :
			x_(x),
			y_(y)
		{
		};
		
		/**********************************************************************/
		
		Vector2D(const Vector2D& rhs)
		{
			x_ = rhs[0];
			y_ = rhs[1];
		};
		
		/**********************************************************************/
		
		~Vector2D()
		{
			Reset();
		};
		
		/**********************************************************************/
		
		/**
		 * Normalizes this vector so that the magnitude has a value of one
		 */
		void Normalize()
		{
			T magnitude = GetMagnitude();
			if (0 != magnitude)
			{
				x_ /= magnitude;
				y_ /= magnitude;
			}
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the magnitude (the length) of this vector\n
		 * makes a call to the expensive sqrt. do not use this function in a realtime loop.\n
		 * Use the Vector2D::GetMagnitudeSquared() function if you can.
		 * \return the magnitude (the length) of this vector
		 */
		T GetMagnitude()
		{
			return static_cast<T>(sqrt((x_ * x_) + (y_ * y_)));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the squared magnitude of this vector
		 * \return the squared magnitude of this vector
		 */
		T GetMagnitudeSquared()
		{
			return static_cast<T>((x_ * x_) + (y_ * y_));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the dot product of the vectors \a rhs and this vector
		 * @param rhs is the second vector needed to calculate the dot product
		 * \return the dot product of the vectors \a rhs and this vector
		 */
		T GetDotProduct(const Vector2D& rhs)
		{
			return static_cast<T>((x_ * rhs[0]) + (y_ * rhs[1]));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the smallest angle between the vectors \a rhs and this vector
		 * @param rhs is the vector to calculate against
		 * \return the smallest angle between the vectors \a rhs and this vector
		 */
		T GetAngle(const Vector2D& rhs)
		{
			return static_cast<T>(acos(GetDotProduct(rhs) / (GetMagnitude() * rhs.GetMagnitude())));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the dot product of the vectors \a rhs and the vector that is perpendicular to this vector.
		 * @param rhs is the second vector needed to calculate the perpendicular dot product
		 * \return the dot product of the vectors \a rhs and the vector that is perpendicular to this vector.
		 */
		T GetPerpendicularDotProduct(const Vector2D& rhs)
		{
			return static_cast<T>(GetPerpendicular().GetDotProduct(rhs));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the vector that is perpendicular to this vector.
		 * A perpendicular vector is a vector that forms a 90 degree angle with another vector.
		 * \return a new vector that is perpendicular to this vector
		 */
		Vector2D GetPerpendicular()
		{
			return Vector2D(-y_, x_);
		};
		
		/**********************************************************************/
		
		/**
		 * Reset this vector to the ZERO vector
		 */
		void Reset()
		{
			x_ = 0.0f;
			y_ = 0.0f;
		};
		
		/**********************************************************************/
		
		/**
		 * Sets this vector to the same vector \a rhs
		 * @param rhs is the vector whose elements are to be assigned to this vector's elements
		 */
		void Set(const Vector2D& rhs)
		{
			x_ = rhs[0];
			y_ = rhs[1];
		};
		
		/**********************************************************************/
		
		/**
		 * accessor function to access the vector's elements by index 0 and 1 for X and Y
		 * @param element should be 0 for the X and 1 for the Y
		 * \return the value of the element requested
		 */
		T& operator[](const int element)
		{
			return elements_[element];
		}
		
		/**********************************************************************/
		
		/**
		 * Adds vector \a rhs to this vector to get a new vector
		 * @param rhs the vector to add to this vector
		 * \return a new vector such as the result of adding the vector \a rhs to this vector
		 */
		Vector2D operator+(const Vector2D& rhs)
		{
			return Vector2D(x_ + rhs[0], y_ + rhs[1]);
		};
		
		/**********************************************************************/
		
		/**
		 * Subtracts vector \a rhs from this vector to get a new vector
		 * @param rhs the vector to subtract from this vector
		 * \return a new vector such as the result of subtracting the vector \a rhs from this vector
		 */
		Vector2D operator-(const Vector2D& rhs)
		{
			return Vector2D(x_ - rhs[0], y_ - rhs[1]);
		};
		
		/**********************************************************************/
		
		/**
		 * Multiplies this vector by the \a scalar value to get a new vector
		 * @param scalar is the value by which to multiply each element of this vector
		 * \return a new vector such as the result of multiplying the scalar value by each element of this vector
		 */
		Vector2D operator*(T scalar)
		{
			return Vector2D(x_ * scalar, y_ * scalar);
		};
		
		/**********************************************************************/
		
		/**
		 * Divides this vector by the \a scalar value to get a new vector
		 * @param scalar is the value by which to divide each element of this vector
		 * \return a new vector such as the result of dividing the scalar value by each element of this vector
		 */
		Vector2D operator/(T scalar)
		{
			return Vector2D(x_ / scalar, y_ / scalar);
		};
		
		/**********************************************************************/
		
		/**
		 * Negation of this vector
		 * \return a new vector that is the inverse of this vector
		 */
		Vector2D operator-()
		{
			return Vector2D(-x_, -y_);
		};
		
		/**********************************************************************/
		
		/**
		 * Adds a vector to this vector
		 * @param rhs is the vector to add to this vector
		 * \return the result of adding the elements of the vector \a rhs to the elements of this vector
		 */
		const Vector2D& operator+=(const Vector2D& rhs)
		{
			x_ += rhs[0];
			y_ += rhs[1];
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Subtracts a vector from this vector
		 * @param rhs is the vector to subtract from this vector
		 * \return the result of subtracting the elements of the vector \a rhs from the elements of this vector
		 */
		const Vector2D& operator-=(const Vector2D& rhs)
		{
			x_ -= rhs[0];
			y_ -= rhs[1];
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Multiplies this vector by another vector
		 * @param rhs is the vector to multiply by
		 * \return the result of multiplying the elements of this vector by the elements of vector \a rhs
		 */
		const Vector2D& operator*=(const Vector2D& rhs)
		{
			x_ *= rhs[0];
			y_ *= rhs[1];
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Divides this vector by another vector
		 * @param rhs is the vector to divide by
		 * \return the result of dividing the elements of this vector by the elements of vector \a rhs
		 */
		const Vector2D& operator/=(const Vector2D& rhs)
		{
			x_ /= rhs[0];
			y_ /= rhs[1];
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Sets this vector to the same vector \a rhs
		 * @param rhs is the vector whose elements are to be assigned to this vector's elements
		 */
		const Vector2D& operator=(const Vector2D& rhs)
		{
			x_ = rhs[0];
			y_ = rhs[1];
			return *this;
		};
		
		/**********************************************************************/
		
	private:
		union
		{
			struct { T elements_[2]; };
			struct { T x_, y_; };
		};
	}; // end class

	typedef Vector2D<float> FloatVector2D;
	typedef Vector2D<double> DoubleVector2D;
	typedef Vector2D<int> IntegerVector2D;

} // end namespace
#endif


