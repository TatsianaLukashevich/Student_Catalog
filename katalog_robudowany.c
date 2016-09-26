//autor:Tatsiana Lukashevich
/*Zadanie 3.1

Napisać komputerowy katalog uczniów (lub odpowiednio rozbudować
poprzedni
program (zad. 2)). Uczniowie zgrupowani są w katalogach uprawianych
dyscyplin sportowych (np. lekkoatletyka, biegi, skok w dal, itp.).
Zarówno
liczba dyscyplin jak i uczniów nie jest ograniczona. W ramach każdej
dyscypliny uczniowie opisywani są jak w zad 2, tzn.: nazwisko, imię,
klasa,
średnia. Każdy uczeń może jednocześnie uprawiać wiele dyscyplin.
Program
powinien umożliwiać:

-    dodawanie nowych i modyfikację już istniejących wpisów,
-	utworzenie nowej lub usunięcie istniejącej dyscypliny,
-	zmianę nazwy dowolnej dyscypliny,
-	przenoszenie określonego ucznia z jednej dyscypliny do drugiej,
-	usuwanie określonego ucznia z danej dyscypliny
-	usuwanie określonego ucznia z całego spisu
-	wyszukiwanie i wyświetlanie uczniów wg zadanych  parametrów -
nazwisko, imię, klasa, średnia (np.: wyświetl wszystkich ze średnią
3.56,
albo: znajdź uczniów o imieniu Jacek) , wyświetlone pozycje powinny
zawierać
pełną informację, tzn. nazwisko, imię, klasa, średnia i uprawiane
dyscypliny.
-	wyświetlanie uczniów z dowolnie wybranej dyscypliny (pozycje w
kolejności alfabetycznej nazwisk)
-	wyświetlanie istniejących dyscyplin

Należy przyjąć, że w danej klasie nie ma kilku różnych uczniów o
takim samym
imieniu i nazwisku. Program powinien reagować i być odporny na
nielogiczne
wprowadzanie danych (np. klasa: ABCD). Niedopuszczalne jest
utworzenie kilku
katalogów o tej samej nazwie.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE "--------------------------------------------\n"

struct address {
  char dyscyplina[30];
  char nazwisko[40];
  char imie[20];
  char klasa[20];
  char ocena[20];
  struct address *next;
  struct address *prior;
};

struct address *start;
struct address *last;
struct address *find(char *);
struct address *find_ucznia( char *name,char *nazw);
struct address *find_uczniawdysc(char *dysc ,char *name,char *nazw);

void enter(void), search(), edit(), edit_nazw(void), search_klasa(void), search_ocena(void),search_imie(void),search_nazw(void), cut(void), edit_dyscyplina(void);
void list(void), list_all(void),list_all_katalogs(void);
void mldelete(struct address **, struct address **);
void dls_store(struct address *i, struct address **start,
               struct address **last);
void zsdelete(struct address **start, struct address **last);
void zsddelete(struct address **start, struct address **last);
void inputs(char *, char *, int), display(struct address *),displays(struct address *), display_katalogs(struct address *);
int menu_select(void);
void clear_buffer();

int main(void)
{
  start = last = NULL;
  int exit_t = 1;
  struct address *info;
  for(;;) {
    switch(menu_select()) {
      case 1: enter();
        break;
      case 2: mldelete(&start, &last);
        break;
     case 3:zsdelete(&start,&last);
         break;
     case 4:zsddelete(&start,&last);
         break;
      case 5: list();
        break;
      case 6: edit();
        break;
      case 7: cut();
        break;
      case 8: search(); //list_all();
        break;
      case 9: list_all_katalogs();
        break;
      case 10:
        printf("Jestes pewny? (yes - 0, no - 1)\n");
        printf("Wybor: "); scanf("%d",&exit_t);
        clear_buffer();
        if (exit_t == 0){
            while(start) {
                info = start->next;
                free(info);
                start = info;
            }
            exit(0);
        }
        else break;
      case 11: list_all();
        break;
    }
  }
  return 0;
}
/* Menu */
int menu_select(void)
{
  char s[80];
  int c;
  printf(LINE);
  printf("MENU:\n");
  printf(LINE);
  printf("1. Wpisz nowego ucznia\n");
  printf("2. Usun dyscypline\n");
  printf("3. Usun ucznia ze wsz dyscyplin\n");
  printf("4. Usun ucznia z dyscypliny\n");
  printf("5. Pokaz uczniow w dyscyplinie\n");
  printf("6. Edytuj ucznia w katalogu\n");
  printf("7. Przenies ucznia do katalogu\n");
  printf("8. Szukaj uczniow\n");
  printf("9. Pokaz dyscypline\n");
  printf("10. Exit\n");
  printf(LINE);
  do {
    printf("\nWybor: ");
    gets(s);
    c = atoi(s);
  } while(c<0 || c>11);
  return c;
}

/* Entering */
void enter(void)
{
  struct address *info;
  int naz=0,dys=1,im=0;

  for(;;) {
    info = (struct address *)malloc(sizeof(struct address));
    if(!info) {
      printf("\nNo free member");
      return;
    }
    printf(LINE);
    //fflush(stdin);
  wern2:
    inputs("Dyscyplina: ", info->dyscyplina, 30);
    while(info->dyscyplina[dys]){
	 if(isalpha(info->dyscyplina[dys])>0 || info->dyscyplina[0]=='\n'){ //jesli nazwisko jest napisane poprawnie sprawdzamy dalej
	 dys++;}
       else {printf("Napisales niepoprawne dane!!\n");
        goto wern2;}}
    if(!info->dyscyplina[0]) break;
    wern:
    inputs("Nazwisko: ", info->nazwisko, 40);
    while(info->nazwisko[naz]){
	 if(isalpha(info->nazwisko[naz])>0){ //jesli nazwisko jest napisane poprawnie sprawdzamy dalej
	 naz++;}
            else {printf("Napisales niepoprawne dane!!\n");
             goto wern;}
      }
    wern1:
    inputs("Imie: ", info->imie, 20);
 while(info->imie[im]){
	 if(isalpha(info->imie[im])>0){ //jesli nazwisko jest napisane poprawnie sprawdzamy dalej
	 im++;}
            else {printf("Napisales niepoprawne dane!!\n");
              goto wern1;}
      }
  while(1){
    inputs("Klasa: np 3a", info->klasa, 20);
     if((isdigit(info->klasa[0])==0 || isalpha(info->klasa[1])==0 || isalpha(info->klasa[2])>0 || isdigit(info->klasa[2])>0 || ispunct(info->klasa[2])>0) || isgraph(info->klasa[2])>0 || isprint(info->klasa[2])>0 ){
	printf("Napisales niepoprawne dane!!\n");
	continue;}
	break;
	}//kontynujemy poprawne wpisanie klasy
  while(1){
    inputs("Ocena w postaci n,nn: ", info->ocena, 20);
   if (isdigit(info->ocena[0])>0 && isdigit(info->ocena[2])>0 && isdigit(info->ocena[3])>0 && info->ocena[1]==',')
{
	break;}
	else{
	printf("Niepoprawne dane!!\n");
	continue;}
	}

    printf(LINE);
    dls_store(info, &start, &last);
  }
}


void inputs(char *prompt, char *s, int count)
{
  char p[255];
// int naz=1;
  do {
    printf(prompt);
    fgets(p, 254, stdin);
    if(strlen(p) > count) printf("\nToo long\n");
    p[0] = toupper(p[0]);
  } while(strlen(p) > count);

  p[strlen(p)-1] = 0;
  strcpy(s, p);

}

void clear_buffer()
{
     char ch;
     while ((ch=getchar()) != '\n' && ch != EOF);
}


 void dls_store(
  struct address *i,
  struct address **start,
  struct address **last
)
{
  struct address *old, *p;

  if(*last==NULL) {
    i->next = NULL;
    i->prior = NULL;
    *last = i;
    *start = i;
    return;
  }
  p = *start;

  old = NULL;
  while(p) {
    if(strcmp(p->dyscyplina, i->dyscyplina)<0){
      old = p;
      p = p->next;
    }
    else {
      if(p->prior) {
        p->prior->next = i;
        i->next = p;
        i->prior = p->prior;
        p->prior = i;
        return;
      }
      i->next = p;
      i->prior = NULL;
      p->prior = i;
      *start = i;
      return;
    }
  }
  old->next = i;
  i->next = NULL;
  i->prior = old;
  *last = i;
}


/* Deleting katalog with records */
void mldelete(struct address **start, struct address **last)
{
  struct address *info;
  char s[80];
  inputs("Dyscyplina: ", s, 30);
  do{

  info = find(s);
  if(info) {
    if(*start==info) {
      *start=info->next;
      if(*start) (*start)->prior = NULL;
      else *last = NULL;
    }
    else {
      info->prior->next = info->next;
      if(info!=*last)
          info->next->prior = info->prior;
      else
        *last = info->prior;
    }
    free(info);
  }
  }while(info);
}

void zsdelete(struct address **start, struct address **last)
{
  struct address *info;
  char s[80];
  char n[80];
  inputs("Nazwisko: ", s, 30);
  inputs("Imie: ", n, 30);
  do{

  info = find_ucznia(n,s);
  if(info) {
    if(*start==info) {
      *start=info->next;
      if(*start) (*start)->prior = NULL;
      else *last = NULL;
    }
    else {
      info->prior->next = info->next;
      if(info!=*last)
          info->next->prior = info->prior;
      else
        *last = info->prior;
    }
    free(info);
  }
  }while(info);
}

void zsddelete(struct address **start, struct address **last)
{
  struct address *info;
  char d[80];
  char s[80];
  char n[80];
  inputs("Dyscyplina: ",d,30);
  inputs("Nazwisko: ", s, 30);
  inputs("Imie: ", n, 30);
  do{

  info = find_uczniawdysc(d,n,s);
  if(info) {
    if(*start==info) {
      *start=info->next;
      if(*start) (*start)->prior = NULL;
      else *last = NULL;
    }
    else {
      info->prior->next = info->next;
      if(info!=*last)
          info->next->prior = info->prior;
      else
        *last = info->prior;
    }
    free(info);
  }
  }while(info);
}

struct address *find_uczniawdysc(char *dysc ,char *name,char *nazw)
{
  struct address *info;

  info = start;
  while(info) {
	if((!strcmp(dysc,info->dyscyplina)) && (!strcmp(nazw, info->nazwisko)) && (!strcmp(name, info->imie))) return info;
    info = info->next;}
 return NULL;
  }

 struct address *find_ucznia( char *name,char *nazw)
{
  struct address *info;

  info = start;
  while(info) {
	if((!strcmp(nazw, info->nazwisko)) && (!strcmp(name, info->imie))) return info;
    info = info->next;}
 return NULL;
  }

/* Help searching function */
struct address *find( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->dyscyplina)) return info;
    info = info->next;
  }
  //printf("Name not found.\n");
  return NULL;
}

struct address *find_nazw( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->nazwisko)) return info;
    info = info->next;
  }
  //printf("Name not found.\n");
  return NULL;
}


struct address *find_imie( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->imie)) return info;
    info = info->next;
  }
  //printf("Name not found.\n");
  return NULL;
}

struct address *find_klasa( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->klasa)) return info;
    info = info->next;
  }
  //printf("Name not found.\n");
  return NULL;
}

struct address *find_ocena( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->ocena)) return info;
    info = info->next;
  }
  //printf("Name not found.\n");
  return NULL;
}

void search(void)
{
    char s[10];
    int c;
    printf(LINE);
    printf("\nSzukaj:\n");
    printf(LINE);
    printf ("1.Szukajnazwisko  2.Szukaj imie 3.Szukaj klase 4.Szukaj ocene\n");
    printf(LINE);
    do {
        printf("\nChoose: ");
        gets(s);
        c = atoi(s);
    } while(c<0 || c>5);
    switch(c) {
      case 1: search_nazw();
        break;
      case 2: search_imie();
        break;
      case 3: search_klasa();
        break;
      case 4: search_ocena();
        break;
    }
}

/*Edit by mineral or zip*/
void edit(void)
{
    char s[10];
    int c;
    printf(LINE);
    printf ("\nEDITING MENU:\n");
    printf(LINE);
    printf ("Edytuj nazwe of\n1. dyscypliny\n2. ucznia");
    printf(LINE);
    do {
        printf("\nWybor: ");
        gets(s);
        c = atoi(s);
    } while(c<0 || c>3);
    switch(c) {
      case 1: edit_dyscyplina();
        break;
      case 2: edit_nazw();
        break;
    }
}

void edit_nazw(void)
{

  struct address *info;
  char s[30], n[30],z[30],k[30],j[30],jj[30],d[30],w[30],ww[30];
  inputs("Podaj Dyscypline: ",d,30);
  inputs("Wpisz nazwisko,ktore chcesz zmienic ", s, 30);
  inputs("Wpisz nazwisko na ktore chcesz zamienic: ", n, 30);
  inputs("Wpisz imie,ktore chcesz zmienic ", z, 30);
  inputs("Wpisz imie na ktore chcesz zamienic: ", k, 30);
  inputs("Wpisz klase,ktore chcesz zmienic ", j, 30);
  inputs("Wpisz klase na ktore chcesz zamienic: ", jj, 30);
  inputs("Wpisz ocene,ktore chcesz zmienic ", w, 30);
  inputs("Wpisz ocene na ktore chcesz zamienic: ", ww, 30);
  info = start;
  while(info) {
    if ((!(strcmp(d, info->dyscyplina)))&&(!(strcmp(s, info->nazwisko)))&&(!(strcmp(z, info->imie)))&&(!(strcmp(j, info->klasa)))&&(!(strcmp(w, info->ocena)))) {
        strcpy(info->nazwisko,n);
	strcpy(info->imie,k);
	strcpy(info->klasa,jj);
	strcpy(info->ocena,ww);
        break;
    }
    info = info->next;
    }
}

/*Edit katalog*/
void edit_dyscyplina(void)
{

  struct address *info;
  char s[30], n[30];
  inputs("Wpisz dyscypline,ktora chcesz edytowac: ", s, 30);
  inputs("Wpisz dyscypline: ", n, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->dyscyplina))) {
        strcpy(info->dyscyplina,n);
    }
    info = info->next;
    }
}

void list(void)
{
  struct address *info;
  char s[30];
  printf(LINE);
  printf("\nPokaz uczniow\n");
  printf(LINE);
  inputs("Dyscyplina: ", s, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->dyscyplina))) display(info);
    info = info->next;
  }
  printf("\n\n");
}


void list_all(void)
{
  struct address *info;

  info = start;
  printf(LINE);
  printf("\nDyscypliny i uczniowie:\n");
  printf(LINE);
  while(info) {
    display(info);
    info = info->next;
  }
  printf("\n\n");
}


void list_all_katalogs(void)
{
  struct address *info;
  int i=1;
  info = start;
  printf(LINE);
  printf("Dyscypliny:\n");
  printf(LINE);
  while(info) {

    printf("%d. ", i++);
    display_katalogs(info);
	printf("\n");
 info=info->next;
  }
  printf("\n");
}

/* Display */
void display(struct address *info)
{
    //printf("Dyscyplina: %s\n", info->dyscyplina);
    printf("|----Nazwisko: %s\n", info->nazwisko);
    printf("|----Imie: %s\n", info->imie);
    printf("|----Klasa: %s\n", info->klasa);
    printf("|----Ocena: %s\n", info->ocena);
    printf("\n\n");
}

void displays(struct address *info)
{
    printf("Dyscyplina: %s\n", info->dyscyplina);
    printf("|----Nazwisko: %s\n", info->nazwisko);
    printf("|----Imie: %s\n", info->imie);
    printf("|----Klasa: %s\n", info->klasa);
    printf("|----Ocena: %s\n", info->ocena);
    printf("\n\n");
}
/*Display katalogs*/
void display_katalogs(struct address *info)
{
    printf("%s", info->dyscyplina);
}

/*Cut&paste*/
void cut(void)
{
  struct address *info;
  char z[30];
  char n[80];
  char k[40];
  inputs("Podaj dyscypline ,z ktorej chcesz przeniesc:", z, 30);
  inputs("Wprowadz dyscypline do ktorej chcesz przeniesc: ", n, 30);
  inputs("podaj nazwisko", k, 40);
 info=start;
    while(info){
      if(!(strcmp(z,info->dyscyplina))){
        if(!(strcmp(k,info->nazwisko))){
      strcpy(info->dyscyplina,n);}}
     info=info->next;
  }
}

void search_nazw(void)
{
  struct address *info;
  char s[80];
  inputs("Nazwisko: ", s, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->nazwisko))) displays(info);
    info = info->next;
  }
  printf("\n\n");
}

void search_imie(void)
{
  struct address *info;
  char s[80];
  inputs("Imie: ", s, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->imie))) displays(info);
    info = info->next;
  }
  printf("\n\n");
}

void search_klasa(void)
{
  struct address *info;
  char s[80];
  inputs("Klasa: ", s, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->klasa))) displays(info);
    info = info->next;
  }
  printf("\n\n");
}

void search_ocena(void)
{
  struct address *info;
  char s[80];
  inputs("Ocena: ", s, 30);
  info = start;
  while(info) {
    if (!(strcmp(s, info->ocena))) displays(info);
    info = info->next;
  }
  printf("\n\n");
}