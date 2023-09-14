#include <stdio.h>
#include <unistd.h>

int ft_atoi (char* str);

int main (int argc, char* argv[])
{
	printf("Atoi: %d\n", ft_atoi(argv[1]));
}

/*
int ft_atoi (char* str)
{
	int i = 0;
	int sign = 1;
	int x = 0;
	int nbr = 0;

	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
	{
		i++;
	}
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			x++;
		i++;
	}
	if (x % 2 == 0)
		sign = 1;
	else
		sign = - 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return nbr*sign;
}*/

/* Exam atoi */

int ft_atoi (char* str)
{
	int i = 0;
	int sign = 1;
	int x = 0;
	int nbr = 0;
	
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	while (str[i] == '+' || str[i] == '-')
	{
		x ++;
		if (x > 1)
		{
			return 0;
		}
		else if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}
