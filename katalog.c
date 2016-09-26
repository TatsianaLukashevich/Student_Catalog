//autor:Tatsiana Lukashevich
//Zadanie 2.1
//Należy stworzyć katalog uczniów liceum. Program powinien umożliwiać
//wczytanie do N = 10 pozycji zawierających:
//- nazwisko
/*- imię
- klasę (od 1 do 3 np. 2b lub 3a)
- średnią z poprzedniego półrocza (np. 3.56)
Listę należy wyświetlić:
a) wg rosnącej kolejności klas (1a, 1b, ...), a w ramach każdej klasy
alfabetycznie wg nazwisk i imion
b) wg średniej (malejąco), a dla tej samej średniej alfabetycznie wg nazwisk
i imion

Wyświetlone pozycje powinny zawierać pełną informację, tzn. nazwisko, imię,
średnią i klasę. Program powinien umożliwiać edycję i usuwanie istniejących
oraz dopisywanie nowych  pozycji po wyświetleniu listy. Powinien reagować i
być odporny na nielogiczne wprowadzanie danych (np. klasa: Abc).*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct katalog //szablon struktury o nazwie katalog
{
	char nazwisko[15];
	char imie[10];
    char klasa[5];
	char ocena[5];
}katalog;

typedef katalog *pk;

katalog k[10];
pk p[10];
	void SortKlasa(struct katalog k[], int n) // babelkowe sortowanie klasy
	{
     int i, a;
     katalog temp;
     for ( a=0; a < n-1; a++)
     for ( i= n-2; i >= a ; i--)
if (strcmp(k[i+1].klasa,k[i].klasa)<0)  //jesli dlugosc znakow klasy jest mnniejsza od poprzedniej ...
     {
     temp = k[i]; //to zamieniamy je
     k[i] = k[i+1];
     k[i+1] = temp;
	}

}
     void SortOcena(struct katalog k[] , int n)
     {
     int i, a;
     katalog temp;
     for ( a=0; a <= n; ++a)
     for ( i= (n-2); i >= a ; --i){
     if(k[i+1].ocena[0] < k[i].ocena[0]) //jesli ocena jest mniejsza od natepnej to..
     {
     temp = k[i];//zamieniamy
     k[i] = k[i+1];
     k[i+1] = temp;}
	if(k[i+1].ocena[0] == k[i].ocena[0]){
	if(k[i+1].ocena[2] < k[i].ocena[2]) //jesli ocena jest mniejsza od natepnej to..
     {
     temp = k[i];//zamieniamy
     k[i] = k[i+1];
     k[i+1] = temp;}
	}
	if(k[i+1].ocena[0] == k[i].ocena[0]){
	if(k[i+1].ocena[2] == k[i].ocena[2]){
	if(k[i+1].ocena[3] < k[i].ocena[3]) //jesli ocena jest mniejsza od natepnej to..
     {
     temp = k[i];//zamieniamy
     k[i] = k[i+1];
     k[i+1] = temp;}
	}
	}
	}
     }
void SortNazwisko2(struct katalog k[], int n)
{
     int i, a;
     katalog temp;
     for ( a=0; a < n-1; a++)
     for ( i= n-2; i >= a ; i--)
	if (strcmp(k[i+1].klasa ,k[i].klasa)==0) //Jesli klasy so rowne to..
      {
     if (strcmp(k[i+1].nazwisko,k[i].nazwisko)<0)//Porownujemy nazwiska, jesli mniejsze,to
     {
     temp = k[i];// to zamieniamy je
     k[i] = k[i+1];
     k[i+1] = temp;
	}
     }
}
void SortNazwisko1(struct katalog k[], int n)
{
     int i, a;
     katalog temp;
     for ( a=0; a < n-1; a++)
     for ( i= n-2; i >= a ; i--)
	if ((k[i+1].ocena[0] == k[i].ocena[0]) && (k[i+1].ocena[2]==k[i].ocena[2]) && (k[i+1].ocena[3] == k[i].ocena[3])){ // jesli oceny so rowne
     if (strcmp(k[i+1].nazwisko,k[i].nazwisko)<0)// to porownujemy nazwiska
     {
     temp = k[i];//zamieniamy
     k[i] = k[i+1];
     k[i+1] = temp;
	}
     }
     }
void SortImie(struct katalog k[], int n)
{
     int i, a;
     katalog temp;
     for ( a=0; a < n-1; a++)
     for ( i= n-2; i >= a ; i--)
	if (strcmp(k[i+1].nazwisko,k[i].nazwisko)==0){// jesli nazwiska sa rowne ,to
     if (strcmp(k[i+1].imie,k[i].imie)<0)//porownujemy imie
     {
     temp = k[i];//zamieniamy
     k[i] = k[i+1];
     k[i+1] = temp;
	}
     }
     }

void usuw(struct katalog k[], int n)
	{
	int i , P;
	printf("Podaj numer pozycju ktora chcesz usunac ");
	scanf("%d", &P);
    for(i = P-1 ; i < n-1; i++)
        k[i]=k[i+1];
	}

int main(void)
{
	int i, n, im, naz,nazn, imn, na,imie;
	      //TABLICA STRUKTUR TYPU KATALOG
    printf("Wprowadz ilosc pozycji ,ktorych chcesz wpisac do katalogu,zeby one nie przekroczaly 10\n");
	scanf("%d",&n);
	if(!( n<= 10))
		{
        printf("Niepoprawna ilosc\n");
		return 0;
		}
	if ( n <= 10)
	{
		for (i=0; i < n ; i++)
		{
	                while(1){
		       wern:
		       naz = 1;
			printf("Podaj nazwisko\n");
			scanf("%s",k[i].nazwisko);
	               if(isupper(k[i].nazwisko[0])==0){              //jesli nazwisko jest z malej litery
	                  printf("Podales nazwisko z malej litery!!\n");
	                     goto wern;}   //jescze raz prosze napisac nazwisko
	               else{
	                while(k[i].nazwisko[naz]){
	                   if(isalpha(k[i].nazwisko[naz])>0 && isupper(k[i].nazwisko[naz])==0 ){ //jesli nazwisko jest napisane poprawnie sprawdzamy dalej
	                     naz++;}
	                   else{
	                     printf("Napisales niepoprawne dane!!\n");//jesli niepoprawne
	                     goto wern;                                //to jeszcze raz prosze napisac nazwisko
	                     }//else
	                            }//while
	                      }//else
	                   break;
	                    }
	                wern1:
	                im =1;
			printf("Podaj imie\n");
			scanf("%s",k[i].imie);
	                if(isupper(k[i].imie[0])==0){
	                  printf("Imie powinno byc z duzej litery!!\n");
	                    goto wern1;}
	                else{
	                 while(k[i].imie[im]){
	                 if (isalpha(k[i].imie[im])>0 && isupper(k[i].imie[im])==0){
	                     im++;
	                                                                }
	                  else{
	                  printf("Napisales niepoprawne dane!!\n");
	                  goto wern1;
	                     }//else
	                        }//while
	                   }//else
	                while(1){
			printf("Podaj klase\n");
			scanf("%s",k[i].klasa);
	                 if((isdigit(k[i].klasa[0])==0 || isalpha(k[i].klasa[1])==0 || isalpha(k[i].klasa[2])>0 || isdigit(k[i].klasa[2])>0 || ispunct(k[i].klasa[2])>0) || isgraph(k[i].klasa[2])>0 || isprint(k[i].klasa[2])>0 ){
	printf("Napisales niepoprawne dane!!\n");
	continue;}
	break;
	}//kontynujemy poprawne wpisanie klasy
	while(1){
			printf("Podaj srednia ocene w postaci n,nn \n");
			scanf("%s", k[i].ocena);
	    if (isdigit(k[i].ocena[0])>0 && isdigit(k[i].ocena[2])>0 && isdigit(k[i].ocena[3])>0 && k[i].ocena[1]==',')
{
	break;}
	else{
	printf("Niepoprawne dane!!\n");
	continue;}
	}
	}//for
	}//if


	int v;
	while(1){
	printf("Jesli chces usunac nacisnij 1\nJesli dodac 2\nEdytowanie na ekr 3, \nWyswietl 4\nwyjti iz programmy 5\n sortuj 6");
	scanf("%d",&v);
	if ( v == 6 )
        {
	int z;
	printf("Jesli chcesz odsortowac wzgledem ocen to nacisnij 11:\n Jesli chcesz odsortowac wzgledem klasy nacisnij 12:\n");
	scanf("%d",&z);
	if (z == 11){
	for(i=0; i < n; ++i){
	p[i]=&k[i];}
        SortOcena( k , n);
	SortNazwisko1( k, n);
	SortImie(k,n);
	for ( i=0; i< n ; i++)
        printf ("%4s %4s %4s %4s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena); continue;}
	if ( z == 12)
	{
	for(i=0; i < n; i++){
	p[i]=&k[i];}
	SortKlasa( k , n);
	SortNazwisko2( k, n);
	SortImie(k,n);
	for ( i=0; i< n ; i++)
        printf ("%4s %4s %4s %4s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena); continue;
        }
	}
	if(v == 1)
	{
		for(i=0; i < n; i++)
		{

			p[i]=&k[i];
		}
		usuw( k , n);
		strcpy(k[n-1].nazwisko, "\0");
		strcpy(k[n-1].imie, "\0");
		strcpy(k[n-1].klasa, "\0");
		strcpy(k[n-1].ocena, "\0");
		n--;
		for ( i=0; i< n ; i++)
   		   	printf ("%4s %4s %4s %4s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena);
		continue;
   		}
	if(v == 2)
	{
		if( (n+1) > 10)
		{
			printf("Jest wiecej niz 10 pozycji\n");
			continue;
		}
	        while(1){
	         wrocn:
	          nazn=1;
		printf("Podaj nazwisko\n");
		scanf("%s",k[n].nazwisko);
	         if(isupper(k[n].nazwisko[0])==0){
	printf("Powinna byc duza litera!!\n");
	goto wrocn;}
	else{
	while(k[n].nazwisko[nazn]){
	if(isalpha(k[n].nazwisko[nazn])>0 && isupper(k[n].nazwisko[nazn])==0){
	nazn++;}
	else{
	printf("Niepoprawne dane!!\n");
	goto wrocn;
	    }//else
	                          }//while
	    }//else
	break;
	}
	while(1){
	wrocn1:
	imn= 1;
		printf("Podaj imie\n");
		scanf("%s",k[n].imie);
	if(isupper(k[n].imie[0])==0){
	printf("Powinno byc z duzej litery!!\n");
	goto wrocn1;}
	else{
	while(k[n].imie[imn]){
	if (isalpha(k[n].imie[imn])>0 && isupper(k[n].imie[imn])==0){
	imn++;
	}
	else{
	printf("Niepoprawne dane!!\n");
	goto wrocn1;
	    }
	                        }
	    }
	break;
	}
	while(1){
		printf("Podaj klase\n");
		scanf("%s",k[n].klasa);
	if((isdigit(k[n].klasa[0])==0 || isalpha(k[n].klasa[1])==0 || isalpha(k[n].klasa[2])>0 || isdigit(k[n].klasa[2])>0 || ispunct(k[n].klasa[2])>0) || isgraph(k[n].klasa[2])>0 || isprint(k[n].klasa[2])>0 ){
	printf("Niepoprawne dane\n");
	continue;}
	break;
	}
	while(1){
		printf("Podaj srednia ocene w postaci n,nn \n");
		scanf("%s", k[n].ocena);
	if (isdigit(k[n].ocena[0])>0 && isdigit(k[n].ocena[2])>0 && isdigit(k[n].ocena[3])>0 && k[n].ocena[1]==','){
	break;}
	else{
	printf("Niepoprawne dane!!\n");
	}
	       }
		n++;
		for(i=0; i < n; i++)
			p[i]=&k[i];
		for ( i=0; i< n ; i++)
   		    printf ("%4s %4s %4s %4s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena);
		continue;
	}
	if(v ==3)
	{
		int poz;
		printf("Podaj pozycje edytowania");
		scanf("%d", &poz);
		strcpy(k[poz-1].nazwisko, "\0");
		strcpy(k[poz-1].imie, "\0");
		strcpy(k[poz-1].klasa, "\0");
		strcpy(k[poz-1].ocena, "\0");
	       while(1){
	        wr:
	         na=1;
		printf("Podaj nazwisko\n");
		scanf("%s",k[poz-1].nazwisko);
	      if(isupper(k[poz-1].nazwisko[0])==0){
	printf("POwinna byc duza litera!!\n");
	goto wr;}
	else{
	  while(k[poz-1].nazwisko[na]){
	  if(isalpha(k[poz-1].nazwisko[na])>0 && isupper(k[poz-1].nazwisko[na])==0){
	  na++;}
	     else{
	      printf("Niepoprawne dane!!\n");
	      goto wr;
	          }//else
	                               }//while
	     }//else
	break;
	}
	while(1){
	wr1:
	imie=1;
		printf("Podaj imie\n");
		scanf("%s",k[poz-1].imie);
	if(isupper(k[poz-1].imie[0])==0){
	printf("Powinna byc duza litera!!\n");
	goto wr1;}
	else{
	        while(k[poz-1].imie[imie]){
	          if (isalpha(k[poz-1].imie[imie])>0 && isupper(k[poz-1].imie[imie])==0){
	          imie++;
	           }
	             else{
	             printf("Niepoprawne dane!!\n");
	             goto wr1;
	                 }
	                                  }
	     }
	break;
	}
	while(1){
		printf("Podaj klase\n");
		scanf("%s",k[poz-1].klasa);
	if((isdigit(k[poz-1].klasa[0])==0 || isalpha(k[poz-1].klasa[1])==0 || isalpha(k[poz-1].klasa[2])>0 || isdigit(k[poz-1].klasa[2])>0 || ispunct(k[poz-1].klasa[2])>0) || isgraph(k[poz-1].klasa[2])>0 || isprint(k[poz-1].klasa[2])>0 ){
	printf("Niepoprawne dane!!\n");
	continue;}
	break;
	}
	while(1){
		printf("Podaj srednia ocene w postaci n,nn \n");
		scanf("%s", k[poz-1].ocena);
	if (isdigit(k[poz-1].ocena[0])>0 && isdigit(k[poz-1].ocena[2])>0 && isdigit(k[poz-1].ocena[3])>0 && k[poz-1].ocena[1]==','){
	break;}
	else{
	printf("Niepoprawne dane!!\n");
	continue;}
	}//while
		for(i=0; i < n; ++i)
			p[i]=&k[i];
		for ( i=0; i< n ; i++)
  		    printf ("%4s %4s %4s %4s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena);
		continue;
	}
	if( v == 4 )
	{
		for(i=0; i < n; ++i)
			p[i]=&k[i];
		for ( i=0; i< n ; i++)
 	       printf ("%s %s %s %s\n", p[i]->nazwisko, p[i]->imie, p[i]->klasa,p[i]->ocena);
		continue;
	}
	if( v ==5)
	{
		return 0;
	}
	}
	return 0;
}