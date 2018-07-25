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

        pawn::array_view<cell, 0> arr(phys_addr, params[2]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
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

        pawn::array_view<cell, 256> arr(phys_addr);        
        assert(arr.size() == 256);

        for (int i = 0; i < arr.size(); i++) {
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

        pawn::array_view<cell, 0, 0> arr(phys_addr, params[2], params[3]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[3]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
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

        pawn::array_view<cell, 0, 128> arr(phys_addr, params[2]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == 128);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
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

        pawn::array_view<cell, 256, 128> arr(phys_addr);
        assert(arr.size() == 256);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == 128);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
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

        pawn::array_view<cell, 64, 0> arr(phys_addr, params[2]);
        assert(arr.size() == 64);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[2]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
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

        pawn::array_view<cell, 0, 0, 0> arr(phys_addr, params[2], params[3], params[4]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[3]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == params[4]);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 0, 0, 128> arr(phys_addr, params[2], params[3]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[3]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == 128);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 0, 128, 0> arr(phys_addr, params[2], params[3]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == 128);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == params[3]);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 0, 64, 96> arr(phys_addr, params[2]);
        assert(arr.size() == params[2]);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == 64);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == 96);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 16, 0, 0> arr(phys_addr, params[2], params[3]);
        assert(arr.size() == 16);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[2]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == params[3]);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 16, 0, 48> arr(phys_addr, params[2]);
        assert(arr.size() == 16);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == params[2]);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == 48);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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

        pawn::array_view<cell, 20, 30, 50> arr(phys_addr);
        assert(arr.size() == 20);
        for (int i = 0; i < arr.size(); i++) {
            assert(arr[i].size() == 30);
            cell *subaddr = &phys_addr[i] + phys_addr[i]/sizeof(cell);
            for (int j = 0; j < arr[i].size(); j++) {
                assert(arr[i][j].size() == 50);
                cell *subsubaddr = &subaddr[j] + subaddr[j]/sizeof(cell);
                for (int k = 0; k < arr[i][j].size(); k++) {
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
        pawn::array_view<cell, 20, 30, 50> arr1(phys_addr, 0);
        pawn::array_view<cell, 20, 30, 0> arr2(phys_addr);
        pawn::array_view<cell, 20, 30, 0> arr3(phys_addr, std::vector<int>());
	    return 1;
    }
#endif
}