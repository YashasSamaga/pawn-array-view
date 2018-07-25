/*
** C++ wrapper for manipulating Pawn arrays
*/

#ifndef PAWN_ARRAY_VIEW_HPP
#define PAWN_ARRAY_VIEW_HPP

#include <cstddef>

namespace pawn {
    template <typename T, std::size_t dims>
    class array_view {
        static_assert(dims > 0, "dimensions must be greater than zero");

    public:
        using value_type = array_view<T, dims - 1>;
        using reference = value_type&;
        using const_reference = const reference;
        using pointer = value_type*;
        using const_pointer = const pointer;
        using size_type = int;
        using difference_type = std::ptrdiff_t;

        array_view() noexcept { }
        array_view(cell *phys_addr) noexcept : indirection_table(phys_addr) { }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        value_type operator[](difference_type index) { return value_type(&indirection_table[index] + indirection_table[index]/sizeof(cell)); }
        const value_type operator[](difference_type index) const { return value_type(&indirection_table[index] + indirection_table[index]/sizeof(cell)); }

        void swap(array_view& av) noexcept { std::swap(this->indirection_table, av.indirection_table); }
        void assign(cell *phys_addr) noexcept { indirection_table = phys_addr; }

    private:
        cell *indirection_table;
    };

    template <typename T>
    class array_view<T, 1> {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const reference;
        using pointer = value_type*;
        using const_pointer = const pointer;
        using size_type = int;
        using difference_type = std::ptrdiff_t;

        array_view() noexcept : mp_first{ nullptr } { }
        array_view(cell *phys_addr) noexcept : mp_first{ phys_addr } { }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        reference operator[](difference_type index) { return static_cast<T>(this->mp_first[index]); }
        const_reference operator[](difference_type index) const { return static_cast<T>(this->mp_first[index]); }
        
        void swap(array_view& av) noexcept { std::swap(this->mp_first, av.mp_first); }      
        void assign(cell *phys_addr) noexcept { this->mp_first = phys_addr; }

    private:
        pointer mp_first;
    };
};
#endif /* PAWN_ARRAY_VIEW_HPP */