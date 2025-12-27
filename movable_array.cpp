// MovableArray<T> - an RAII dynamic array with move semantics
#include <iostream>
#include "debug_print.h"

template <typename T>
class MovableArray
{
private:
    T *data_;
    size_t size_;

public:
    // Default constructor: create an empty array
    MovableArray() noexcept : data_(nullptr), size_(0)
    {
        debug_print("Default constructor called");
    }

    /* Constructor with size parameter */
    explicit MovableArray(size_t size) : size_(size)
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

    /* Constructor with size and initial value */
    MovableArray(size_t size, const T &init_value) : size_(size)
    {
        if (size_ > 0)
        {
            data_ = new T[size_];
            std::fill(data_, data_ + size_, init_value);
            debug_print("Allocated array of " + std::to_string(size_) + " elements, initialized to " + std::to_string(init_value));
        }
        else
        {
            data_ = nullptr;
            debug_print("Created empty array");
        }
    }

    /* Move constructor */
    MovableArray(MovableArray &&other) noexcept
        : data_(other.data_), size_(other.size_)
    {
        other.data_ = nullptr; // source object gives up ownership
        other.size_ = 0;
        debug_print("Move constructor called, took ownership of the array!");
    }

    /* Move assignment */
    MovableArray &operator=(MovableArray &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;      // release current resource
            data_ = other.data_; // take ownership of new resource
            size_ = other.size_;
            other.data_ = nullptr; // source object gives up ownership
            other.size_ = 0;
            debug_print("Move assignment called, took ownership of the array!");
        }
        return *this;
    }

    /* Destructor */
    ~MovableArray()
    {
        delete[] data_;
        debug_print("Array destroyed, size: " + std::to_string(size_));
    }

    // Subscript operator - non-const version (modifiable)
    T &operator[](size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range!");
        }
        return data_[index];
    }

    // Subscript operator - const version (read-only)
    const T &operator[](size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range!");
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
        if (is_empty())
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

    // Reallocate the array (loses existing data)
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

    // Disable copy operations (use =delete)
    MovableArray(const MovableArray &) = delete;
    MovableArray &operator=(const MovableArray &) = delete;
};

/* Factory function: create a temporary array */
template <typename T>
MovableArray<T> create_movable_array(size_t size, T (*map_func)(size_t))
{
    MovableArray<T> tmp(size);
    // initialize some data
    for (size_t i = 0; i < size; ++i)
    {
        tmp[i] = map_func(i);
    }
    return std::move(tmp); // explicit move
}

/* main function */
int main()
{
    debug_enabled = true; // Enable debug printing
    std::cout << "=== MovableArray<T> Move Semantics Demo ===" << std::endl;

    // Create arrays of different types
    std::cout << "\n1. Create integer array:" << std::endl;
    MovableArray<int> int_array(5, 0); // 5 elements, initialized to 0
    int_array.display();

    // Use subscript operator
    for (size_t i = 0; i < int_array.get_size(); ++i)
    {
        int_array[i] = static_cast<int>(i * 10);
    }
    std::cout << "After modification: ";
    int_array.display();

    std::cout << "\n2. Create double array:" << std::endl;
    MovableArray<double> double_array(3, 1.5);
    double_array[1] = 3.14;
    double_array[2] = 2.718;
    double_array.display();

    std::cout << "\n3. Move semantics demonstration:" << std::endl;

    // Move construction
    MovableArray<int> source_array =
        create_movable_array<int>(10, [](size_t i)
                                  { return static_cast<int>(i + 1); });
    source_array.display();

    std::cout << "\n4. Move assignment demonstration:" << std::endl;

    // First create a target array
    MovableArray<int> target_array(2, 99);
    target_array.display();

    // Move-assign (target_array will release its old memory and take over source_array)
    target_array = std::move(source_array);

    std::cout << "After move assignment:" << std::endl;
    std::cout << "target_array: ";
    target_array.display();
    std::cout << "source_array (ownership transferred): ";
    source_array.display();
    std::cout << "source_array is empty: " << std::boolalpha << source_array.is_empty() << std::endl;

    std::cout << "\n5. Resize demonstration:" << std::endl;
    MovableArray<int> resizable_array(3, 42);
    resizable_array.display();

    resizable_array.resize(6);
    resizable_array.fill(100);
    resizable_array.display();

    resizable_array.resize(2);
    resizable_array.display();

    std::cout << "\n=== Demo finished ===" << std::endl;

    return 0;
}
