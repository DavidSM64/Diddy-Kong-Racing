#ifndef BYTES_VIEW_H
#define BYTES_VIEW_H

#include <vector>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <optional>
#include <functional>
#include <algorithm>

class BytesView {
public:
    // TODO: Can I use this with std::vector without needing a default constructor? Only reason for `_data` being a pointer instead of a reference.
    BytesView() {
    }

    BytesView(std::vector<uint8_t> &vec, size_t startOffset=0, std::optional<size_t> size=std::nullopt) : _startOffset(startOffset), _data(&vec) {
        if(size == std::nullopt) {
            _length = _data->size() - _startOffset;
        } else {
            _length = size.value();
        }
        if (_startOffset + _length > _data->size()) {
            throw std::out_of_range("BytesView range exceeds vector size");
        }
    }

    BytesView(std::vector<uint8_t> *vec, size_t startOffset = 0, std::optional<size_t> size=std::nullopt) : _startOffset(startOffset), _data(vec) {
        if(size == std::nullopt) {
            _length = _data->size() - _startOffset;
        } else {
            _length = size.value();
        }
        if (_startOffset + _length > _data->size()) {
            throw std::out_of_range("BytesView range exceeds vector size");
        }
    }

    const uint8_t operator[](size_t index) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        if (index >= _length) {
            throw std::out_of_range("Index out of range");
        }
        return _data->at(_startOffset + index);
    }

    uint8_t& operator[](size_t index) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        if (index >= _length) {
            throw std::out_of_range("Index out of range");
        }
        return (*_data)[_startOffset + index];
    }

    size_t offset() const {
        return _startOffset;
    }

    size_t size() const {
        return _length;
    }

    const uint8_t* data() const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return &_data->at(_startOffset);
    }

    const std::reference_wrapper<std::vector<uint8_t>> data_vector() const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return std::ref(*_data);
    }

    template<typename T>
    T* data_cast(size_t offset=0) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return reinterpret_cast<T*>(&_data->at(_startOffset) + offset);
    };
    
    // Copy data from a vector.
    void copy_from(const std::vector<uint8_t> &srcData, size_t offset = 0) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        std::copy(srcData.begin(), srcData.end(), _data->begin() + _startOffset + offset);
    }
    
    // Copy data from another view into this view.
    void copy_from(BytesView srcView, size_t offset = 0) {
        copy_from(srcView.data_vector(), offset);
    }
    
    BytesView get_sub_view(size_t startOffset, std::optional<size_t> size=std::nullopt) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        size_t newSize;
        if (size == std::nullopt) {
            newSize = _length - startOffset;
        } else {
            newSize = size.value();
        }
        return BytesView(_data, _startOffset + startOffset, newSize);
    }

    // little-endian unsigned 32-bit value.
    uint32_t get_u32_le(size_t offset) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return (_data->at(_startOffset + offset + 3) << 24) |
               (_data->at(_startOffset + offset + 2) << 16) |
               (_data->at(_startOffset + offset + 1) << 8)  |
               (_data->at(_startOffset + offset + 0));
    }

    int32_t get_s32_le(size_t offset) const {
        return (int32_t)get_u32_le(offset);
    }
    
    void set_u32_le(size_t offset, uint32_t value) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        (*_data)[_startOffset + offset + 3] = (value >> 24) & 0xFF;
        (*_data)[_startOffset + offset + 2] = (value >> 16) & 0xFF;
        (*_data)[_startOffset + offset + 1] = (value >>  8) & 0xFF;
        (*_data)[_startOffset + offset + 0] =  value        & 0xFF;
    }
    
    void set_s32_le(size_t offset, int32_t value) {
        set_u32_le(offset, (uint32_t)value);
    }

    // little-endian unsigned 16-bit value.
    uint16_t get_u16_le(size_t offset) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return (_data->at(_startOffset + offset + 1) << 8) |
               (_data->at(_startOffset + offset + 0));
    }

    int16_t get_s16_le(size_t offset) const {
        return (int16_t)get_u16_le(offset);
    }
    
    void set_u16_le(size_t offset, uint16_t value) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        (*_data)[_startOffset + offset + 1] = (value >> 8) & 0xFF;
        (*_data)[_startOffset + offset + 0] = value        & 0xFF;
    }
    
    void set_s16_le(size_t offset, int16_t value) {
        set_u16_le(offset, (uint16_t)value);
    }

    // big-endian unsigned 16-bit value.
    uint16_t get_u16_be(size_t offset) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return (_data->at(_startOffset + offset + 0) << 8) |
               (_data->at(_startOffset + offset + 1));
    }

    int16_t get_s16_be(size_t offset) const {
        return (int16_t)get_u16_be(offset);
    }
    
    void set_u16_be(size_t offset, uint16_t value) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        (*_data)[_startOffset + offset + 0] = (value >> 8) & 0xFF;
        (*_data)[_startOffset + offset + 1] = value        & 0xFF;
    }
    
    void set_s16_be(size_t offset, int16_t value) {
        set_u16_be(offset, (uint16_t)value);
    }

    // big-endian unsigned 32-bit value.
    uint32_t get_u32_be(size_t offset) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        return (_data->at(_startOffset + offset + 0) << 24) | 
               (_data->at(_startOffset + offset + 1) << 16) | 
               (_data->at(_startOffset + offset + 2) << 8)  | 
               (_data->at(_startOffset + offset + 3));
    }

    int32_t get_s32_be(size_t offset) const {
        return (int32_t)get_u32_be(offset); 
    }
    
    void set_u32_be(size_t offset, uint32_t value) {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");
        (*_data)[_startOffset + offset + 0] = (value >> 24) & 0xFF;
        (*_data)[_startOffset + offset + 1] = (value >> 16) & 0xFF;
        (*_data)[_startOffset + offset + 2] = (value >>  8) & 0xFF;
        (*_data)[_startOffset + offset + 3] =  value        & 0xFF;
    }
    
    void set_s32_be(size_t offset, int32_t value) {
        set_u32_be(offset, (uint32_t)value);
    }

    void print(int32_t offset = 0, int32_t length = 32, size_t groupBy = 4) const {
        if (_data == nullptr) throw std::runtime_error("BytesView was not initialized!");

        
        std::stringstream ss;
        
        if(_length == 0) {
            ss << "BytesView is empty!";
            std::cout << ss.str() << std::endl;
            return;
        }

        if (length > (int32_t)_length - offset) {
            length = (int32_t)_length - offset;
        }
        if (groupBy < 1) groupBy = 1;

        size_t byteCountInLine = 0;
        while (length > 0) {
            for (size_t i = 0; i < groupBy; i++) {
                try {
                    int byteValue = _data->at(_startOffset + offset + i) & 0xFF;
                    ss << std::hex << std::setw(2) << std::setfill('0') << byteValue;
                } catch (const std::out_of_range& oor) {
                    break;
                }
            }
            ss << " ";
            offset += groupBy;
            length -= groupBy;
            byteCountInLine += groupBy;
            if (byteCountInLine >= 16) {
                byteCountInLine = 0;
                ss << std::endl;
            }
        }

        std::cout << ss.str() << std::endl;
    }

private:
    size_t _startOffset = 0;
    size_t _length = 0;
    std::vector<uint8_t> *_data = nullptr;
};


// Allows BytesView to be converted into a std::istream
class BytesViewStreamBuf : public std::streambuf {
public:
    BytesViewStreamBuf(BytesView bytesView) {
        char* begin = reinterpret_cast<char*>(const_cast<uint8_t*>(bytesView.data()));
        this->setg(begin, begin, begin + bytesView.size());
    }
};

#endif // BYTES_VIEW_H