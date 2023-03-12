#include "cub.h"

char	check_correct(t_main *M, double x, double y, char *flg)
{
	if ((int)y < 0 || (int)y / 32 >= M->map_H || \
		(int)x < 0 || (int)x / 32 >= M->map_W[(int)y / 32])
	{
		*flg = 0;
		return (0);
	}
	return (1);
}

char	check_wall(t_main *M, double x, double y)
{
	if (get_map_char(M->map, y, x) == '1')
		return (1);
	return (0);
}