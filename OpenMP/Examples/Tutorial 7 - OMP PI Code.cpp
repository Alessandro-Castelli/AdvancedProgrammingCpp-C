# include <cstdlib>
# include <cstring>
# include <iomanip>
# include <iostream>
# include <omp.h>

using namespace std;

int main ( int argc, char *argv[] );
void r8_test ( int r8_logn_max );
double r8_abs ( double r8 );
double r8_pi_est_omp ( int n );
double r8_pi_est_seq ( int n );

//****************************************************************************80

int main ( int argc, char *argv[] )
{
  int r8_logn_max = 1000000;

  cout << "\n";
  cout << "COMPUTE_PI\n";
  cout << "  C++/OpenMP version\n";
  cout << "\n";
  cout << "  Estimate the value of PI by summing a series.\n";

  cout << "\n";
  cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";     // Comando per estrarre il numero di processori
  cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";   // Comando per estrarre il numero di threads

  r8_test ( r8_logn_max );  // Eseguo r8_test con input 10 = r8_logn_max
//
//  Terminate.
//
  cout << "\n";
  cout << "COMPUTE_PI\n";
  cout << "  Normal end of execution.\n";

  return 0;
}
//****************************************************************************80

void r8_test ( int logn_max ) // Qui l'input della funzione è 10 e questa è la funzione principale

//****************************************************************************80
//
//  Purpose:
//
//    R8_TEST estimates the value of PI using double.
//
//  Discussion:
//
//    PI is estimated using N terms.  N is increased from 10^2 to 10^LOGN_MAX.
//    The calculation is repeated using both sequential and Open MP enabled code.
//    Wall clock time is measured by calling SYSTEM_CLOCK.
{
  double error;
  double estimate;
  int logn;
  char mode[4];
  int n;
  double r8_pi = 3.141592653589793;
  double wtime;

  cout << "\n";
  cout << "R8_TEST:\n";
  cout << "  Estimate the value of PI,\n";
  cout << "  using double arithmetic.\n";
  cout << "\n";
  cout << "  N = number of terms computed and added;\n";
  cout << "\n";
  cout << "  MODE = SEQ for sequential code;\n";
  cout << "  MODE = OMP for Open MP enabled code;\n";
  cout << "  (performance depends on whether Open MP is used,\n";
  cout << "  and how many processes are available)\n";
  cout << "\n";
  cout << "  ESTIMATE = the computed estimate of PI;\n";
  cout << "\n";
  cout << "  ERROR = ( the computed estimate - PI );\n";
  cout << "\n";
  cout << "  TIME = elapsed wall clock time;\n";
  cout << "\n";
  cout << "  Note that you can''t increase N forever, because:\n";
  cout << "  A) ROUNDOFF starts to be a problem, and\n";
  cout << "  B) maximum integer size is a problem.\n";
  cout << "\n";
  cout << "             N Mode    Estimate        Error           Time\n";
  cout << "\n";

  n = 1;

  for ( logn = 1; logn <= logn_max; logn++ )
  {
//
//  Note that when I set N = 10**LOGN directly, rather than using
//  recursion, I got inaccurate values of N when LOGN was "large",
//  that is, for LOGN = 10, despite the fact that N itself was
//  a KIND = 8 integer!  
// 
//  Sequential calculation.
//
    strcpy ( mode, "SEQ" );

    wtime = omp_get_wtime ( ); // tempo di esecuzione

    estimate = r8_pi_est_seq ( n ); // valore stimato in maniera sequenziale classica

    wtime = omp_get_wtime ( ) - wtime;

    error = r8_abs ( estimate - r8_pi );

    cout << "  " << setw(14) << n
         << "  " << setw(3)  << mode
         << "  " << setw(14) << estimate
         << "  " << setw(14) << error 
         << "  " << setw(14) << wtime << "\n";
//
//  Open MP enabled calculation.
//
    strcpy ( mode, "OMP" );

    wtime = omp_get_wtime ( );

    estimate = r8_pi_est_omp ( n );  // valore stimato in maniera parallela

    wtime = omp_get_wtime ( ) - wtime;

    error = r8_abs ( estimate - r8_pi );

    cout << "  " << setw(14) << n
         << "  " << setw(3)  << mode
         << "  " << setw(14) << estimate
         << "  " << setw(14) << error 
         << "  " << setw(14) << wtime << "\n";

    n = n * 10;
  }

  return;
}
//****************************************************************************80

double r8_abs ( double r8 )

//****************************************************************************80
//
//  Purpose:
// 
//    R8_ABS returns the absolute value of a double.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    14 November 2007
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, double R8, a real number.
//
//    Output, double R8_ABS, the absolute value of R4.
//
{
  double value;

  if ( 0.0 <= r8 )
  {
    value = r8;
  }
  else
  {
    value = - r8;
  }
  return value;
}
//****************************************************************************80

double r8_pi_est_omp ( int n )

//****************************************************************************80
//
//  Purpose:
//
//    R8_PI_EST_OMP estimates the value of PI, using Open MP.
//
//  Discussion:
//
//    The calculation is based on the formula for the indefinite integral:
//
//      Integral 1 / ( 1 + X**2 ) dx = Arctan ( X ) 
//
//    Hence, the definite integral
//
//      Integral ( 0 <= X <= 1 ) 1 / ( 1 + X**2 ) dx 
//      = Arctan ( 1 ) - Arctan ( 0 )
//      = PI / 4.
//
//    A standard way to approximate an integral uses the midpoint rule.
//    If we create N equally spaced intervals of width 1/N, then the
//    midpoint of the I-th interval is 
//
//      X(I) = (2*I-1)/(2*N).  
//
//    The approximation for the integral is then:
//
//      Sum ( 1 <= I <= N ) (1/N) * 1 / ( 1 + X(I)**2 )
//
//    In order to compute PI, we multiply this by 4; we also can pull out
//    the factor of 1/N, so that the formula you see in the program looks like:
//
//      ( 4 / N ) * Sum ( 1 <= I <= N ) 1 / ( 1 + X(I)**2 )
//
//    Until roundoff becomes an issue, greater accuracy can be achieved by 
//    increasing the value of N.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    13 November 2007
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the number of terms to add up.
//
//    Output, double R8_PI_EST_OMP, the estimated value of pi.
//
{
  double h;
  double estimate;
  int i;
  double sum2;
  double x;

  h = 1.0 / ( double ) ( 2 * n );

  sum2 = 0.0;

# pragma omp parallel \
  shared ( h, n ) \
  private ( i, x )

# pragma omp for reduction ( + : sum2 )

  for ( i = 1; i <= n; i++ )
  {
    x = h * ( double ) ( 2 * i - 1 );
    sum2 = sum2 + 1.0 / ( 1.0 + x * x );
  }

  estimate = 4.0 * sum2 / ( double ) ( n );

  return estimate;
}
//****************************************************************************80

double r8_pi_est_seq ( int n )

//****************************************************************************80
//
//  Purpose:
//
//    R8_PI_EST_SEQ estimates the value of PI, using sequential execution.
//
//  Discussion:
//
//    The calculation is based on the formula for the indefinite integral:
//
//      Integral 1 / ( 1 + X**2 ) dx = Arctan ( X ) 
//
//    Hence, the definite integral
//
//      Integral ( 0 <= X <= 1 ) 1 / ( 1 + X**2 ) dx 
//      = Arctan ( 1 ) - Arctan ( 0 )
//      = PI / 4.
//
//    A standard way to approximate an integral uses the midpoint rule.
//    If we create N equally spaced intervals of width 1/N, then the
//    midpoint of the I-th interval is 
//
//      X(I) = (2*I-1)/(2*N).  
//
//    The approximation for the integral is then:
//
//      Sum ( 1 <= I <= N ) (1/N) * 1 / ( 1 + X(I)**2 )
//
//    In order to compute PI, we multiply this by 4; we also can pull out
//    the factor of 1/N, so that the formula you see in the program looks like:
//
//      ( 4 / N ) * Sum ( 1 <= I <= N ) 1 / ( 1 + X(I)**2 )
//
//    Until roundoff becomes an issue, greater accuracy can be achieved by 
//    increasing the value of N.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    13 November 2007
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, integer N, the number of terms to add up.
//
//    Output, double R8_PI_EST_SEQ, the estimated value of pi.
//
{
  double h;
  double estimate;
  int i;
  double sum2;
  double x;

  h = 1.0 / ( double ) ( 2 * n );

  sum2 = 0.0;

  for ( i = 1; i <= n; i++ )
  {
    x = h * ( double ) ( 2 * i - 1 );
    sum2 = sum2 + 1.0 / ( 1.0 + x * x );
  }

  estimate = 4.0 * sum2 / ( double ) ( n );

  return estimate;
}


