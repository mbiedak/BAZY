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
	int len = 20;
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

void printAllRecords(record* database)
{
	int i = 0;
	for (i = 0; i<NUM_OF_RECORDS; ++i)
	{
		printf("%s, %s, %d, %s, %d\n", database[i].surname, database[i].name, database[i].age, database[i].city, database[i].salary);
	}
}

int findFirst(record* database) //chcialbym, zeby ta funkcja zwracala int, zeby pozniej mogl przypisac "i" do findFirst
{
	int i = 0;
	for (i = 0; i<NUM_OF_RECORDS; ++i)
	{
		if ( !database[i].filled )
		{
			return i;
		}
	}
	return i;
}

void add(record* database)
{
	int i = findFirst(database);
        
        printf("Bedziemy wypelniac rekord nr %d.\n", i);
        
	printf("Wprowadz nazwisko:\n");
	scanf("%s", database[i].surname);
	printf("Wprowadz imie:\n");
	scanf("%s", database[i].name);
	printf("Wprowadz wiek:\n");
	scanf("%d", &database[i].age);
	printf("Wprowadz miasto:\n");
	scanf("%s", database[i].city);
	printf("Wprowadz pensje:\n");
	scanf("%d", &database[i].salary);
}

void cut(record* database)
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

void edit(record* database)
{
	int i=0;
        
        do
        {
		printf("Ktory rekord edytowac? Podaj liczbe z zakresu 1 do %d:", NUM_OF_RECORDS);
		scanf("%d", &i);
		i = i - 1;
	}while(i<0 || i>=NUM_OF_RECORDS);
        
        printf("Wprowadz nazwisko:\n");
	scanf("%s", database[i].surname);
	printf("Wprowadz imie:\n");
	scanf("%s", database[i].name);
	printf("Wprowadz wiek:\n");
	scanf("%d", &database[i].age);
	printf("Wprowadz miasto:\n");
	scanf("%s", database[i].city);
	printf("Wprowadz pensje:\n");
	scanf("%d", &database[i].salary);
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

int askMenu(record* database)
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
		add(database);
		break;
	case CUT:
		cut(database);
		break;
	case EDIT:
		edit(database);
		break;
	case SHOW:
		printAllRecords(database);
		break;
	case SORT_AGE:
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
	//record* database = allocBase(NUM_OF_RECORDS);
	int succes = 0;
        allocBase(NUM_OF_RECORDS);

	while (succes == 0)
	{
		printMenu();
		succes = askMenu(db);
	}

	scanf("%s");
	return 0;
}

