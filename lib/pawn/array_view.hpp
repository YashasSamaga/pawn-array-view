/*
** C++ wrapper for manipulating Pawn arrays
**
** TODO: support jagged arrays
**
*/

#ifndef PAWN_ARRAY_VIEW_HPP
#define PAWN_ARRAY_VIEW_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>

namespace pawn {
    /* abstract class to ensure a common interface for all types of array_view classes */
    template <typename T>
    class array_view_interface {
    public:
        using value_type = T;
        using size_type = int;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        virtual ~array_view_interface() { };

        virtual iterator begin() noexcept = 0;
        virtual iterator end() noexcept = 0;
        virtual const_iterator cbegin() const noexcept = 0;
        virtual const_iterator cend() const noexcept = 0;
        virtual const_iterator begin() const noexcept = 0;
        virtual const_iterator end() const noexcept = 0;

        virtual reverse_iterator rbegin() noexcept = 0;
        virtual reverse_iterator rend() noexcept = 0;
        virtual const_reverse_iterator crbegin() const noexcept = 0;
        virtual const_reverse_iterator crend() const noexcept = 0;
        virtual const_reverse_iterator rbegin() const noexcept = 0;
        virtual const_reverse_iterator rend() const noexcept = 0;

        virtual size_type size() const noexcept = 0;

        virtual reference operator[](difference_type index) = 0;
        virtual const_reference operator[](difference_type index) const = 0;
        virtual reference at(difference_type index) = 0;
        virtual const_reference at(difference_type index) const = 0;
        
        virtual pointer data() noexcept = 0;
        virtual const_pointer data() const noexcept = 0;        
    };

    /* multi-dimensional array with the size of the highest dimension known at compile-time */
    template <typename T, std::size_t N, std::size_t... dims>
    class array_view : public array_view_interface<array_view<T, dims...>> {
    public:
        using typename array_view_interface::value_type;
        using typename array_view_interface::reference;
        using typename array_view_interface::const_reference;
        using typename array_view_interface::pointer;
        using typename array_view_interface::const_pointer;
        using typename array_view_interface::iterator;
        using typename array_view_interface::const_iterator;
        using typename array_view_interface::reverse_iterator;
        using typename array_view_interface::const_reverse_iterator;
        using typename array_view_interface::size_type;
        using typename array_view_interface::difference_type;

        array_view() noexcept { }

        template <typename... UnknownDimSizes>
        array_view(cell *phys_addr, UnknownDimSizes&&...args) noexcept {
            for (int i = 0; i < N; i++) {                
                subarray[i].assign(&phys_addr[i] + phys_addr[i]/sizeof(cell), args...);
            }
        }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        iterator begin() noexcept { return &this->subarray[0]; }
        iterator end() noexcept { return this->begin() + N; }
        const_iterator cbegin() const noexcept { return this->begin(); }
        const_iterator cend() const noexcept { return this->end(); }
        const_iterator begin() const noexcept { return this->begin(); }
        const_iterator end() const noexcept { return this->end(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(this->cend()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(this->cbegin()); }
        const_reverse_iterator rbegin() const noexcept { return this->crend(); }
        const_reverse_iterator rend() const noexcept { return this->crbegin(); }

        constexpr size_type size() const noexcept { return N; }

        const_reference operator[](difference_type index) const { return this->subarray[index]; }
        reference operator[](difference_type index) { return this->subarray[index]; }

        const_reference at(difference_type index) const { return this->subarray.at(index); }
        reference at(difference_type index) { return this->subarray.at(index); }

        const_pointer data() const noexcept { return &this->subarray[0]; }
        pointer data() noexcept { return &this->subarray[0]; }

        void swap(array_view& av) noexcept { std::swap(this->subarray, av.subarray); }

        template <typename... UnknownDimSizes>
        void assign(cell *phys_addr, UnknownDimSizes&&...args) {
            for (int i = 0; i < N; i++) {
                subarray[i].assign(&phys_addr[i] + phys_addr[i]/sizeof(cell), args...);
            }
        }

        bool operator==(const array_view& other) const { return std::equal(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator<(const array_view& other) const { return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator!=(const array_view& other) const { return !(*this == other); };
        bool operator<=(const array_view& other) const { return (*this < other) || (*this == other); };
        bool operator>(const array_view& other) const { return other < *this; };
        bool operator>=(const array_view& other) const { return !(*this < other) || (*this == other); };

    private:
        std::array<value_type, N> subarray;
    };

    /* multi-dimensional array in which the size of the highest dimension is unknown at compile-time */
    template <typename T, std::size_t... dims>
    class array_view<T, 0, dims...> : public array_view_interface<array_view<T, dims...>> {
    public:
        using typename array_view_interface::value_type;
        using typename array_view_interface::reference;
        using typename array_view_interface::const_reference;
        using typename array_view_interface::pointer;
        using typename array_view_interface::const_pointer;
        using typename array_view_interface::iterator;
        using typename array_view_interface::const_iterator;
        using typename array_view_interface::reverse_iterator;
        using typename array_view_interface::const_reverse_iterator;
        using typename array_view_interface::size_type;
        using typename array_view_interface::difference_type;

        array_view() noexcept { }

        template <typename... UnknownDimSizes>
        array_view(cell *phys_addr, size_type dim_size, UnknownDimSizes&&... args) noexcept {
            subarray.reserve(dim_size);
            for (int i = 0; i < dim_size; i++)
                subarray.emplace_back(&phys_addr[i] + phys_addr[i]/sizeof(cell), args...);
        }

        array_view(const array_view& other) = default;
        array_view& operator=(const array_view& view) noexcept = default;

        iterator begin() noexcept { return &this->subarray[0]; }
        iterator end() noexcept { return this->begin() + this->size(); }
        const_iterator cbegin() const noexcept { return this->begin(); }
        const_iterator cend() const noexcept { return this->end(); }
        const_iterator begin() const noexcept { return this->begin(); }
        const_iterator end() const noexcept { return this->end(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(this->cend()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(this->cbegin()); }
        const_reverse_iterator rbegin() const noexcept { return this->crend(); }
        const_reverse_iterator rend() const noexcept { return this->crbegin(); }

        size_type size() const noexcept { return subarray.size(); }

        const_reference operator[](difference_type index) const { return this->subarray[index]; }
        reference operator[](difference_type index) { return this->subarray[index]; }

        const_reference at(difference_type index) const { return this->subarray.at(index); }
        reference at(difference_type index) { return this->subarray.at(index); }

        const_pointer data() const noexcept { return &this->subarray[0]; }
        pointer data() noexcept { return &this->subarray[0]; }

        void swap(array_view& av) noexcept { std::swap(this->subarray, av.subarray); }

        template <typename... UnknownDimSizes>
        void assign(cell *phys_addr, size_type dim_size, UnknownDimSizes&&... args) {
            subarray.reserve(dim_size);
            for (int i = 0; i < dim_size; i++)
                subarray.emplace_back(&phys_addr[i] + phys_addr[i]/sizeof(cell), args...);
        }

        bool operator==(const array_view& other) const { return std::equal(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator<(const array_view& other) const { return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator!=(const array_view& other) const { return !(*this == other); };
        bool operator<=(const array_view& other) const { return (*this < other) || (*this == other); };
        bool operator>(const array_view& other) const { return other < *this; };
        bool operator>=(const array_view& other) const { return !(*this < other) || (*this == other); };

    private:
        std::vector<value_type> subarray;
    };

    /* single dimension array of fixed size */
    template <typename T, std::size_t N>
    class array_view<T, N> : public array_view_interface<T> {
    public:
        using typename array_view_interface::value_type;
        using typename array_view_interface::reference;
        using typename array_view_interface::const_reference;
        using typename array_view_interface::pointer;
        using typename array_view_interface::const_pointer;
        using typename array_view_interface::iterator;
        using typename array_view_interface::const_iterator;
        using typename array_view_interface::reverse_iterator;
        using typename array_view_interface::const_reverse_iterator;
        using typename array_view_interface::size_type;
        using typename array_view_interface::difference_type;

        array_view() noexcept : mp_first{ nullptr } { }
        array_view(cell *phys_addr) noexcept : mp_first{ phys_addr } { }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        iterator begin() noexcept { return this->mp_first; }
        iterator end() noexcept { return this->mp_first + N; }
        const_iterator cbegin() const noexcept { return this->mp_first; }
        const_iterator cend() const noexcept { return this->mp_first + N; }
        const_iterator begin() const noexcept { return this->cbegin(); }
        const_iterator end() const noexcept { return this->cend(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(this->cend()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(this->cbegin()); }
        const_reverse_iterator rbegin() const noexcept { return this->crend(); }
        const_reverse_iterator rend() const noexcept { return this->crbegin(); }

        constexpr size_type size() const noexcept { return N; }

        const_reference operator[](difference_type index) const { return *(this->mp_first + index); }
        reference operator[](difference_type index) { return *(this->mp_first + index); }

        const_reference at(difference_type index) const {
            //throw a compile time error if possible?
            if (index >= this->size() || index < 0) {
                std::ostringstream err;
                err << "pawn::array_view::at >> 'index' (" << index << ") out of range (size = " << this->size() << ")" << std::endl;
                throw std::out_of_range(err.str());
            }
            return (*this)[index];
        }

        reference at(difference_type index) {
            if (index >= this->size() || index < 0) {
                std::ostringstream err;
                err << "pawn::array_view::at >> 'index' (" << index << ") out of range (size = " << this->size() << ")" << std::endl;
                throw std::out_of_range(err.str());
            }
            return (*this)[index];
        }

        const_pointer data() const noexcept { return this->mp_first; }
        pointer data() noexcept { return this->mp_first; }

        void swap(array_view& av) noexcept { std::swap(this->mp_first, av.mp_first); }
      
        void assign(cell *phys_addr) noexcept { this->mp_first = phys_addr; }

        bool operator==(const array_view& other) const { return std::equal(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator<(const array_view& other) const { return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator!=(const array_view& other) const { return !(*this == other); };
        bool operator<=(const array_view& other) const { return (*this < other) || (*this == other); };
        bool operator>(const array_view& other) const { return other < *this; };
        bool operator>=(const array_view& other) const { return !(*this < other) || (*this == other); };

    private:
        pointer mp_first;
    };

    /* single dimensional array of variable size */
    template <typename T>
    class array_view<T, 0> : public array_view_interface<T> {
    public:
        using typename array_view_interface::value_type;
        using typename array_view_interface::reference;
        using typename array_view_interface::const_reference;
        using typename array_view_interface::pointer;
        using typename array_view_interface::const_pointer;
        using typename array_view_interface::iterator;
        using typename array_view_interface::const_iterator;
        using typename array_view_interface::reverse_iterator;
        using typename array_view_interface::const_reverse_iterator;
        using typename array_view_interface::size_type;
        using typename array_view_interface::difference_type;

        array_view() noexcept : mp_first{ nullptr }, mp_last{ nullptr } { }
        array_view(cell *phys_addr, int size) noexcept : mp_first{ phys_addr }, mp_last{ phys_addr + size } { }
        array_view(cell *phys_addr_first, cell *phys_addr_end) noexcept : mp_first{ phys_addr_first }, mp_last{ phys_addr_end } { }

        array_view(const array_view& other) noexcept = default;
        array_view& operator=(const array_view& view) noexcept = default;

        iterator begin() noexcept { return this->mp_first; }
        iterator end() noexcept { return this->mp_last; }
        const_iterator cbegin() const noexcept { return this->mp_first; }
        const_iterator cend() const noexcept { return this->mp_last; }
        const_iterator begin() const noexcept { return this->cbegin(); }
        const_iterator end() const noexcept { return this->cend(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(this->end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(this->begin()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(this->cend()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(this->cbegin()); }
        const_reverse_iterator rbegin() const noexcept { return this->crend(); }
        const_reverse_iterator rend() const noexcept { return this->crbegin(); }

        size_type size() const noexcept { return this->cend() - this->cbegin(); }

        const_reference operator[](difference_type index) const { return *(this->mp_first + index); }
        reference operator[](difference_type index) { return *(this->mp_first + index); }

        const_reference at(difference_type index) const {
            //throw a compile time error if possible?
            if (index >= this->size() || index < 0) {
                std::ostringstream err;
                err << "pawn::array_view::at >> 'index' (" << index << ") out of range (size = " << this->size() << ")" << std::endl;
                throw std::out_of_range(err.str());
            }
            return (*this)[index];
        }

        reference at(difference_type index) {
            if (index >= this->size() || index < 0) {
                std::ostringstream err;
                err << "pawn::array_view::at >> 'index' (" << index << ") out of range (size = " << this->size() << ")" << std::endl;
                throw std::out_of_range(err.str());
            }
            return (*this)[index];
        }

        const_pointer data() const noexcept { return this->mp_first; }
        pointer data() noexcept { return this->mp_first; }

        void swap(array_view& av) noexcept
        {
            using std::swap;
            swap(this->mp_first, av.mp_first);
            swap(this->mp_last, av.mp_last);
        }

        void assign(cell *phys_addr, int size) {
            if (size < 0) { // TODO allow zero size?
                throw std::range_error("pawn::array_view::assign >> recieved negative size\n");
            }
            this->mp_first = phys_addr;
            this->mp_last = phys_addr + size;
        }

        void assign(cell *phys_addr_first, cell *phys_addr_last) {
            if (phys_addr_first > phys_addr_last) { // TODO allow zero size? 
                throw std::range_error("pawn::array_view::assign >> invalid range");
            }
            this->mp_first = phys_addr_first;
            this->mp_last = phys_addr_last;
        }

        bool operator==(const array_view& other) const { return std::equal(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator<(const array_view& other) const { return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end()); }
        bool operator!=(const array_view& other) const { return !(*this == other); };
        bool operator<=(const array_view& other) const { return (*this < other) || (*this == other); };
        bool operator>(const array_view& other) const { return other < *this; };
        bool operator>=(const array_view& other) const { return !(*this < other) || (*this == other); };

    private:
        pointer mp_first;
        pointer mp_last;
    };
};
#endif /* PAWN_ARRAY_VIEW_HPP */