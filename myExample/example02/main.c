#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

#define EVENT_KEY_PRESS 2
#define EVENT_KEY_EXIT 17
#define KEY_ESC 53

int	key_press(int keycode, void * params)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	void	*img;

	int	img_width;
	int	img_height;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "my_mlx");
	img = mlx_xpm_file_to_image(mlx, "../textures/wall_n.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx, win, img, 50, 50);
	printf("width : %d, height : %d\n", img_width, img_height);
	mlx_hook(win, EVENT_KEY_PRESS, 0, &key_press, (void*)0);
	mlx_loop(mlx);
	return (0);
}
