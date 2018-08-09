/*
** C++ wrapper for manipulating Pawn arrays
*/

#ifndef PAWN_ARRAY_VIEW_HPP
#define PAWN_ARRAY_VIEW_HPP

#include <cstddef>
#include <utility>
#include <type_traits>

namespace pawn {
    template <typename T, std::size_t dims>
    class array_view {
        static_assert(dims > 0, "dimensions must be greater than zero");

    public:
        using value_type = array_view<T, dims - 1>;
        using reference = std::add_lvalue_reference_t<value_type>;
        using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
        using pointer = std::add_pointer_t<value_type>;
        using const_pointer = std::add_pointer_t<std::add_const_t<value_type>>;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        array_view() noexcept : indirection_table{ nullptr } { }
        array_view(cell *phys_addr) noexcept : indirection_table{ phys_addr } { }

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
        using reference = std::add_lvalue_reference_t<value_type>;
        using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
        using pointer = std::add_pointer_t<value_type>;
        using const_pointer = std::add_pointer_t<std::add_const_t<value_type>>;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        array_view() noexcept : mp_first{ nullptr } { }
        array_view(cell *phys_addr) noexcept : mp_first{ phys_addr } { }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        static_assert(sizeof(cell) == sizeof(value_type));
        reference operator[](difference_type index) { return reinterpret_cast<reference>(this->mp_first[index]); }
        const_reference operator[](difference_type index) const { return reinterpret_cast<reference>(this->mp_first[index]); }
        
        void swap(array_view& av) noexcept { std::swap(this->mp_first, av.mp_first); }      
        void assign(cell *phys_addr) noexcept { this->mp_first = phys_addr; }

    private:
        cell* mp_first;
    };
};
#endif /* PAWN_ARRAY_VIEW_HPP */