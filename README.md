# Pawn Array View

Pawn Array View (PAV) library is a C++ wrapper for Pawn arrays. This abstracts the details of how the Pawn arrays are stored in memory and provides a intutive C/++ like interface for dealing with them.

## Installing

1. include `array_view.hpp` to use PAV

## Structures

```
template <typename T, std::size_t dims>
class pawn::array_view<T, dims>;
```

The `pawn::array_view` takes two template parameters: type of the values in the array (`T`) and the number of dimensions (`dims`).

### Constructors

`pawn::array_view() noexcept;`

`pawn::array_view(cell *phys_addr) noexcept;`  

The `phys_addr` parameter takes the address of the indirection table (begining of the multidimensional array). In case of single dimensional arrays, it takes the address to the begining of the array data.

### Member types

member type |
----------- |
value_type  |
reference   |
const_reference |
pointer         |
const_pointer   |
size_type       |
difference_type |

### Member functions


member function | description
--------------- | ----------------------------        
operator=       | point to the same array as RHS
operator\[\]    | access array elements or subarray 
swap            | swap objects
assign          | assign the array to wrap around       

### Example
```pawn
//native test_function(arr[][], sz_major = sizeof(arr), sz_minor = sizeof(arr[]));
cell AMX_NATIVE_CALL test_cell_0_0(AMX* amx, cell* params)
{
    cell *phys_addr;
    amx_GetAddr(amx, params[1], &phys_addr);
    assert(phys_addr != NULL);

    pawn::array_view<cell, 2> arr(phys_addr);
    for (int i = 0; i < params[2]; i++) {
        for (int j = 0; j < params[3]; j++) {
            logprintf("%d\n", arr[i][j]);
        }
    }
	  return 1;
}
 ```

