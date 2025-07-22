#include "fdf.h"



void rotate_screen_coordinates(t_point **points, int rows, int cols, float angle_deg, int pivot_x, int pivot_y)
{
	float rad = angle_deg * 3.14 / 180.0f;
    float cos_a = cosf(rad);
    float sin_a = sinf(rad);
	
    for (int i = 0; i < rows; i++)
    {
		for (int j = 0; j < cols; j++)
        {
			int x = points[i][j].screen_x - pivot_x;
            int y = points[i][j].screen_y - pivot_y;
			
            int rotated_x = (int)(x * cos_a - y * sin_a);
            int rotated_y = (int)(x * sin_a + y * cos_a);
			
            points[i][j].screen_x = rotated_x + pivot_x;
            points[i][j].screen_y = rotated_y + pivot_y;
        }
    }
}


int handle_key(int keycode, t_vars *vars)
{
	static float angle = 0;
	
    if (keycode == 65307)
	exit(0);
    else if (keycode == 'w' || keycode == 119)
	vars->scale += 2;
    else if ((keycode == 's' || keycode == 115) && vars->scale > 2)
	vars->scale -= 2;
    else if (keycode == 65363) // Sol
	vars->offset_x -= 20;
    else if (keycode == 65361) // Sağ
	vars->offset_x += 20;
    else if (keycode == 65364) // Yukarı
	vars->offset_y -= 20;
    else if (keycode == 65362) // Aşağı
	vars->offset_y += 20;
    else if (keycode == 'a' || keycode == 97) // A tuşu - saat yönü
	vars->rotation_angle -= 5;
    else if (keycode == 'd' || keycode == 100) // D tuşu - saatin tersi
        vars->rotation_angle += 5;
		
	mlx_clear_window(vars->mlx, vars->win);
    apply_isometric_projection(vars->points, vars->row, vars->col, vars->offset_x, vars->offset_y, vars->scale);
	rotate_screen_coordinates(vars->points, vars->row, vars->col, vars->rotation_angle, vars->offset_x, vars->offset_y);
    draw_map(vars->mlx, vars->win, vars->points, vars->row, vars->col);
    return (0);
}

int handle_expose(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	apply_isometric_projection(vars->points, vars->row, vars->col, vars->offset_x, vars->offset_y, vars->scale);
	rotate_screen_coordinates(vars->points, vars->row, vars->col, vars->rotation_angle, vars->offset_x, vars->offset_y);
	draw_map(vars->mlx, vars->win, vars->points, vars->row, vars->col);
	return (0);
}