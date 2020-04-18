////////////////////////////////////////////////////////////////////////////////
// Rotation, Translation, Skalierung und weitere Vektor-Operationen           //
// 18/04/2020 - Entwickelt von Finn Liebner                                   //
////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

enum {X, Y, Z};

#include "gnuplot.c"
#include "vektor.c"

double p[10][3]; // Stützvektoren
double q[10][3]; // Richtungsvektoren

////////////////////////////////////////////////////////////////////////////////

void main(void)
{
  plot_test();

  p[0][X] = 0.000; q[0][X] = 1.000;
  p[0][Y] = 0.000; q[0][Y] = 0.000;
  p[0][Z] = 0.000; q[0][Z] = 0.000;
  plot_vkt(p[0], q[0], 255,0,0);

  printf(" Vektor (rot): \n");
  prt_vektor(p[0], q[0]);
  plot_vkt(p[0], q[0], 255,0,0);
  
  rot_vektor(p[0], 0, 0, 90);
  rot_vektor(q[0], 0, 0, 90);

  printf("\n Vektor nach der Drehung (blau): \n");
  prt_vektor(p[0], q[0]);
  plot_vkt(p[0], q[0], 0,0,255);
  
  plot_term();
  plot_svg();

  printf(" Außerdem kann dieses Programm Vektoren Skalieren und Verschieben. Teste dazu mal skl_vektor() und trl_vektor() aus. \n");
}

////////////////////////////////////////////////////////////////////////////////
