#include <stdlib.h>
#include <stdio.h>

//workgroupsize --> RED

int main()
{

	int i,j;
	int local_size_x = 16;
	int local_size_y = 16;

	int shift = 6;

	int global_size_x = local_size_x + shift;
	int global_size_y = local_size_y + shift;	

	int shared_mem[(local_size_x + 2*shift)* (local_size_y + 2*shift)];
	int global_mem[global_size_x][global_size_y];


	//Creating
	for(i=0; i < local_size_x + 2*shift; i++)
	{
		for(j = 0; j < local_size_y + 2*shift; j++)
		{
			global_mem[i][j] = j + i*(local_size_y + 2*shift);
			printf("%d\t",global_mem[i][j]);
		}

		printf("\n");
	}

	//workgroup 
	int loc_x;
	int loc_y;
	int local_tmp_id;

	int global_id_x;
	int global_id_y;
	printf("\n");

	for(loc_y = 0; loc_y < local_size_y;loc_y++)
	{
		global_id_y = loc_y;

		for(loc_x=0; loc_x < local_size_x; loc_x++)
		{
			global_id_x = loc_x;

			if(global_id_x >= shift && global_id_y >= shift)
			{
				shared_mem[loc_x + loc_y*global_size_x] = global_mem[loc_y+shift][loc_x+shift];
				printf("%d\t",shared_mem[loc_x + loc_y*global_size_x]);

				//left
				if(loc_x <= shift)
				{
					int loc_tmp_id = (shift + loc_y)*local_size_x + loc_x;
					shared_mem[loc_tmp_id] = global_mem[global_id_x - shift][global_id_y];
					printf("%d\t",shared_mem[loc_tmp_id]);
				}	

			}
		}
		printf("\n");
	}



}

