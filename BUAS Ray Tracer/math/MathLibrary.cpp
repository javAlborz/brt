#include "MathLibrary.h"

#include <random>

bool mathlibrary::are_numbers_equal_epsilon(float n1, float n2)
{
	return (fabs(n1 - n2) < n1 * FLOAT_EPSILON);
}

vec3 mathlibrary::reflect(const vec3 & normal, const vec3 & indir)
{
	return indir - normal * (2.f * indir.dot(normal)); // dir - normalat * 2.f * dir.dot(normalat)
}

vec3 mathlibrary::refract(const vec3 & normal, const vec3 & indir, const float refrectiveindex)
{
	float cost1 = indir.dot(normal); // c1 = cos(theta1)
	float n1 = 1, n2 = refrectiveindex; // n1 is index of refraction of medium the ray is in before entering the second one
	// TODO: possibly by passing n1 I can truly simulate the effect of a hollow sphere

	vec3 N = normal;
	if (cost1 < 0.f) // if inside
	{
		cost1 *= -1.f;
	}
	else // else outside
	{
		N *= -1.f;
		std::swap(n1, n2);
	}

	float eta = n1 / n2; // sin(theta2)/sin(theta1) = n1/n2
	// cos(x)^2 + sin(x)^2 = 1		so: cos(x) = sqrtf(1 - sin(x)^2)
	float k = 1.f - pow(eta, 2) * (1 - pow(cost1, 2)); // 
	if (k < 0.f)
	{
		return vec3(); // total internal reflection
	}
	else
	{
		return (N * (eta * cost1 - sqrtf(k))) + (indir * eta); // (N * (n1/n2 * cos(theta1) - cos(theta2))) + (indir * n1/n2)
	}
}

float mathlibrary::mat3_determinant(float mat[9])
{
	return (mat[0] * mat[4] * mat[8] + mat[1] * mat[5] * mat[6] + mat[2] * mat[3] * mat[7] -
		mat[0] * mat[5] * mat[7] - mat[1] * mat[3] * mat[8] - mat[2] * mat[4] * mat[6]);
}

float mathlibrary::random_float_gen(float includedlow, float excludedhigh)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(includedlow, excludedhigh);

	return float(dist(gen));
}

float mathlibrary::modulo(const float& x)
{
	return x - std::floor(x);
}

vec3 mathlibrary::random_point_in_unit_sphere()
{
	float u = random_float_gen(0.f, 1.f);
	float x = random_float_gen(-1.f, 1.f);
	float y = random_float_gen(-1.f, 1.f);
	float z = random_float_gen(-1.f, 1.f);

	float mag = sqrt(x * x + y * y + z * z);
	x /= mag; y /= mag; z /= mag;

	float c = pow(u, 1 / 3); // cube root

	return vec3(x, y, z) * c;
}

#pragma region vec2
vec2::vec2()
{
	m_X = 0.f;
	m_Y = 0.f;
}

vec2::vec2(float a_X, float a_Y)
{
	m_X = a_X;
	m_Y = a_Y;
}

vec2& vec2::operator=(const vec2& rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	return *this;
}

vec2 & vec2::operator+=(const vec2 & a_Rhs)
{
	*this = *this + a_Rhs;
	return *this;
}

vec2 & vec2::operator-=(const vec2 &a_Rhs)
{
	*this = *this - a_Rhs;
	return *this;
}

vec2 & vec2::operator*=(float a_Rhs)
{
	*this = *this * a_Rhs;
	return *this;
}

vec2 & vec2::operator/=(float a_Rhs)
{
	*this = *this / a_Rhs;
	return *this;
}

float vec2::operator[](int a_Index) const
{
	assert(a_Index < 2);
	return v[a_Index];
}

float & vec2::operator[](int a_Index)
{
	assert(a_Index < 2);
	return v[a_Index];
}

vec2& vec2::normalize()
{
	*this = *this / this->length();
	return *this;
}

// --- following are non member functions
vec2 operator+(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return vec2(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y);
}

vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs)
{
	return vec2(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y);
}

vec2 operator*(const vec2 &a_Lhs, float a_Rhs)
{
	return vec2(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs);
}

vec2 operator/(const vec2 & a_Lhs, float a_Rhs)
{
	return vec2(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs);
}

bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs)
{
	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y); // might want to create a check that uses an epsilon too
}

bool operator!=(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}
#pragma endregion 
// vec2 ------------------------------------------------------------------------------------------------------------------------------

#pragma region vec3
vec3::vec3()
{
	m_X = 0.f;
	m_Y = 0.f;
	m_Z = 0.f;
}

vec3::vec3(float a_X, float a_Y, float a_Z)
{
	m_X = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
}

vec3 & vec3::operator=(const vec3 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	m_Z = rhs.m_Z;
	return *this;
}

vec3 & vec3::operator+=(const vec3 & a_Rhs)
{
	*this = *this + a_Rhs;
	return *this;
}

vec3 & vec3::operator-=(const vec3 & a_Rhs)
{
	*this = *this - a_Rhs;
	return *this;
}

vec3 & vec3::operator*=(float a_Rhs)
{
	*this = *this * a_Rhs;
	return *this;
}

vec3 & vec3::operator/=(float a_Rhs)
{
	*this = *this / a_Rhs;
	return *this;
}

float vec3::operator[](int a_Index) const
{
	assert(a_Index < 3);
	return v[a_Index];
}

float & vec3::operator[](int a_Index)
{
	assert(a_Index < 3);
	return v[a_Index];
}

vec3& vec3::normalize()
{
	*this = *this / this->length();
	return *this;
}

vec3 vec3::up()
{
	return vec3(0.f, 1.f, 0.f);
}

vec3 vec3::invert()
{
	return vec3(1.f / m_X, 1.f / m_Y, 1.f / m_Z); // positive number divided by zero will return +inf because of IEEE floating point standard
}

// --- following are non member functions
vec3 operator+(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y, a_Lhs.m_Z + a_Rhs.m_Z);
}

vec3 operator-(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y, a_Lhs.m_Z - a_Rhs.m_Z);
}

vec3 operator*(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs, a_Lhs.m_Z * a_Rhs);
}

vec3 operator/(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs, a_Lhs.m_Z / a_Rhs);
}

bool operator==(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z);
}

bool operator!=(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}
#pragma endregion
// vec3 ------------------------------------------------------------------------------------------------------------------------------

#pragma region vec4
vec4::vec4()
{
	m_X = 0.f;
	m_Y = 0.f;
	m_Z = 0.f;
	m_W = 0.f;
}

vec4::vec4(float a_X, float a_Y, float a_Z, float a_W)
{
	m_X = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
	m_W = a_W;
}

vec4::vec4(const vec3& v, float a_W)
{
	m_V = v;
	m_W = a_W;
}
#pragma endregion
// vec4 ------------------------------------------------------------------------------------------------------------------------------

#pragma region mat4
mat4::mat4()
{
	// set to zero matrix
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.f;
	}
}

mat4::mat4(vec3 a_Row0, float a_03, vec3 a_Row1, float a_13, vec3 a_Row2, float a_23, vec3 a_Row3, float a_33)
{
	m_00 = a_Row0.m_X;
	m_01 = a_Row0.m_Y;
	m_02 = a_Row0.m_Z;
	m_03 = a_03;
	m_10 = a_Row1.m_X;
	m_11 = a_Row1.m_Y;
	m_12 = a_Row1.m_Z;
	m_13 = a_13;
	m_20 = a_Row2.m_X;
	m_21 = a_Row2.m_Y;
	m_22 = a_Row2.m_Z;
	m_23 = a_23;
	m_30 = a_Row3.m_X;
	m_31 = a_Row3.m_Y;
	m_32 = a_Row3.m_Z;
	m_33 = a_33;
}

mat4::mat4(float a_00, float a_01, float a_02, float a_03, float a_10, float a_11, float a_12, float a_13, float a_20, float a_21, float a_22, float a_23, float a_30, float a_31, float a_32, float a_33)
{
	m_00 = a_00;
	m_01 = a_01;
	m_02 = a_02;
	m_03 = a_03;
	m_10 = a_10;
	m_11 = a_11;
	m_12 = a_12;
	m_13 = a_13;
	m_20 = a_20;
	m_21 = a_21;
	m_22 = a_22;
	m_23 = a_23;
	m_30 = a_30;
	m_31 = a_31;
	m_32 = a_32;
	m_33 = a_33;
}

mat4 & mat4::operator=(const mat4 & rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = rhs.m[i];
	}
	return *this;
}

mat4 & mat4::operator+=(const mat4 & a_Rhs)
{
	*this = *this + a_Rhs;
	return *this;
}

mat4 & mat4::operator-=(const mat4 & a_Rhs)
{
	*this = *this - a_Rhs;
	return *this;
}

mat4 & mat4::operator*=(const mat4 & a_Rhs)
{
	*this = *this * a_Rhs;
	return *this;
}

float mat4::determinant() const
{
	// reference: https://people.richland.edu/james/lecture/m116/matrices/determinant.html
	// http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/fourD/index.htm
	// https://en.wikipedia.org/wiki/Determinant

	// A, B, C, D = Laplace expansion (cofactor expansion)
	// m_00*A - m_01*B + m_02*C - m_03*D
	float result = 0.f;
	for (int i = 0; i < 4; i++) // for A, B, C and D
	{
		float subm[9];
		int submatrixIndex = 0;
		for (int loopR = 1; loopR < 4; loopR++) // start at 1, won't need the first row now, first row is used later
		{
			for (int loopC = 0; loopC < 4; loopC++)
			{
				if (loopC != i) // skip column
				{
					subm[submatrixIndex] = mm[loopR][loopC];
					submatrixIndex++;
				}
			}
		}

		// determinant 3x3 submatrix
		float val = m[i] * mathlibrary::mat3_determinant(subm);
		result += (i % 2 == 0) ? val : -val; // again, as mentioned above: m_00*A - m_01*B + m_02*C - m_03*D
	}

	return result;

	// literal formula, got this from uclideanspace.com, decided to place in loop to show understanding of formula
// 	return m_03 * m_12 * m_21 * m_30 - m_02 * m_13 * m_21 * m_30 -
// 		m_03 * m_11 * m_22 * m_30 + m_01 * m_13 * m_22 * m_30 +
// 		m_02 * m_11 * m_23 * m_30 - m_01 * m_12 * m_23 * m_30 -
// 		m_03 * m_12 * m_20 * m_31 + m_02 * m_13 * m_20 * m_31 +
// 		m_03 * m_10 * m_22 * m_31 - m_00 * m_13 * m_22 * m_31 -
// 		m_02 * m_10 * m_23 * m_31 + m_00 * m_12 * m_23 * m_31 +
// 		m_03 * m_11 * m_20 * m_32 - m_01 * m_13 * m_20 * m_32 -
// 		m_03 * m_10 * m_21 * m_32 + m_00 * m_13 * m_21 * m_32 +
// 		m_01 * m_10 * m_23 * m_32 - m_00 * m_11 * m_23 * m_32 -
// 		m_02 * m_11 * m_20 * m_33 + m_01 * m_12 * m_20 * m_33 +
// 		m_02 * m_10 * m_21 * m_33 - m_00 * m_12 * m_21 * m_33 -
// 		m_01 * m_10 * m_22 * m_33 + m_00 * m_11 * m_22 * m_33;
}

mat4 mat4::identity()
{
	mat4 identityMat;

	identityMat.mm[0][0] = 1.f;
	identityMat.mm[1][1] = 1.f;
	identityMat.mm[2][2] = 1.f;
	identityMat.mm[3][3] = 1.f;
	return identityMat;
}

mat4 mat4::rotateX(float a_Radians)
{
	mat4 product = mat4::identity();

	float c = static_cast<float>(cos(a_Radians));
	float s = static_cast<float>(sin(a_Radians));

	product.m_11 = c;
	product.m_12 = -s;
	product.m_21 = s;
	product.m_22 = c;

	// Google rotation matrix for reference for all of these
	return product;
}

mat4 mat4::rotateY(float a_Radians)
{
	mat4 product = mat4::identity();

	float c = static_cast<float>(cos(a_Radians));
	float s = static_cast<float>(sin(a_Radians));

	product.m_00 = c;
	product.m_02 = s;
	product.m_20 = -s;
	product.m_22 = c;

	return product;
}

mat4 mat4::rotateZ(float a_Radians)
{
	mat4 product = mat4::identity();

	float c = static_cast<float>(cos(a_Radians));
	float s = static_cast<float>(sin(a_Radians));

	product.m_00 = c;
	product.m_01 = -s;
	product.m_10 = s;
	product.m_11 = c;

	return product;
}

mat4 mat4::translate(const vec3 &a_Translation)
{
	mat4 product = mat4::identity();

	product.m_03 = a_Translation.m_X;
	product.m_13 = a_Translation.m_Y;
	product.m_23 = a_Translation.m_Z;

	// translation matrix: identity + amount to translate
	//	1		0		0		x
	//	0		1		0		y
	//	0		0		1		z
	//	0		0		0		1

	return product;
}

mat4 mat4::lookat(const vec3 & a_Eye, const vec3 & a_Center, const vec3 & a_Up)
{
	// transpose of rotation matrix is inverse of it

	// reference: google lookat matrix
	// https://learnopengl.com/Getting-started/Camera

	// normalizing here is important otherwise values end up being eg 0.98 instead of 1.00
	vec3 forward = (a_Center - a_Eye).normalize();
	vec3 side = forward.cross(a_Up).normalize();
	vec3 up = side.cross(forward).normalize();

	mat4 product = mat4(
		side.m_X, up.m_X, -forward.m_X, 0.f,
		side.m_Y, up.m_Y, -forward.m_Y, 0.f,
		side.m_Z, up.m_Z, -forward.m_Z, 0.f,
		-side.dot(a_Eye), -up.dot(a_Eye), -forward.dot(a_Eye), 1.f); // m_32 is negative in test but positive in my result, I assume that the test is wrong here
	// TODO: ask lecturers about it on Monday, already inquired with fellow students, no answer yet

	return product;
}

mat4 mat4::projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far)
{
	mat4 product;

	float q = 1.f / static_cast<float>(tan(0.5f * a_FovY)); // assuming a_FovY is in radians, multiplying times 0.5f sometimes faster than dividing by 2
	float a = q / a_AspectRatio;
	float b = (a_Near + a_Far) / (a_Near - a_Far); // same as -(far+near)/(far-near)
	float c = (2.f * a_Near * a_Far) / (a_Near - a_Far); // ^

	product.m[0 + 0 * 4] = a;
	product.m[1 + 1 * 4] = q;
	product.m[2 + 2 * 4] = b;
	product.m[3 + 2 * 4] = c;
	product.m[2 + 3 * 4] = -1.f;

	// TODO: task to lecturers about following:
	// projection matrix in unit test is written in transposed form (row major instead of column major). c and -1 are swapped. This makes unit test invalid
	//	a		0		0		0
	//	0		q		0		0
	//	0		0		b		c
	//	0		0		-1		0
	// Google perspective projection matrix for reference

	return product;
}

vec3 mat4::transform_vector(const vec3 & lpos) const
{
	return  ((*this) * vec4(lpos, 1));
}

vec3 mat4::transform_direction(const vec3 & ldir) const
{
	return (*this) * vec4(ldir, 0);
}

vec3 mat4::inverse_transform_vector(const vec3 & wpos) const
{
	mat4 inversed = (*this);
	return inversed.inverse() * vec4(wpos, 1); // vec4*vec3 operator discards position (set up like vec4(x,y,z,0), and not like vec4(x,y,z,1), as a position vector should
}

vec3 mat4::inverse_transform_direction(const vec3 & wdir) const
{
	mat4 inversed = (*this);
	return inversed.inverse() * vec4(wdir, 0);
}

// --- following are non member functions
mat4 operator+(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 product;
	for (int i = 0; i < 16; i++)
	{
		product.m[i] = a_Lhs.m[i] + a_Rhs.m[i];
	}
	return product;
}

mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs)
{
	mat4 product;
	for (int i = 0; i < 16; i++)
	{
		product.m[i] = a_Lhs.m[i] - a_Rhs.m[i];
	}
	return product;
}

mat4 operator*(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 product;
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			product.m[4 * row + column] =
				a_Lhs.mm[row][0] * a_Rhs.mm[0][column] +
				a_Lhs.mm[row][1] * a_Rhs.mm[1][column] +
				a_Lhs.mm[row][2] * a_Rhs.mm[2][column] +
				a_Lhs.mm[row][3] * a_Rhs.mm[3][column];
		}
	}
	return product;
}

vec3 operator*(const mat4 & a_Lhs, const vec3 & a_Rhs)
{
	// this is in here because it's in the mathlibrary, it's not necessary because of my vec4 multiplication. multiplying a 4x4 matrix with a 3x1 vector isn't possible anyway, so this is kind of a trick.
	return a_Lhs * vec4(a_Rhs, 1);
}

vec3 operator*(const mat4 &a_Lhs, const vec4 &a_Rhs)
{
	vec3 product(
		a_Lhs.m[0] * a_Rhs.m_X + a_Lhs.m[4] * a_Rhs.m_Y + a_Lhs.m[8] * a_Rhs.m_Z + a_Lhs.m[12] * a_Rhs.m_W,
		a_Lhs.m[1] * a_Rhs.m_X + a_Lhs.m[5] * a_Rhs.m_Y + a_Lhs.m[9] * a_Rhs.m_Z + a_Lhs.m[13] * a_Rhs.m_W,
		a_Lhs.m[2] * a_Rhs.m_X + a_Lhs.m[6] * a_Rhs.m_Y + a_Lhs.m[10] * a_Rhs.m_Z + a_Lhs.m[14] * a_Rhs.m_W);
	return product;
}
#pragma endregion
// mat4 ------------------------------------------------------------------------------------------------------------------------------