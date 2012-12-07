#include <stdio.h>
#include <stdlib.h>
//#define DEBUG
#define MAX_deepness 12
#define MAX_color 5
#define FILENAME "matrix12random.txt"
/* Ha el�re tudhat� a d�nt�sek sz�ma */
typedef struct point{
		short color;// 0 ha nincs kiszinezve
}point;

typedef struct{
	point dots[MAX_deepness];
	short matrix[MAX_deepness][MAX_deepness];
    int copy_of_valasztasi_lehetosegek_szama,
        copy_of_aktualis_lehetoseg_sorszama;
} model;
int szomszedos_e(int pont1_sorszam, int pont2_sorszam, model input);
int* milyen_szinu_lehet(int pont_sorszam,model input);
int maxcolor(model m);
model m,*t;
#ifdef DEBUG
int debug[12];
#endif

int vezerlo_valtozo,	/* Vez�rlo v�ltoz� */
    korabbi_dontesek_szama,	/* Kor�bbi d�nt�sek sz�ma */
    valasztasi_lehetosegek_szama,	/* V�laszt�si lehetos�gek sz�ma */
    aktualis_lehetoseg_sorszama;	/* Aktu�lis lehetos�g sorsz�ma */

int ft1(void){/* A c�lt el�rt�k? */
	int i,retval=1;
	for ( i = 0; i <MAX_deepness ; i++){
		if( !m.dots[i].color) return 0; 
	}
	return 1;
}

int ft2(void){/* Egy�ltal�n lehets�ges m�g a c�lt el�rni? */
	int i = maxcolor(m);
	if (i <= MAX_color)
	return 1;
	else return 0;
}

void pa0(void){/* Elok�sz�t�s */
	int i,j;
	FILE* fp;
    t=(model*)calloc(sizeof (model),MAX_deepness);
	if(!(fp = fopen(FILENAME,"r"))) exit(-1);
	for ( i = 0; i < MAX_deepness;i++)
	{
		for( j = 0; j <MAX_deepness ;j++)
		{
			m.matrix[i][j] = fgetc(fp)-'0';
			// m�trix felt�lt�se
		}
		if(fgetc(fp) != '\n') printf("Gond van a matrix.txt-vel");
	}

}

int fa1(void){/* D�nt�si lehetos�gek sz�mba v�tele *///aktualis_lehetoseg_sorszama az aktu�lis sorsz�m
	return milyen_szinu_lehet(korabbi_dontesek_szama,m)[0];
}

void pa2(void){/* D�nt�si lehetos�gek rangsorol�sa *///Nincs rangsorol�s
}

void pa4(void){/*Vissza�ll�t�s */
    m=t[korabbi_dontesek_szama];
    valasztasi_lehetosegek_szama=m.copy_of_valasztasi_lehetosegek_szama;
    aktualis_lehetoseg_sorszama=m.copy_of_aktualis_lehetoseg_sorszama;
}

void pa6(void){/*Ment�s */
    m.copy_of_valasztasi_lehetosegek_szama=valasztasi_lehetosegek_szama;
    m.copy_of_aktualis_lehetoseg_sorszama=aktualis_lehetoseg_sorszama;
    t[korabbi_dontesek_szama]=m;
}
int van_ilyen_szinu_szomszedja(int incolor, int pont_sorszam){
	int  i ;
	for(i = 0; i <= MAX_deepness;i++){
		if( i == pont_sorszam) i++;
		if(szomszedos_e(i,pont_sorszam,m)&& m.dots[i].color == incolor)return 1;
	}
	return 0;
}
int* milyen_szinu_lehet(int pont_sorszam,model input){
	int * retval,i,k = 0;
	int j = maxcolor(m);
	retval = (int*)calloc(sizeof(int), j+1);//els� a darabsz�m
	for(i  = 1; i <= j; i++){
		if (i == pont_sorszam)i++;
		if(!van_ilyen_szinu_szomszedja(i,pont_sorszam)){
			
			retval[k+1] = i;k++;
			}
		}
	if(k ==0&&j >= MAX_color){retval[0] = 0; return retval;}
	if(k>0)
		{retval[0] = k ;
		return retval;}
	if (k ==0 &&  j< MAX_color) { retval[0] =1; retval[1] = j+1;
	return retval;}
	exit(-2);
	return retval;
}
int szomszedos_e(int pont1_sorszam, int pont2_sorszam, model input){
	if(input.matrix[pont1_sorszam][pont2_sorszam] || input.matrix[pont2_sorszam][pont1_sorszam]) return 1;
	else return 0;
}
int maxcolor(model m){
	int i,retval=0;
	for ( i = 0; i < MAX_deepness;i++){
		if(retval<m.dots[i].color) retval = m.dots[i].color;
	}
	return retval;
}
void pa7(void){/*�rv�nyre juttat�s */
	m.dots[korabbi_dontesek_szama].color = milyen_szinu_lehet(korabbi_dontesek_szama,m)[aktualis_lehetoseg_sorszama+1];
}

void pa8(void){/* Megold�s kijelz�se */
	int i ;
	for ( i = 0; i<MAX_deepness; i++) 
		printf("A %d. pont %d. szinre van szinezve\n",i,m.dots[i].color);
}

int main(void){
    pa0();
    vezerlo_valtozo=1;
    korabbi_dontesek_szama=0;
    while(vezerlo_valtozo)
        switch(vezerlo_valtozo){
            case 1: if (ft1()){
                        pa8();
                        vezerlo_valtozo=0;
                      }
                      else if (ft2()) if ((valasztasi_lehetosegek_szama=fa1())){
                                          pa2();
                                          aktualis_lehetoseg_sorszama=0;
                                          vezerlo_valtozo=3;
                                         }
                                         else vezerlo_valtozo=2;
                              else vezerlo_valtozo=2;
                    break;
            case 2: if (korabbi_dontesek_szama){
                        korabbi_dontesek_szama--;
                        pa4();
                        if (aktualis_lehetoseg_sorszama<valasztasi_lehetosegek_szama-1){
                            aktualis_lehetoseg_sorszama++;
                            vezerlo_valtozo=3;
                           }
                           else vezerlo_valtozo=2;
                       }
                       else {
                           printf("A graf nem szinezheto %d szinnel!\n",MAX_color);
                           vezerlo_valtozo=0;
                       }
                    break;
            case 3: pa6();
                    pa7();
                    korabbi_dontesek_szama++;
                    vezerlo_valtozo=1;
        }
		getchar();
    return 0;

}
