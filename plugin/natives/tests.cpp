#include "main.h"
#include <pawn/array_view.hpp>

#include <cassert>

namespace sample::natives {
    //native test_cell_0(arr[], sz = sizeof(arr));
    cell AMX_NATIVE_CALL test_cell_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 1> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            assert(arr[i] == phys_addr[i]);
        }
	    return 1;
    }

    //native test_cell_256(arr[256]);
    cell AMX_NATIVE_CALL test_cell_256(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 1> arr(phys_addr);
        for (int i = 0; i < 256; i++) {
            assert(arr[i] == phys_addr[i]);
        }
	    return 1;
    }

    //native test_cell_0_0(arr[][], sz_major = sizeof(arr), sz_minor = sizeof(arr[]));
    cell AMX_NATIVE_CALL test_cell_0_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 2> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < params[3]; j++) {
                assert(arr[i][j] == subaddr[j]);
            }
        }
	    return 1;
    }

    //native test_cell_0_128(arr[][128], sz_major = sizeof(arr));
    cell AMX_NATIVE_CALL test_cell_0_128(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 2> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 128; j++) {
                assert(arr[i][j] == subaddr[j]);
            }
        }
	    return 1;
    }

    //native test_cell_256_128(arr[256][128]);
    cell AMX_NATIVE_CALL test_cell_256_128(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 2> arr(phys_addr);
        for (int i = 0; i < 256; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 128; j++) {
                assert(arr[i][j] == subaddr[j]);
            }
        }
	    return 1;
    }

    //native test_cell_64_0(arr[64][], sz_minor = sizeof(arr[]));
    cell AMX_NATIVE_CALL test_cell_64_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 2> arr(phys_addr);
        for (int i = 0; i < 64; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 64; j++) {
                assert(arr[i][j] == subaddr[j]);
            }
        }
	    return 1;
    }

    //native test_cell_0_0_0(arr[][][], sz_major = sizeof(arr), sz_middle = sizeof(arr[]), sz_minor = sizeof(arr[][]));
    cell AMX_NATIVE_CALL test_cell_0_0_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < params[3]; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < params[4]; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_0_0_128(arr[][][128], sz_major = sizeof(arr), sz_middle = sizeof(arr[]));
    cell AMX_NATIVE_CALL test_cell_0_0_128(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < params[3]; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < 128; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_0_128_0(arr[][128][], sz_major = sizeof(arr), sz_minor = sizeof(arr[][]));
    cell AMX_NATIVE_CALL test_cell_0_128_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 128; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < params[3]; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_0_64_96(arr[][64][96], sz_major = sizeof(arr));
    cell AMX_NATIVE_CALL test_cell_0_64_96(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < params[2]; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 64; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < 96; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_16_0_0(arr[16][][], sz_middle = sizeof(arr[]), sz_minor = sizeof(arr[][]));
    cell AMX_NATIVE_CALL test_cell_16_0_0(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < 16; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < params[2]; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < params[3]; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_16_0_48(arr[16][][48], sz_middle = sizeof(arr[]));
    cell AMX_NATIVE_CALL test_cell_16_0_48(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < 16; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < params[2]; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < 48; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

    //native test_cell_20_30_50(arr[20][30][50]);
    cell AMX_NATIVE_CALL test_cell_20_30_50(AMX* amx, cell* params)
    {
        cell *phys_addr;
        amx_GetAddr(amx, params[1], &phys_addr);
        assert(phys_addr != NULL);

        pawn::array_view<cell, 3> arr(phys_addr);
        for (int i = 0; i < 20; i++) {
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < 30; j++) {
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < 50; k++) {
                    assert(arr[i][j][k] == subsubaddr[k]);
                }
            }
        }
	    return 1;
    }

#ifdef RUN_NEGATIVE_TESTS
    cell AMX_NATIVE_CALL test_cell_neg_tests(AMX* amx, cell* params)
    {
        cell *phys_addr;
        pawn::array_view<cell, 0> arr1(phys_addr, 0);
	    return 1;
    }
#endif
}