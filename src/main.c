// #include <stdio.h>
// #include <stdlib.h>
// # include <unistd.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include <string.h>

// char	**ft_split(char *s, char c);

// int	ft_count_str(char *s1, char *s2)
// {
// 	int	i;
// 	int	e;

// 	i = 0;
// 	e = 0;
// 	while (s1 != NULL && s1[i] != '\0')
// 		i++;
// 	while (s2[e] != '\0')
// 	{
// 		e++;
// 		i++;
// 	}
// 	i = i + 2;
// 	return (i);
// }

// char	*ft_strcat(char *dest, char *src)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	char			*tmp;

// 	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
// 	if (!tmp)
// 		return (0);
// 	i = 0;
// 	while (dest[i] != '\0')
// 	{
// 		tmp[i] = dest[i];
// 		i++;
// 	}
// 	j = 0;
// 	tmp[i] = '/';
// 	i++;
// 	while (src[j] != '\0')
// 	{
// 		tmp[i] = src[j];
// 		i++;
// 		++j;
// 	}
// 	tmp[i++] = '\0';
// 	return (tmp);
// }

// char	*ft_strcat_red(char *dest, char *src)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	char			*tmp;

// 	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
// 	if (!tmp)
// 		return (0);
// 	i = 0;
// 	while (dest && dest[i] != '\0')
// 	{
// 		tmp[i] = dest[i];
// 		i++;
// 	}
// 	tmp[i] = ' ';
// 	i++;
// 	j = 0;
// 	while (src[j] != '\0')
// 	{
// 		tmp[i] = src[j];
// 		i++;
// 		++j;
// 	}
// 	tmp[i++] = '\0';
// 	return (tmp);
// }

// int	ft_redir_strchr(char *s, int c)
// {
// 	int		i;
// 	int		nb_chr;

// 	i = 0;
//     nb_chr = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c && s[i + 1] != c && s[i - 1] && s[i - 1] != c)
// 			nb_chr++;
// 		i++;
// 	}
// 	return (nb_chr);
// }


// int	ft_strchr(char *s, int c)
// {
// 	int		i;
// 	int		nb_chr;

// 	i = 0;
//     nb_chr = 0;
// 	while (s && s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			nb_chr++;
// 		i++;
// 	}
// 	return (nb_chr);
// }

// int	what_path(char **path, char *cmd)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while (path[i])
// 	{
// 		str = ft_strcat(path[i], cmd);
// 		if (access(str, F_OK) == 0)
// 		{
// 			free(str);
// 			return (i);
// 		}
// 		free(str);
// 		i++;
// 	}
// 	return (-1);
// }

// void    separate(char *dest)
// {
//     int i=0;
//     int count = 0;
//     char **cmd;
//     char **file = malloc(sizeof(char *) * 3);
//     char *tmp_file;
//     char **tmp_all;
//     tmp_all = ft_split(dest,' ');
//     // while(tmp_all[i])
//     // {
//     //     printf("dest = %s\n", tmp_all[i]);
//     //     i++;
//     // }
//     while (tmp_all[i]) 
//     {
//         if (ft_strchr(tmp_all[i], '<') > 0)
//         {
//             if (tmp_all[i + 1])
//                 file[count] = ft_strcat_red(tmp_all[i], tmp_all[i +1]);
//             count++;
//         }
//         i++;
//     }
//     i = 0;
//     while (tmp_all[i])
//     {
//         i++;
//     }
//     cmd = malloc(sizeof(char *) * ((count * 2) + 1));
//     i = 0;
//     count = 0;
//     while (tmp_all[i]) 
//     {
//         if (ft_strchr(tmp_all[i], '<') == 0)
//         {
//             cmd[count] = ft_strcat_red("", tmp_all[i]);
//             count++;
//         }
//         else
//             i++;
//         i++;
//     }
//     i = 0;
//     while(cmd[i])
//     {
//         printf("dest = %s\n", cmd[i]);
//         i++;
//     }

// }

// int main()
// {
//     char *dest = "grep < outfile x ";

//     separate(dest);
//     return 0;
// }