#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
static unsigned char colors[800][800][3]={{{0}}};
//std::vector < std::vector < std::vector < char > > > colors;
const int iXmaxG=800;
const int iYmaxG=800;
const int MaxColorComponentValue=255;
char *comment="# ";
int ilosc_watkow=16;
 void call_from_thread(int startx, int starty)
 {
	 std::cout<<"Jestem Proces "<<starty/(iYmaxG/ilosc_watkow)<<". Pomaluje x:"<<startx<<"-"<<iXmaxG<<" y:"<<starty<<"-"<<starty+(iYmaxG/ilosc_watkow)<<" !\n";
	 static unsigned char color[3];
       /* screen ( integer) coordinate */
             int iX,iY;
             const int iXmax = iXmaxG;
           const int iYmax = iYmaxG;
             /* world ( double) coordinate = parameter plane*/
             double Cx,Cy;
             const double CxMin=-2.5;
             const double CxMax=1.5;
             const double CyMin=-2.0;
             const double CyMax=2.0;
             /* */
             double PixelWidth=(CxMax-CxMin)/iXmax;
             double PixelHeight=(CyMax-CyMin)/iYmax;
             /* color component ( R or G or B) is coded from 0 to 255 */
             /* it is 24 bit color RGB file */



                     /* Z=Zx+Zy*i  ;   Z0 = 0 */
                     double Zx, Zy;
                     double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
                     /*  */
                     int Iteration;
                     const int IterationMax=200;
                     /* bail-out value , radius of circle ;  */
                     const double EscapeRadius=2;
                     double ER2=EscapeRadius*EscapeRadius;

  for(iY=starty;iY<starty+(iYmaxG/ilosc_watkow);iY++)
         {
              Cy=CyMin + iY*PixelHeight;
              if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
              for(iX=startx;iX<iXmaxG;iX++)
              {
                         Cx=CxMin + iX*PixelWidth;
                         /* initial value of orbit = critical point Z= 0 */
                         Zx=0.0;
                         Zy=0.0;
                         Zx2=Zx*Zx;
                         Zy2=Zy*Zy;
                         /* */
                         for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
                         {
                             Zy=2*Zx*Zy + Cy;
                             Zx=Zx2-Zy2 +Cx;
                             Zx2=Zx*Zx;
                             Zy2=Zy*Zy;
                         };
                         /* compute  pixel color (24 bit = 3 bytes) */
                         if (Iteration==IterationMax)
                         { /*  interior of Mandelbrot set = black */
                            color[0]=0;
                            color[1]=0;
                            color[2]=0;
                         }
                      else
                         { /* exterior of Mandelbrot set = white */
                              color[0]=255; /* Red*/
                              color[1]=255;  /* Green */
                              color[2]=255;/* Blue */
                         };
                         /*write color to the file*/
                         //fwrite(color,1,3,fp);
                         colors[iY][iX][0]=color[0];
                         colors[iY][iX][1]=color[1];
                         colors[iY][iX][2]=color[2];
                 }

         }
 }

 int main()
 {
	 FILE * fp;
	     char *filename="new1.ppm";
	     fp= fopen(filename,"wb");

	     fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmaxG,iYmaxG,MaxColorComponentValue);

	 //colors.resize(iYmaxG,std::vector<std::vector<char> >(iXmaxG,std::vector<char>(3)));

	 std::vector<std::thread> t;
     for (int i = 0; i < ilosc_watkow; i++)
     {
    	 t.push_back(std::thread (call_from_thread,0,(iYmaxG/ilosc_watkow)*i));

     }

     for (int i = 0; i < ilosc_watkow; i++)
     {
         t[i].join();
     }
     t.clear();

     for (int i=0; i<iYmaxG;i++)
    	 for (int j=0; j<iXmaxG;j++)
    		 fwrite(colors[i][j],1,3,fp);



     fclose(fp);
     std::cout<<"Wyeksportowano do pliku "<<filename<<".\n";
 }
