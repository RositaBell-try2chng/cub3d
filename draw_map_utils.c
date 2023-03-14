#include "cub.h"

char	check_border_minimap(t_main *M, int p, int c, int flg)
{
	int	res;
	int	dop;

	res = p - M_HALF + c;
	if (flg == -1)
	{
		if (res < 0 || res / 32 >= M->map_H)
			return (1);
		return (0);
	}
	dop = M->pl->y - M_HALF + flg;
	if (res < 0 || (res) / 32 >= M->map_W[dop / 32])
		return (1);
	return (0);
}

