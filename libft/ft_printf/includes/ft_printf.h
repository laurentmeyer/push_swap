/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 11:26:01 by lmeyer            #+#    #+#             */
/*   Updated: 2017/01/02 21:34:47 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# define MODIFIERS "hljz"
# define ACCEPTABLE "0123456789.hljz#0-+ "
# define CONVERSIONS "sSpdDioOuUxXcC%"
# define ERR -1
# define FLAG_ALTERNATE (1 << 0)
# define FLAG_SPACE (1 << 1)
# define FLAG_ZERO (1 << 2)
# define FLAG_MINUS (1 << 3)
# define FLAG_PLUS (1 << 4)

enum					e_modif
{
	none,
	l,
	ll,
	hh,
	h,
	j,
	z
};

typedef union			u_types
{
	void				*generic;
	int					c;
	wint_t				lc;
	char				*s;
	wchar_t				*ls;
	signed char			hhd;
	unsigned char		hhu;
	short				hd;
	unsigned short		hu;
	int					d;
	unsigned int		u;
	long				ld;
	unsigned long		lu;
	long long			lld;
	unsigned long long	llu;
	intmax_t			jd;
	uintmax_t			ju;
	size_t				zd;
	ssize_t				zu;
}						t_types;

typedef struct			s_conv
{
	int					flags;
	int					width;
	int					precision;
	enum e_modif		modifier;
	char				conversion;
}						t_conv;

typedef char			*t_handler(t_conv *conv, void *v);

int						ft_printf(const char *format, ...);
int						ft_vprintf(const char *format, va_list ap);
int						ft_asprintf(char **ret, const char *format, ...);
int						ft_vasprintf(char **ret, const char *format,
										va_list ap);
int						find_next_conversion(char *format, char **start,
												char **end);
t_conv					*new_conversion(char *start, int len);
int						get_modifier(char *s);
int						get_flags(char *s);
int						get_precision(char *s);
int						get_width(char *s);
t_handler				*get_handler(t_conv *conv);
char					*handler_integers(t_conv *conv, void *arg);
char					*handler_string(t_conv *conv, void *arg);
char					*handler_percent(t_conv *conv, void *arg);
char					*handler_char(t_conv *conv, void *arg);
char					*handler_pointer(t_conv *conv, void *arg);
char					*ft_itoa_base_max_unsigned(uintmax_t value, int base);
char					*ft_itoa_base_max_signed(intmax_t value, int base);

#endif
