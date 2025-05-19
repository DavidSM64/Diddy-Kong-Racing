#include "mathHelper.h"

using namespace DkrAssetsTool;

/***************************************************************************/

Vec2f::Vec2f() : x(0), y(0) {}

Vec2f::Vec2f(float s) : x(s), y(s) {
}

Vec2f::Vec2f(float x, float y) : x(x), y(y){
}

Vec2f::Vec2f(std::vector<float> &floats, size_t offset) : x(floats[offset]), y(floats[offset+1]) {
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

Vec3f Vec3f::operator+(const Vec3f& other) {
    return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f Vec3f::operator-(const Vec3f& other) {
    return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::operator*(const Vec3f& other) {
    return Vec3f(x * other.x, y * other.y, z * other.z);
}

Vec3f Vec3f::operator*(const float other) {
    return Vec3f(x * other, y * other, z * other);
}

Vec3f Vec3f::operator/(const Vec3f& other) {
    return Vec3f(x / other.x, y / other.y, z / other.z);
}

Vec3f Vec3f::operator/(const float other) {
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
