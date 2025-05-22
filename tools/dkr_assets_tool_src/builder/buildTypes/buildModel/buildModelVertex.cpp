#include "buildModelVertex.h"

using namespace DkrAssetsTool;

const Vec3f POSITION_ZERO = {};
const Vec4f COLOR_NULL = {};
const Vec4f COLOR_WHITE = { 1.0f };

BuildModelVertex::BuildModelVertex() : _position(POSITION_ZERO), _color(COLOR_NULL) {
}

BuildModelVertex::BuildModelVertex(const Vec3f position) : _position(position), _color(COLOR_WHITE) {
}

BuildModelVertex::BuildModelVertex(const Vec3f position, const Vec4f color) : _position(position), _color(color) {
}

BuildModelVertex::~BuildModelVertex() {
}

bool BuildModelVertex::operator==(const BuildModelVertex& other) const {
    return (_position == other._position) && (_color == other._color);
}

bool BuildModelVertex::operator!=(const BuildModelVertex& other) const {
    return !operator==(other);
}

Vec3f BuildModelVertex::position() const {
    return _position;
}

Vec4f BuildModelVertex::color() const {
    return _color;
}

bool BuildModelVertex::is_color_white() const {
    return _color == COLOR_WHITE;
}

void BuildModelVertex::write_to(DkrVertex *outVertex) {
    // Write position
    outVertex->x = static_cast<int16_t>(_position.x * 10);
    outVertex->y = static_cast<int16_t>(_position.y * 10);
    outVertex->z = static_cast<int16_t>(_position.z * 10);
    
    // Write color
    outVertex->r = _color.get_red_as_byte();
    outVertex->g = _color.get_green_as_byte();
    outVertex->b = _color.get_blue_as_byte();
    outVertex->a = _color.get_alpha_as_byte();
}

 std::ostream& operator<<(std::ostream& os, const BuildModelVertex& vertex) {
    os << "{ pos: " << vertex.position() << ", color: 0x" << std::hex << vertex.color().get_as_rgba() << std::dec << " }";
    return os;
}
