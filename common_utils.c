#include "cub.h"

char	get_map_char(char **map, double y, double x)
{
	int		m_x;
	int		m_y;

	m_y = (int)(y / 32);
	m_x = (int)(x / 32);
	return (map[m_y][m_x]);
}