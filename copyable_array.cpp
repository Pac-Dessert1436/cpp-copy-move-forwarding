// CopyableArray<T> - a dynamic array that supports copy semantics
#include <iostream>
#include "debug_print.h"

template <typename T>
class CopyableArray
{
private:
    T *data_;
    size_t size_;

public:
    // Default constructor
    CopyableArray() noexcept : data_(nullptr), size_(0)
    {
        debug_print("Created empty array");
    }

    // Constructor with size parameter
    explicit CopyableArray(size_t size) : size_(size)
    {
        if (size_ > 0)
        {
            data_ = new T[size_];
            debug_print("Allocated array of " + std::to_string(size_) + " elements");
        }
        else
        {
            data_ = nullptr;
            debug_print("Created empty array");
        }
    }

    // Copy constructor
    CopyableArray(const CopyableArray &other) : size_(other.size_)
    {
        if (size_ > 0)
        {
            data_ = new T[size_];
            std::copy(other.data_, other.data_ + size_, data_);
            debug_print("Copied array of " + std::to_string(size_) + " elements");
        }
        else
        {
            data_ = nullptr;
            debug_print("Created empty array");
        }
    }

    // Copy assignment operator
    CopyableArray &operator=(const CopyableArray &other)
    {
        if (this != &other)
        {
            delete[] data_; // release current resource
            size_ = other.size_;
            if (size_ > 0)
            {
                data_ = new T[size_];
                std::copy(other.data_, other.data_ + size_, data_);
                debug_print("Copied array of " + std::to_string(size_) + " elements");
            }
            else
            {
                data_ = nullptr;
                debug_print("Created empty array");
            }
        }
        return *this;
    }

    // Destructor
    ~CopyableArray()
    {
        delete[] data_;
        debug_print("Array destroyed, size: " + std::to_string(size_));
    }

    // Subscript operator - non-const version (modifiable)
    T &operator[](size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Subscript operator - const version (read-only)
    const T &operator[](size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Get array size
    size_t get_size() const noexcept
    {
        return size_;
    }

    // Check if array is empty
    bool is_empty() const noexcept
    {
        return size_ == 0;
    }

    // Get raw pointer (use with caution)
    T *get_data() noexcept
    {
        return data_;
    }

    const T *get_data() const noexcept
    {
        return data_;
    }

    // Display array contents
    void display() const
    {
        std::cout << "Array contents [size=" << size_ << "]: ";
        if (size_ == 0)
        {
            std::cout << "(empty)" << std::endl;
        }
        else
        {
            for (size_t i = 0; i < size_; ++i)
            {
                std::cout << data_[i];
                if (i < size_ - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

    // Fill the array
    void fill(const T &value)
    {
        if (data_ && size_ > 0)
        {
            std::fill(data_, data_ + size_, value);
        }
    }

    // Reset the array (release memory)
    void reset() noexcept
    {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }

    // Reallocate the array
    void resize(size_t new_size)
    {
        if (new_size == size_)
        {
            return;
        }

        if (new_size == 0)
        {
            reset();
            debug_print("Array resized to: 0");
            return;
        }

        // If there was existing data, copy the part that fits
        T *new_data = new T[new_size];
        if (data_ && size_ > 0)
        {
            size_t copy_size = std::min(size_, new_size);
            std::copy(data_, data_ + copy_size, new_data);
        }
        delete[] data_;
        data_ = new_data;
        size_ = new_size;
        debug_print("Array resized to: " + std::to_string(size_));
    }
};

int main()
{
    debug_enabled = true; // Enable debug printing
    std::cout << "=== CopyableArray<T> Copy Semantics Demo ===" << std::endl;
    // Create an integer array
    CopyableArray<int> int_array(5);
    int_array.fill(42);
    int_array.display();
    // Copy the array
    CopyableArray<int> copied_array = int_array; // Copy constructor
    std::cout << "After copying: ";
    copied_array.display();
    // Modify the copied array
    copied_array[0] = 99;
    std::cout << "After modifying copied array:" << std::endl;
    std::cout << "Original array: ";
    int_array.display();
    std::cout << "Copied array: ";
    copied_array.display();
    return 0;
}