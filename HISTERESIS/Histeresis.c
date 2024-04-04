#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define L 24

//para generacion de numeros aleatorios
#define NormRANu (2.3283063671E-10F)

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran,ig1,ig2,ig3;

void ini_ran(int semilla);
float Random(void);
void configuracionInicial(int flag,int *s);
void guardaConfiguracion(int *s, char name[]);
void lee_input(double *beta_inicial,double *beta_final,double *delta_beta,int *flag,int *semilla,int *N_Ter,int *N_med,int *N_Met);
void Probabilidad_beta(double beta, double expon[]);
void Metropolis(int*s,int*x_right, int*x_left, int*y_up, int *y_down,double *expon);
double energia(int *s,int *xp,int *yp); //E
double magnetizacion(int *s);   //M
void Vector_Medidas(int *s,double *vec_mag,double *vec_energ,int *xp, int *yp, int N_m);
void var(double *serie,int Numero, double *Media, double *Varianza);
void inicio_vectores(double *e_medio,double *e_medio_cuadrado,double *m_medio,double *m_medio_cuadrado,double *m_medio_absoluto,double *Cv,double *X,double *var_energia,double *var_magnetizacion,int N_pasos);
void escribir_fichero(double e_medio[], double m_medio[],double e_medio_cuadrado[],double m_medio_absoluto[], double m_medio_cuadrado[],double X[], double Cv[],double error_energia[],double error_magnetizacion[], int N_pasos);
void calculaValoresMedios(int N_med,double *Energia,double *Magnetizacion,double *mediaEnergia,double *mediaMagnetizacion,double *media2Energia,double *media2Magnetizacion,double *mediaMagnetizacionAbsoluta,double *Cv,double *X,double *error_energia,double *error_magnetizacion,int beta);

int main(){

    int s[L*L]; //red de spines
    double expon[5];    //tabla de probabilidades

    int flag,semilla;


    int i,sentido,N_betas, N_m, N_M,n; //variables mudas
    int N_pasos;





    double beta;
    double beta_inicial;
    double beta_final;
    double delta_beta;
    int N_Ter;
    int N_med;
    int N_Met;

    lee_input(&beta_inicial,&beta_final,&delta_beta,&flag,&semilla,&N_Ter,&N_med,&N_Met);

    N_pasos=(beta_final-beta_inicial)/delta_beta;
    beta=beta_inicial;


    double vec_energ[N_med];
    double vec_mag[N_med];
    double e_medio[N_pasos], e_medio_cuadrado[N_pasos], m_medio[N_pasos], m_medio_cuadrado[N_pasos], m_medio_absoluto[N_pasos], Cv[N_pasos], X[N_pasos],error_energia[N_pasos],error_magnetizacion[N_pasos];
    inicio_vectores(e_medio,e_medio_cuadrado,m_medio,m_medio_cuadrado,m_medio_absoluto,Cv,X,error_energia,error_magnetizacion,N_pasos);

    //Construimos los desplazamientos
    int x_right[L];
    int y_up[L];
    int x_left[L];
    int y_down[L];

    for (i=0;i<L;i++){
        x_right[i]=1;
        y_up[i]=L;
        x_left[i]=-1;
        y_down[i]=-L;
    }

    x_right[L-1]=-(L-1);    //xp
    y_up[L-1]=-L*(L-1);     //yp
    x_left[0]=L-1;          //xm
    y_down[0]=L*(L-1);      //ym


    ini_ran(semilla);
    configuracionInicial(flag,s);



    for(sentido=0;sentido<2;sentido++){
        for(N_betas=0;N_betas<N_pasos;N_betas++){


            Probabilidad_beta(beta,expon);  //tabla probabilidad para la beta
            printf("b");

            for(n=0;n<N_Ter;n++){   //TERMALIZACIÓN
                Metropolis(s,x_right,x_left,y_up,y_down,expon); //montecarlo
            }
            printf("c");



            /*
            realizamos Nmed ciclos
            para cada ciclo, realizamos NMet ciclos de metrópolis
            medimos al finalizar cada uno de estos ultimos bloques - tenemos NMedidaas

            */
            for(N_m=0;N_m<N_med;N_m++){ //bucle de medidas
                for(N_M=0;N_M<N_Met;N_M++){ //iteraciones de Monte Carlo
                    Metropolis(s,x_right,x_left,y_up,y_down,expon);
                }
                Vector_Medidas(s,vec_mag,vec_energ,x_right,y_up,N_m); //calculo directamnete y meto los resultados en un vector
            }
            calculaValoresMedios(N_med,vec_energ,vec_mag,e_medio,m_medio,e_medio_cuadrado, m_medio_cuadrado,m_medio_absoluto,Cv,X,error_energia,error_magnetizacion,N_betas);
            beta+=delta_beta;


        }
        delta_beta=-delta_beta;

        printf("a");


    }


    escribir_fichero(e_medio,m_medio,e_medio_cuadrado,m_medio_absoluto,m_medio_cuadrado,X,Cv,error_energia,error_magnetizacion,N_pasos);








    return 0;
}
void escribir_fichero(double e_medio[], double m_medio[],double e_medio_cuadrado[],double m_medio_absoluto[], double m_medio_cuadrado[],double X[], double Cv[],double error_energia[],double error_magnetizacion[], int N_pasos){
    int i;
    FILE *f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8,*f9;
    f1=fopen("Ficheros de salida/e_medio.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f1,"\n%lf",e_medio[i]);
    fclose(f1);
    f2=fopen("Ficheros de salida/m_medio.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f2,"\n%lf",m_medio[i]);
    fclose(f2);
    f3=fopen("Ficheros de salida/m_medio_cuadrado.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f3,"\n%lf",m_medio_cuadrado[i]);
    fclose(f3);
    f4=fopen("Ficheros de salida/m_medio_absoluto.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f4,"\n%lf",m_medio_absoluto[i]);
    fclose(f4);
    f5=fopen("Ficheros de salida/X.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f5,"\n%lf",X[i]);
    fclose(f5);
    f6=fopen("Ficheros de salida/Cv.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f6,"\n%lf",Cv[i]);
    fclose(f6);
    f7=fopen("Ficheros de salida/Error_energia.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f7,"\n%lf",error_energia[i]);
    fclose(f7);
    f8=fopen("Ficheros de salida/Error_magnetizacion.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f8,"\n%lf",error_magnetizacion[i]);
    fclose(f8);
    f9=fopen("Ficheros de salida/e_medio_cuadrado.txt","wt");
            for(i=0;i<N_pasos;i++)
                fprintf(f9,"\n%lf",e_medio_cuadrado[i]);
    fclose(f9);
}


void calculaValoresMedios(int N_med,double *Energia,double *Magnetizacion,double *mediaEnergia,double *mediaMagnetizacion,double *media2Energia,double *media2Magnetizacion,double *mediaMagnetizacionAbsoluta,double *Cv,double *X,double *error_energia,double *error_magnetizacion,int beta){
    int i;
    for(i=0;i<N_med;i++){
        mediaEnergia[beta]+=Energia[i];
        mediaMagnetizacion[beta]+=Magnetizacion[i];
        media2Energia[beta]+=Energia[i]*Energia[i];
        media2Magnetizacion[beta]+=Magnetizacion[i]*Magnetizacion[i];
    }
    mediaEnergia[beta]/=N_med;
    mediaMagnetizacion[beta]/=N_med;
    media2Energia[beta]/=N_med;
    media2Magnetizacion[beta]/=N_med;
    mediaMagnetizacionAbsoluta[beta]=fabs(mediaMagnetizacion[beta]);
    Cv[beta]=2*L*L*(media2Energia[beta]-mediaEnergia[beta]);
    X[beta]=L*L*(media2Magnetizacion[beta]-mediaMagnetizacionAbsoluta[beta]);
    var(Energia,N_med,&mediaEnergia[beta],&error_energia[beta]);
    var(Magnetizacion,N_med,&mediaMagnetizacion[beta],&error_magnetizacion[beta]);
    error_energia[beta]=sqrt(error_energia[beta])/N_med;
    error_magnetizacion[beta]=sqrt(error_magnetizacion[beta])/N_med;
}
void var(double *serie,int Numero, double *Media, double *Varianza){
	int i;
	for(i=0;i<Numero;i++){
		*Varianza+=(*(serie+i)-*Media)*(*(serie+i)-*Media);
	}
	*Varianza=*Varianza/Numero;
}
//medir la energia
double energia(int *s,int *xp,int *yp){ //E

    int n,i,j;
    double E;

    n=0;
    E=0;
    for(j=0;j<L;j++){
        for(i=0;i<L;i++){
            E+=s[n]*(s[n+xp[i]]+s[n+yp[j]]);
            n++;
        }
    }

    return E/L/L/2;
}

//funcion magnetizacion
double magnetizacion(int *s){   //M
    double mag;
    int n;
    for(n=0;n<(L*L);n++){
        mag+=s[n];
    }
    return mag/L/L;

}


void Vector_Medidas(int *s,double *vec_mag,double *vec_energ, int *xp, int *yp, int N_m){
    vec_mag[N_m]=magnetizacion(s);
    vec_energ[N_m]=energia(s,xp,yp);

}
void Metropolis(int*s, int*x_right, int*x_left, int*y_up, int *y_down,double *expon){

    int i,j,n=0;
    int indice=0;
    double cociente=0;
    for (i=0;i<L;i++){
        for (j=0;j<L;j++){
            indice=s[n]*(s[n+x_right[j]]+s[n+x_left[j]]+s[n+y_up[i]]+s[n+y_down[i]])/2+2;
            cociente=expon[indice];
            if(Random()<cociente)
                s[n]=-s[n];
        n++;
    }
}
}
void Probabilidad_beta(double beta, double expon[]){
    expon[0]=exp(-beta*(-8));
    expon[1]=exp(-beta*(-4));
    expon[2]=exp(-beta*(-0));
    expon[3]=exp(-beta*(4));
    expon[4]=exp(-beta*(8));
}

//guardar configuracion
void guardaConfiguracion(int *s, char name[]){
    int i;

    FILE *f;
    f=fopen(name,"wt");


    for(i=0;i<(L*L);i++)
        fprintf(f,"%d%c",s[i],(i+1)%L==0?'\n':' '); //expresion ternaria

    fclose(f);
}
void inicio_vectores(double *e_medio,double *e_medio_cuadrado,double *m_medio,double *m_medio_cuadrado,double *m_medio_absoluto,double *Cv,double *X,double *error_energia,double *error_magnetizacion,int N_pasos){
    int i;
    for(i=0;i<N_pasos;i++){
        e_medio[i]=0;
        e_medio_cuadrado[i]=0;
        m_medio[i]=0;
        m_medio_cuadrado[i]=0;
        m_medio_absoluto[i]=0;
        Cv[i]=0;
        X[i]=0;
        error_energia[i]=0;
        error_magnetizacion[i]=0;
    }
}
//configuracion incial de spines
void configuracionInicial(int flag,int *s){ //hay q crear un fichero
    int i;
    FILE *Fconf;
    switch(flag){
        case 0:
            for(i=0;i<(L*L);i++){
                if(Random()>0.5)
                    s[i]=1;
                else
                    s[i]=-1;
            }

        break;
        case 1:
            for(i=0;i<(L*L);i++)
                s[i]=1;
        case 2: //leer de un fichero
            #ifdef TEXT
            Fconf=fopen("conf_ising.txt","rt");
            for(i=0;i<L*L;i++)
                fscanf(Fconf,"%c",s[i]);
            fclose(Fconf);
            #endif // TEXT
            #ifdef BINARY
            Fconf=fopen("conf_ising.dat","rb");
                fread(s,sizeof(s[0]),V,Fconf);
            fclose(Fconf);

            #endif // BINARY
        break;
    }

}
void lee_input(double *beta_inicial,double *beta_final,double *delta_beta,int *flag,int *semilla,int *N_Ter,int *N_med,int *N_Met){
    char name[50],*ptr;
    double number;
    FILE *f_in;

    f_in=fopen("Constantes.txt","r");

    while(fgets(name,50,f_in)){
        ptr=strtok(name," ");
        number=atof(strtok(NULL," "));

        if(strcmp(ptr,"beta_inicial")==0)
            *beta_inicial=number;
        if(strcmp(ptr,"beta_final")==0)
            *beta_final=number;
        if(strcmp(ptr,"delta_beta")==0)
            *delta_beta=number;
        if(strcmp(ptr,"N_Ter")==0)
            *N_Ter=number;
        if(strcmp(ptr,"N_med")==0)
            *N_med=number;
        if(strcmp(ptr,"N_Met")==0)
            *N_Met=number;
        if(strcmp(ptr,"flag")==0)
            *flag=number;
        if(strcmp(ptr,"semilla")==0)
            *semilla=number;
    }
    fclose(f_in);
}
float Random(void){
    float r;

    //genermamos un numero aleatorio a la vez que modificamos un numero de la rueda

    ig1=ind_ran - 24;   //los numeros magicos
    ig2=ind_ran - 55;
    ig3=ind_ran - 61;
    irr[ind_ran]=irr[ig1]+irr[ig2]; //cambiamos la propia rueda
    ir1=(irr[ind_ran]^irr[ig3]);    //numero random
    ind_ran++;
    r=ir1*NormRANu;
    //printf("r=%f\n",r);
    return r;

}

//iniciar numeros aleatorios
void ini_ran(int semilla)
{

    int INI,FACTOR,SUM,i;

    if(semilla==0)
        semilla=time(NULL);

    srand(semilla);

    INI=semilla;
    FACTOR=67397;
    SUM=7364893;

    for(i=0;i<256;i++)
    {
        INI=(INI*FACTOR+SUM);
        irr[i]=INI;
    }
    ind_ran=ig1=ig2=ig3=0;
}