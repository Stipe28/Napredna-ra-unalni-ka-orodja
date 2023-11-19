#include <iostream>
#include <cmath>

double
taylorArctan (double x, int n)
{
  double sum = 0.0;
  for (int i = 0; i < n; ++i)
    {
      int exponent = 2 * i + 1;
      double term = pow (-1, i) * pow (x, exponent) / (exponent);
      sum += term;
    }
  return sum;
}

double
trapezna (double a, double b, int n)
{
  double h = (b - a) / n;
  double sum =
    0.5 * (exp (3 * a) * taylorArctan (a / 2.0, 10) +
	   exp (3 * b) * taylorArctan (b / 2.0, 10));

  for (int i = 1; i < n; ++i)
    {
      double x = a + i * h;
      sum += exp (3 * x) * taylorArctan (x / 2.0, 10);
    }

  return sum * h;
}

int
main ()
{
  double a = 0.0;		// Spodnja meja integracije
  double b = M_PI / 4.0;	// Zgornja meja integracije
  int n = 10000;			// Število intervalov trapezne metode

  double result = trapezna (a, b, n);

  std::cout << "Rezultat z uporabo trapezne metode: " << result << std::endl;

  return 0;
}
