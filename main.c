#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MESE 20
#define FILE_NAME "mese.txt"
typedef struct {
    int id;
    int capacitate;
    int rezervata;
    char data[20];
    char interval_orar[12];
} Masa;

Masa mese[MAX_MESE];
int nr_mese=0;

void green() {printf("\033[1;32m");}
void cyan() {printf("\033[1;36m");}
void red() {printf("\033[1;31m");}
void yellow() {printf("\033[1;33m");}
void purple() {printf("\033[1;35m");}
void orange() {printf("\033[1;38;5;214m");}
void lightpink() {printf("\033[1;38;5;200m");}
void gray() {printf("\033[1;38;5;245m");}
void lightred() {printf("\033[1;38;5;196m");}
void lightgreen() {printf("\033[1;38;5;82m");}
void lightorange() {printf("\033[1;38;5;208m");}
void coral() {printf("\033[1;38;5;211m");}
void reset() {printf("\033[0m");}

void continuare(){
    yellow();
    printf("\n--- Apasa enter pentru a continua. ---\n");
    reset();
    while(getchar() != '\n');
    getchar();
}

int toateCifre(const char *s,int start,int end){
    for(int i=start;i<end;i++)
        if(isdigit(s[i])==0)
            return 0;
    return 1;
}

int esteDataValida(const char *s){
    if(strlen(s)!=10)
        return 0;
    if(s[2]!='-' || s[5]!='-')
        return 0;
    if(!toateCifre(s,0,2) || !toateCifre(s,3,5) || !toateCifre(s,6,10))
        return 0;
    int zi=(s[0]-'0')*10+(s[1]-'0');
    int luna=(s[3]-'0')*10+(s[4]-'0');
    int an=(s[6]-'0')*1000+(s[7]-'0')*100+(s[8]-'0')*10+(s[9]-'0');
    if(luna<1 || luna>12)
        return 0;
    int zileLuna[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int bisect=(an%4==0 && an%100!=0);
    if(bisect)
        zileLuna[2]=29;
    if(zi<1 || zi>zileLuna[luna])
        return 0;
    return 1;
}
int esteOraValida(const char *s){
    if(strlen(s)!=5)
        return 0;
    if(s[2]!=':')
        return 0;
    if(!toateCifre(s,0,2) || !toateCifre(s,3,5))
        return 0;
    int h=(s[0]-'0')*10+(s[1]-'0');
    int m=(s[3]-'0')*10+(s[4]-'0');
    return (h>=0 && h<24 && m>=0 && m<60);
}
int esteIntervalValid(const char *s){
    if(strlen(s)!=11)
        return 0;
    if(s[5]!='-')
        return 0;
    char oraStart[6],oraStop[6];
    strncpy(oraStart,s,5);
    oraStart[5]='\0';
    strncpy(oraStop,s+6,5);
    oraStop[5]='\0';
    if (!esteOraValida(oraStart) || !esteOraValida(oraStop))
        return 0;
    int h1=(oraStart[0]-'0')*10+(oraStart[1]-'0');
    int m1=(oraStart[3]-'0')*10+(oraStart[4]-'0');
    int h2=(oraStop [0]-'0')*10+(oraStop [1]-'0');
    int m2=(oraStop [3]-'0')*10+(oraStop [4]-'0');
    int startMin=h1*60+m1;
    int stopMin=h2*60+m2;
    return startMin<stopMin;
}
void incarcaMese(){
    FILE *f=fopen(FILE_NAME, "r");
    if(!f)
        return;
    nr_mese=0;
    while(fscanf(f,"%d %d %d %s %s",&mese[nr_mese].id,&mese[nr_mese].capacitate,&mese[nr_mese].rezervata,mese[nr_mese].data,mese[nr_mese].interval_orar)!=EOF) {
        nr_mese++;
    }
    fclose(f);
}
void salveazaMese(){
    FILE *f=fopen(FILE_NAME, "w");
    for(int i=0;i<nr_mese;i++)
        fprintf(f,"%d %d %d %s %s\n",mese[i].id,mese[i].capacitate,mese[i].rezervata,mese[i].data,mese[i].interval_orar);
    fclose(f);
}
void sorteazaMese(){
    for(int i=0;i<nr_mese-1;i++){
        for(int j=i+1;j<nr_mese;j++){
            if(mese[i].id>mese[j].id){
                Masa aux=mese[i];
                mese[i]=mese[j];
                mese[j]=aux;
            }
        }
    }
}
void afiseazaMese(){
    system("cls");
    sorteazaMese();
    yellow();
    printf("\n--- Lista meselor ---\n");
    for(int i=0;i<nr_mese;i++){
        lightorange();
        printf("Masa - ");
        cyan();
        if (mese[i].id<10)
            printf(" %d ",mese[i].id);
        else
            printf("%d ",mese[i].id);
        lightorange();
        printf("- Capacitate: ");
        cyan();
        if (mese[i].capacitate<10)
            printf(" %d persoane",mese[i].capacitate);
        else
            printf("%d persoane",mese[i].capacitate);
        if(mese[i].rezervata==1){
        lightred();
        printf(" Rezervata ");
        purple();
        printf("in data de ");
        lightpink();
        printf("%s",mese[i].data);
        purple();
        printf(" intre orele ");
        lightpink();
        printf("%s\n",mese[i].interval_orar);
        reset();
    }
        else {
            lightgreen();
            printf(" Disponibila\n");
            reset();
        }
    }
    continuare();
}
void adaugaMasa(){
    system("cls");
    yellow();
    printf("--- Adaugare masa ---\n");
    reset();
    if(nr_mese>=MAX_MESE){
        red();
        printf("\nNu mai pot fi adaugate mese!\n");
        reset();
        continuare();
        return;
    }
    int id,capacitate;
    while(1){
        lightorange();
        printf("ID Masa: ");
        reset();
        scanf("%d", &id);
    if (id>20 || id<1){
        red();
        printf("\nID-ul mesei trebuie sa fie intre 1 si 20!\n\n");
        reset();
        }
    else
        break;
    }
    for(int i=0;i<nr_mese;i++){
        if(mese[i].id==id){
            red();
            printf("\nO masa cu acest ID exista deja!\n");
            reset();
            continuare();
            return;
        }
    }
    lightorange();
    printf("Capacitate: ");
    reset();
    scanf("%d",&capacitate);
    mese[nr_mese].id=id;
    mese[nr_mese].capacitate=capacitate;
    mese[nr_mese].rezervata=0;
    strcpy(mese[nr_mese].data, "00-00-0000");
    strcpy(mese[nr_mese].interval_orar, "00:00-00:00");
    nr_mese++;
    salveazaMese();
    green();
    printf("\nMasa a fost adaugata!\n");
    reset();
    continuare();
    system("cls");
}
void stergeMasa(){
    system("cls");
    yellow();
    printf("--- Stergere masa ---\n");
    reset();
    int id;
    lightorange();
    printf("ID Masa de sters: ");
    reset();
    scanf("%d",&id);
    for(int i=0;i<nr_mese;i++){
        if(mese[i].id == id){
            for(int j=i;j<nr_mese-1;j++){
                mese[j]=mese[j+1];
            }
            nr_mese--;
            salveazaMese();
            green();
            printf("\nMasa a fost stearsa!\n");
            reset();
            continuare();
            system("cls");
            return;
        }
    }
    salveazaMese();
    red();
    printf("\nMasa nu a fost gasita!\n");
    reset();
    continuare();
}
void rezervaMasa(){
    system("cls");
    yellow();
    printf("--- Rezervare masa ---\n");
    reset();
    int id;
    lightorange();
    printf("ID Masa(Nr. cuprins intre 1 si 20): ");
    reset();
    scanf("%d",&id);
    for(int i=0;i<nr_mese;i++){
        if(mese[i].id==id){
            if(mese[i].rezervata==1){
                red();
                printf("\nMasa este deja rezervata!\n");
                reset();
                continuare();
                return;
            }
            while(1){
                lightorange();
                printf("Data (ZZ-LL-AAAA): ");
                reset();
                scanf("%19s", mese[i].data);
                if(esteDataValida(mese[i].data))
                    break;
                red();
                printf("Va rog sa introduceti o data valida (precum: 19-03-2025)\n");
                reset();
            }
            while(1){
                lightorange();
                printf("Interval orar (HH:MM-HH:MM): ");
                reset();
                scanf("%19s", mese[i].interval_orar);
                if(esteIntervalValid(mese[i].interval_orar)){
                    mese[i].rezervata=1;
                    salveazaMese();
                    break;
                }
                    red();
                    printf("Va rog sa introduceti un interval orar valid (precum: 12:00-14:00)\n");
                    reset();
            }
            green();
            printf("\nMasa a fost rezervata!\n");
            reset();
            continuare();
            system("cls");
            return;
        }
    }
    salveazaMese();
    red();
    printf("\nMasa nu a fost gasita!\n");
    reset();
    continuare();
}
void anuleazaRezervare(){
    system("cls");
    yellow();
    printf("--- Anulare rezervare masa ---\n");
    int id;
    lightorange();
    printf("ID Masa: ");
    reset();
    scanf("%d", &id);
    for(int i=0;i<nr_mese;i++){
        if(mese[i].id == id && mese[i].rezervata){
            mese[i].rezervata=0;
            salveazaMese();
            green();
            printf("\nRezervarea a fost anulata!\n");
            reset();
            continuare();
            system("cls");
            return;
        }
    }
    salveazaMese();
    red();
    printf("\nRezervarea nu a fost gasita!\n");
    reset();
    continuare();
}
int main() {
    incarcaMese();
    int optiune;
    do {
        system("cls");
        yellow();
        printf("=== Meniu Restaurant ===\n");
        coral();
        printf("1. Afiseaza mese\n2. Adauga masa\n3. Sterge masa\n4. Rezerva masa\n5. Anuleaza rezervare\n0. Iesire\n");
        printf("Optiune: ");
        reset();
        scanf("%d", &optiune);
        switch(optiune){
            case 1:
                afiseazaMese();
                break;
            case 2:
                adaugaMasa();
                break;
            case 3:
                stergeMasa();
                break;
            case 4:
                rezervaMasa();
                break;
            case 5:
                anuleazaRezervare();
                break;
            case 0:
                cyan();
                printf("\nProgramul s-a incheiat.\n");
                break;
            default:
                cyan();
                printf("\nOptiune invalida!\n");
                reset();
                continuare();
        }
    }while(optiune!=0);
    return 0;
}
