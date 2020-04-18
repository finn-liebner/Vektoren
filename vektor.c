////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double rad(double deg);
double deg(double rad);
double btr_vektor(double vektor[]);
void   skl_vektor(double vektor[], double s);
void   trl_vektor(double vektor[], double tx, double ty, double tz);
void   cpy_vektor(double vd[], double vs[]);
void   rot_vektor(double vektor[], double alpha, double beta, double gamma);
void   mul_matrix(double a[], double b[3][3]);
void   prt_vektor(double p[], double q[]);

////////////////////////////////////////////////////////////////////////////////

// Grad zu Radiant
double rad(double deg)
{
  return (deg/180)*M_PI;
}

////////////////////////////////////////////////////////////////////////////////

// Radiant zu Grad
double deg(double rad)
{
  return (rad/M_PI)*180;
}

////////////////////////////////////////////////////////////////////////////////

// Betrag bzw. Länge
double btr_vektor(double vektor[])
{
  return sqrt(pow(vektor[0],2)+pow(vektor[1],2)+pow(vektor[2],2));
}

////////////////////////////////////////////////////////////////////////////////

// Skalierung
void skl_vektor(double vektor[], double s)
{
  vektor[0] = vektor[0] * s;
  vektor[1] = vektor[1] * s;
  vektor[2] = vektor[2] * s;
}

////////////////////////////////////////////////////////////////////////////////

// Translation in X, Y und Z-Richtung
void trl_vektor(double vektor[], double tx, double ty, double tz)
{
  vektor[0] = vektor[0] + tx;
  vektor[1] = vektor[1] + ty;
  vektor[2] = vektor[2] + tz;
}

////////////////////////////////////////////////////////////////////////////////

// Vektor kopieren
void cpy_vektor(double vd[], double vs[])
{
  for(unsigned int n=0; n<3; n++)
  {
    vd[n] = vs[n];
  }
}

////////////////////////////////////////////////////////////////////////////////

// Rotation um X, Y und Z-Achse
void rot_vektor(double vektor[], double alpha, double beta, double gamma)
{
  double w0 = rad(alpha);
  double rx[3][3] =
  {
    {1.0,     0.0,      0.0},
    {0.0, cos(w0), -sin(w0)},
    {0.0, sin(w0),  cos(w0)}
  };
  mul_matrix(vektor, rx);

  double w1 = rad(beta);
  double ry[3][3] =
  {
    { cos(w1), 0.0, sin(w1)},
    {     0.0, 1.0,     0.0},
    {-sin(w1), 0.0, cos(w1)}
  };
  mul_matrix(vektor, ry);

  double w2 = rad(gamma);
  double rz[3][3] =
  {
    {cos(w2), -sin(w2), 0.0},
    {sin(w2),  cos(w2), 0.0},
    {    0.0,      0.0, 1.0}
  };
  mul_matrix(vektor, rz);
}

////////////////////////////////////////////////////////////////////////////////

// Matrizenmultiplikation für die Rotation
void mul_matrix(double a[], double b[3][3])
{
  double c[3] = {0.0, 0.0, 0.0};
  for(int r=0; r<3; r++)
  {
    for(int n=0; n<3; n++)
    {
      c[r] = c[r] + a[n]*b[r][n];
    }
  }
  for(int r=0; r<3; r++)
  {
    a[r] = c[r];
  }
}

////////////////////////////////////////////////////////////////////////////////

// Ausgabe eines Vektors
void prt_vektor(double p[], double q[])
{
  printf(" ┌─    ─┐ ┌─    ─┐ \n");
  printf(" │ %4.f │ │ %4.f │ \n", p[X], q[X]);
  printf(" │ %4.f │ │ %4.f │ \n", p[Y], q[Y]);
  printf(" │ %4.f │ │ %4.f │ \n", q[Z], q[Z]);
  printf(" └─    ─┘ └─    ─┘ \n");
}

////////////////////////////////////////////////////////////////////////////////
