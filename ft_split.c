#include "cub.h"

static unsigned int	count_words(char const *s, char c)
{
    size_t			i;
    int				flg;
    unsigned int	cnt;

    flg = 1;
    i = 0;
    cnt = 0;
    while (s[i])
    {
        if (s[i] != c)
        {
            if (flg == 1)
                cnt++;
            flg = 0;
        }
        else
            flg = 1;
        i++;
    }
    return (cnt);
}

static char	*str_mod_dup(const char *s, char c, char **splt, size_t j)
{
    size_t	i;
    char	*new;

    i = 0;
    while (s[i] != c && s[i])
        i++;
    new = (char *)malloc(sizeof(char) * (i + 1));
    if (NULL == new)
    {
        while (j--)
            free(splt[j]);
        return (NULL);
    }
    i = 0;
    while (s[i] != c && s[i])
    {
        new[i] = s[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

static void	real_split(char const *s, char ***splt, char c, size_t i)
{
    int		flg;
    size_t	j;

    flg = 1;
    j = -1;
    while (s[++j])
    {
        if (s[j] != c)
        {
            if (flg == 1)
            {
                (*(splt))[i] = str_mod_dup(&s[j], c, *splt, i);
                if (NULL == (*(splt))[i])
                {
                    free(*splt);
                    *splt = NULL;
                }
                i++;
            }
            flg = 0;
        }
        else
            flg = 1;
    }
}

char	**ft_split(char const *s, char c)
{
    unsigned int	cnt;
    char			**splt;

    cnt = count_words(s, c);
    splt = (char **)malloc(sizeof(char *) * (cnt + 1));
    if (NULL == splt)
        return (NULL);
    splt[cnt] = NULL;
    real_split(s, &splt, c, 0);
    return (splt);
}