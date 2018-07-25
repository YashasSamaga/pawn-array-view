#pragma dynamic 100000000

#include <sample>

native random(max);

main () {
	new arr1[512];
	for(new i = 0; i < sizeof(arr1); i++)
	    arr1[i] = random(cellmax);
	    
 	new arr2[256];
 	for(new i = 0; i < sizeof(arr2); i++)
	    arr2[i] = random(cellmax);
	    
 	new arr3[123][234];
 	for(new i = 0; i < sizeof(arr3); i++)
 	    for(new j = 0; j < sizeof(arr3[]); j++)
	    	arr3[i][j] = random(cellmax);
	    
 	new arr4[64][128];
 	for(new i = 0; i < sizeof(arr4); i++)
 	    for(new j = 0; j < sizeof(arr4[]); j++)
	    	arr4[i][j] = random(cellmax);
	    	
 	new arr5[256][128];
 	for(new i = 0; i < sizeof(arr5); i++)
 	    for(new j = 0; j < sizeof(arr5[]); j++)
	    	arr5[i][j] = random(cellmax);
	    	
	new arr6[64][123];
	for(new i = 0; i < sizeof(arr6); i++)
 	    for(new j = 0; j < sizeof(arr6[]); j++)
	    	arr6[i][j] = random(cellmax);
	    	
	new arr7[2][2][2];
	for(new i = 0; i < sizeof(arr7); i++)
 	    for(new j = 0; j < sizeof(arr7[]); j++)
 	        for(new k = 0; k < sizeof(arr7[][]); k++)
	    		arr7[i][j][k] = random(cellmax);
	    		
	new arr8[25][25][128];
	for(new i = 0; i < sizeof(arr8); i++)
 	    for(new j = 0; j < sizeof(arr8[]); j++)
 	        for(new k = 0; k < sizeof(arr8[][]); k++)
	    		arr8[i][j][k] = random(cellmax);
	    		
	new arr9[30][128][10];
	for(new i = 0; i < sizeof(arr9); i++)
 	    for(new j = 0; j < sizeof(arr9[]); j++)
 	        for(new k = 0; k < sizeof(arr9[][]); k++)
	    		arr9[i][j][k] = random(cellmax);
	    		
	new arr10[10][64][96];
	for(new i = 0; i < sizeof(arr10); i++)
 	    for(new j = 0; j < sizeof(arr10[]); j++)
 	        for(new k = 0; k < sizeof(arr10[][]); k++)
	    		arr10[i][j][k] = random(cellmax);
	    		
	new arr11[16][5][5];
	for(new i = 0; i < sizeof(arr11); i++)
 	    for(new j = 0; j < sizeof(arr11[]); j++)
 	        for(new k = 0; k < sizeof(arr11[][]); k++)
	    		arr11[i][j][k] = random(cellmax);
	    		
	new arr12[16][5][48];
	for(new i = 0; i < sizeof(arr12); i++)
 	    for(new j = 0; j < sizeof(arr12[]); j++)
 	        for(new k = 0; k < sizeof(arr12[][]); k++)
	    		arr12[i][j][k] = random(cellmax);
	    		
	new arr13[20][30][50];
	for(new i = 0; i < sizeof(arr13); i++)
 	    for(new j = 0; j < sizeof(arr13[]); j++)
 	        for(new k = 0; k < sizeof(arr13[][]); k++)
	    		arr13[i][j][k] = random(cellmax);
	    		
	test_cell_0(arr1);
	test_cell_256(arr2);
    test_cell_0_0(arr3);
    test_cell_0_128(arr4);
    test_cell_256_128(arr5);
    test_cell_64_0(arr6);
    test_cell_0_0_0(arr7);
    test_cell_0_0_128(arr8);
    test_cell_0_128_0(arr9);
    test_cell_0_64_96(arr10);
    test_cell_16_0_0(arr11);
    test_cell_16_0_48(arr12);
    test_cell_20_30_50(arr13);
    
}