#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 16

//para generacion de numeros aleatorios
#define NormRANu (2.3283063671E-10F)

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran,ig1,ig2,ig3;
void ini_ran(int SEMILLA);
float Random(void);

void configura(int*s, int flag);
double alea0_1();
double energia(int*s,int*xp,int*yp);
void guardaConfiguracion(int*s);
void escribe_fichero(double energia,int iteracion,FILE*f);
void guardaMagnetizacion(int*s,int iteracion,FILE*f);
void Histogram(double *input, double *output, int N_data, int N_interval, double *delta, double *min, double *max);


void iteraMonteCarlo(int*s, double beta, int *x_right, int *x_left, int *y_up, int *y_down);
int main(){
    srand(705);
    int flag,i,j, indice=0, t_termalizacion=5,estabilidad=0;
    int N_iter=50;
    int epsilon=5;
    flag=0;
    int red[L*L];
    ini_ran(1234); //PARISI RAPUANO - SEMILLA=1234
    double memoriza_energia[N_iter], memoriza_delta_energia[epsilon];
    double E_media,e_media,E_vieja,E_nueva,suma=0,suma_energia=0;
    
    // Debemos inicializar suma_delta_energia y [...]_magnetizacion para que tengan inicialmente una media alta.
    for (i=0;i<epsilon;i++)
        memoriza_delta_energia[i]=L*L*L;


    double beta=0.55;




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

    x_right[L-1]=-(L-1);
    y_up[L-1]=-L*(L-1);
    x_left[0]=L-1;
    y_down[0]=L*(L-1);

// Ya hemos definido los direccionemientos.
// Llevamos a cabo iteraciones de Monte Carlo.

 /*FILE*f,*g;
f=fopen("energy.txt","wt");
g=fopen("magnetization.txt","wt");
*/

int N_conf=50, N_interval=10,k;
double datos_energia[N_conf];
double histograma_energia[N_interval];



for (k=0; k<N_conf; k++){
        srand((unsigned int)k);
                configura(red,flag);
                E_vieja=energia(red,x_right,y_up);

for (i=0; i<N_iter; i++){

   // escribe_fichero(E_vieja,i,f);
   // guardaMagnetizacion(red,i,g);

    iteraMonteCarlo(red,beta,x_right,x_left,y_up,y_down);

    E_nueva=energia(red,x_right,y_up);

// TODA ESTA PARTE ES PARA CALCULAR EL TIEMPO DE TERMALIZACIÓN. SI TOMAMOS ESTE TIEMPO FIJO SE DEBE QUITAR (poniendo estabilidad=1)

    // Ahora queremos ver cuando las medidas se hacen estables. Para ello guardamos las variaciones de energia en un array.
    indice=i-((i/(epsilon))*(epsilon)); // Con esto transformamos el indice para que, al pasarse del tamaño de memoriza_delta_energia, vuelva al 0.

        memoriza_delta_energia[indice]=E_nueva-E_vieja; //"Memoriza las "epsilon" últimas variaciones de energía.
    //Cuando la media de esas variaciones sea próxima a 0, entonces la medida será estable. Calculemos la media.
        suma=0;
    for (j=0;j<epsilon;j++){
        suma+=memoriza_delta_energia[j];
    }
        if(sqrt((suma/epsilon)*(suma/epsilon))<(L*L)/250.0 && estabilidad==0){
        /*
            Si el valor absoluto de la media es baja, la medida lleva siendo estable "epsilon" iteraciones.
            Guardamos los valores que ya tiene el array "memoriza_energia" y los siguientes.
        */
            t_termalizacion=i-epsilon; // El tiempo que ha sido inestable es el tiempo que llevamos menos "epsilon" iteraciones.
                if(t_termalizacion<0)    // Sería el caso de que sea estable desde el principio.
                    t_termalizacion=0;
            estabilidad=1;  // Para que el if solo se haga una vez.
        
// HASTA AQUÍ SE PODRÍA QUITAR

    }
     if(estabilidad==0){
        memoriza_energia[indice]=E_vieja; 
    }else if(i>=t_termalizacion){
        memoriza_energia[i-t_termalizacion]=E_vieja;
    
    } /*
    En caso de que no haya estabilidad, "memoriza_energia" guarda solo las "epsilon" últimas variables
    En el caso de que ya se haya alcanzado la estabilidad, mantendrá los que ya hay en el array e irá añadiendo el resto"
    */

    E_vieja=E_nueva; // Dejamos la energia vieja preparada para la siguiente iteracion.
    }


    suma_energia=0;
        for (i=0;i<(N_iter-t_termalizacion);i++){
            suma_energia+=memoriza_energia[i];
        }
    E_media=suma_energia/(N_iter-t_termalizacion); // Ya tenemos la energia extensiva media.
    e_media=E_media/(2*L*L); // Y esta es la energía intensiva media (es decir, está entre siempre -1, y 1).
printf("%lf ",e_media);
    datos_energia[k]=e_media;
}

double delta;
double min=0, max=1;
FILE*F,*G;
F=fopen("Hist_energy.txt", "wt");
G=fopen("aversiva.txt", "wt");
for (i=0;i<N_conf;i++)
        fprintf(G,"%d %lf\n",i,datos_energia[i]);
    Histogram(datos_energia,histograma_energia,N_conf,N_interval,&delta,&min,&max);

    for (i=0;i<N_interval;i++)
        fprintf(F,"%d %lf\n",i,histograma_energia[i]);
    fclose(F);
    fclose(G);


   /* fclose(f);
    fclose(g);
    printf("La energia media extensiva es %lf\nLa energia media intensiva es %lf\nEl tiempo de termalizacion es %d\n",E_media,e_media,t_termalizacion);
*/

 // guardaConfiguracion(red);
}

/*
double alea0_1(){
return rand()/((double)RAND_MAX+1.0);
}
*/

void configura(int *s, int flag){
    int i;
    double x;
    int spin;
    switch (flag){
        case 0:
            for (i=0;i<L*L;i++){
            x=Random();
            if (x<0.5)
                s[i]=1;
            else
                s[i]=-1;
            }
        break;
        case 1:
            x=Random();
            if (x<0.5)
                spin='1';
            else
                spin=-1;
            for (i=0;i<L*L;i++)
                s[i]=spin;

        break;

}
}
double energia(int*s,int*xp,int*yp){
int i, j, n=0;
double energia=0;  //¿Por qué se guarda la energía al acabar el subalgoritmo?
for (i=0;i<L;i++){
    for(j=0;j<L;j++){
        energia+=-s[n]*(s[n+yp[i]]+s[n+xp[j]]);
        n++;
    }
}
    return energia;
}

double magnetizacion(int*s){
    int i;
    double magnetizacion=0;
        for (i=0;i<L*L;i++){
            magnetizacion+=s[i];
        }
        return magnetizacion/(L*L);
}

void guardaConfiguracion(int*s){
    int i;
    FILE*f;
    f=fopen("config.txt","wt");
      for (i=0;i<L*L;i++){
        fprintf(f,"%d%c",s[i],(i+1)%L==0?'\n':' ');
      }
    fclose(f);
      }
      
// Procedemos a construir las iteraciones de Monte Carlo (cada una modifica todo el sistema).
void iteraMonteCarlo(int*s, double beta, int*x_right, int*x_left, int*y_up, int *y_down){

int n=0, indice, i, j;
double cociente; //Cociente de probabilidades
double expon[5]; //La exponencial de la probabilidad de la energía solo puede tomar 5 valores: -8,-4, 0, 4 y 8.
    
    expon[0]=exp(-beta*(-8));
    expon[1]=exp(-beta*(-4));
    expon[2]=exp(-beta*(-0));
    expon[3]=exp(-beta*(4));
    expon[4]=exp(-beta*(8));

for (i=0;i<L;i++)
    for (j=0;j<L;j++){
        /*

        Suponemos un cambio (red[n]=-red[n]), y calculamos la diferencia de enrgía:
            DE = Ef-Ei = +red[n]*(los alrededores) + red[n]*(los alrededores) (En Ef red[n] es -1, y la energía cambia el signo de ambas)
            DE=2*red[n]*(red[n+x_right[j]]+red[n+x_left[j]]+red[n+y_up[i]]+red[n+y_down[i]]);

        Ahora, calculamos si es mas probable la configuracion de energía con el cambio, o sin el cambio
        mediante el cociente Prob(Ef)/Prob(Ei)=exp(-beta*(Ef-Ei))

        Como la exponencial es compleja de calcular, utilizamos el array calculado anteriormente con la exponencial resuelta.
        También tenemos que definir el criterio para seleccionar el índice del array en función del valor de DE que corresponda.
            indice=DE/4 +2;
        De hecho, aún podemos simplificar más el cálculo:
        
        */
       indice=s[n]*(s[n+x_right[j]]+s[n+x_left[j]]+s[n+y_up[i]]+s[n+y_down[i]])/2+2;
       cociente=expon[indice];
        // Ahora utilizamos el algoritmo de metrópolis para ver si aceptamos o no el cambio de spin que hemos supuesto:
        if(Random()<cociente)
            s[n]=-s[n];
        n++;
    }
    /*
     Ya está finalizada la iteración de Monte Carlo.
     
     ANÁLISIS: Como puede verse, si el supuesto cambio da lugar una configuración más probable, lo aceptaremos siempre.
               Pero si da lugar a una configuación más improbable, también hay una posibilidad de aceptar el cambio.
    */
}
void escribe_fichero(double energia,int iteracion,FILE*f){

    fprintf(f,"%d %lf\n",iteracion,energia);
}
void guardaMagnetizacion(int*s,int iteracion,FILE*f){
    fprintf(f,"%d %lf\n",iteracion,magnetizacion(s));
}
void Histogram(double *input, double *output, int N_data, int N_interval, double *delta, double *min, double *max)
{
//Definimos mínimo y máximo:
*min=100;
*max=0;

int i;
for (i=-0;i<N_data;i++){
if(input[i]<*min)
*min=input[i];
if (input[i]>*max)
*max=input[i];
}

//Definimos los numeros que contiene cada intervalo como delta:
*delta=(*max-*min)/N_interval;
//Definimos un entero que serán las celdas en las que estarán los diferentes números.
int celda;
//PARTE IMPORTANTE DEL PROGRAMA:
for (i=0;i<N_interval;i++)
output[i]=0;
for (i=0;i<N_data;i++){
celda=(int)((input[i]-(*min))/(*delta));
if(celda==N_interval)
celda=celda-1;
output[celda]++;
}
//Normalizamos: 1=suma(delta*altura)*A=A*delta*suma[i]=A*delta*N_data
double A;
A=1/(*delta*N_data);
for (i=0;i<N_interval;i++)
output[i]=A*output[i];

}

float Random(void){ //Parisi-Rapuano
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
void ini_ran(int SEMILLA)
{
    int INI,FACTOR,SUM,i;

    srand(SEMILLA);

    INI=SEMILLA;
    FACTOR=67397;
    SUM=7364893;

    for(i=0;i<256;i++)
    {
        INI=(INI*FACTOR+SUM);
        irr[i]=INI;
    }
    ind_ran=ig1=ig2=ig3=0;
}
