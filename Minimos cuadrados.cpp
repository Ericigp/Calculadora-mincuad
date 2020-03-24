/**************************************************************************************************/
/** Programa que toma datos de un fichero llamado datos.txt y realiza los cálculos oportunos     **/
/** para realizar el ajuste por mínimos cuadrados requerido para las prácticas de TEB.           **/
/** El programa saca los datos a un archivo .csv llamado resultados para asi facilitar el        **/
/** copiarlos directamente a una tabla de lyx/LaTeX mediante la función pegado simple.           **/
/** Ademas tambien realiza cálculos de estadistica descriptiva tales como la media               **/
/** y el coeficiente de correlación linear.                                                      **/
/** Eric Iglesias Peral 2019                                                                     **/
/**************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#define MAX 300

using namespace std;


void leerfichero (int& n,double datos[][MAX]);
double media (double datos[][MAX],int n);
double x(double datos[][MAX],int n,double resultados[][7]);
double y(double datos[][MAX],int n,double resultados[][7]);
double xy(double datos[][MAX],int n,double resultados[][7]);
double x2(double datos[][MAX],int n,double resultados[][7]);
double y2(double datos[][MAX],int n,double resultados[][7]);
double xX(double datos[][MAX],double mediaX,int n,double resultados[][7]);
double Yalfaxbeta (double datos[][MAX],double alfa,double beta,int n,double resultados[][7]);
double alfa (int n,double X, double Y,double XY,double X2);
double erroralfa(double Yaxb,double XX,int n);
double beta (double A,double X,double Y, int n);
double errorbeta(double errorA,double X, int n);
double rlin (double X,double Y, double XY, double X2,double Y2, int n);
void mostrarresultados(double resultados[][7], int n);
void excel (int n,double resultados [][7]);

int main (void)
{
    double datos[MAX][MAX];
    double resultados[MAX][7];

    int n;
    double X,Y,mediaX,A,B,XY,X2,Y2,XX,Yaxb,errorA,errorB,r;

    leerfichero(n,datos);
    mediaX=media(datos,n);
    X=x(datos,n,resultados);
    Y=y(datos,n,resultados);
    XY=xy(datos,n,resultados);
    X2=x2(datos,n,resultados);
    Y2=y2(datos,n,resultados);
    XX=xX(datos,mediaX,n,resultados);
    A=alfa(n,X,Y,XY,X2);
    B=beta(A,X,Y,n);
    Yaxb=Yalfaxbeta(datos,A,B,n,resultados);
    errorA=erroralfa(Yaxb,X,n);
    errorB=errorbeta(errorA,X,n);
    r=rlin(X,Y,XY,X2,Y2,n);

    excel(n,resultados);

    cout<<"La matriz de resultante es: "<<endl<<endl;
    mostrarresultados(resultados,n);

    cout<<endl;
    cout<<"La media vale : "<<mediaX<<endl;
    cout<<"La A vale : "<<A<<endl;
    cout<<"Su error vale : "<<errorA<<endl;
    cout<<"La B vale : "<<B<<endl;
    cout<<"Su error vale : "<<errorB<<endl;
    cout<<"El coeficiente de relacion lineal vale : "<<r<<endl;

    system("pause");

    return 0;
}

void leerfichero (int& n,double datos[][MAX])
{
    ifstream fich;
    int i=0;

    fich.open("Datos.txt");
    if(!(fich.is_open()))
    {
        cout<<"Error al abrir el fichero de datos"<<endl;
    }


    else
        while (!fich.eof())
        {
            fich>>datos [i][0];
            fich>>datos [i][1];
            i++;
        }
    n=i;
    fich.close();
    return;
}
void excel (int n,double resultados [][7])
{
    int i=0;
    ofstream fich;

    fich.open("Resultados.csv");

    while ((!fich.eof())&& (i<n))
    {
        fich<<resultados[i][0]<<";"<<resultados[i][1]<<";"<<resultados[i][2]<<";"<<resultados[i][3]<<";"<<resultados[i][4]<<";"<<resultados[i][5]<<";"<<resultados[i][6]<<endl;

        i++;
    }

    fich.close();

    return;

}

double x(double datos[][MAX],int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        resultados[i][0]=datos[i][0];
        suma+=datos[i][0];
    }

    return suma;
}

double y(double datos[][MAX],int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        aux=0.0;
        aux=datos[i][1];
        resultados[i][1]=aux;
        suma+=aux;
    }

    return suma;
}

double x2(double datos[][MAX], int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        aux=0.0;
        aux=datos[i][0]*datos[i][0];
        resultados[i][3]=aux;
        suma+=aux;
    }

    return suma;
}

double xy(double datos[][MAX],int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        aux=0.0;
        aux=datos[i][0]*datos[i][1];
        resultados[i][2]=aux;
        suma+=aux;
    }

    return suma;
}

double y2(double datos[][MAX],int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        aux=0.0;
        aux=datos[i][1]*datos[i][1];
        resultados[i][4]=aux;
        suma+=aux;
    }

    return suma;
}

double xX(double datos[][MAX],double mediaX,int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        if ((datos[i][0]==0.0) && (datos[i][1]==0.0))
            continue;
        else
        {
            aux=0.0;
            aux=(datos[i][0]-mediaX)*(datos[i][0]-mediaX);
            resultados[i][5]=aux;
            suma+=aux;
        }
    }

    return suma;
}

double Yalfaxbeta (double datos[][MAX],double alfa,double beta,int n,double resultados[][7])
{
    double suma=0.0,aux;
    int i;

    for(i=0;i<n;i++)
    {
        if ((datos[i][0]==0.0) && (datos[i][1]==0.0))
            continue;
        else
        {
            aux=0.0;
            aux=(datos[i][1]-alfa*datos[i][0]-beta);
            resultados[i][6]=aux;
            suma+=aux;
        }
    }

    return suma;
}

double media (double datos[][MAX],int n)
{
    double suma=0.0;
    int i;

    for(i=0;i<=n;i++)
        suma+=datos[i][0];

    return suma/n;
}

double alfa (int n,double X, double Y,double XY,double X2)
{
    double alfa;

    alfa=(n*XY-X*Y)/(n*X2-X*X);

    return alfa;
}

double beta (double A,double X,double Y, int n)
{
    double beta;

    beta=(Y-A*X)/n;

    return beta;
}

double erroralfa(double Yaxb,double XX,int n)
{
    double EA;

    EA=sqrt((Yaxb*Yaxb)/((n-2.0)*XX));

    return EA;
}

double errorbeta(double errorA,double X, int n)
{
    double EB;

    EB= errorA*sqrt(X/(n*1.0));

    return EB;
}
double rlin (double X,double Y, double XY, double X2,double Y2, int n)
{
    double r;

    r=(n*XY-X*Y)/sqrt((n*X2-X*X)*(n*Y2-Y*Y));

    return r;
}

void mostrarresultados(double resultados[][7], int n)
{
    int i,j;

    cout<<"x \t\t y \t\t xy \t\t x^2 \t\t y^2 \t\t (x-X)^2 \t\t (y-ax-b)^2 "<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<7;j++)
            cout<<resultados[i][j]<<"\t\t";
        cout<<endl;
    }
    return;
}
