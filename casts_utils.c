#include "cub.h"

char	check_correct(t_main *M, double x, double y, char *flg)
{
	if ((int)y < 0 || (int)y / 32 >= M->map_H ||
		(int)x < 0 || (int)x / 32 >= M->map_W[(int)y / 32])
	{
		*flg = 0;
		return (0);
	}
	return (1);
}

char	check_wall(t_main *M, double x, double y)
{
	if (M->map[(int)y / 32][(int)x / 32] == '1')
		return (1);
	return (0);
}