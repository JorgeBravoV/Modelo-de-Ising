#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define L 16
void configura(char*s, int flag);
double alea0_1();
double energia(char*s,int*xp,int*yp);
void guardaConfiguracion(char*s);
void escribe_fichero(double energia,int iteracion,FILE*f);
void guardaMagnetizacion(char*s,int iteracion,FILE*f);

void iteraMonteCarlo(char*s, double beta, int *x_right, int *x_left, int *y_up, int *y_down);
int main(){
    srand(705);
    int flag,i,j, indice, Iteracion_estable,estabilidad=0;
    int N_iter=500;
    flag=0;
    char red[L*L];
    double suma_delta_energia[100];//suma_delta_magnetizacion[N_iter/10];
    double E_media,E_vieja,E_nueva,suma=0,suma_energia=0;
    
    // Debemos inicializar suma_delta_energia y [...]_magnetizacion para que tengan inicialmente una media alta.
    for (i=0;i<N_iter/10;i++)
        suma_delta_energia[100]=L*L*L;


    double beta=0.55;


    configura(red,flag);

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
FILE*f,*g;
f=fopen("energy.txt","wt");
g=fopen("magnetization.txt","wt");
for (i=0; i<N_iter; i++){

    escribe_fichero(E_vieja,i,f);
    guardaMagnetizacion(red,i,g);

    iteraMonteCarlo(red,beta,x_right,x_left,y_up,y_down);

    E_nueva=energia(red,x_right,y_up);

    // Ahora queremos ver cuando las medidas se hacen estables. Para ello guardamos las variaciones de energia en un array.
    indice=i-((i/(100))*(100)); //Con esto transformamos el indice para que, al pasarse del tamaño de N_iter, vuelva al 0.

    suma_delta_energia[indice]=energia(red,x_right,y_up)-E_vieja;
    //Cuando la media de esas variaciones sea próxima a 0, entonces la medida será estable. Calculemos la media.
    for(j=0;j<100;j++)
        suma+=suma_delta_energia[j];
    if(suma/100<L*L/10.0 && estabilidad==0){ //Si la media es baja, empezamos a calcular la media a partir de aquí.
        Iteracion_estable=i;
        estabilidad=1;
        suma_energia=0;
    }
    suma_energia+=E_nueva;
    E_vieja=E_nueva; //Dejamos la energia vieja preparada para la siguiente iteracion.
}
    E_media=suma_energia/(N_iter-Iteracion_estable); //Ya tenemos la energia media.
    fclose(f);
    fclose(g);
    printf("La media es %lf",E_media);
    
guardaConfiguracion(red);
    return 0;
}
double alea0_1(){
return rand()/((double)RAND_MAX+1.0);

}
void configura(char *s, int flag){
int i;
double x;
char spin;
switch (flag){
case 0:
for (i=0;i<L*L;i++){
x=alea0_1();
if (x<0.5)
s[i]=1;
else
s[i]=-1;
}
break;
case 1:
x=alea0_1();
if (x<0.5)
spin='1';
else
spin=-1;
for (i=0;i<L*L;i++)
s[i]=spin;

break;

}
}
double energia(char*s,int*xp,int*yp){
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

double magnetizacion(char*s){
    int i;
    double magnetizacion=0;
        for (i=0;i<L*L;i++){
            magnetizacion+=s[i];
        }
        return magnetizacion/(L*L);
}

void guardaConfiguracion(char*s){
    int i;
    FILE*f;
    f=fopen("config.txt","wt");
      for (i=0;i<L*L;i++){
        fprintf(f,"%d%c",s[i],(i+1)%L==0?'\n':' ');
      }
    fclose(f);
      }
      
// Procedemos a construir las iteraciones de Monte Carlo (cada una modifica todo el sistema).
void iteraMonteCarlo(char*s, double beta, int*x_right, int*x_left, int*y_up, int *y_down){

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
        if(alea0_1()<cociente)
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
void guardaMagnetizacion(char*s,int iteracion,FILE*f){
    fprintf(f,"%d %lf\n",iteracion,magnetizacion(s));
}