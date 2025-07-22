#include "fdf.h"

int get_color(int z)
{
	if (z <= 0)
		return 0x1E90FF; // deniz mavisi
	else if (z > 0 && z <= 5)
		return 0x00FF00; // yeşil
	else if (z > 5 && z <= 15)
		return 0xFFFF00; // sarı
	else if (z > 15 && z <= 30)
		return 0xFFA500; // turuncu
	else
		return 0xFF0000; // kırmızı
}

int get_red(int color)    { return (color >> 16) & 0xFF; }
int get_green(int color)  { return (color >> 8) & 0xFF; }
int get_blue(int color)   { return color & 0xFF; }

int interpolate(int start, int end, float t)
{
	return (int)(start + (end - start) * t);
}

int get_gradient_color(int color_start, int color_end, float t)
{
	int r = interpolate(get_red(color_start), get_red(color_end), t);
	int g = interpolate(get_green(color_start), get_green(color_end), t);
	int b = interpolate(get_blue(color_start), get_blue(color_end), t);
	return (r << 16) | (g << 8) | b;
}
