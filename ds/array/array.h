#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cstddef>

template <typename T, size_t CAPACITY>
class Array {
    // TODO: add type aliases
    // TODO: add iterators
public:
    // Constructors
    // TODO: fix bag with default constructor then type T doesn's have default constructor
    Array() : _size(0) { fill(T()); }

    Array(T element) : _size(CAPACITY) { fill(element); }

    Array(std::initializer_list<T> elements) : _size(elements.size()) {
        if (elements.size() > CAPACITY)
            throw std::runtime_error("Can'i initialize Array with more elements then MAX_SIZE");

        // TODO: rewrite using range loop
        auto it = elements.begin();
        for (size_t i = 0; i < CAPACITY; i++) {
            if (it != elements.end()) {
                _data[i] = *it++;
            }
            else {
                _data[i] = T();
            }
        }
    }

    // Element access
    T &at(size_t index) { return _get_element_with_bounds_check(index); }

    const T &at(size_t index) const { return _get_element_with_bounds_check(index); }

    // TODO: remove at() methods, use only [] with bounds check
    T &operator[](size_t index) { return _data[index]; }

    const T &operator[](size_t index) const { return _data[index]; }

    T &front() { return _data[0]; }

    const T &front() const { return _data[0]; }

    T &back() { return _data[CAPACITY - 1]; }

    const T &back() const { return _data[CAPACITY - 1]; }

    T *data() { return _data; }

    const T *data() const { return _data; }

    // Capacity
    constexpr size_t size() const { return CAPACITY; }

    bool empty() { return _size == 0; };

    // Fill Array
    void fill(T element) {
        for (size_t i = 0; i < CAPACITY; i++) {
            _data[i] = element;
        }
    }

    // Find element and return it's index
    long find(const T &element) {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i] == element) {
                return i;
            }
        }
        return -1;
    }

private:
    size_t _size;
    T _data[CAPACITY];

    // Utils
    void _check_range(size_t index) const {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
    }

    T &_get_element_with_bounds_check(size_t index) {
        _check_range(index);
        return _data[index];
    }

    const T &_get_element_with_bounds_check(size_t index) const {
        _check_range(index);
        return _data[index];
    }
}; // Array

// TODO: move output operator to class using 'friend'
template <typename T, size_t S>
std::ostream &operator<<(std::ostream &out, const Array<T, S> &arr) {
    // TODO: check if array is empty, if not, out << "{ " << arr[0]; and loop after
    out << "Array {";
    for (size_t i = 0; i < arr.size(); i++) {
        if (i == 0)
            out << arr[i];
        else
            out << ", " << arr[i];
    }
    out << '}';
    return out;
}

#endif // ARRAY_H
