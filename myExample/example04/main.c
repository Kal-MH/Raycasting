#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

#define EVENT_KEY_PRESS 2
#define EVENT_KEY_EXIT 17
#define KEY_ESC 53

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define IMG_WIDTH 400
#define IMG_HEIGHT 300

typedef struct	s_img {
	void	*img_ptr;
	int	*data;
	int	width;
	int	height;
	int	size_l;
	int	bpp;
	int	endian;
}		t_img;

typedef struct	s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
}		t_mlx;

int	key_press(int keycode, void * params)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	t_mlx	*mlx;
	int	count_w;
	int	count_h;
	t_img	img;

	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "my mlx");
	img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "../textures/wall_n.xpm", &img.width, &img.height);
	img.data = (int*)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

	//The reason why I cast to (int*), if I let this as void *type,
	//whenever I refer to the array values, I need to multiply them by 4.
	//Check keuhdall's github
	
	count_h = -1;
	while (++count_h < img.height)
	{
		count_w = -1;
		while (++count_w < img.width)
		{
			if (count_w % 2)
				img.data[count_h * img.width + count_w] = 0xFFFFFF;
			else
				img.data[count_h * img.width + count_w] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, EVENT_KEY_PRESS, 0, &key_press, (void*)0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
