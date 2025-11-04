#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <iostream>
#include <utility>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t size;

public:
    Array() : capacity(2), size(0), data(std::make_unique<T[]>(2)) {}
    
    Array(const Array& other) : capacity(other.capacity), size(other.size) {
        data = std::make_unique<T[]>(capacity);
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : data(std::move(other.data)), capacity(other.capacity), size(other.size) {
        other.size = 0;
        other.capacity = 0;
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            capacity = other.capacity;
            size = other.size;
            data = std::make_unique<T[]>(capacity);
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            capacity = other.capacity;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void Add(T element) {
        if (size == capacity) {
            size_t new_capacity = capacity * 2;
            auto new_data = std::make_unique<T[]>(new_capacity);
            
            for (size_t i = 0; i < size; i++) {
                new_data[i] = std::move(data[i]);
            }
            
            data = std::move(new_data);
            capacity = new_capacity;
        }
        data[size++] = std::move(element);
    }

    void Remove(size_t index) {
        if (index >= size) return;
        
        for (size_t i = index; i < size - 1; i++) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
    
    T& operator[](size_t index) { 
        return data[index]; 
    }
    
    const T& operator[](size_t index) const { 
        return data[index]; 
    }
    
    size_t Size() const { 
        return size; 
    }
    
    size_t Capacity() const { 
        return capacity; 
    }
    
    T* begin() { return data.get(); }
    const T* begin() const { return data.get(); }
    T* end() { return data.get() + size; }
    const T* end() const { return data.get() + size; }
};

#endif
