
// CODESTYLE: v2.0

// Vector.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: 2D and 3D vector classes

/**
 * \file Vector.h
 * \brief A Good Ole Game Programmer Math Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>

namespace ENGINE
{
	/**
	 * \class Vector
	 * \brief A template class that implements basic multi-dimensional vector operations
	 * \ingroup MathGroup
	 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
	 */

	template <const int elementCount, typename T>
	class Vector
	{
	public:
	
		/**
		 * Default class constructor
		 * If you wish, you can define a special flag to get a small boost in performance
		 * before including the Vector.h file
		 * \code
#define DISABLE_CONSTRUCTOR_INITIALIZATION
#include "Vector.h"
		 * \endcode
		 * This will make the constructor do nothing, and the vector's elements will NOT be initialized.
		 * Use this with caution.
		 */
		Vector()
		{
#if !defined(DISABLE_CONSTRUCTOR_INITIALIZATION)
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] = static_cast<T>(0.0f);
			}
#endif
		};
		
		/**********************************************************************/
		
		/**
		 * Implicitly converts the vector to a pointer of type T
		 * \return a pointer to type T
		 * \note You should use this with caution, as accessing the vector data via a pointer can be dangerous
		 */
		operator T* ()
		{
			return data_;
		};
		
		/**********************************************************************/
		
		/**
		 * Implicitly converts the vector to a const pointer of type T
		 * \return a const pointer to type T
		 */
		operator const T* () const
		{
			return data_;
		};
		
		/**********************************************************************/
		
		/**
		 * Accessor function to access the vector's elements by index
		 * @param element is the element index to access
		 * \return a reference to the specified element of the vector
		 */
		T& operator[](const int element)
		{
			return data_[element];
		};
		
		/**********************************************************************/
		
		/**
		 * Accessor function to access the vector's elements by index
		 * @param element is the element index to access
		 * \return a read-only reference to the specified element of the vector
		 */
		const T& operator[](const int element)
		{
			return data_[element];
		};
		
		/**********************************************************************/
		
		/**
		 * Adds a vector to this vector
		 * @param rhs is the vector to add to this vector
		 * \return the result of adding the elements of the vector \a rhs to the elements of this vector
		 */
		Vector<elementCount, T>& operator+=(const Vector<elementCount, T>& rhs)
		{
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] += rhs[index];
			}
			
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Subtracts a vector from this vector
		 * @param rhs is the vector to subtract from this vector
		 * \return the result of subtracting the elements of the vector \a rhs from the elements of this vector
		 */
		Vector<elementCount, T>& operator-=(const Vector<elementCount, T>& rhs)
		{
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] -= rhs[index];
			}
			
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Multiplies this vector by a scalar value
		 * @param scalar is the value to multiply by
		 * \return this vector after it has been multiplied by the scalar value
		 */
		Vector<elementCount, T>& operator*=(T scalar)
		{
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] *= scalar;
			}
			
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Divides this vector by a scalar value
		 * @param scalar is the value to divide by
		 * \return this vector after it has been divided by the scalar value
		 */
		Vector<elementCount, T>& operator/=(T scalar)
		{
			T calcScalar = static_cast<T>(1.0f / scalar);
			
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] *= calcScalar;
			}
			
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Simple pass-through of this vector for using as a right-hand-side value in a calculation
		 * \return this vector
		 */
		Vector<elementCount, T> operator+() const
		{
			return *this;
		};
		
		/**********************************************************************/
		
		/**
		 * Negation of this vector
		 * \return a new vector that is the inverse of this vector
		 */
		Vector<elementCount, T> operator-() const
		{
			Vector<elementCount, T> negated = *this;
			for (int index = 0; index < elementCount; index++)
			{
				data_[index] = -data_[index];
			}
			return negated;
		};
		
		/**********************************************************************/
		
		/**
		 * Adds the vector \a rhs to this vector
		 * @param rhs is the vector to add
		 * \return a new vector that is the result of the addition
		 */
		Vector<elementCount, T> operator+(const Vector<elementCount, T>& rhs) const
		{
			return Vector<elementCount, T>(*this) += rhs;
		};
		
		/**********************************************************************/
		
		/**
		 * Subtracts the vector \a rhs from this vector
		 * @param rhs is the vector to subtract
		 * \return a new vector that is the result of the subtraction
		 */
		Vector<elementCount, T> operator-(const Vector<elementCount, T>& rhs) const
		{
			return Vector<elementCount, T>(*this) -= rhs;
		};
		
		/**********************************************************************/
		
		/**
		 * Multiplies this vector by a scalar value
		 * @param scalar is the value to multiply by
		 * Returns a new vector that is the result of the multiplication
		 */
		Vector<elementCount, T> operator*(T scalar) const
		{
			return Vector<elementCount, T>(*this) *= scalar;
		};
		
		/**********************************************************************/
		
		/**
		 * Divides this vector by a scalar value
		 * @param scalar is the value to divide by
		 * Returns a new vector that is the result of the division
		 */
		Vector<elementCount, T> operator/(T scalar) const
		{
			return Vector<elementCount, T>(*this) /= scalar;
		};
		
		/**********************************************************************/
		
		/**
		 * Compares the equality of this vector against the vector \a rhs
		 * @param rhs is the vector to compare against
		 * \return true if the vectors are equal, false if they are not
		 */
		bool operator==(const Vector<elementCount, T>& rhs) const
		{
			for (int index = 0; index < elementCount; index++)
			{
				if (data_[index] != rhs[index])
				{
					return false;
				}
			}
			return true;
		};
		
		/**********************************************************************/
		
		/**
		 * Compares the inequality of this vector against the vector \a rhs
		 * @param rhs is the vector to compare against
		 * \return true if the vectors are not equal, false if they are
		 */
		bool operator!=(const Vector<elementCount, T>& rhs) const
		{
			for (int index = 0; index < elementCount; index++)
			{
				if (data_[index] != rhs[index])
				{
					return true;
				}
			}
			return false;
		};
		
		/**********************************************************************/
		
		/**
		 * Normalizes this vector so that the magnitude has a value of one
		 */
		void Normalize() 
		{
			*this *= static_cast<T>(1.0f / GetMagnitude());
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the magnitude (the length) of this vector\n
		 * makes a call to the expensive sqrt. do not use this function in a realtime loop.\n
		 * Use the Vector2D::GetMagnitudeSquared() function if you can.
		 * \return the magnitude (the length) of this vector
		 */
		T GetMagnitude() const
		{
			T magnitude = 0;
			
			for (int index = 0; index < elementCount; index++)
			{
				magnitude += (data_[index] * data_[index]);
			}
			
			return static_cast<T>(sqrt(magnitude));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the squared magnitude of this vector
		 * \return the squared magnitude of this vector
		 */
		T GetMagnitudeSquared() const
		{
			T magnitude = 0;
			for (int index = 0; index < elementCount; index++)
			{
				magnitude += (data_[index] * data_[index]);
			}
			
			return static_cast<T>(magnitude);
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the dot product of the vectors \a rhs and this vector
		 * @param rhs is the second vector needed to calculate the dot product
		 * \return the dot product of the vectors \a rhs and this vector
		 */
		T GetDotProduct(const Vector<elementCount, T>& rhs) const
		{
			T dotProduct = 0;
			
			for (int index = 0; index < elementCount; index++)
			{
				dotProduct += (data_[index] * rhs[index]);
			}
			
			return static_cast<T>(dotProduct);
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the smallest angle between the vectors \a rhs and this vector
		 * @param rhs is the vector to calculate against
		 * \return the smallest angle between the vectors \a rhs and this vector
		 */
		T GetAngle(const Vector<elementCount, T>& rhs) const
		{
			return static_cast<T>(acos(GetDotProduct(rhs) / (GetMagnitude() * rhs.GetMagnitude())));
		};
		
	protected:
		
		/**
		 * \var data_
		 * \brief an array of type T to hold the elements of the vector
		 */
		T data_[elementCount];
	};
	
	/**************************************************************************/
	
	/**
	 * \class Vector2D
	 * \brief A template class that implements basic 2D vector operations
	 * \ingroup MathGroup
	 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
	 */
	template <typename T>
	class Vector2D : public Vector<2, T>
	{
	public:
	
		/**
		 * Default class constructor
		 * If you wish, you can define a special flag to get a small boost in performance
		 * before including the Vector.h file
		 * \code
#define DISABLE_CONSTRUCTOR_INITIALIZATION
#include "Vector.h"
		 * \endcode
		 * This will make the constructor do nothing, and the vector's elements will NOT be initialized.
		 * Use this with caution.
		 */
		Vector2D()
		{
#if !defined(DISABLE_CONSTRUCTOR_INITIALIZATION)
			this->data_[0] = static_cast<T>(0.0f);
			this->data_[1] = static_cast<T>(0.0f);
#endif
		};
		
		/**********************************************************************/
		
		/**
		 * Alternate class constructor - sets the elements of the vector
		 */
		Vector2D(T x, T y)
		{
			this->data_[0] = x;
			this->data_[1] = y;
		};
		
		/**********************************************************************/
		
		/**
		 * Alternate class constructor
		 */
		Vector2D(const T* rhs) : 
			Vector<2, T>(rhs)
		{
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the dot product of the vectors \a rhs and the vector that is perpendicular to this vector.
		 * @param rhs is the second vector needed to calculate the perpendicular dot product
		 * \return the dot product of the vectors \a rhs and the vector that is perpendicular to this vector.
		 */
		T GetPerpendicularDotProduct(const Vector2D<T>& rhs) const
		{
			return static_cast<T>(GetPerpendicular().GetDotProduct(rhs));
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the vector that is perpendicular to this vector.
		 * A perpendicular vector is a vector that forms a 90 degree angle with another vector.
		 * \return a new vector that is perpendicular to this vector
		 */
		Vector2D<T> GetPerpendicular()
		{
			return Vector2D<T>(-this->data_[1], this->data_[0]);
		};
		
	};
	
	/**************************************************************************/
	
	/**
	 * \class Vector3D
	 * \brief A template class that implements basic 3D vector operations
	 * \ingroup MathGroup
	 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
	 */
	template <typename T>
	class Vector3D : public Vector<3, T>
	{
	public:
	
		/**
		 * Default class constructor
		 * If you wish, you can define a special flag to get a small boost in performance
		 * before including the Vector.h file
		 * \code
#define DISABLE_CONSTRUCTOR_INITIALIZATION
#include "Vector.h"
		 * \endcode
		 * This will make the constructor do nothing, and the vector's elements will NOT be initialized.
		 * Use this with caution.
		 */
		Vector3D()
		{
#if !defined(DISABLE_CONSTRUCTOR_INITIALIZATION)
			this->data_[0] = static_cast<T>(0.0f);
			this->data_[1] = static_cast<T>(0.0f);
			this->data_[2] = static_cast<T>(0.0f);
#endif
		};
		
		/**********************************************************************/
		
		/**
		 * Alternate class constructor - sets the elements of the vector
		 */
		Vector3D(T x, T y, T z)
		{
			this->data_[0] = x;
			this->data_[1] = y;
			this->data_[2] = z;
		};
		
		/**********************************************************************/
		
		/**
		 * Alternate class constructor
		 */
		Vector3D(const T* rhs) : 
			Vector<3, T>(rhs)
		{
			
		};
		
		/**********************************************************************/
		
		/**
		 * Gets the cross-product of two vectors
		 * @param rhs is the vector to calculate against
		 * \return the cross-product of this vector and the vector \a rhs
		 */
		Vector3D<T> GetCrossProduct(const Vector3D<T>& rhs) const
		{
			return Vector3D<T>(
				this->data_[1] * rhs[2] - this->data_[2] * rhs[1],
				this->data_[2] * rhs[0] - this->data_[0] * rhs[2],
				this->data_[0] * rhs[1] - this->data_[1] * rhs[0]);
		};
	};
	
	/**************************************************************************/
	
	//! A 2D vector of element type float
	typedef Vector2D<float> 	FloatVector2D;
	
	//! A 2D vector of element type double
	typedef Vector2D<double> 	DoubleVector2D;
	
	//! A 2D vector of element type integer
	typedef Vector2D<int> 		IntegerVector2D;
	
	//! A 3D vector of element type float
	typedef Vector3D<float>		FloatVector3D;
	
	//! A 3D vector of element type double
	typedef Vector3D<double>	DoubleVector3D;
	
	//! A 3D vector of element type integer
	typedef Vector3D<int>		IntegerVector3D;




#if 0
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
#endif

} // end namespace
#endif


