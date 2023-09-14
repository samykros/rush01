#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void imprimir_tablero(int tablero[4][4]);
int check_row(int tablero[4][4], int fila, int numero);
int check_column(int tablero[4][4], int columna, int numero);
int check_visibility_row_left(int tablero[4][4], int fila, int rowLeft, int rowRight);
int check_visibility_column_up(int tablero[4][4], int columna, int colUp, int colDown);
int check_visibility_row_right(int tablero[4][4], int fila, int rowLeft, int rowRight);
int check_visibility_column_down(int tablero[4][4], int columna, int colUp, int colDown);
int resolver_tablero(int tablero[4][4], int rowLeft[4], int rowRight[4], int colUp[4], int colDown[4], int fila, int columna);
void resolver_con_restricciones(int col1up, int col2up, int col3up, int col4up, int col1down, int col2down, int col3down, int col4down, int row1left, int row2left, int row3left, int row4left, int row1right, int row2right, int row3right, int row4right);
//int	atoi(char *str);

int main(int argc, char *argv[])
{
    if (argc != 17)
    {
        // habria que mirar como poner que: 0 < col1up < 5 igual con los demas.
        printf("Not a valid input\n");
        return 1;
    }

    // mi atoi function no funciona :(
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
    
    return 0;
}

// para imprimir, basico
void imprimir_tablero(int tablero[4][4])
{
	int i = 0;
	int j = 0;
	
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%d ", tablero[i][j]); // la posicion del tablero piensa, no es tan dificil
			j++;
		}
		printf("\n"); // cada 4 salto de linia duhhh
		i++;
	}
}





// Verifica si el número 'numero' es válido en la fila, si ya lo tenemos
int check_row(int tablero[4][4], int fila, int numero)
{
    for (int i = 0; i < 4; i++)
    {
        if (tablero[fila][i] == numero)
            return 0;
    }
    return 1;
}

// Verifica si el número 'numero' es válido en la columna, si ya lo tenemos
int check_column(int tablero[4][4], int columna, int numero)
{
    for (int i = 0; i < 4; i++)
    {
        if (tablero[i][columna] == numero)
            return 0;
    }
    return 1;
}








// Verifica las restricciones de visibilidad en fila
int check_visibility_row_left(int tablero[4][4], int fila, int rowLeft, int rowRight)
{
    int visible = 0;  
    int max_height = 0;
    
    for (int j = 0; j < 4; j++)
    {
        if (tablero[fila][j] == 0)
            return 1; // Casilla vacía, no podemos decidir todavía
            
        if (tablero[fila][j] > max_height)
        {
            max_height = tablero[fila][j];
            visible++;
        }
    }
    
    return visible == rowLeft;
}

// Verifica las restricciones de visibilidad en columna
int check_visibility_column_up(int tablero[4][4], int columna, int colUp, int colDown)
{
    int visible = 0;
    int max_height = 0;
    
    for (int i = 0; i < 4; i++)
    {
        if (tablero[i][columna] == 0)
            return 1; // Casilla vacía, no podemos decidir todavía
            
        if (tablero[i][columna] > max_height)
        {
            max_height = tablero[i][columna];
            visible++;
        }
    }
    
    return visible == colUp;
}

int check_visibility_row_right(int tablero[4][4], int fila, int rowLeft, int rowRight)
{
    int visible = 0;
    int max_height = 0;

    for (int j = 3; j >= 0; j--)  // Nota: empezamos desde la derecha
    {
        if (tablero[fila][j] == 0)
            return 1;

        if (tablero[fila][j] > max_height)
        {
            max_height = tablero[fila][j];
            visible++;
        }
    }

    return visible == rowRight;
}

// Verifica las restricciones de visibilidad en columna desde abajo
int check_visibility_column_down(int tablero[4][4], int columna, int colUp, int colDown)
{
    int visible = 0;
    int max_height = 0;

    for (int i = 3; i >= 0; i--)  // Nota: empezamos desde abajo
    {
        if (tablero[i][columna] == 0)
            return 1;

        if (tablero[i][columna] > max_height)
        {
            max_height = tablero[i][columna];
            visible++;
        }
    }

    return visible == colDown;
}










// Función de backtracking para resolver el tablero
int resolver_tablero(int tablero[4][4], int rowLeft[4], int rowRight[4], int colUp[4], int colDown[4], int fila, int columna)
{
    if (fila == 4)
        return 1;

    for (int numero = 1; numero <= 4; numero++)
    {
        if (check_row(tablero, fila, numero) && check_column(tablero, columna, numero))
        {
            tablero[fila][columna] = numero;

            if (check_visibility_row_left(tablero, fila, rowLeft[fila], rowRight[fila]) && 
                check_visibility_row_right(tablero, fila, rowLeft[fila], rowRight[fila]) &&
                check_visibility_column_up(tablero, columna, colUp[columna], colDown[columna]) && 
                check_visibility_column_down(tablero, columna, colUp[columna], colDown[columna]))
            {
                int nueva_fila = fila;
                int nueva_columna = columna + 1;

                if (nueva_columna == 4)
                {
                    nueva_columna = 0;
                    nueva_fila++;
                }

                if (resolver_tablero(tablero, rowLeft, rowRight, colUp, colDown, nueva_fila, nueva_columna))
                    return 1;
            }

            tablero[fila][columna] = 0;  // Restablecemos el valor si no se cumple la condición
        }
    }

    return 0;
}















void resolver_con_restricciones(int col1up, int col2up, int col3up, int col4up, int col1down, int col2down, int col3down, int col4down, int row1left, int row2left, int row3left, int row4left, int row1right, int row2right, int row3right, int row4right)
{
	int tablero[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	int colUp[4] = {col1up, col2up, col3up, col4up};
	int colDown[4] = {col1down, col2down, col3down, col4down};
	int rowLeft[4] = {row1left, row2left, row3left, row4left};
	int rowRight[4] = {row1right, row2right, row3right, row4right};
    int fila = 0;
    int columna = 0;

    printf("colUp: %d %d %d %d\n", col1up, col2up, col3up, col4up);
    printf("colDown: %d %d %d %d\n", col1down, col2down, col3down, col4down);
    printf("rowLeft: %d %d %d %d\n", row1left, row2left, row3left, row4left);
    printf("rowRight: %d %d %d %d\n", row1right, row2right, row3right, row4right);

    printf("\n");
	if (resolver_tablero(tablero, rowLeft, rowRight, colUp, colDown, fila, columna))
	{
		imprimir_tablero(tablero);
	} else
	{
		printf("No hay solución.\n");
	}
}
