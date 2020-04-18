////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int  plot_test(void);
void plot_vkt(double p[], double q[], int r, int g, int b);
void plot_pkt(double x[], int r, int g, int b);
void plot_clr(void);
void plot_term(void);
void plot_svg(void);
void plot_png(void);

////////////////////////////////////////////////////////////////////////////////

int plot_test(void)
{
  if(system("gnuplot -e \"exit\""))
  {
    printf("GNUplot fehlt.\n");
    return(-1);
  }
  else
  {
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////

bool plot_init = true;

void plot_vkt(double p[], double q[], int r, int g, int b)
{
  FILE *fp0;

  if(plot_init == true)
  {
    plot_clr();
    plot_init = false;
  }
  else
  {
    fp0 = fopen("data0.dat", "a");

    fprintf(fp0, " % 7f % 7f % 7f % 7f % 7f % 7f 0x%02x%02x%02x \n",
            p[X], p[Y], p[Z], q[X], q[Y], q[Z], r, g, b);

    fclose(fp0);
  }
}

////////////////////////////////////////////////////////////////////////////////

void plot_pkt(double p[], int r, int g, int b)
{
  FILE *fp1;

  if(plot_init == true)
  {
    plot_clr();
    plot_init = false;
  }
  else
  {
    fp1 = fopen("data1.dat", "a");

    fprintf(fp1, " % 7f % 7f % 7f 0x%02x%02x%02x \n",
            p[X], p[Y], p[Z], r, g, b);

    fclose(fp1);
  }
}

////////////////////////////////////////////////////////////////////////////////

void plot_clr(void)
{
  FILE *fp0;
  FILE *fp1;

  fp0 = fopen("data0.dat", "w");
  fp1 = fopen("data1.dat", "w");

  if(fp0 != NULL && fp1 != NULL)
  {
    fprintf(fp0, "# %8s %9s %9s %9s %9s %9s %8s \n",
                 "Px", "Py", "Pz", "Bx", "By", "Bz", "RGB");
    fprintf(fp1, "# %8s %9s %9s %8s \n", "X", "Y", "Z", "RGB");
  }
  else
  {
    printf("Datei konnte nicht geöffnet werden.\n");
  }

  fclose(fp0);
  fclose(fp1);
}

////////////////////////////////////////////////////////////////////////////////

void plot_term(void)
{
  char cmd[] =
  {
    "gnuplot "
    "-e \"set terminal sixelgd size 1280,1080 font 'Consolas' 20\" "
    "-e \"set object rect from screen 0,0 to screen 1.1,1.1 "
         "behind fc rgb '#181818' fs solid noborder\" "
    "-e \"set key textcolor rgb 'white'\" "
    //"-e \"set style line 101 lc rgb '#FFFFFF' lt 2 lw 2\" "
    //"-e \"set border front ls 101\" "
    "-e \"set border lw 1 lc rgb 'white'\" "
    "-e \"set xtics textcolor rgb 'white'\" "
    "-e \"set ytics textcolor rgb 'white'\" "
    "-e \"set ztics 1 textcolor rgb 'white'\" "
    //"-e \"set xlabel 'Numer of Points'\" "
    "-e \"set xlabel 'X' textcolor rgb 'white'\" "
    "-e \"set ylabel 'Y' textcolor rgb 'white'\" "
    "-e \"set zlabel 'Z' textcolor rgb 'white'\" "

    "-e \"set xrange [-3:3]\" "
    "-e \"set yrange [-3:3]\" "
    "-e \"set zrange [-3:3]\" "
    "-e \"set xyplane at -3\" "
    //"-e \"set view 60,40\" "
    //"-e \"set view 0,0\" "
    "-e \"set view equal xyz\" "
    //"-e \"set label 'n=500' at screen 0.1,0.15 tc rgb 'white' font 'Consolas,26'\" "
    //"-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
    //     "vectors lw 3 lc rgb variable notitle\" "
    "-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
         "vectors lw 3 lc rgb variable notitle, "
         "'data1.dat' using 1:2:3:4 with points "
         "pt 2 ps 3 lw 2 lc rgb variable notitle\" "
  };
  system(cmd);
}

////////////////////////////////////////////////////////////////////////////////

void plot_svg(void)
{
  time_t now;
  time(&now);
  struct tm *t;
  t = localtime(&now);

  char cmd[900] =
  {
    "gnuplot "
    "-e \"set terminal svg size 1280,1080 fname 'Verdana'\" "
    //"-e \"set output 'data0.svg'\" "
  };

  char cmd1[40];
  sprintf(cmd1, "-e \"set output 'plot %02d-%02d-%02d %02d-%02d-%04d.svg'\" ",
          t->tm_hour, t->tm_min, t->tm_sec, t->tm_mday, (t->tm_mon+1), (t->tm_year+1900));

  char cmd2[] =
  {
    "-e \"set style line 80 lt rgb '#808080'\" "
    "-e \"set border back linestyle 80\" " // 255, 15, 4095
    "-e \"set style line 81 dt 3  # dashed\" "
    "-e \"set style line 81 lt rgb '#808080' lw 0.5  # grey\" "
    "-e \"set grid back linestyle 81\" "
    "-e \"set tics nomirror\" "
    //"-e \"set linetype 1 lc rgb '#0072bd' pt 9 pi -10 ps 2 dt 3\" "
    "-e \"set bmargin 4\" "
    "-e \"set lmargin 5\" "
    "-e \"set rmargin 4\" "
    "-e \"set key top right\" "
    "-e \"set key spacing 1.5\" "
    "-e \"set key width -12\" "
    "-e \"set style textbox opaque noborder\" "

    //"-e \"set polar\" "
    //"-e \"show polar\" "
    "-e \"set xrange [-3:3]\" "
    "-e \"set yrange [-3:3]\" "
    "-e \"set zrange [-3:3]\" "
    "-e \"set xyplane at -3\" "
    //"-e \"set view 60,40\" "
    //"-e \"set view 0,0\" "
    "-e \"set view equal xyz\" "

    //"-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
    //     "vectors lw 2 lc rgb variable notitle\" "
    "-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
         "vectors lw 3 lc rgb variable notitle, "
         "'data1.dat' using 1:2:3:4 with points "
         "pt 2 ps 3 lw 2 lc rgb variable notitle\" "
    //"-e \"splot [x=-3:3] [y=-3:3] sin(x)*cos(y) lt rgb '#FF0000' lw 1\" "
  };

  strcat(cmd, cmd1);
  strcat(cmd, cmd2);

  system(cmd);
}

////////////////////////////////////////////////////////////////////////////////

int cnt = 0;

void plot_png(void)
{
  char cmd[900] =
  {
    "gnuplot "
    "-e \"set terminal png size 1280,1080 font 'Consolas' 16\" "
  };

  char cmd1[40];
  sprintf(cmd1, "-e \"set output 'Gnuplot/plot%04d.png'\" ", cnt);
  cnt++;

  char cmd2[] =
  {
    "-e \"set object rect from screen 0,0 to screen 1.1,1.1 "
         "behind fc rgb '#181818' fs solid noborder\" "
    "-e \"set key textcolor rgb 'white'\" "
    "-e \"set border lw 1 lc rgb 'white'\" "
    "-e \"set xtics textcolor rgb 'white' offset -0.4,-0.4\" "
    "-e \"set ytics textcolor rgb 'white' offset 0.3,-0.2\" "
    "-e \"set ztics 1 textcolor rgb 'white'\" "
    "-e \"set xlabel 'X' textcolor rgb 'white'\" "
    "-e \"set ylabel 'Y' textcolor rgb 'white'\" "
    "-e \"set zlabel 'Z' textcolor rgb 'white'\" "
    "-e \"set xrange [-3:3]\" "
    "-e \"set yrange [-3:3]\" "
    "-e \"set zrange [-3:3]\" "
    "-e \"set xyplane at -3\" "
    "-e \"set view equal xyz\" "
    //"-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
    //     "vectors lw 3 lc rgb variable notitle\" "
    "-e \"splot 'data0.dat' using 1:2:3:4:5:6:7 with "
         "vectors lw 3 lc rgb variable notitle, "
         "'data1.dat' using 1:2:3:4 with points "
         "pt 2 ps 3 lw 2 lc rgb variable notitle\" "
    //"-e \"splot [x=-3:3] [y=-3:3] sin(x)*cos(y) lt rgb '#FF0000' lw 1\" "
  };

  strcat(cmd, cmd1);
  strcat(cmd, cmd2);

  system(cmd);
}

////////////////////////////////////////////////////////////////////////////////
