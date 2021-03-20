void fill_header(t_all *all)
{
        all->header.res = 0;
        all->header.no = 0;
        all->header.so = 0;
        all->header.we = 0;
        all->header.ea = 0;
        all->header.s = 0;
        all->header.f = 0;
        all->header.c = 0;
}

int strs_len(char **strs)
{
        int len;

        len = 0;
        if (strs != 0)
                while (strs[len] != 0)
                        len++;
        return (len);
}

void free_strs(char **strs)
{
        int i;

        i = 0;
        while (strs[i] != 0)
        {
                free(strs[i]);
                i++;
        }
        free(strs[i]);
        free(strs);
}

int check_header_dublicates(t_all all)
{
        if (all.header.res > 1)
                return (0);
        if (all.header.no > 1)
                return (0);
        if (all.header.so > 1)
                return (0);
        if (all.header.we > 1)
                return (0);
        if (all.header.ea > 1)
                return (0);
        if (all.header.s > 1)
                return (0);
        if (all.header.f > 1)
                return (0);
        if (all.header.c > 1)
                return (0);
        return (1);
}

char *check_header(t_all all)
{
        if (all.header.res != 1)
                return (CONF);
        if (all.header.no != 1)
                return (CONF);
        if (all.header.so != 1)
                return (CONF);
        if (all.header.we != 1)
                return (CONF);
        if (all.header.ea != 1)
                return (CONF);
        if (all.header.s != 1)
                return (CONF);
        if (all.header.f != 1)
                return (CONF);
        if (all.header.c != 1)
                return (CONF);
        return ("1");
}

char *check_fill_res(int i, t_all *all)
{
        int j;
        char **strs;
        int resx;
        int resy;

        j = 0;
        while (all->map[i][++j] != 0)
                if ((all->map[i][j] < '0' || all->map[i][j] > '9') && all->map[i][j] != ' ')
                        return (RES);
        j = 0;
        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 3)
                return (RES);
        all->width = ft_atoi(strs[1]);
        all->height = ft_atoi(strs[2]);
        mlx_get_screen_size(all->win.mlx, &resx, &resy);
        if (all->width > resx)
                all->width = resx;
        if (all->height > resy)
                all->height = resy;
        if (all->width <= 0 || all->height <= 0)
                return (RES);
        free_strs(strs);
        all->header.res++;
        return ("1");
}

char *check_fill_no(int i, t_all *all)
{
        char **strs;
        int fd;

        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 2)
                return (NO);
        if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
                return (NO);
        all->image_n.path = ft_strdup(strs[1]);
        fd = open(all->image_n.path, O_RDONLY);
        if (fd == -1)
                return (PATH_NO);
        close (fd);
        if (all->image_n.path == NULL)
                return (NO);
        free_strs(strs);
        all->header.no++;
        close(fd);
        return ("1");
}

char *check_fill_so(int i, t_all *all)
{
        char **strs;
        int fd;

        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 2)
                return (SO);
        if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
                return (SO);
        all->image_s.path = ft_strdup(strs[1]);
        fd = open(all->image_s.path, O_RDONLY);
        if (fd == -1)
                return (PATH_SO);
        close (fd);
        if (all->image_s.path == NULL)
                return (SO);
        free_strs(strs);
        all->header.so++;
        close(fd);
        return ("1");
}

char *check_fill_we(int i, t_all *all)
{
        char **strs;
        int fd;

        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 2)
                return (WE);
        if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
                return (WE);
        all->image_w.path = ft_strdup(strs[1]);
        fd = open(all->image_w.path, O_RDONLY);
        if (fd == -1)
                return (PATH_WE);
        close (fd);
        if (all->image_w.path == NULL)
                return (WE);
        free_strs(strs);
        all->header.we++;
        close(fd);
        return ("1");
}

char *check_fill_ea(int i, t_all *all)
{
        char **strs;
        int fd;

        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 2)
                return (EA);
        if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
                return (EA);
        all->image_e.path = ft_strdup(strs[1]);
        fd = open(all->image_e.path, O_RDONLY);
        if (fd == -1)
                return (PATH_EA);
        close (fd);
        if (all->image_e.path == NULL)
                return (EA);
        free_strs(strs);
        all->header.ea++;
        close(fd);
        return ("1");
}

char *check_fill_s(int i, t_all *all)
{
        char **strs;
        int fd;

        strs = ft_split(all->map[i], ' ');
        if (strs_len(strs) != 2)
                return (S);
        if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
                return (S);
        all->sprite.path = ft_strdup(strs[1]);
        fd = open(all->sprite.path, O_RDONLY);
        if (fd == -1)
                return (PATH_S);
        close (fd);
        if (all->sprite.path == NULL)
                return (S);
        free_strs(strs);
        all->header.s++;
        close(fd);
        return ("1");
}

int check_one_num(char *str)
{
        char **strs;
        int num;

        strs = ft_split(str, ' ');
        if (strs_len(strs) != 1)
                return (-1);
        num = ft_atoi(strs[0]);
        free_strs(strs);
        return (num);
}

char *check_fill_f(int i, t_all *all)
{
        char **strs;
        char *str;
        int r;
        int g;
        int b;

        r = 0;
        while (all->map[i][++r] != 0)
                if ((all->map[i][r] < '0' || all->map[i][r] > '9') && all->map[i][r] != ' ' && all->map[i][r] != ',')
                        return (FLOOR);
        str = all->map[i] + 1;
        strs = ft_split(str, ',');
        if (strs_len(strs) != 3)
                return (FLOOR);
        r = check_one_num(strs[0]);
        g = check_one_num(strs[1]);
        b = check_one_num(strs[2]);
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                return (FLOOR);
        all->floor_color = create_trgb(0, r, g, b);
        free_strs(strs);
        all->header.f++;
        return ("1");
}

char *check_fill_c(int i, t_all *all)
{
        char **strs;
        char *str;
        int r;
        int g;
        int b;

        r = 0;
        while (all->map[i][++r] != 0)
                if ((all->map[i][r] < '0' || all->map[i][r] > '9') && all->map[i][r] != ' ' && all->map[i][r] != ',')
                        return (CEIL);
        str = all->map[i] + 1;
        strs = ft_split(str, ',');
        if (strs_len(strs) != 3)
                return (CEIL);
        r = check_one_num(strs[0]);
        g = check_one_num(strs[1]);
        b = check_one_num(strs[2]);
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                return (CEIL);
        all->ceil_color = create_trgb(0, r, g, b);
        free_strs(strs);
        all->header.c++;
        return ("1");
}

char *check_circuit(int i, int end, t_all all)
{
        int j;
        int start;

        j = 0;
        start = i;
        while (all.map[i] != 0)
        {
                j = 0;
                while (all.map[i][j] != 0)
                {
                        if (all.map[i][j] == '0' || all.map[i][j] == '2' || all.map[i][j] == 'N' || all.map[i][j] == 'W' || all.map[i][j] == 'S' || all.map[i][j] == 'E')
                        {
                                if ((i == start) || (j == 0) || (j > (int)ft_strlen(all.map[i - 1])) || all.map[i - 1][j - 1] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 1) || all.map[i - 1][j] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 2) || all.map[i - 1][j + 1] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((j > (int)ft_strlen(all.map[i]) - 2) || all.map[i][j + 1] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 2) || all.map[i + 1][j + 1] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 1) || all.map[i + 1][j] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((i == end) || (j == 0) || (j > (int)ft_strlen(all.map[i + 1])) || all.map[i + 1][j - 1] == ' ')
                                        return (BAD_CIRCUIT);
                                if ((j == 0) || (j > (int)ft_strlen(all.map[i])) || all.map[i][j - 1] == ' ')
                                        return (BAD_CIRCUIT);
                        }
                        j++;
                }
                i++;
        }
        return ("1");
}

char *check_player(int i, t_all all)
{
        int j;
        int count;

        count = 0;
        j = 0;
        while (all.map[i] != 0)
        {
                j = 0;
                while (all.map[i][j] != 0)
                {
                        if (all.map[i][j] == 'N' || all.map[i][j] == 'W' || all.map[i][j] == 'S' || all.map[i][j] == 'E')
                                count++;
                        j++;
                }
                i++;
        }
        if (count != 1)
                return (PLAYER);
        return ("1");
}

char *check_symbols(int i, t_all all)
{
        int j;
        int temp_i;

        temp_i = i;
        j = 0;
        while (all.map[i] != 0)
        {
                j = 0;
                if (ft_strlen(all.map[i]) == 0)
                        return (MAP_EMPTY_LINE);
                while (all.map[i][j])
                {
                        if (all.map[i][j] != ' ' && all.map[i][j] != '1' && all.map[i][j] != '0' && all.map[i][j] != 'N' && all.map[i][j] != 'W' && all.map[i][j] != 'S' && all.map[i][j] != 'E' && all.map[i][j] != '2')
                                return (MAP_WRONG_SYMBOLS);
                        j++;
                }
                i++;
        }
        if (check_circuit(temp_i, i - 1, all)[0] != '1')
                return (BAD_CIRCUIT);
        return ("1");
}

char *check_map(int i, t_all all)
{
        if (check_player(i, all)[0] != '1')
                return (check_player(i, all));
        if (check_symbols(i, all)[0] != '1')
                return (check_symbols(i, all));
        return ("1");
}

char *check_ident(int *i, t_all *all)
{
        char *answer;

        if (ft_strlen(all->map[*i]) == 0)
                return ("1");
        else if (ft_strncmp(all->map[*i], "R ", 2) == 0)
                answer = check_fill_res(*i, all);
        else if (ft_strncmp(all->map[*i], "NO ", 3) == 0)
                answer = check_fill_no(*i, all);
        else if (ft_strncmp(all->map[*i], "SO ", 3) == 0)
                answer = check_fill_so(*i, all);
        else if (ft_strncmp(all->map[*i], "WE ", 3) == 0)
                answer = check_fill_we(*i, all);
        else if (ft_strncmp(all->map[*i], "EA ", 3) == 0)
                answer = check_fill_ea(*i, all);
        else if (ft_strncmp(all->map[*i], "S ", 2) == 0)
                answer = check_fill_s(*i, all);
        else if (ft_strncmp(all->map[*i], "F ", 2) == 0)
                answer = check_fill_f(*i, all);
        else if (ft_strncmp(all->map[*i], "C ", 2) == 0)
                answer = check_fill_c(*i, all);
        else
                return ("0");
        if (answer[0] != '1')
                return (answer);
        return ("1");
}

int check_empty_line(int i, t_all all)
{
        int j;

        j = 0;
        while (all.map[i][j])
        {
                if (all.map[i][j] != ' ')
                        return (1);
                j++;
        }
        return (0);
}

int check_line(int i, t_all all)
{
        int j;

        j = 0;
        while (all.map[i][j] != 0)
        {
                if (all.map[i][j] != ' ' && all.map[i][j] != '1' && all.map[i][j] != '0' && all.map[i][j] != 'N' && all.map[i][j] != 'W' && all.map[i][j] != 'S' && all.map[i][j] != 'E' && all.map[i][j] != '2')
                        return (0);
                j++;
        }
        return (1);
}

char *check_cub(t_all *all)
{
        int i;

        fill_header(all);
        i = 0;
        if (all->map[i] == 0)
                return (EMPTY_FILE);
        while (check_ident(&i, all)[0] == '1')
        {
                if (all->map[i] == 0)
                        break;
                i++;
        }
        if (all->map[i] == 0 && check_header(*all)[0] != '1') // нет карты, но что-то с количеством идентификаторов
                return (check_header(*all));
        if (check_ident(&i, all)[0] == '1') // с идентификаторами все норм, но нет карты
                return (NO_MAP);
        if (check_empty_line(i, *all) == 0) // строка из пробелов
                return (WRONG_LINE);
        if (check_ident(&i, all)[0] != '0' && check_ident(&i, all)[0] != '1') // ошибка идентификатора
                return (check_ident(&i, all));
        if (check_ident(&i, all)[0] == '0' && check_header_dublicates(*all) == 1 && check_header(*all)[0] != '1' && check_line(i, *all) == 0) // рандом строка, в идентификаторах нет дубликатов и они не все есть
                return (WRONG_LINE);
        if (check_header(*all)[0] != '1') //
                return (check_header(*all));
        if (check_map(i, *all)[0] != '1') // чекаю карту
                return (check_map(i, *all));
        return ("1");
}

int main(int argc, char **argv)
{
        t_all   all;
        int fd;
        char *checker;

        if (argc == 1)
        {
                printf("Error\nMap not specified");
                return (0);
        }
        if (argc > 3)
        {
                printf("Error\nMore than 2 arguments");
                return (0);
        }
        fd = open(argv[1], O_RDONLY);
        all.map = parcer(fd);
        all.win.mlx = mlx_init();
        checker = check_cub(&all);
        if (checker[0] != '1')
        {
                close(fd);
                printf("Error\n%s", checker);
                return (0);
        }
        else
                printf("Всё норм, не забудь убрать!\n");

        all.win.win = mlx_new_window(all.win.mlx, all.width, all.height, "cub3d");
        all.win.img = mlx_new_image(all.win.mlx, all.width, all.height);
        all.win.addr = mlx_get_data_addr(all.win.img, &all.win.bpp, &all.win.line_len, &all.win.end);

        all.image_e.img = mlx_xpm_file_to_image(all.win.mlx, all.image_e.path, &all.image_e.img_width, &all.image_e.img_height);
        all.image_e.addr = mlx_get_data_addr(all.image_e.img, &all.image_e.bpp, &all.image_e.line_len, &all.image_e.end);

        all.image_s.img = mlx_xpm_file_to_image(all.win.mlx, all.image_s.path, &all.image_s.img_width, &all.image_s.img_height);
        all.image_s.addr = mlx_get_data_addr(all.image_s.img, &all.image_s.bpp, &all.image_s.line_len, &all.image_s.end);

        all.image_n.img = mlx_xpm_file_to_image(all.win.mlx, all.image_n.path, &all.image_n.img_width, &all.image_n.img_height);
        all.image_n.addr = mlx_get_data_addr(all.image_n.img, &all.image_n.bpp, &all.image_n.line_len, &all.image_n.end);

        all.image_w.img = mlx_xpm_file_to_image(all.win.mlx, all.image_w.path, &all.image_w.img_width, &all.image_w.img_height);
        all.image_w.addr = mlx_get_data_addr(all.image_w.img, &all.image_w.bpp, &all.image_w.line_len, &all.image_w.end);

        all.sprite.img = mlx_xpm_file_to_image(all.win.mlx, all.sprite.path, &all.sprite.img_width, &all.sprite.img_height);
        all.sprite.addr = mlx_get_data_addr(all.sprite.img, &all.sprite.bpp, &all.sprite.line_len, &all.sprite.end);
        fill_map_on_screen(&all);
        cast_ray(&all);
        mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.img, 0, 0);
        if ((argc == 3) && ft_strncmp(argv[2], "--save", 7) == 0)
        {
                close(fd);
                screenshot(all);
                close_win(&all);
                return (1);
        }
        mlx_hook(all.win.win, 17, 0L, close_win, &all);
        mlx_hook(all.win.win, 2, 1L<<0, key_hook, &all);
        mlx_loop(all.win.mlx);
        return (1);
}
