/*napisa program o strukturze:
- imie
- wiek
- zarobki
MENU: dodawanie, zapis, odczyt, usun, edycja, sortowanie po nazwisko, wieku, zapis i odczyt do/z pliku - sprawozdanie, wlasne 2 funkcje
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


const int NUM_OF_RECORDS = 4;

enum MENU
{
	OPEN = 0, //funkcja zasyjaca plik do programu
	SAVE, //funkcja zapisjaca bazê do pliku *.txt
	ADD, //funkcja dodajaca rekord do bazy
	CUT, //funkcja wycinajaca rekord z bazy
	EDIT, //funkcja edytujaca dany rekord
	SHOW, //funkcja pokazujaca stan bazy na której aktualnie pracujemy
	SORT_AGE, //funkcja sortujaca wg wieku
	SORT_NAME,
	EXIT,
	LAST_MENU
};
const int TEXT_LEN = 20;
typedef struct dbRecords
{
	char surname[TEXT_LEN];
	char name[TEXT_LEN];
	int age;
	char city[TEXT_LEN];
	int salary;
        int filled;
} record;

record db[NUM_OF_RECORDS];

void allocBase(int numberOfRecords)
{
	int len = 20; //po co tutaj ta zmienna skoro nie jest użyta?
	for (int i = 0; i < numberOfRecords; ++i)
	{
		db[i].surname[0] = '\0';
		db[i].name[0] = '\0';
		db[i].age = 0;
		db[i].city[0] = '\0';
		db[i].salary = 0;
                db[i].filled = 0;
	}
}

void printAllRecords()
{
	int i = 0;
	for (i = 0; i<NUM_OF_RECORDS; ++i)
	{
		printf("%s, %s, %d, %s, %d\n", db[i].surname, db[i].name, db[i].age, db[i].city, db[i].salary);
	}
}

int findFirst() //chcialbym, zeby ta funkcja zwracala int, zeby pozniej mogl przypisac "i" do findFirst
{
	int i = 0;
	for (i = 0; i<NUM_OF_RECORDS; ++i)
	{
		if ( !db[i].filled )
		{
			return i;
		}
	}
	return i;
}

void open()
{
	FILE *pFILE; //identyfikator pliku
	pFILE = fopen("baza.txt", "r");
	int i = 0;
	while ((fgets(buf, 256, pFILE)) != NULL)
	{// oczywiscie nie bedzie dzialalo, bo cos z pamiecia jest nie halo
		sscanf(buf, "%s %s %d %s %d", db[i].surname, db[i].name, &db[i].age, db[i].city, &db[i].salary);
		++i;
		db[i].filled = 1;
	}
	free(buf);
}

void save()
{
	FILE * pFILE;
	pFILE = fopen("baza.txt", "w");
	int i = 0;
	while (db[i].filled !=0)
	{
		printf("%s %s %d %s %d\n", db[i].surname, db[i].name, db[i].age, db[i].city, db[i].salary);
	}
	fclose(pFILE);
}

void add(void)
{
	int i = findFirst(); 
    printf("Bedziemy wypelniac rekord nr %d.\n", i);
	printf("Wprowadz nazwisko:\n");
	scanf("%s", db[i].surname);
	printf("Wprowadz imie:\n");
	scanf("%s", db[i].name);
	printf("Wprowadz wiek:\n");
	scanf("%d", &db[i].age);
	printf("Wprowadz miasto:\n");
	scanf("%s", db[i].city);
	printf("Wprowadz pensje:\n");
	scanf("%d", &db[i].salary);
	db[i].filled = 1;
}
/*
void cut(record* database)
        db[i].filled = 1;
}
nie rozumiem tej funkcji do końca
*/ 
void cut()
{
	int i=0;
        
        do
        {
		printf("Ktory rekord wyciac? Podaj liczbe z zakresu 1 do %d:", NUM_OF_RECORDS);
		scanf("%d", &i);
		i = i - 1;
	}while(i<0 || i>=NUM_OF_RECORDS);
	db[i].surname[0] = '\0';
	db[i].name[0] = '\0';
	db[i].age = 0;
	db[i].city[0] = '\0';
	db[i].salary = 0;
	db[i].filled = 0;
}

void edit()
{
	int i=0;
        
        do
        {
		printf("Ktory rekord edytowac? Podaj liczbe z zakresu 1 do %d:", NUM_OF_RECORDS);
		scanf("%d", &i);
		i = i - 1;
	}while(i<0 || i>=NUM_OF_RECORDS);
        
        printf("Wprowadz nazwisko:\n");
	scanf("%s", db[i].surname);
	printf("Wprowadz imie:\n");
	scanf("%s", db[i].name);
	printf("Wprowadz wiek:\n");
	scanf("%d", &db[i].age);
	printf("Wprowadz miasto:\n");
	scanf("%s", db[i].city);
	printf("Wprowadz pensje:\n");
	scanf("%d", &db[i].salary);
        db[i].filled = 1;
}

char menuText[LAST_MENU][41] = {
	"Pobierz istniejaca baze z pliku *.txt",
	"Zapisz aktualna baze do pliku *.txt",
	"Dodaj rekord do bazy",
	"Wytnij rekord",
	"Edytuj rekord",
	"Pokaz wszystkie rekordy",
	"Sortuj wg wieku",
	"Sortuj wg nazwiska",
	"Koniec programu" };

void printMenu(void)
{
	int i = 0;
	printf("\n\nMenu:\n");
	for (i = 0; i<LAST_MENU; ++i)
	{
		printf("%d %s\n", i, menuText[i]);
	}
}

void copyRecord(record* source, record* dest)
{
    dest->age = source->age;
    dest->filled = source->filled;
    dest->salary = source->salary;
    
    strcpy(dest->city, source->city);
    strcpy(dest->name, source->name);
    strcpy(dest->surname, source->surname);
}

void switchRecords(record* a, record* b)
{
    record temp;
    copyRecord(a, &temp);
    copyRecord(b, a);
    copyRecord(&temp, b);
}

void sortAge(void)
{
    int changes = 1;
    while(changes>0)
    {
        changes = 0;
        for(int i=0; i<NUM_OF_RECORDS-1; i++)
        {
            if(db[i].age > db[i+1].age)
            {
                changes++;
                switchRecords(&db[i], &db[i+1]);
            }
        }
    }
}

int askMenu()
{
	int pozycjaMenu = 0;
	printf("Wybierz opcje (0-8)");
	scanf("%d", &pozycjaMenu);
	switch (pozycjaMenu)
	{
	case OPEN:
		printf("Baza zostala pobrana");
		break;
	case SAVE:
		printf("Baza zostala zapisana do pliku");
		break;
	case ADD:
		add();
		break;
	case CUT:
		cut();
		break;
	case EDIT:
		edit();
		break;
	case SHOW:
		printAllRecords();
		break;
	case SORT_AGE:
                sortAge();
		printf("Posortowano wg wieku");
		break;
	case SORT_NAME:
		printf("Posortowano wg nazwiska");;
		break;
	case EXIT:
		return 1;   //dopiero tutaj mozemy wyjsc z zapetlonego menu - do funkcji main i zwracamy 1 konczac program
	}
	return 0;
}

int main()
{
	int succes = 0;
        allocBase(NUM_OF_RECORDS);

	while (succes == 0)
	{
		printMenu();
		succes = askMenu();
	}

	scanf("%s");
	return 0;
}

