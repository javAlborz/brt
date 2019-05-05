#pragma once
#include <xtgmath.h> // needed for pow and sqrt
#include <cassert>

#define FLOAT_EPSILON 0.000001f

#define M_PI 3.14159265358979323846f // pi as defined in standard library <math.h>
#define DEG_TO_RAD = M_PI / 180.f
#define RAD_TO_DEG = 180.f / M_PI

// naming conventions in math/MathLibrary.h differ from the rest of the project

class vec3; // this way reflect function can use it
class mathlibrary
{
public:
	static bool are_numbers_equal_epsilon(float n1, float n2);
	static vec3 reflect(const vec3& normal, const vec3& indir);
	static vec3 refract(const vec3& normal, const vec3& indir, const float refrectiveindex);
	static float mat3_determinant(float mat[9]);

	// generate random float [a, b)
	static float random_float_gen(float includedlow, float excludedhigh);
	static float modulo(const float& x);

	static vec3 random_point_in_unit_sphere();
};

#pragma region vec2
class vec2
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
		};
		float v[2];
	};
#pragma warning(pop)

public:
	vec2();
	vec2(float a_X, float a_Y);

	vec2& operator=(const vec2& rhs);

	vec2& operator+=(const vec2 &a_Rhs);
	vec2& operator-=(const vec2 &a_Rhs);
	vec2& operator*=(float a_Rhs);
	vec2& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec2 const& a_Rhs) const
	{
		return m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y;
	}
	vec2& normalize();
	inline float length() const
	{
		return static_cast<float>(sqrt(dot(*this))); // sqrt(pow(m_X, 2) + pow(m_Y, 2)) = this.dot(this), but this way I avoid code duplication, not too sure about micro optimizations, see Learning Log for explanation.
	}
};

vec2 operator+(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator*(const vec2 &a_Lhs, float a_Rhs);
vec2 operator/(const vec2 &a_Lhs, float a_Rhs);
bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs);
bool operator!=(const vec2 &a_Lhs, const vec2 &a_Rhs);
#pragma endregion

#pragma region vec3
class vec3 {
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
		float v[3];
	};
#pragma warning(pop)

public:
	vec3();
	vec3(float a_X, float a_Y, float a_Z);

	vec3& operator=(const vec3& rhs);

	vec3& operator+=(const vec3 &a_Rhs);
	vec3& operator-=(const vec3 &a_Rhs);
	vec3& operator*=(float a_Rhs);
	vec3& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec3 const& a_Rhs) const
	{
		return m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y + m_Z * a_Rhs.m_Z;
	}
	inline vec3 cross(vec3 const& a_Rhs) const
	{
		return vec3(
			m_Y * a_Rhs.m_Z - m_Z * a_Rhs.m_Y,
			m_Z  *a_Rhs.m_X - m_X * a_Rhs.m_Z,
			m_X * a_Rhs.m_Y - m_Y * a_Rhs.m_X);
	}
	vec3& normalize();
	inline float length() const
	{
		return static_cast<float>(sqrt(dot(*this))); // sqrt(pow(m_X, 2) + pow(m_Y, 2) + pow(m_Z, 2)) = this.dot(this), but this way I avoid code duplication, not too sure about micro optimizations, see Learning Log for explanation.
	}

	static vec3 up();
	vec3 invert();
};

vec3 operator+(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator-(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator*(const vec3 &a_Lhs, float a_Rhs);
vec3 operator/(const vec3 &a_Lhs, float a_Rhs);
bool operator==(const vec3 &a_Lhs, const vec3 &a_Rhs);
bool operator!=(const vec3 &a_Lhs, const vec3 &a_Rhs);
#pragma endregion

#pragma region vec4
class vec4
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union
	{
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
		float v[4];
		struct
		{
			vec3 m_V;
			float m_W;
		};
	};
#pragma warning(pop)

public:
	vec4();
	vec4(float a_X, float a_Y, float a_Z, float a_W);
	vec4(const vec3& v, float a_W);
};
#pragma endregion

#pragma region mat4
class mat4
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_00; float m_01; float m_02; float m_03;
			float m_10; float m_11; float m_12; float m_13;
			float m_20; float m_21; float m_22; float m_23;
			float m_30; float m_31; float m_32; float m_33;
		};
		float m[16];
		float mm[4][4];
	};
#pragma warning(pop)

public:
	mat4();
	mat4(vec3 a_Row0, float a_03,
		vec3 a_Row1, float a_13,
		vec3 a_Row2, float a_23,
		vec3 a_Row3, float a_33);
	mat4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33);

	mat4& operator=(const mat4& rhs);

	mat4& operator+=(const mat4 &a_Rhs);
	mat4& operator-=(const mat4 &a_Rhs);
	mat4& operator*=(const mat4 &a_Rhs);

	float determinant() const;
	inline mat4& inverse()
	{
		// reference: http://semath.info/src/inverse-cofactor-ex4.html

		float det = determinant();
		assert(det != 0.f); //cannot divide by zero

		float d = 1.f / det;
		mat4 newm;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				newm.mm[row][col] = d * adjugate(*this, col, row);
			}
		}
		// multiply every d by adjugate matrix
		// adjugate matrix Aij=(-1)^(i+j)*Mij
		// Mij is submatrix obtained by removing j-th row and i-th column from A

		*this = newm;
		return *this;
	}

	inline float adjugate(mat4& mat, int column, int row)
	{
		float product;
		float submatrix[9];
		int submatrixIndex = 0;
		for (int loopR = 0; loopR < 4; loopR++)
		{
			if (loopR != row)
			{
				for (int loopC = 0; loopC < 4; loopC++)
				{
					if (loopC != column)
					{
						submatrix[submatrixIndex] = mat.mm[loopC][loopR];
						submatrixIndex++;
					}
				}
			}
		}

		// compiler will optimize
		product =
			submatrix[0 * 3 + 0] * submatrix[1 * 3 + 1] * submatrix[2 * 3 + 2] +
			submatrix[0 * 3 + 1] * submatrix[1 * 3 + 2] * submatrix[2 * 3 + 0] +
			submatrix[0 * 3 + 2] * submatrix[1 * 3 + 0] * submatrix[2 * 3 + 1] -
			submatrix[0 * 3 + 2] * submatrix[1 * 3 + 1] * submatrix[2 * 3 + 0] -
			submatrix[0 * 3 + 1] * submatrix[1 * 3 + 0] * submatrix[2 * 3 + 2] -
			submatrix[0 * 3 + 0] * submatrix[1 * 3 + 2] * submatrix[2 * 3 + 1];
		return product * static_cast<float>(pow(-1, column + row));
	}

	static mat4 identity();
	static mat4 rotateX(float a_Radians);
	static mat4 rotateY(float a_Radians);
	static mat4 rotateZ(float a_Radians);
	static mat4 translate(const vec3 &a_Translation);

	static mat4 lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up);
	static mat4 projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far);

	vec3 position() const
	{
		return vec3(mm[0][3], mm[1][3], mm[2][3]);
	}

	/// local to world position
	vec3 transform_vector(const vec3& lpos) const;
	/// local to world direction
	vec3 transform_direction(const vec3& ldir) const;

	/// world to local position
	vec3 inverse_transform_vector(const vec3& wpos) const;
	/// world to local direction
	vec3 inverse_transform_direction(const vec3& wdir) const;
};

mat4 operator+(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator*(const mat4 &a_Lhs, const mat4 &a_Rhs);
vec3 operator*(const mat4 &a_Lhs, const vec3 &a_Rhs);
vec3 operator*(const mat4 &a_Lhs, const vec4 &a_Rhs);
#pragma endregion