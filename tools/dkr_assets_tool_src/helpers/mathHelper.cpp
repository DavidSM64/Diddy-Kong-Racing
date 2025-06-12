#include "mathHelper.h"

#include <cmath>

using namespace DkrAssetsTool;

/***************************************************************************/

Vec2f::Vec2f() : x(0), y(0) {}

Vec2f::Vec2f(float s) : x(s), y(s) {
}

Vec2f::Vec2f(float x, float y) : x(x), y(y){
}

Vec2f::Vec2f(std::vector<float> &floats, size_t offset) : x(floats[offset]), y(floats[offset+1]) {
}

Vec2f::Vec2f(std::vector<double>& doubles, size_t offset) : x(doubles[offset]), y(doubles[offset + 1]) {
}

float Vec2f::operator[](int index) const {
    return values[index];
}

float& Vec2f::operator[](int index) {
    return values[index];
}

bool Vec2f::operator==(const Vec2f& other) const {
    return (x == other.x) && (y == other.y);
}

bool Vec2f::operator!=(const Vec2f& other) const {
    return !operator==(other);
}

Vec2f Vec2f::operator+(const Vec2f& other) {
    return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f& other) {
    return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(const Vec2f& other) {
    return Vec2f(x * other.x, y * other.y);
}

Vec2f Vec2f::operator*(const float other) {
    return Vec2f(x * other, y * other);
}

Vec2f Vec2f::operator/(const Vec2f& other) {
    return Vec2f(x / other.x, y / other.y);
}

Vec2f Vec2f::operator/(const float other) {
    return Vec2f(x / other, y / other);
}

// The namespace is needed here for g++ to resolve the function correctly.
namespace DkrAssetsTool {
    std::ostream& operator<<(std::ostream& os, const Vec2f& vec) {
        os << "{ x: " << vec.x << ", y: " << vec.y << " }";
        return os;
    }
}

Vec2f Vec2f::min(const Vec2f& other) const {
    return Vec2f(
        (x < other.x) ? x : other.x,
        (y < other.y) ? y : other.y
    );
}

Vec2f Vec2f::max(const Vec2f& other) const {
    return Vec2f(
        (x > other.x) ? x : other.x,
        (y > other.y) ? y : other.y
    );
}

void Vec2f::update_min(const Vec2f& other){
    x = (x < other.x) ? x : other.x;
    y = (y < other.y) ? y : other.y;
}

void Vec2f::update_max(const Vec2f& other){
    x = (x > other.x) ? x : other.x;
    y = (y > other.y) ? y : other.y;
}

bool Vec2f::within(const Vec2f& other, float amountU, float amountV) {
    return (std::abs(u - other.u) < amountU) && (std::abs(v - other.v) < amountV);
}

bool Vec2f::is_zero() const {
    return (x == 0.0f) && (y == 0.0f);
}

void Vec2f::copy_to(float* dst) {
    dst[0] = x;
    dst[1] = y;
}

std::vector<float> Vec2f::to_vector() {
    return { x, y };
}

std::vector<double> Vec2f::to_double_vector() {
    return { x, y };
}

/***************************************************************************/

Vec3f::Vec3f() : x(0), y(0), z(0) {}

Vec3f::Vec3f(float s) : x(s), y(s), z(s) {
}

Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {
}

Vec3f::Vec3f(std::vector<float>& floats, size_t offset) : x(floats[offset]), y(floats[offset + 1]), z(floats[offset + 2]) {
}

Vec3f::Vec3f(std::vector<double>& doubles, size_t offset) : x(doubles[offset]), y(doubles[offset + 1]), z(doubles[offset + 2]) {
}

float Vec3f::operator[](int index) const {
    return values[index];
}

float& Vec3f::operator[](int index) {
    return values[index];
}

bool Vec3f::operator==(const Vec3f& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}

bool Vec3f::operator!=(const Vec3f& other) const {
    return !operator==(other);
}

Vec3f Vec3f::operator+(const Vec3f& other) const {
    return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f &Vec3f::operator+=(const Vec3f& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3f Vec3f::operator-(const Vec3f& other) const {
    return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::operator*(const Vec3f& other) const {
    return Vec3f(x * other.x, y * other.y, z * other.z);
}

Vec3f Vec3f::operator*(const float other) const {
    return Vec3f(x * other, y * other, z * other);
}

Vec3f Vec3f::operator/(const Vec3f& other) const {
    return Vec3f(x / other.x, y / other.y, z / other.z);
}

Vec3f Vec3f::operator/(const float other) const {
    return Vec3f(x / other, y / other, z / other);
}

// The namespace is needed here for g++ to resolve the function correctly.
namespace DkrAssetsTool {
    std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
        os << "{ x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << " }";
        return os;
    }
}

Vec3f Vec3f::min(const Vec3f& other) const {
    return Vec3f(
        (x < other.x) ? x : other.x,
        (y < other.y) ? y : other.y,
        (z < other.z) ? z : other.z
    );
}

Vec3f Vec3f::max(const Vec3f& other) const {
    return Vec3f(
        (x > other.x) ? x : other.x,
        (y > other.y) ? y : other.y,
        (z > other.z) ? z : other.z
    );
}

void Vec3f::update_min(const Vec3f& other) {
    x = (x < other.x) ? x : other.x;
    y = (y < other.y) ? y : other.y;
    z = (z < other.z) ? z : other.z;
}

void Vec3f::update_max(const Vec3f& other) {
    x = (x > other.x) ? x : other.x;
    y = (y > other.y) ? y : other.y;
    z = (z > other.z) ? z : other.z;
}

bool Vec3f::is_zero() const {
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
}

void Vec3f::copy_to(float* dst) {
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

std::vector<float> Vec3f::to_vector() {
    return { x, y, z };
}

std::vector<double> Vec3f::to_double_vector() {
    return { x, y, z };
}

/***************************************************************************/

Vec4f::Vec4f() : x(0), y(0), z(0), w(0) {}

Vec4f::Vec4f(float s) : x(s), y(s), z(s), w(s) {}

Vec4f::Vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
}

Vec4f::Vec4f(uint8_t red, uint8_t green, uint8_t blue) {
    x = static_cast<float>(red) / 255.0f;
    y = static_cast<float>(green) / 255.0f;
    z = static_cast<float>(blue) / 255.0f;
    w = 1.0f; // Alpha is assumed to be full.
}

Vec4f::Vec4f(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    x = static_cast<float>(red) / 255.0f;
    y = static_cast<float>(green) / 255.0f;
    z = static_cast<float>(blue) / 255.0f;
    w = static_cast<float>(alpha) / 255.0f;
}

Vec4f::Vec4f(uint32_t rgba) {
    // Extract rgba into individual channels
    uint8_t red = (rgba >> 24);
    uint8_t green = (rgba >> 16);
    uint8_t blue = (rgba >> 8);
    uint8_t alpha = (rgba);
    x = static_cast<float>(red) / 255.0f;
    y = static_cast<float>(green) / 255.0f;
    z = static_cast<float>(blue) / 255.0f;
    w = static_cast<float>(alpha) / 255.0f;
}

Vec4f::Vec4f(std::vector<float>& floats, size_t offset) : x(floats[offset]), y(floats[offset + 1]), 
    z(floats[offset + 2]), w(floats[offset + 3]) {}

Vec4f::Vec4f(std::vector<double>& doubles, size_t offset) : x(doubles[offset]), y(doubles[offset + 1]), 
    z(doubles[offset + 2]), w(doubles[offset + 3]) {}

Vec4f::Vec4f(std::vector<uint8_t>& bytes, size_t offset) : 
    Vec4f(bytes[offset], bytes[offset+1], bytes[offset+2], bytes[offset+3]) {
}

float Vec4f::operator[](int index) const {
    return values[index];
}

float& Vec4f::operator[](int index) {
    return values[index];
}

bool Vec4f::operator==(const Vec4f& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
}

bool Vec4f::operator!=(const Vec4f& other) const {
    return !operator==(other);
}

Vec4f Vec4f::operator+(const Vec4f& other) {
    return Vec4f(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4f Vec4f::operator-(const Vec4f& other) {
    return Vec4f(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4f Vec4f::operator*(const Vec4f& other) {
    return Vec4f(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vec4f Vec4f::operator*(const float other) {
    return Vec4f(x * other, y * other, z * other, w * other);
}

Vec4f Vec4f::operator/(const Vec4f& other) {
    return Vec4f(x / other.x, y / other.y, z / other.z, w / other.w);
}

Vec4f Vec4f::operator/(const float other) {
    return Vec4f(x / other, y / other, z / other, w / other);
}

// The namespace is needed here for g++ to resolve the function correctly.
namespace DkrAssetsTool {
    std::ostream& operator<<(std::ostream& os, const Vec4f& vec) {
        os << "{ x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w << " }";
        return os;
    }
}

Vec4f Vec4f::min(const Vec4f& other) const {
    return Vec4f(
        (x < other.x) ? x : other.x,
        (y < other.y) ? y : other.y,
        (z < other.z) ? z : other.z,
        (w < other.w) ? w : other.w
    );
}

Vec4f Vec4f::max(const Vec4f& other) const {
    return Vec4f(
        (x > other.x) ? x : other.x,
        (y > other.y) ? y : other.y,
        (z > other.z) ? z : other.z,
        (w > other.w) ? w : other.w
    );
}

void Vec4f::update_min(const Vec4f& other) {
    x = (x < other.x) ? x : other.x;
    y = (y < other.y) ? y : other.y;
    z = (z < other.z) ? z : other.z;
    w = (w < other.w) ? w : other.w;
}

void Vec4f::update_max(const Vec4f& other) {
    x = (x > other.x) ? x : other.x;
    y = (y > other.y) ? y : other.y;
    z = (z > other.z) ? z : other.z;
    w = (w > other.w) ? w : other.w;
}

bool Vec4f::is_zero() const {
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f);
}

void Vec4f::copy_to(float* dst) {
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
    dst[3] = w;
}

uint8_t Vec4f::get_red_as_byte() const {
    return static_cast<uint8_t>(r * 255.0f);
}

uint8_t Vec4f::get_green_as_byte() const {
    return static_cast<uint8_t>(g * 255.0f);
}

uint8_t Vec4f::get_blue_as_byte() const {
    return static_cast<uint8_t>(b * 255.0f);
}

uint8_t Vec4f::get_alpha_as_byte() const {
    return static_cast<uint8_t>(a * 255.0f);
}

uint32_t Vec4f::get_as_rgba() const {
    return (get_red_as_byte() << 24)   |
           (get_green_as_byte() << 16) | 
           (get_blue_as_byte() << 8)   | 
           (get_alpha_as_byte());
}

std::vector<float> Vec4f::to_vector() {
    return { x, y, z, w };
}

std::vector<double> Vec4f::to_double_vector() {
    return { x, y, z, w };
}

/***************************************************************************/

Mat4x4f::Mat4x4f() {
    // Should set this to be an identity matrix
    for(size_t i = 0; i < 16; i++) {
        values[i] = ((i % 5) == 0) ? 1.0f : 0.0f;
    }
}

Mat4x4f::Mat4x4f(const std::vector<float> &src, size_t offset) {
    for(size_t i = 0; i < 16; i++) {
        values[i] = src[offset + i];
    }
}

Mat4x4f::Mat4x4f(const std::vector<double> &src, size_t offset)  {
    for(size_t i = 0; i < 16; i++) {
        values[i] = static_cast<float>(src[offset + i]);
    }
}

// Constructor using Euler angles (rotEuler in radians, XYZ order)
Mat4x4f::Mat4x4f(const Vec3f &translation, const Vec3f &rotEuler, const Vec3f &scale) {
    // Extract angles
    float cx = cosf(rotEuler.x), sx = sinf(rotEuler.x);
    float cy = cosf(rotEuler.y), sy = sinf(rotEuler.y);
    float cz = cosf(rotEuler.z), sz = sinf(rotEuler.z);

    // Rotation matrix from Euler angles (XYZ order)
    float m00 = cy * cz;
    float m01 = -cy * sz;
    float m02 = sy;

    float m10 = sx * sy * cz + cx * sz;
    float m11 = -sx * sy * sz + cx * cz;
    float m12 = -sx * cy;

    float m20 = -cx * sy * cz + sx * sz;
    float m21 = cx * sy * sz + sx * cz;
    float m22 = cx * cy;

    // Apply scale
    m00 *= scale.x; m01 *= scale.x; m02 *= scale.x;
    m10 *= scale.y; m11 *= scale.y; m12 *= scale.y;
    m20 *= scale.z; m21 *= scale.z; m22 *= scale.z;

    // Set matrix rows
    rows[0] = { m00, m01, m02, 0.0f };
    rows[1] = { m10, m11, m12, 0.0f };
    rows[2] = { m20, m21, m22, 0.0f };
    rows[3] = { translation.x, translation.y, translation.z, 1.0f };
}

// Constructor using quaternion (x, y, z, w format)
Mat4x4f::Mat4x4f(const Vec3f &translation, const Vec4f &quat, const Vec3f &scale) {
    float x = quat.x, y = quat.y, z = quat.z, w = quat.w;

    float xx = x * x, yy = y * y, zz = z * z;
    float xy = x * y, xz = x * z, yz = y * z;
    float wx = w * x, wy = w * y, wz = w * z;

    // Rotation matrix from quaternion
    float m00 = 1.0f - 2.0f * (yy + zz);
    float m01 = 2.0f * (xy - wz);
    float m02 = 2.0f * (xz + wy);

    float m10 = 2.0f * (xy + wz);
    float m11 = 1.0f - 2.0f * (xx + zz);
    float m12 = 2.0f * (yz - wx);

    float m20 = 2.0f * (xz - wy);
    float m21 = 2.0f * (yz + wx);
    float m22 = 1.0f - 2.0f * (xx + yy);

    // Apply scale
    m00 *= scale.x; m01 *= scale.x; m02 *= scale.x;
    m10 *= scale.y; m11 *= scale.y; m12 *= scale.y;
    m20 *= scale.z; m21 *= scale.z; m22 *= scale.z;

    // Set matrix rows
    rows[0] = { m00, m01, m02, 0.0f };
    rows[1] = { m10, m11, m12, 0.0f };
    rows[2] = { m20, m21, m22, 0.0f };
    rows[3] = { translation.x, translation.y, translation.z, 1.0f };
}

Mat4x4f Mat4x4f::operator*(const Mat4x4f& other) const {
    Mat4x4f result;

    // Row-major multiplication: result[i][j] = dot(row_i of a, column_j of b)
    for (int row = 0; row < 4; ++row) {
        const Vec4f& r = rows[row];
        for (int col = 0; col < 4; ++col) {
            result.values[row * 4 + col] =
                r.x * other.values[0 * 4 + col] +
                r.y * other.values[1 * 4 + col] +
                r.z * other.values[2 * 4 + col] +
                r.w * other.values[3 * 4 + col];
        }
    }

    return result;
}
    
Vec3f Mat4x4f::get_translation() const {
    return Vec3f(values[3], values[7], values[11]);
}

// Utility: Normalize a 3D vector
inline Vec3f normalize3(const Vec3f& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (len > 0.0f) ? Vec3f{v.x / len, v.y / len, v.z / len} : Vec3f{0.0f, 0.0f, 0.0f};
}

Vec3f Mat4x4f::get_rotation_euler() const {
    // Extract and normalize axes to remove scale
    Vec3f xAxis = normalize3(Vec3f(rows[0].x, rows[0].y, rows[0].z));
    Vec3f yAxis = normalize3(Vec3f(rows[1].x, rows[1].y, rows[1].z));
    Vec3f zAxis = normalize3(Vec3f(rows[2].x, rows[2].y, rows[2].z));

    // Reconstruct rotation matrix
    float   m00 = xAxis.x, m01 = xAxis.y, m02 = xAxis.z;
    float   m10 = yAxis.x, m11 = yAxis.y, m12 = yAxis.z;
    float /*m20 = zAxis.x, m21 = zAxis.y,*/ m22 = zAxis.z;

    Vec3f euler;

    // XYZ rotation extraction
    if (std::abs(m02) < 1.0f) {
        euler.y = std::asin(m02); // pitch
        euler.x = std::atan2(-m12, m22); // yaw
        euler.z = std::atan2(-m01, m00); // roll
    } else {
        // Gimbal lock
        euler.y = (m02 > 0.0f) ? +M_PI / 2.0f : -M_PI / 2.0f;
        euler.x = std::atan2(m10, m11);
        euler.z = 0.0f;
    }

    return euler;
}

Vec4f Mat4x4f::get_rotation_quaternion() const {
    // Normalize rotation axes (remove scale)
    Vec3f xAxis = normalize3(Vec3f(rows[0].x, rows[0].y, rows[0].z));
    Vec3f yAxis = normalize3(Vec3f(rows[1].x, rows[1].y, rows[1].z));
    Vec3f zAxis = normalize3(Vec3f(rows[2].x, rows[2].y, rows[2].z));

    // Reconstruct rotation matrix
    float m00 = xAxis.x, m01 = xAxis.y, m02 = xAxis.z;
    float m10 = yAxis.x, m11 = yAxis.y, m12 = yAxis.z;
    float m20 = zAxis.x, m21 = zAxis.y, m22 = zAxis.z;

    Vec4f q; // x, y, z, w
    float trace = m00 + m11 + m22;

    if (trace > 0.0f) {
        float s = std::sqrt(trace + 1.0f) * 2.0f;
        q.w = 0.25f * s;
        q.x = (m21 - m12) / s;
        q.y = (m02 - m20) / s;
        q.z = (m10 - m01) / s;
    } else if ((m00 > m11) && (m00 > m22)) {
        float s = std::sqrt(1.0f + m00 - m11 - m22) * 2.0f;
        q.w = (m21 - m12) / s;
        q.x = 0.25f * s;
        q.y = (m01 + m10) / s;
        q.z = (m02 + m20) / s;
    } else if (m11 > m22) {
        float s = std::sqrt(1.0f + m11 - m00 - m22) * 2.0f;
        q.w = (m02 - m20) / s;
        q.x = (m01 + m10) / s;
        q.y = 0.25f * s;
        q.z = (m12 + m21) / s;
    } else {
        float s = std::sqrt(1.0f + m22 - m00 - m11) * 2.0f;
        q.w = (m10 - m01) / s;
        q.x = (m02 + m20) / s;
        q.y = (m12 + m21) / s;
        q.z = 0.25f * s;
    }

    return q;
}

Vec3f Mat4x4f::get_scale() const {
    return Vec3f(values[0], values[5], values[10]);
}

/***************************************************************************/
