#include <stdio.h>
#include "mlx.h"

int main()
{
	void *mlx = NULL;
	void *win = NULL;
	/* int x = 0; */
	/* int y = 0; */

	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "cub3d");
	mlx_loop(mlx);
}
