#pragma once
#include <cstdint>
#include <iostream>
#include <functional>
#include <limits>

namespace DkrAssetsTool {

// TODO: Make a generic Vecf class, and then define Vec2f,Vec3f,Vec4f off of that.

struct Vec2f {
    union {
        struct {
            float x;
            float y;
        };
        struct {
            float u; // Same as x
            float v; // Same as y
        };
        float values[2];
    };

    Vec2f();
    Vec2f(float s);
    Vec2f(float x, float y);
    Vec2f(std::vector<float> &floats, size_t offset = 0);
    Vec2f(std::vector<double> &doubles, size_t offset = 0);

    float operator[](int index) const;
    float& operator[](int index);
    bool operator==(const Vec2f& other) const;
    bool operator!=(const Vec2f& other) const;
    Vec2f operator+(const Vec2f& other);
    Vec2f operator-(const Vec2f& other);
    Vec2f operator*(const Vec2f& other);
    Vec2f operator*(const float other);
    Vec2f operator/(const Vec2f& other);
    Vec2f operator/(const float other);
    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec);

    Vec2f min(const Vec2f& other) const; // Returns the minimum XY values of both vectors
    Vec2f max(const Vec2f& other) const; // Returns the maximum XY values of both vectors

    void update_min(const Vec2f& other); // Updates this struct to be the minimum of this and other.
    void update_max(const Vec2f& other); // Updates this struct to be the maximum of this and other.

    bool within(const Vec2f& other, float amountU, float amountV);

    bool is_zero() const;

    void copy_to(float *dst);

    std::vector<float> to_vector();
    std::vector<double> to_double_vector();

    static Vec2f min_value() {
        return Vec2f(std::numeric_limits<float>::min());
    }
    static Vec2f max_value() {
        return Vec2f(std::numeric_limits<float>::max());
    }
};


struct Vec3f {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float values[3];
    };

    Vec3f();
    Vec3f(float s);
    Vec3f(float x, float y, float z);
    Vec3f(std::vector<float> &floats, size_t offset = 0);
    Vec3f(std::vector<double> &doubles, size_t offset = 0);

    float operator[](int index) const;
    float& operator[](int index);
    bool operator==(const Vec3f& other) const;
    bool operator!=(const Vec3f& other) const;
    Vec3f operator+(const Vec3f& other) const;
    Vec3f &operator+=(const Vec3f& other);
    Vec3f operator-(const Vec3f& other) const;
    Vec3f operator*(const Vec3f& other) const;
    Vec3f operator*(const float other) const;
    Vec3f operator/(const Vec3f& other) const;
    Vec3f operator/(const float other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);

    Vec3f min(const Vec3f& other) const; // Returns the minimum XYZ values of both vectors
    Vec3f max(const Vec3f& other) const; // Returns the maximum XYZ values of both vectors

    void update_min(const Vec3f& other); // Updates this struct to be the minimum of this and other.
    void update_max(const Vec3f& other); // Updates this struct to be the maximum of this and other.

    bool is_zero() const;

    void copy_to(float* dst);

    std::vector<float> to_vector();
    std::vector<double> to_double_vector();

    static Vec3f min_value() {
        return Vec3f(std::numeric_limits<float>::min());
    }
    static Vec3f max_value() {
        return Vec3f(std::numeric_limits<float>::max());
    }
};

struct Vec4f {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        struct {
            float r; // Same as x
            float g; // Same as y
            float b; // Same as z
            float a; // Same as w
        };
        float values[4];
    };

    Vec4f();
    Vec4f(float s);
    Vec4f(float x, float y, float z, float w);
    Vec4f(uint8_t r, uint8_t g, uint8_t b);
    Vec4f(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Vec4f(uint32_t rgba);
    Vec4f(std::vector<float> &floats, size_t offset = 0);
    Vec4f(std::vector<double> &doubles, size_t offset = 0);
    Vec4f(std::vector<uint8_t> &bytes, size_t offset = 0);

    float operator[](int index) const;
    float& operator[](int index);
    bool operator==(const Vec4f& other) const;
    bool operator!=(const Vec4f& other) const;
    Vec4f operator+(const Vec4f& other);
    Vec4f operator-(const Vec4f& other);
    Vec4f operator*(const Vec4f& other);
    Vec4f operator*(const float other);
    Vec4f operator/(const Vec4f& other);
    Vec4f operator/(const float other);
    friend std::ostream& operator<<(std::ostream& os, const Vec4f& vec);

    Vec4f min(const Vec4f& other) const; // Returns the minimum XYZW values of both vectors
    Vec4f max(const Vec4f& other) const; // Returns the maximum XYZW values of both vectors

    void update_min(const Vec4f& other); // Updates this struct to be the minimum of this and other.
    void update_max(const Vec4f& other); // Updates this struct to be the maximum of this and other.

    bool is_zero() const;

    void copy_to(float* dst);

    uint8_t get_red_as_byte() const;
    uint8_t get_green_as_byte() const;
    uint8_t get_blue_as_byte() const;
    uint8_t get_alpha_as_byte() const;
    uint32_t get_as_rgba() const;

    std::vector<float> to_vector();
    std::vector<double> to_double_vector();

    static Vec4f min_value() {
        return Vec4f(std::numeric_limits<float>::min());
    }
    static Vec4f max_value() {
        return Vec4f(std::numeric_limits<float>::max());
    }
};

struct Mat4x4f {
    union {
        Vec4f rows[4];
        float values[16];
    };
    
    Mat4x4f(); // Identity matrix
    Mat4x4f(const std::vector<float> &src, size_t offset = 0);
    Mat4x4f(const std::vector<double> &src, size_t offset = 0);
    Mat4x4f(const Vec3f &translation, const Vec3f &rotEuler, const Vec3f &scale);
    Mat4x4f(const Vec3f &translation, const Vec4f &rotQuaternion, const Vec3f &scale);
    
    Mat4x4f operator*(const Mat4x4f& other) const;
    
    static Mat4x4f identity() {
        return Mat4x4f(std::vector<float>{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 0
        });
    }
    
    Vec3f get_translation() const;
    
    Vec3f get_rotation_euler() const;
    Vec4f get_rotation_quaternion() const;
    
    Vec3f get_scale() const;
};
   
}

namespace std {
    template <>
    struct hash<DkrAssetsTool::Vec2f> {
        std::size_t operator()(const DkrAssetsTool::Vec2f& vec) const {
            return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y);
        }
    };
    template <>
    struct hash<DkrAssetsTool::Vec3f> {
        std::size_t operator()(const DkrAssetsTool::Vec3f& vec) const {
            return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y) ^ std::hash<float>()(vec.z);
        }
    };
    template <>
    struct hash<DkrAssetsTool::Vec4f> {
        std::size_t operator()(const DkrAssetsTool::Vec4f& vec) const {
            return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y) ^ std::hash<float>()(vec.z) ^ std::hash<float>()(vec.w);
        }
    };
}
