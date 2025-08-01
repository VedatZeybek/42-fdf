/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:15:51 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 08:15:52 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_valid_char(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	else
		return ((c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + base - 10)
			|| (c >= 'A' && c < 'A' + base - 10));
}

int	ft_char_to_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	val;

	result = 0;
	if (!str)
		return (0);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	while (*str)
	{
		if (!ft_is_valid_char(*str, base))
			break ;
		val = ft_char_to_val(*str);
		if (val < 0 || val >= base)
			break ;
		result = result * base + val;
		str++;
	}
	return (result);
}
