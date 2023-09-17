#include "matrex.h"

void	fill_mt(t_matrex *mt, double *values)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (i < mt->rows)
	{
		j = 0;
		while (j < mt->colums)
		{
			mt->matrex[i][j] = values[k];
			k++;
			j++;
		}
		i++;
	}
}

double	*create_colums(int c)
{
	int		i;
	double	*new_col;

	i = 0;
	new_col = malloc(c * sizeof(double));
	while (i < c)
	{
		new_col[i] = .0;
		i++;
	}
	return (new_col);
}

t_matrex	*creat_matrex(int rows, int colums)
{
	t_matrex	*new_mt;
	int			i;
	double		**mt;

	if (rows <= 0 || colums <= 0)
		return (NULL);
	new_mt = malloc(sizeof(t_matrex));
	i = 0;
	new_mt->rows = rows;
	new_mt->colums = colums;
	mt = malloc(sizeof(double *) * rows);
	while (i < rows)
		mt[i++] = create_colums(colums);
	new_mt->matrex = mt;
	return (new_mt);
}

t_matrex	*mt_multiplication(t_matrex *mt1, t_matrex *mt2)
{
	t_matrex	*result;
	int			i;
	int			j;
	int			k;

	i = 0;
	if (!mt1 || !mt2 || mt1->colums != mt2->rows)
		return (NULL);
	result = creat_matrex(mt1->rows, mt2->colums);
	while (i < mt1->rows)
	{
		k = 0;
		while (k < mt2->colums)
		{
			j = 0;
			while (j < mt1->colums)
			{
				result->matrex[i][k] += (mt1->matrex[i][j] * mt2->matrex[j][k]);
				j++;
			}
			k++;
		}
		i++;
	}
	return (result);
}

void	free_mt(t_matrex *mt)
{
	int	i;

	i = 0;
	while (i < mt->rows)
		free(mt->matrex[i++]);
	free(mt->matrex);
	free(mt);
}

t_matrex	*y_rotation(float theta)
{
	t_matrex	*rotation;
	double		values[9];

	values[0] = cos(theta);
	values[1] = 0;
	values[2] = sin(theta);
	values[3] = 0;
	values[4] = 1;
	values[5] = 0;
	values[6] = -sin(theta);
	values[7] = 0;
	values[8] = cos(theta);
	rotation = creat_matrex(3, 3);
	fill_mt(rotation, values);
	return (rotation);
}

t_matrex	*x_rotation(float theta)
{
	t_matrex	*rotation;
	double		values[9];

	values[0] = 1;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
	values[4] = cos(theta);
	values[5] = -sin(theta);
	values[6] = 0;
	values[7] = sin(theta);
	values[8] = cos(theta);
	rotation = creat_matrex(3, 3);
	fill_mt(rotation, values);
	return (rotation);
}

t_matrex	*z_rotation(float theta)
{
	t_matrex	*rotation;
	double		values[9];

	values[0] = cos(theta);
	values[1] = -sin(theta);
	values[2] = 0;
	values[3] = sin(theta);
	values[4] = cos(theta);
	values[5] = 0;
	values[6] = 0;
	values[7] = 0;
	values[8] = 1;
	rotation = creat_matrex(3, 3);
	fill_mt(rotation, values);
	return (rotation);
}

t_matrex	*rotation_mt(t_matrex *point, float x, float y, float z)
{
	t_mat		mat;
	t_matrex	*result;
	t_matrex	*tmp;

	mat.y_rotation_mt = y_rotation(y);
	mat.x_rotation_mt = x_rotation(x);
	mat.z_rotation_mt = z_rotation(z);
	result = mt_multiplication(mat.y_rotation_mt, point);
	tmp = mt_multiplication(mat.x_rotation_mt, result);
	free_mt(result);
	result = tmp;
	tmp = mt_multiplication(mat.z_rotation_mt, result);
	free_mt(result);
	result = tmp;
	free_mt(mat.y_rotation_mt);
	free_mt(mat.x_rotation_mt);
	free_mt(mat.z_rotation_mt);
	return (result);
}

t_matrex	*projection_mt(t_matrex *point)
{
	double		values[6];
	t_matrex	*projection;
	t_matrex	*result;

	values[0] = 1;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
	values[4] = 1;
	values[5] = 0;
	projection = creat_matrex(2, 3);
	fill_mt(projection, values);
	result = mt_multiplication(projection, point);
	free_mt(projection);
	return (result);
}
