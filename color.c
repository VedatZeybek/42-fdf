#include "fdf.h"

int get_color(int z)
{
	if (z <= 0)
		return 0x1E90FF;
	else if (z > 0 && z <= 5)
		return 0x00FF00;
	else if (z > 5 && z <= 15)
		return 0xFFFF00;
	else if (z > 15 && z <= 30)
		return 0xFFA500;
	else
		return 0xFF0000;
}

int get_color_component(int color, int index)
{
	if (index == 0) // RED
		return (color >> 16) & 0xFF;
	else if (index == 1) // GREEN
		return (color >> 8) & 0xFF;
	else if (index == 2) // BLUE
		return color & 0xFF;
	return (0);
}


int interpolate(int start, int end, float t)
{
	return (int)(start + (end - start) * t);
}

int get_gradient_color(int color_start, int color_end, float t)
{
	int r = interpolate(get_color_component(color_start, 0), get_color_component(color_end, 0), t);
	int g = interpolate(get_color_component(color_start, 1), get_color_component(color_end, 1), t);
	int b = interpolate(get_color_component(color_start, 2), get_color_component(color_end, 2), t);

	return (r << 16) | (g << 8) | b;
}

