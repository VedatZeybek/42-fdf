#include "fdf.h"

void rotate_screen_coordinates(t_fdf *fdf)
{
	float rad = fdf->rotation_angle * 3.14 / 180.0f;
    float cos_a = cosf(rad);
    float sin_a = sinf(rad);
	
    for (int i = 0; i < fdf->row; i++)
    {
		for (int j = 0; j < fdf->col; j++)
        {
			int x = fdf->points[i][j].screen_x - fdf->offset_x;
            int y = fdf->points[i][j].screen_y - fdf->offset_y;
			
            int rotated_x = (int)(x * cos_a - y * sin_a);
            int rotated_y = (int)(x * sin_a + y * cos_a);
			
            fdf->points[i][j].screen_x = rotated_x + fdf->offset_x;
            fdf->points[i][j].screen_y = rotated_y + fdf->offset_y;
        }
    }
}


int handle_key(int keycode, t_fdf *fdf)
{
	static float angle = 0;
	
    if (keycode == 65307)
	exit(0);
    else if (keycode == 'w' || keycode == 119)
	fdf->scale += 1;
    else if ((keycode == 's' || keycode == 115) && (fdf->scale > 7))
	fdf->scale -= 1;
    else if (keycode == 65363) // Sol
	fdf->offset_x -= 20;
    else if (keycode == 65361) // Sağ
	fdf->offset_x += 20;
    else if (keycode == 65364) // Yukarı
	fdf->offset_y -= 20;
    else if (keycode == 65362) // Aşağı
	fdf->offset_y += 20;
    else if (keycode == 'a' || keycode == 97) // A tuşu - saat yönü
	fdf->rotation_angle -= 5;
    else if (keycode == 'd' || keycode == 100) // D tuşu - saatin tersi
        fdf->rotation_angle += 5;
		
	mlx_clear_window(fdf->mlx, fdf->win);
    apply_isometric_projection(fdf);
	rotate_screen_coordinates(fdf);
    draw_map(fdf);
    return (0);
}

int handle_expose(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
    apply_isometric_projection(fdf);
	rotate_screen_coordinates(fdf);
    draw_map(fdf);
	return (0);
}