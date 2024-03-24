#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T = double>
class Vector {
public:
    class ConstIterator;
    class Iterator;
    // Type aliases
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = Vector::Iterator;
    using const_iterator = Vector::ConstIterator;

public: // Construct, destruct
    Vector() = default;

    Vector(size_type n) : max_sz(n) {
        // If new memory with size 0 -> real address with garbage
        // If nullpointer -> no address, no value
        if (n != 0)
            values = new value_type[n];
    }

    Vector(const Vector &vec) : Vector(vec.max_sz) {
        for (size_type i = 0; i < vec.sz; i++)
            values[sz++] = vec.values[i];
    }

    Vector(std::initializer_list<value_type> il) : Vector(il.size()) {
        for (const_reference val : il)
            values[sz++] = val;
    }

    ~Vector() {
        delete[] values;
    }

public: // Iterators
    iterator begin() {
        return iterator(values);
    }

    const_iterator begin() const {
        return const_iterator(values);
    }

    iterator end() {
        return iterator(values + sz);
    }

    const_iterator end() const {
        return const_iterator(values + sz);
    }

    class Iterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector::reference;
        using pointer = Vector::pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;

    public: // Constuct
        Iterator() = default;

        Iterator(pointer ptr) : ptr(ptr) {}

    public: // Operators
        reference operator*() {
            return *ptr;
        }

        pointer operator->() {
            return ptr;
        }

        iterator operator++(int) {
            return Iterator(ptr++);
        }

        iterator &operator++() {
            ++ptr;
            return *this;
        }

        bool operator==(const const_iterator &cit) const {
            return ptr == cit.ptr;
        }

        bool operator!=(const const_iterator &cit) const {
            return ptr != cit.ptr;
        }

        operator const_iterator() const {
            return ConstIterator(ptr);
        }

    private:
        pointer ptr = nullptr;
    };

    class ConstIterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector::const_reference;
        using pointer = Vector::const_pointer;
        using difference_type = Vector::difference_type;
        using iterator_category = std::forward_iterator_tag;

    public: // Constuct
        ConstIterator() = default;

        ConstIterator(pointer ptr) : ptr(ptr) {}

    public: // Operators
        reference operator*() const {
            return *ptr;
        }

        pointer operator->() const {
            return ptr;
        }

        const_iterator operator++(int) {
            return ConstIterator(ptr++);
        }

        const_iterator &operator++() {
            ++ptr;
            return *this;
        }

        bool operator==(const const_iterator &cit) const {
            return ptr == cit.ptr;
        }

        bool operator!=(const const_iterator &cit) const {
            return ptr != cit.ptr;
        }

        friend bool Iterator::operator==(const const_iterator &cit) const;

        friend bool Iterator::operator!=(const const_iterator &cit) const;

        friend difference_type operator-(const const_iterator &lop, const const_iterator &rop) {
            return lop.ptr - rop.ptr;
        }

    private:
        pointer ptr = nullptr;
    };

public: // Capacity
    size_type size() const {
        return sz;
    }

    size_type capacity() const {
        return max_sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void reserve(size_t n) {
        if (n > max_sz)
            realloc(n);
    }

    void shrink_to_fit() {
        if (sz < max_sz)
            realloc(sz);
    }

public: // Modifiers
    void clear() {
        sz = 0;
    }

    void push_back(const_reference val) {
        if (sz == max_sz)
            // Grow factor of 2 never allows to use all
            // of the allocated mem -> using factor 1.5
            realloc(max_sz + max_sz / 2 + 1);
        values[sz++] = val;
    }

    void pop_back() {
        if (sz == 0)
            throw std::runtime_error("Vector.pop_back : out of bounds");
        --sz;
    }

    iterator insert(const_iterator pos, const_reference val) {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) > sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current = static_cast<size_type>(diff);
        if (sz >= max_sz)
            realloc(max_sz + max_sz / 2 + 1);
        for (size_type i = sz; i-- > current;)
            values[i + 1] = values[i];
        values[current] = val;
        ++sz;
        return Iterator(values + current);
    }

    iterator erase(const_iterator pos) {
        auto diff = pos - begin();
        if (diff < 0 || static_cast<size_type>(diff) >= sz)
            throw std::runtime_error("Iterator out of bounds");
        size_type current = static_cast<size_type>(diff);
        for (size_type i = current; i < sz - 1; i++)
            values[i] = values[i + 1];
        --sz;
        return Iterator(values + current);
    }

public: // Operators
    reference operator[](size_type index) {
        if (index >= sz)
            throw std::runtime_error("Vector.operator[] : index out of bounds");
        return values[index];
    }

    const_reference operator[](size_type index) const {
        if (index >= sz)
            throw std::runtime_error("Vector.operator[] const : index out of bounds");
        return values[index];
    }

    Vector &operator=(Vector other_vec) {
        std::swap(sz, other_vec.sz);
        std::swap(max_sz, other_vec.max_sz);
        std::swap(values, other_vec.values);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &vec) {
        out << '[';
        if (vec.sz >= 1)
            out << vec.values[0];
        for (size_t i = 1; i < vec.sz; i++)
            out << ", " << vec.values[i];
        out << ']';
        return out;
    }

private:
    size_type sz = 0;
    size_type max_sz = 0;
    pointer values = nullptr;

private: // Utils
    void realloc(size_type new_sz) {
        if (new_sz < sz)
            return;
        pointer tmp_ptr = new value_type[new_sz];
        for (size_type i = 0; i < sz; i++)
            tmp_ptr[i] = values[i];
        delete[] values;
        values = tmp_ptr;
        max_sz = new_sz;
    }
}; // Vector

#endif // VECTOR_H
