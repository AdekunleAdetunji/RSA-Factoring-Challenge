#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>

/**
 * pollard_rho - algorithm to use to find the factors of an integer
 * @n: the number to be factorized
 */
void pollard_rho(mpz_t n)
{
	mpz_t two, x, y, d;

	mpz_inits(two, x, y, d, NULL);
	mpz_set_ui(two, 2);

	if (mpz_divisible_p(n, two))
	{
		gmp_printf("%Zd=%Zd*%Zd\n", n, n, two);
		mpz_clears(two, x, y, d, NULL);
		return;
	}

	mpz_set_ui(x, 2);
	mpz_set_ui(y, 2);
	mpz_set_ui(d, 1);

	while (mpz_cmp_ui(d, 1) == 0)
	{
		mpz_mul(x, x, x);
		mpz_add_ui(x, x, 1);
		mpz_mod(x, x, n);

		mpz_mul(y, y, y);
		mpz_add_ui(y, y, 1);
		mpz_mod(y, y, n);
		mpz_mul(y, y, y);
		mpz_add_ui(y, y, 1);
		mpz_mod(y, y, n);

		mpz_sub(d, x, y);
		mpz_abs(d, d);
		mpz_gcd(d, d, n);
	}

	gmp_printf("%Zd=%Zd*%Zd\n", n, d, n);
	mpz_clears(two, x, y, d, NULL);
}

/**
 * main - main function where the input digit is read and the pollard_rho
 * function is called
 * @argc: The number of arguments supplied on the command line
 * @argv: A vector of the argument strings supplied on the command line
 * Return: 1
 */
int main(int argc, char *argv[])
{
	char line[256];
	FILE *file;
	mpz_t num;

	if (argc < 2)
	{
		printf("Usage: ./program <filename>\n");
		return (1);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Failed to open the file.\n");
		return (1);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		mpz_init(num);
		mpz_set_str(num, line, 10);
		pollard_rho(num);
		mpz_clear(num);
	}

	fclose(file);
	return (0);
}
