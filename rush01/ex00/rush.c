/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/2 12:19:30 by spascual          #+#    #+#             */
/*   Updated: 2023/09/3 12:19:39 by spascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// declare functions
void	imprimir_tablero(int tablero[4][4]);
int	check_row(int tablero[4][4], int fila, int numero);
int	check_column(int tablero[4][4], int columna, int numero);
int	check_visibility_row_left(int tablero[4][4], int fila, int rowLeft, int rowRight);
int	check_visibility_column_up(int tablero[4][4], int columna, int colUp, int colDown);
int	check_visibility_row_right(int tablero[4][4], int fila, int rowLeft, int rowRight);
int	check_visibility_column_down(int tablero[4][4], int columna, int colUp, int colDown);
int	resolver_tablero(int tablero[4][4], int rowLeft[4], int rowRight[4], int colUp[4], int colDown[4], int fila, int columna);
void	resolver_con_restricciones(int col1up, int col2up, int col3up, int col4up, int col1down, int col2down, int col3down, int col4down, int row1left, int row2left, int row3left, int row4left, int row1right, int 	row2right, int row3right, int row4right);
int	atoi(const char *str);
void	ft_putchar(char c);

int	main(int argc, char *argv[])
{
	if (argc != 17)
	{
		ft_putchar('E');
		ft_putchar('r');
		ft_putchar('r');
        	return (1);
	}

	// geting the visibility numbers from the terminal
	int col1up = atoi(argv[1]);
	int col2up = atoi(argv[2]);
	int col3up = atoi(argv[3]);
	int col4up = atoi(argv[4]);
	int col1down = atoi(argv[5]);
	int col2down = atoi(argv[6]);
	int col3down = atoi(argv[7]);
	int col4down = atoi(argv[8]);
	int row1left = atoi(argv[9]);
	int row2left = atoi(argv[10]);
	int row3left = atoi(argv[11]);
	int row4left = atoi(argv[12]);
	int row1right = atoi(argv[13]);
	int row2right = atoi(argv[14]);
	int row3right = atoi(argv[15]);
	int row4right = atoi(argv[16]);

	resolver_con_restricciones(col1up, col2up, col3up, col4up, col1down, col2down, col3down, col4down, row1left, row2left, row3left, row4left, row1right, row2right, row3right, row4right);

	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	atoi(const char *str)
{
	int	res; // Stores the final result
	int	sign; // Stores the sign of the number

	res = 0; // Initialize the result to zero
	sign = 1; // Initialize the sign as positive
	
	 // Ignore leading white spaces in the string
	while(*str == ' ')
	{
		str++;
	}
	
	// Check for '+' or '-' sign at the beginning
	if(*str == '+' || *str == '-')
	{
		if(*str == '-')
		{
			sign = -1; // If '-' is encountered, set the sign as negative
		}
		str++;
	}
	
	// Convert the digits in the string to an integer value
	while(*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0'); // Multiply the current result by 10 for space and add the converted digit (more info atoi.txt)
		str++;
	}
	return (res * sign); // Return the resulting integer value with the appropriate sign (number * +-1)
}

void	imprimir_tablero(int tablero[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < 4) // Iterates throw big rows, the {{}, {}, {}, {}}
	{
		j = 0;
		while(j < 4) // Iterates throw rows {0,0,0,0}
		{
			ft_putchar(tablero[i][j] + '0'); // Converts to character.
			if (j < 3)
            			ft_putchar(' '); // to make it more readeble, put if for j < 3
			j++;
		}
		ft_putchar('\n'); // every four rows line break
		i++;
	}
}

// Technically tablero[i][j] i && j both iterates throw row, think and you'll understand
// Where checking that the big row where in dosn't already contain the number we're trying to put in th cell
int	check_row(int tablero[4][4], int fila, int numero)
{
	int	i;

	i = 0;
	while(i < 4)
	{
		if(tablero[fila][i] == numero)
			return (0);
		i++;
	}
	return (1);
}

// Imagin with columna = 0, it searches for the number in the column
int	check_column(int tablero[4][4], int columna, int numero)
{
	int	i;

	i = 0;
	while(i < 4)
	{
		if(tablero[i][columna] == numero)
			return (0);
		i++;
	}
	return (1);
}

// rowRight is not being used, could take it out, but it works, so DON'T TOUCH
int	check_visibility_row_left(int tablero[4][4], int fila, int rowLeft, int rowRight)
{
	int	visible; // Counts te number of visible blocks from the left
	int	max_height; // Maintains the height of the highest block found on the row left to right
	int	j;

	visible = 0;
	max_height = 0;
	j = 0;

	// Iterates throw rows, imagin fila = 0
	while(j < 4)
	{
		// checks if the cell is empty, don't understand fully, is my code going throw the board more than once or backtracking? If it is backtracking, why do I need it?
		if(tablero[fila][j] == 0)
		{
			return (1);
		}
		// Checks if the number is greater than max_height, if it is it sets that number as the max height
		if(tablero[fila][j] > max_height)
		{
			max_height = tablero[fila][j]; // Asigning max_height to cell?? Maybe to know which cell has the highest block
			visible++; // At the beginnig you can't see any blocks, so the visibility is 0, everytime you set a new max_height, you are seing one more block, that's why visible++ and why we return what we return
		}
		j++;
	}
	// Returns a check, checking if visible is the same as the visibility on rowLeft
	return (visible == rowLeft);
}

// colDown is not being used, could take it out, but it works, so DON'T TOUCH
int	check_visibility_column_up(int tablero[4][4], int columna, int colUp, int colDown)
{
	int	visible;
	int	max_height;
	int	i;

	visible = 0;
	max_height = 0;
	i = 0;
	while(i < 4)
	{
		if(tablero[i][columna] == 0)
		{
			return (1);
		}
		if(tablero[i][columna] > max_height)
		{
			max_height = tablero[i][columna];
			visible++;
		}
		i++;
	} 
	return (visible == colUp);
}

// rowLeft is not being used, could take it out, but it works, so DON'T TOUCH
int	check_visibility_row_right(int tablero[4][4], int fila, int rowLeft, int rowRight)
{
	int	visible;
	int	max_height;
	int	j;

	visible = 0;
	max_height = 0;
	j = 3;
	while(j >= 0)
		{
		if(tablero[fila][j] == 0)
		{
			return (1);
		}
		if(tablero[fila][j] > max_height)
		{
			max_height = tablero[fila][j];
			visible++;
		}
		j--; // You noticed, -- because we're going right to left, draw it, easier to imagine (backwards)
	}
	return (visible == rowRight);
}

// colDown is not being used, could take it out, but it works, so DON'T TOUCH
int	check_visibility_column_down(int tablero[4][4], int columna, int colUp, int colDown)
{
	int	visible = 0;
	int	max_height = 0;
	int	i;
	
	i = 3;
	while(i >= 0)
	{
		if(tablero[i][columna] == 0)
		{
			return (1);
		}
		if(tablero[i][columna] > max_height)
		{
			max_height = tablero[i][columna];
			visible++;
		}
		i--; // Yep, same backwards
	}
	return (visible == colDown);
}

int	resolver_tablero(int tablero[4][4], int rowLeft[4], int rowRight[4], int colUp[4], int colDown[4], int fila, int columna)
{
	if (fila == 4) // If fila == 4 everythings ok, means we're finished, is checked in the recursive resolver_tablero a few lines below, at first it obviously doesn't go throw here
		return 1;

	int numero; // The number we're checking

	numero = 1; // won't be less than 1
	while(numero <= 4) // won't be greater than 4 duhh
	{
		if(check_row(tablero, fila, numero) && check_column(tablero, columna, numero)) // checks sudoku like, checks if numero is in the row or column already, we wan't the condition to be false, if the condition isn't true we'll skip to numero++
		{
			tablero[fila][columna] = numero; // Great, numero is not in the rows or columns, so we try to put it in the cell and see what happens
			// Now we're checking for the 4 tipes of visibility
			if(check_visibility_row_left(tablero, fila, rowLeft[fila], rowRight[fila]) && check_visibility_row_right(tablero, fila, rowLeft[fila], rowRight[fila]) && check_visibility_column_up(tablero, columna, colUp[columna], colDown[columna]) && check_visibility_column_down(tablero, columna, colUp[columna], colDown[columna]))
			{
				int	nueva_fila; // Don't understand the need to create 2 new variables to check, can I use fila and columna and not create new ones?
				int	nueva_columna;
				
				nueva_fila = fila; // two option because of if in the recursive function
				nueva_columna = columna + 1; // Move on to the next cell in the row {0,0,0,0}
				if(nueva_columna == 4) // If we checked the 4 cells in a row 
				{
					nueva_columna = 0;
					nueva_fila++; // If we got the 4 rows completed we move on to the next row {{}, {}}
				}
				if(resolver_tablero(tablero, rowLeft, rowRight, colUp, colDown, nueva_fila, nueva_columna)) // recursive function, don't fully understand
				{
					return (1); // Yay it's done (does that mean I don't need to check at the begining if fila == 4?
				}
			}
			tablero[fila][columna] = 0; // If the visibility isn't check we return the cell to 0
		}
		numero++; // tryes another number
	}
	return (0); // Couldn't find solution
}

void	resolver_con_restricciones(int col1up, int col2up, int col3up, int col4up, int col1down, int col2down, int col3down, int col4down, int row1left, int row2left, int row3left, int row4left, int row1right, int row2right, int row3right, int row4right)
{
	int	tablero[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	int	colUp[4] = {col1up, col2up, col3up, col4up};
	int	rowLeft[4] = {row1left, row2left, row3left, row4left};
	int	colDown[4] = {col1down, col2down, col3down, col4down};
	int	rowRight[4] = {row1right, row2right, row3right, row4right};
	int	fila;
	int	columna;

	fila = 0;
	columna = 0;
	if(resolver_tablero(tablero, rowLeft, rowRight, colUp, colDown, fila, columna))
	{
		imprimir_tablero(tablero);
	}
	else
	{
		ft_putchar('E');
		ft_putchar('r');
		ft_putchar('r');
	}
}
