/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 22:18:36 by vlevko            #+#    #+#             */
/*   Updated: 2018/01/23 17:47:27 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/libft.h"

unsigned long long int	ft_pow_lu(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (unsigned long long int)(nbr * ft_pow_lu(nbr, pow - 1));
}

uintmax_t	ft_pow_mu(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (uintmax_t)(nbr * ft_pow_mu(nbr, pow - 1));
}

size_t	ft_pow_su(int nbr, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (size_t)(nbr * ft_pow_su(nbr, pow - 1));
}

char	*ft_itoa_base_lu(char c, unsigned long long int val, int base)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	while (ft_pow_lu(base, i) - 1 < val)
		i++;
	str = ft_strnew(i);
	if (val == 0)
		return (str);
	while (i-- > 0)
	{
		str[i] = (val % base) + (val % base > 9 ? c - 10 : '0');
		val /= base;
	}
	return (str);
}

char	*ft_itoa_base_mu(char c, uintmax_t val, int base)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	while (ft_pow_mu(base, i) - 1 < val)
		i++;
	str = ft_strnew(i);
	if (val == 0)
		return (str);
	while (i-- > 0)
	{
		str[i] = (val % base) + (val % base > 9 ? c - 10 : '0');
		val /= base;
	}
	return (str);
}

char	*ft_itoa_base_su(char c, size_t val, int base)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	while (ft_pow_su(base, i) - 1 < val)
		i++;
	str = ft_strnew(i);
	if (val == 0)
		return (str);
	while (i-- > 0)
	{
		str[i] = (val % base) + (val % base > 9 ? c - 10 : '0');
		val /= base;
	}
	return (str);
}

void	ft_putnbr_ll(int minval, long long int nbr)
{
	long long int	tmp;
	long long int	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar(nbr / cnt + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	if (minval)
		nbr++;
	ft_putchar(nbr + '0');
}

void	hldi_zero(int *count, int wid, t_plist *spec)
{
	while (wid-- > 0)
	{
		if (spec->fg[4] && wid == 1)
			ft_putchar('+');
		else
			ft_putchar(' ');
		wid--;
		(*count)++;
	}
}

void	hldi_min(int *minval, long long int *val)
{
	*minval = 1;
	(*val)++;
}

void	pc_di(int *count, char c, int *dec)
{
	ft_putchar(c);
	if (dec)
		(*dec)--;
	(*count)++;
}

void	hldi_left(int *count, int cwpm[4], long long int val, t_plist *spec)
{
	if (spec->fg[4] && val >= 0)
		pc_di(count, '+', &(cwpm[1]));
	else if (spec->fg[3] && val >= 0)
		pc_di(count, ' ', &(cwpm[1]));
	if (val < 0)
	{
		pc_di(count, '-', &(cwpm[1]));
		val = -val;
	}
	while (cwpm[2]-- > cwpm[0])
		pc_di(count, '0', &(cwpm[1]));
	ft_putnbr_ll(cwpm[3], val);
	*count += cwpm[0];
	cwpm[1] -= cwpm[0];
	while (cwpm[1] > 0)
		pc_di(count, ' ', &(cwpm[1]));
}

void	hldi_r_prec(int *count, int *wid, long long int *val, t_plist *spec)
{
	while (*wid > 0)
		pc_di(count, ' ', wid);
	if (spec->fg[4] && *val >= 0)
		pc_di(count, '+', 0);
	else if (spec->fg[3] && *val >= 0)
		pc_di(count, ' ', 0);
	if (*val < 0)
	{
		pc_di(count, '-', 0);
		*val *= -1;
	}
}

void	hldi_r_noprec(int *count, int *wid, long long int *val, t_plist *spec)
{
	if (spec->fg[1])
	{
		if (spec->fg[4] && *val >= 0)
			pc_di(count, '+', 0);
		else if (spec->fg[3] && *val >= 0)
			pc_di(count, ' ', 0);
		if (*val < 0)
		{
			pc_di(count, '-', 0);
			*val *= -1;
		}
		while (*wid > 0)
			pc_di(count, '0', wid);
		return ;
	}
	while (*wid > 0)
		pc_di(count, ' ', wid);
	(spec->fg[4] && *val >= 0) ? (pc_di(count, '+', 0)) : \
	((spec->fg[3] && *val >= 0) ? (pc_di(count, ' ', 0)) : ((*wid) = 0));
	if (*val < 0)
	{
		pc_di(count, '-', 0);
		*val *= -1;
	}
}

void	hldi_right(int *count, int cwpm[4], long long int val, t_plist *spec)
{
	if (cwpm[2] > cwpm[0])
		cwpm[1] -= cwpm[2];
	else
		cwpm[1] -= cwpm[0];
	if (val < 0)
		cwpm[1] -= 1;
	else if (spec->fg[4])
		cwpm[1] -= 1;
	else if (spec->fg[3])
		cwpm[1] -= 1;
	if (spec->wp[2])
		hldi_r_prec(count, &(cwpm[1]), &val, spec);
	else
		hldi_r_noprec(count, &(cwpm[1]), &val, spec);
	while (cwpm[2] > cwpm[0])
		pc_di(count, '0', &(cwpm[2]));
	ft_putnbr_ll(cwpm[3], val);
	*count += cwpm[0];
}

void	cast_hldi(int *count, long long int val, t_plist *spec)
{
	long long int	nbr;
	int				cwpm[4];

	nbr = val;
	cwpm[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwpm[1] = spec->wp[0];
	cwpm[2] = spec->wp[1];
	if (val == 0 && cwpm[2] == 0)
		return (hldi_zero(count, cwpm[1], spec));
	cwpm[3] = 0;
	while (nbr /= 10)
		(cwpm[0])++;
	if (val == LONG_MIN)
		hldi_min(&(cwpm[3]), &val);
	if (spec->fg[2])
		hldi_left(count, cwpm, val, spec);
	else
		hldi_right(count, cwpm, val, spec);
}

void	ft_putchar_w(wint_t c)
{
	write(1, &c, 1);
}

void	cast_pc(int *count, char c, t_plist *spec)
{
	int	wid;

	wid = spec->wp[0];
	if (c == 0)
	{
		while (wid-- > 1)
			pc_di(count, ((spec->fg[1] && !spec->fg[2]) ? '0' : ' '), 0);
		pc_di(count, '\0', 0);
		return ;
	}
	if (spec->fg[2])
	{
		pc_di(count, c, 0);
		while (wid-- > 1)
			pc_di(count, ' ', 0);
	}
	else
	{
		while (wid-- > 1)
			(spec->fg[1]) ? (pc_di(count, '0', 0)) : (pc_di(count, ' ', 0));
		pc_di(count, c, 0);
	}
}

void	cast_loc_two(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[2];

	mask = 49280;
	val = (unsigned int)(c);
	bytes[1] = (val << 26) >> 26;
	bytes[0] = ((val >> 6) << 27) >> 27;
	octet = (mask >> 8) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[1];
	ft_putchar_w(octet);
}

void	cast_loc_three(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[3];

	mask = 14712960;
	val = (unsigned int)(c);
	bytes[2] = (val << 26) >> 26;
	bytes[1] = ((val >> 6) << 26) >> 26;
	bytes[0] = ((val >> 12) << 28) >> 28;
	octet = (mask >> 16) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 16) >> 24) | bytes[1];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[2];
	ft_putchar_w(octet);
}

void	cast_loc_four(wint_t c)
{
	unsigned int	mask;
	unsigned int	val;
	unsigned char	octet;
	unsigned char	bytes[4];

	mask = 4034953344;
	val = (unsigned int)(c);
	bytes[3] = (val << 26) >> 26;
	bytes[2] = ((val >> 6) << 26) >> 26;
	bytes[1] = ((val >> 12) << 26) >> 26;
	bytes[0] = ((val >> 18) << 29) >> 29;
	octet = (mask >> 24) | bytes[0];
	ft_putchar_w(octet);
	octet = ((mask << 8) >> 24) | bytes[1];
	ft_putchar_w(octet);
	octet = ((mask << 16) >> 24) | bytes[2];
	ft_putchar_w(octet);
	octet = ((mask << 24) >> 24) | bytes[3];
	ft_putchar_w(octet);
}

int	count_bytes_w(unsigned long long int n)
{
	if (n <= 0x007F)
		return (1);
	else if (n <= 0x07FF)
		return (2);
	else if (n <= 0xFFFF)
		return (3);
	return (4);
}

void	pc_w_left(int *count, int wid, int size, wint_t c)
{
	if (size == 1)
	{
		c = (unsigned char)(c);
		ft_putchar_w(c);
	}
	else if (size == 2)
		cast_loc_two(c);
	else if (size == 3)
		cast_loc_three(c);
	else if (size == 4)
		cast_loc_four(c);
	if (wid > size)
		*count += wid;
	else
		*count += size;
	while (wid-- > size)
		ft_putchar(' ');
}

void	pc_w_right(int *count, int ws[2], wint_t c, t_plist *spec)
{
	if (ws[0] > ws[1])
		*count += ws[0];
	else
		*count += ws[1];
	while (ws[0]-- > ws[1])
		ft_putchar((spec->fg[1] ? '0' : ' '));
	if (ws[1] == 1)
	{
		c = (unsigned char)(c);
		ft_putchar_w(c);
	}
	else if (ws[1] == 2)
		cast_loc_two(c);
	else if (ws[1] == 3)
		cast_loc_three(c);
	else if (ws[1] == 4)
		cast_loc_four(c);
}

void	cast_pc_w(int *count, wint_t c, t_plist *spec)
{
	int	ws[2];

	ws[1] = 0;
	ws[1] = count_bytes_w(c);
	ws[0] = spec->wp[0];
	if (ws[1] != 1 && MB_CUR_MAX < ws[1])
	{
		*count = -1;
		return ;
	}
	if (c == 0)
	{
		while ((ws[0])-- > 1)
			pc_di(count, ((spec->fg[1]) ? '0' : ' '), 0);
		pc_di(count, '\0', 0);
		return ;
	}
	if (spec->fg[2])
		pc_w_left(count, ws[0], ws[1], c);
	else
		pc_w_right(count, ws, c, spec);
}

void	oxX_zero(int *count, char c, char *val, int wid)
{
	if (c == 'p')
		wid -= 2;
	while (wid > 0)
		pc_di(count, ' ', &wid);
	if (c == 'p')
	{
		ft_putstr("0x");
		*count += 2;
	}
	else if (c == 'O')
	{
		ft_putchar('0');
		(*count)++;
	}
	ft_strdel(&val);
}

void	oxX_left(int *count, char *val, int cwp[3])
{
	while ((cwp[2])-- > cwp[0])
		pc_di(count, '0', &(cwp[1]));
	ft_putstr(val);
	*count += cwp[0];
	cwp[1] -= cwp[0];
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
	ft_strdel(&val);
}

void	xX_right(int *count, char c, int cwp[3], t_plist *spec)
{
	if ((spec->fg[0]) || c == 'p')
		cwp[1] -= 2;
	(cwp[2] > cwp[0]) ? (cwp[1] -= cwp[2]) : (cwp[1] -= cwp[0]);
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
	{
		if (((spec->fg[0] && cwp[0] != 0) || c == 'p') && spec->fg[1])
		{
			ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
			*count += 2;
		}
		while (cwp[1] > 0)
			pc_di(count, ((spec->fg[1]) ? '0' : ' '), &(cwp[1]));
	}
	if (((spec->fg[0] && cwp[0] != 0) || c == 'p') && spec->fg[1] == 0)
	{
		ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
		*count += 2;
	}
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

void	cast_xX(int *count, char c, char *val, t_plist *spec)
{
	int	cwp[3];

	cwp[0] = 0;
	(spec->wp[2] == 0) ? (spec->wp[1] = 1) : (cwp[0] = 0);
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	cwp[0] = ft_strlen(val);
	if (cwp[0] == 0 && cwp[2] == 0)
		return (oxX_zero(count, c, val, cwp[1]));
	if (spec->fg[2])
	{
		if ((spec->fg[0] && cwp[0] != 0) || c == 'p')
		{
			ft_putstr((c == 'a' || c == 'p' ? "0x" : "0X"));
			cwp[1] -= 2;
			*count += 2;
		}
		oxX_left(count, val, cwp);
		return ;
	}
	xX_right(count, c, cwp, spec);
	ft_putstr(val);
	*count += cwp[0];
	ft_strdel(&val);
}

void	ft_putnbr_lu(unsigned long long int nbr)
{
	unsigned long long int	tmp;
	unsigned long long int	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar((nbr / cnt) + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	ft_putchar(nbr + '0');
}

void	ft_putnbr_mu(uintmax_t nbr)
{
	uintmax_t	tmp;
	uintmax_t	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar((nbr / cnt) + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	ft_putchar(nbr + '0');
}

void	ft_putnbr_su(size_t nbr)
{
	size_t	tmp;
	size_t	cnt;

	cnt = 1;
	tmp = nbr;
	while (tmp /= 10)
		cnt *= 10;
	while (cnt / 10)
	{
		ft_putchar((nbr / cnt) + '0');
		nbr %= cnt;
		cnt /= 10;
	}
	ft_putchar(nbr + '0');
}

void	smlu_zero(int *count, int wid)
{
	while (wid > 0)
		pc_di(count, ' ', &wid);
}

void	smlu_left(int *count, int cwp[3])
{
	*count += cwp[0];
	cwp[1] -= cwp[0];
	while (cwp[1] > 0)
		pc_di(count, ' ', &(cwp[1]));
}

void	smlu_rt(int *count, int cwp[3], t_plist *spec)
{
	cwp[1] -= (cwp[2] > cwp[0]) ? cwp[2] : cwp[0];
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
		while (cwp[1] > 0)
			pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

void	cast_lu(int *count, unsigned long long int val, t_plist *spec)
{
	unsigned long long int	nbr;
	int						cwp[3];

	nbr = val;
	cwp[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	if (val == 0 && cwp[2] == 0)
		return (smlu_zero(count, cwp[1]));
	while (nbr /= 10)
		(cwp[0])++;
	if (spec->fg[2])
	{
		while ((cwp[2])-- > cwp[0])
			pc_di(count, '0', &(cwp[1]));
		ft_putnbr_lu(val);
		smlu_left(count, cwp);
		return ;
	}
	smlu_rt(count, cwp, spec);
	ft_putnbr_lu(val);
	*count += cwp[0];
}

void	cast_mu(int *count, uintmax_t val, t_plist *spec)
{
	uintmax_t	nbr;
	int			cwp[3];

	nbr = val;
	cwp[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	if (val == 0 && cwp[2] == 0)
		return (smlu_zero(count, cwp[1]));
	while (nbr /= 10)
		(cwp[0])++;
	if (spec->fg[2])
	{
		while ((cwp[2])-- > cwp[0])
			pc_di(count, '0', &(cwp[1]));
		ft_putnbr_mu(val);
		smlu_left(count, cwp);
		return ;
	}
	smlu_rt(count, cwp, spec);
	ft_putnbr_mu(val);
	*count += cwp[0];
}

void	cast_su(int *count, size_t val, t_plist *spec)
{
	size_t	nbr;
	int		cwp[3];

	nbr = val;
	cwp[0] = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	if (val == 0 && cwp[2] == 0)
		return (smlu_zero(count, cwp[1]));
	while (nbr /= 10)
		(cwp[0])++;
	if (spec->fg[2])
	{
		while (cwp[2]-- > cwp[0])
			pc_di(count, '0', &(cwp[1]));
		ft_putnbr_su(val);
		smlu_left(count, cwp);
		return ;
	}
	smlu_rt(count, cwp, spec);
	ft_putnbr_su(val);
	*count += cwp[0];
}

void	o_right(int *count, int cwp[3], t_plist *spec)
{
	if (spec->fg[0] && cwp[2] <= cwp[0])
		(cwp[1])--;
	else if (cwp[2] > cwp[0])
		cwp[1] -= cwp[2];
	if (cwp[2] <= cwp[0])
		cwp[1] -= cwp[0];
	if (spec->wp[2])
		while (cwp[1] > 0)
			pc_di(count, ' ', &(cwp[1]));
	else
		while (cwp[1] > 0)
			pc_di(count, (spec->fg[1] ? '0' : ' '), &(cwp[1]));
	if (spec->fg[0])
		pc_di(count, '0', &(cwp[2]));
	while (cwp[2] > cwp[0])
		pc_di(count, '0', &(cwp[2]));
}

void	cast_o(int *count, char *val, t_plist *spec)
{
	int	cwp[3];

	cwp[0] = 0;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	cwp[1] = spec->wp[0];
	cwp[2] = spec->wp[1];
	cwp[0] = ft_strlen(val);
	if (cwp[0] == 0 && cwp[2] == 0)
		return (oxX_zero(count, ((spec->fg[0]) ? 'O' : 'o'), val, cwp[1]));
	if (spec->fg[2])
	{
		if (spec->fg[0] && cwp[2] <= cwp[0])
			pc_di(count, '0', &(cwp[1]));
		oxX_left(count, val, cwp);
		return ;
	}
	o_right(count, cwp, spec);
	ft_putstr(val);
	*count += cwp[0];
	ft_strdel(&val);
}

int	print_c(int *count, char c)
{
	if (c != '%')
	{
		ft_putchar(c);
		(*count)++;
		return (1);
	}
	return (0);
}

void	parse_ctrl(t_plist *spec, const char **f)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < 5)
	{
		spec->fg[i] = 0;
		if (i < 2)
		{
			spec->wp[i] = 0;
			spec->hh[i] = 0;
			spec->ll[i] = 0;
			spec->jz[i] = 0;
		}
		if (i == 2)
			spec->wp[i] = 0;
	}
	while (**f == '#' || **f == '0' || **f == '-' || **f == ' ' || **f == '+' \
		|| **f == 'l' || **f == 'h' || **f == 'j' || **f == 'z' || **f == 'L' \
		|| **f == 't' || **f == '.' || (**f >= '0' && **f <= '9'))
	{
		if (**f == '#')
		{
			spec->fg[0] = 1;
			(*f)++;
		}
		if (**f == '0')
		{
			spec->fg[1] = 1;
			(*f)++;
		}
		if (**f == '-')
		{
			spec->fg[2] = 1;
			(*f)++;
		}
		if (**f == ' ')
		{
			spec->fg[3] = 1;
			(*f)++;
		}
		if (**f == '+')
		{
			spec->fg[4] = 1;
			(*f)++;
		}
		if (**f >= '1' && **f <= '9')
		{
			i = 0;
			str = NULL;
			while (ft_isdigit((*f)[i]))
				i++;
			str = ft_strsub(*f, 0, i);
			spec->wp[0] = ft_atoi(str);
			ft_strdel(&str);
			while (i-- > 0)
				(*f)++;
		}
		if (**f == '.')
		{
			(*f)++;
			i = 0;
			str = NULL;
			if (**f == '-')
				(*f)++;
			while (ft_isdigit((*f)[i]))
				i++;
			str = ft_strsub(*f, 0, i);
			spec->wp[2] = 1;
			spec->wp[1] = ft_atoi(str);
			ft_strdel(&str);
			while (i-- > 0)
				(*f)++;
		}
		if (**f == 'h')
		{
			(*f)++;
			if (**f == 'h')
			{
				(*f)++;
				spec->hh[1] = 1;
			}
			else
				spec->hh[0] = 1;
		}
		if (**f == 'l')
		{
			(*f)++;
			if (**f == 'l')
			{
				(*f)++;
				spec->ll[1] = 1;
			}
			else
				spec->ll[0] = 1;
		}
		if (**f == 'L')
			(*f)++;
		if (**f == 'j')
		{
			spec->jz[0] = 1;
			(*f)++;
		}
		if (**f == 'z')
		{
			spec->jz[1] = 1;
			(*f)++;
		}
		if (**f == 't')
			(*f)++;
	}
}

void	cast_s(int *count, char *str, t_plist *spec)
{
	char	*res;
	char	*tmp;
	int		len;
	int		wid;
	int		prec;

	res = NULL;
	tmp = NULL;
	wid = spec->wp[0];
	prec = spec->wp[1];
	if (str == NULL)
		tmp = ft_strdup("(null)");
	else
		tmp = ft_strdup(str);
	len = 0;
	len = ft_strlen(tmp);
	if (spec->fg[2])
	{
		if (spec->wp[2])
		{
			res = ft_strsub(tmp, 0, prec);
			wid -= ft_strlen(res);
			*count += ft_strlen(res);
		}
		else
		{
			wid -= len;
			res = ft_strdup(tmp);
			*count += len;
		}
		ft_putstr(res);
		ft_strdel(&res);
		while (wid > 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
	}
	else
	{
		if (spec->wp[2])
		{
			res = ft_strsub(tmp, 0, prec);
			wid -= ft_strlen(res);
			*count += ft_strlen(res);
		}
		else
		{
			wid -= len;
			res = ft_strdup(tmp);
			*count += len;
		}
		while (wid > 0)
		{
			ft_putchar((spec->fg[1] ? '0' : ' '));
			wid--;
			(*count)++;
		}
		ft_putstr(res);
		ft_strdel(&res);
	}
	ft_strdel(&tmp);
}

size_t	ft_countlen_w(int prec, const wchar_t *s)
{
	size_t			len;
	unsigned int	bytes;

	len = 0;
	while (*s != '\0')
	{
		bytes = count_bytes_w(*s);
		if (prec != -1 && bytes + len > (unsigned int)(prec))
			break ;
		len += bytes;
		s++;
	}
	return (len);
}

void	ft_putstr_w(int len, wchar_t const *s)
{
	int	bytes;

	bytes = 0;
	if (s)
		while (*s != '\0')
		{
			bytes = count_bytes_w(*s);
			if (len - bytes < 0)
				break ;
			len -= bytes;
			if (bytes == 1)
				ft_putchar_w((unsigned char)(*s));
			else if (bytes == 2)
				cast_loc_two(*s);				
			else if (bytes == 3)
				cast_loc_three(*s);
			else
				cast_loc_four(*s);
			s++;
		}
}

void	ft_strdel_w(wchar_t **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

size_t	ft_strlen_w(const wchar_t *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

wchar_t	*ft_strcpy_w(wchar_t *dst, const wchar_t *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

wchar_t	*ft_strdup_w(const wchar_t *s1)
{
	wchar_t	*s2;

	if (!(s2 = (wchar_t *)malloc(sizeof(wchar_t) * (ft_strlen_w(s1) + 1))))
		return (NULL);
	ft_strcpy_w(s2, s1);
	return (s2);
}

void	cast_ws(int *count, wchar_t *str, t_plist *spec)
{
	int		len;
	int		wid;
	int		prec;
	wchar_t	*res;

	if (str == NULL)
		res = ft_strdup_w(L"(null)");
	else
		res = ft_strdup_w(str);
	len = 0;
	wid = spec->wp[0];
	if (spec->wp[2])
		prec = spec->wp[1];
	else
		prec = -1;
	len = ft_countlen_w(prec, res);
	if (spec->fg[2])
	{
		if (prec == 0)
		{
			while (wid > 0)
			{
				ft_putchar(' ');
				wid--;
				(*count)++;
			}
			ft_strdel_w(&res);
			return ;
		}
		wid -= len;
		*count += len;;		
		ft_putstr_w(len, res);
		while (wid > 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
	}
	else
	{
		if (prec == 0)
		{
			while (wid > 0)
			{
				ft_putchar((spec->fg[1] ? '0' : ' '));
				wid--;
				(*count)++;
			}
			ft_strdel_w(&res);
			return ;
		}
		wid -= len;
		*count += len;			
		while (wid > 0)
		{
			ft_putchar((spec->fg[1] ? '0' : ' '));
			wid--;
			(*count)++;
		}
		ft_putstr_w(len, res);
	}
	ft_strdel_w(&res);
}

void	ft_putnbr_m(int minval, intmax_t n)
{
	intmax_t	tmp;
	intmax_t	count;

	count = 1;
	tmp = n;
	while (n /= 10)
		count *= 10;
	while (count / 10)
	{
		ft_putchar((tmp / count) + '0');
		tmp %= count;
		count /= 10;
	}
	if (minval)
		tmp++;
	ft_putchar(tmp + '0');
}

void	cast_mdi(int *count, intmax_t val, t_plist *spec)
{
	intmax_t	nb;
	int	cnt;
	int	wid;
	int	prec;
	int	minval;

	nb = val;
	cnt = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	wid = spec->wp[0];
	prec = spec->wp[1];
	minval = 0;
	if (val == 0 && prec == 0)
	{
		while (wid > 0)
		{
			if (spec->fg[4] && wid == 1)
				ft_putchar('+');
			else
				ft_putchar(' ');
			wid--;
			(*count)++;
		}
		return ;
	}	
	while (nb /= 10)
		cnt++;
	if (val == INTMAX_MIN)
	{
		minval = 1;
		val++;
	}
	if (spec->fg[2])
	{
		if (spec->fg[4] && val >= 0)
		{
			ft_putchar('+');
			wid--;
			(*count)++;
		}
		else if (spec->fg[3] && val >= 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
		if (val < 0)
		{
			ft_putchar('-');
			val = -val;
			wid--;
			(*count)++;
		}
		while (prec > cnt)
		{
			ft_putchar('0');
			wid--;
			(*count)++;
			prec--;
		}
		ft_putnbr_m(minval, val);
		*count += cnt;
		while (wid > 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
	}
	else
	{
		if (prec > cnt)
			wid -= prec;
		else
			wid -= cnt;
		if (val < 0)
			wid -= 1;
		else if (spec->fg[4])
			wid -= 1;
		else if (spec->fg[3])
			wid -= 1;
		if (spec->wp[2])
		{
			while (wid > 0)
			{
				ft_putchar(' ');
				wid--;
				(*count)++;
			}
			if (spec->fg[4] && val >= 0)
			{
				ft_putchar('+');
				(*count)++;
			}
			else if (spec->fg[3] && val >= 0)
			{
				ft_putchar(' ');
				(*count)++;
			}
			if (val < 0)
			{
				ft_putchar('-');
				val = -val;
				(*count)++;
			}
		}
		else
		{
			if (spec->fg[1])
			{
				if (spec->fg[4] && val >= 0)
				{
					ft_putchar('+');
					(*count)++;
				}
				else if (spec->fg[3] && val >= 0)
				{
					ft_putchar(' ');
					(*count)++;
				}
				if (val < 0)
				{
					ft_putchar('-');
					val = -val;
					(*count)++;
				}
				while (wid > 0)
				{
					ft_putchar('0');
					wid--;
					(*count)++;
				}
			}
			else
			{
				while (wid > 0)
				{
					ft_putchar(' ');
					wid--;
					(*count)++;
				}
				if (spec->fg[4] && val >= 0)
				{
					ft_putchar('+');
					(*count)++;
				}
				else if (spec->fg[3] && val >= 0)
				{
					ft_putchar(' ');
					(*count)++;
				}
				if (val < 0)
				{
					ft_putchar('-');
					val = -val;
					(*count)++;
				}
			}
		}
		while (prec > cnt)
		{
			ft_putchar('0');
			prec--;
			(*count)++;
		}
		ft_putnbr_m(minval, val);
		*count += cnt;
	}
}

void	ft_putnbr_ss(int minval, ssize_t n)
{
	ssize_t	tmp;
	ssize_t	count;

	count = 1;
	tmp = n;
	while (n /= 10)
		count *= 10;
	while (count / 10)
	{
		ft_putchar((tmp / count) + '0');
		tmp %= count;
		count /= 10;
	}
	if (minval)
		tmp++;
	ft_putchar(tmp + '0');
}

void	cast_ssdi(int *count, ssize_t val, t_plist *spec)
{
	ssize_t	nb;
	int	cnt;
	int	wid;
	int	prec;
	int	minval;

	nb = val;
	cnt = 1;
	if (spec->wp[2] == 0)
		spec->wp[1] = 1;
	wid = spec->wp[0];
	prec = spec->wp[1];
	minval = 0;
	if (val == 0 && prec == 0)
	{
		while (wid > 0)
		{
			if (spec->fg[4] && wid == 1)
				ft_putchar('+');
			else
				ft_putchar(' ');
			wid--;
			(*count)++;
		}
		return ;
	}
	while (nb /= 10)
		cnt++;
	if (val == -SSIZE_MAX - 1)
	{
		minval = 1;
		val++;
	}
	if (spec->fg[2])
	{
		if (spec->fg[4] && val >= 0)
		{
			ft_putchar('+');
			wid--;
			(*count)++;
		}
		else if (spec->fg[3] && val >= 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
		if (val < 0)
		{
			ft_putchar('-');
			val = -val;
			wid--;
			(*count)++;
		}
		while (prec > cnt)
		{
			ft_putchar('0');
			wid--;
			(*count)++;
			prec--;
		}
		ft_putnbr_ss(minval, val);
		*count += cnt;
		while (wid > 0)
		{
			ft_putchar(' ');
			wid--;
			(*count)++;
		}
	}
	else
	{
		if (prec > cnt)
			wid -= prec;
		else
			wid -= cnt;
		if (val < 0)
			wid -= 1;
		else if (spec->fg[4])
			wid -= 1;
		else if (spec->fg[3])
			wid -= 1;
		if (spec->wp[2])
		{
			while (wid > 0)
			{
				ft_putchar(' ');
				wid--;
				(*count)++;
			}
			if (spec->fg[4] && val >= 0)
			{
				ft_putchar('+');
				(*count)++;
			}
			else if (spec->fg[3] && val >= 0)
			{
				ft_putchar(' ');
				(*count)++;
			}
			if (val < 0)
			{
				ft_putchar('-');
				val = -val;
				(*count)++;
			}
		}
		else
		{
			if (spec->fg[1])
			{
				if (spec->fg[4] && val >= 0)
				{
					ft_putchar('+');
					(*count)++;
				}
				else if (spec->fg[3] && val >= 0)
				{
					ft_putchar(' ');
					(*count)++;
				}
				if (val < 0)
				{
					ft_putchar('-');
					val = -val;
					(*count)++;
				}
				while (wid > 0)
				{
					ft_putchar('0');
					wid--;
					(*count)++;
				}
			}
			else
			{
				while (wid > 0)
				{
					ft_putchar(' ');
					wid--;
					(*count)++;
				}
				if (spec->fg[4] && val >= 0)
				{
					ft_putchar('+');
					(*count)++;
				}
				else if (spec->fg[3] && val >= 0)
				{
					ft_putchar(' ');
					(*count)++;
				}
				if (val < 0)
				{
					ft_putchar('-');
					val = -val;
					(*count)++;
				}
			}
		}
		while (prec > cnt)
		{
			ft_putchar('0');
			prec--;
			(*count)++;
		}
		ft_putnbr_ss(minval, val);
		*count += cnt;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*f;
	int			count;
	t_plist		*spec;

	f = format;
	count = 0;
	spec = (t_plist *)malloc(sizeof(t_plist));
	va_start(ap, format);
	while (*f)
	{
		if (print_c(&count, *f++))
			continue;
		parse_ctrl(spec, &f);
		if (*f == 'D' || *f == 'O' || *f == 'U' || *f == 'S' || *f == 'C')
			spec->ll[0] = 1;
		if (*f == 'd' || *f == 'i' || *f == 'D')
		{
			if (spec->jz[1] == 1 && *f != 'D')
				cast_ssdi(&count, (ssize_t)(va_arg(ap, ssize_t)), spec);
			else if (spec->jz[0] == 1 && *f != 'D')
				cast_mdi(&count, (intmax_t)(va_arg(ap, intmax_t)), spec);
			else if (spec->ll[1] && *f != 'D')
				cast_hldi(&count, (long long int)(va_arg(ap, long long int)), spec);
			else if (spec->ll[0])
				cast_hldi(&count, (long int)(va_arg(ap, long int)), spec);
			else if (spec->hh[1] && *f != 'D')
				cast_hldi(&count, (signed char)(va_arg(ap, int)), spec);
			else if (spec->hh[0] && *f != 'D')
				cast_hldi(&count, (short int)(va_arg(ap, int)), spec);
			else if (*f != 'D')
				cast_hldi(&count, (int)(va_arg(ap, int)), spec);
		}
		else if (*f == 'c' || *f == 'C')
		{
			if (spec->ll[0])
				cast_pc_w(&count, (wint_t)(va_arg(ap, wint_t)), spec);
			else
				cast_pc(&count, (unsigned char)(va_arg(ap, int)), spec);
		}
		else if (*f == 'u' || *f == 'U')
		{
			if (spec->jz[1] && *f != 'U')
				cast_su(&count, (size_t)(va_arg(ap, size_t)), spec);
			else if (spec->jz[0] && *f != 'U')
				cast_mu(&count, (uintmax_t)(va_arg(ap, uintmax_t)), spec);
			else if (spec->ll[1] && *f != 'U')
				cast_lu(&count, (unsigned long long int)(va_arg(ap, unsigned long long int)), spec);
			else if (spec->ll[0])
				cast_lu(&count, (unsigned long int)(va_arg(ap, unsigned long int)), spec);
			else if (spec->hh[1] && *f != 'U')
				cast_lu(&count, (unsigned char)(va_arg(ap, unsigned int)), spec);
			else if (spec->hh[0] && *f != 'U')
				cast_lu(&count, (unsigned short int)(va_arg(ap, unsigned int)), spec);
			else if (*f != 'U')
				cast_lu(&count, (unsigned int)(va_arg(ap, unsigned int)), spec);
		}
		else if (*f == 'x' || *f == 'X')
		{
			if (spec->jz[1])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_su((*f == 'x' ? 'a' : 'A'), (size_t)(va_arg(ap, size_t)), 16), spec);
			else if (spec->jz[0])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_mu((*f == 'x' ? 'a' : 'A'), (uintmax_t)(va_arg(ap, uintmax_t)), 16), spec);
			else if (spec->ll[1])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((*f == 'x' ? 'a' : 'A'), (unsigned long long int)(va_arg(ap, unsigned long long int)), 16), spec);
			else if (spec->ll[0])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((*f == 'x' ? 'a' : 'A'), (unsigned long int)(va_arg(ap, unsigned long int)), 16), spec);
			else if (spec->hh[1])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((*f == 'x' ? 'a' : 'A'), (unsigned char)(va_arg(ap, unsigned int)), 16), spec);
			else if (spec->hh[0])
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((*f == 'x' ? 'a' : 'A'), (unsigned short int)(va_arg(ap, unsigned int)), 16), spec);
			else
				cast_xX(&count, (*f == 'x' ? 'a' : 'A'), ft_itoa_base_lu((*f == 'x' ? 'a' : 'A'), (unsigned int)(va_arg(ap, unsigned int)), 16), spec);
		}
		else if (*f == 'o' || *f == 'O')
		{
			if (spec->jz[1] && *f != 'O')
				cast_o(&count, ft_itoa_base_su('o', (size_t)(va_arg(ap, size_t)), 8), spec);
			else if (spec->jz[0] && *f != 'O')
				cast_o(&count, ft_itoa_base_mu('o', (uintmax_t)(va_arg(ap, uintmax_t)), 8), spec);
			else if (spec->ll[1] && *f != 'O')
				cast_o(&count, ft_itoa_base_lu('o', (unsigned long long int)(va_arg(ap, unsigned long long int)), 8), spec);
			else if (spec->ll[0])
				cast_o(&count, ft_itoa_base_lu('o', (unsigned long int)(va_arg(ap, unsigned long int)), 8), spec);
			else if (spec->hh[1] && *f != 'O')
				cast_o(&count, ft_itoa_base_lu('o', (unsigned char)(va_arg(ap, unsigned int)), 8), spec);
			else if (spec->hh[0] && *f != 'O')
				cast_o(&count, ft_itoa_base_lu('o', (unsigned short int)(va_arg(ap, unsigned int)), 8), spec);
			else if (*f != 'O')
				cast_o(&count, ft_itoa_base_lu('o', (unsigned int)(va_arg(ap, unsigned int)), 8), spec);
		}
		else if (*f == 's' || *f == 'S')
		{
			if (spec->ll[0])
				cast_ws(&count, va_arg(ap, wchar_t *), spec);
			else
				cast_s(&count, va_arg(ap, char *), spec);
		}
		else if (*f == 'p')
		{
			spec->fg[0] = 1;
			cast_xX(&count, 'p', ft_itoa_base_lu('a', (unsigned long int)(va_arg(ap, void *)), 16), spec);
		}
		else if (*f == '%')
			cast_pc(&count, '%', spec);
		else if (*f != '\0')
			cast_pc(&count, *f, spec);
		if (count == -1)
			break ;
		else if (*f != '\0')
			f++;
	}
	va_end(ap);
	if (spec)
	{
		free(spec);
		spec = NULL;
	}
	return (count);
}
