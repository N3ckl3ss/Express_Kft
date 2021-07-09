#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct patient
{
	unsigned int id;
	char name[50];
	char adress[50];
	char taj[50];
	char tests[50];
	char express[10];
};

unsigned int id = 1;

void read_console_messages(const char *console_text, char *result)
{
	printf(console_text);
	scanf("\n%[^\t\n]s",result);

}
void file_creation()
{
    FILE *file = fopen("adatbazis.txt", "a"); 
    fclose(file);
}

struct patient *file_read(FILE *file)
{
    struct patient *aktual = (struct patient *)malloc(sizeof(struct patient));
    fscanf(file, "%u\t%[^\t]\t%s\t%s\t%[^\t]\t%s", &(aktual->id), aktual->name, aktual->adress, aktual->taj, aktual->tests, aktual->express);
    return aktual;
}


void id_setup()
{
    FILE *infile;
    struct patient *aktual;

    id = 0;

    infile = fopen("adatbazis.txt", "r");
    if (infile != NULL)
    {
        aktual = file_read(infile);
        while (!feof(infile))
        {
            id = aktual->id;
            aktual = file_read(infile);
        }
    }
    fclose(infile);
    id++;
}


void patient_creation(const struct patient *createpatient)
{
	struct patient a;
	int test = 0;
	a.tests[0]= '\0';
    	char beolvasott_ertek[50];
    	if (createpatient != NULL)
    	{
        	a = *createpatient;
    	}
    	a.id = id;
    	id++;
    	read_console_messages("Name:\n", beolvasott_ertek);

    	if (strcmp(beolvasott_ertek, "-\0") == 0)
    	{
        	strcpy(a.name, createpatient->name);
    	}
    	else
    	{
        	strcpy(a.name, beolvasott_ertek);
    	}
   	
       read_console_messages("Adress:\n",beolvasott_ertek);
    
        if(strcmp(beolvasott_ertek, "-\0") == 0)
	{
		strcpy(a.adress, createpatient->adress);
	}
	else
	{
		strcpy(a.adress, beolvasott_ertek);
	}
	read_console_messages("TAJ:\n",beolvasott_ertek);
	if(strcmp(beolvasott_ertek, "-\0") == 0)
	{
		strcpy(a.taj, createpatient->taj);
	}
	else
	{
		strcpy(a.taj, beolvasott_ertek);
	}

	printf("Which tests would you like to get?\n");
	printf("1) COVID19\n");
	printf("2) HIV\n");
	printf("3) Cancer\n");
	printf("4) Blood\n");
	printf("5) Hepatitis\n");
	printf("6) Rabies\n");
	printf("7) Rorschach\n");
	printf("8)continue\n");
	do
	{
		scanf("%c", &test);
		switch (test)
		{
		case '1':
		strcat(a.tests, "  COVID19");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '2':
		strcat(a.tests, "  HIV");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '3':
		strcat(a.tests, "  Cancer");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '4':
		strcat(a.tests, "  Blood");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '5':
		strcat(a.tests, "  Hepatitis");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '6':
		strcat(a.tests, "  Rabies");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;
		case '7':
		strcat(a.tests, "  Rorschach");
		printf("Choose an other or continue by pressing 8 and Enter\n");
			break;	
		case '8':
		printf("continue");
            		break;
		default:
			break;
		}
		
	} while (test != '8');
	
	read_console_messages("Would you like Express VIP(Y/N):\n",beolvasott_ertek);
	if(strcmp(beolvasott_ertek, "-\0") == 0)
	{
		strcpy(a.express, createpatient->express);
	}
	else
	{
		strcpy(a.express, beolvasott_ertek);
	}


	FILE *outfile;
    	outfile = fopen("adatbazis.txt", "a");

    	if (outfile == NULL)
    	{
       	 fprintf(stderr, "\nHiba fajl megnyitaskor\n");
       	 exit(1);
    	}
    	fprintf(outfile, "%u\t%s\t%s\t%s\t%s\t%s\n", a.id, a.name, a.adress, a.taj, a.tests, a.express);
    	if (fprintf != 0)
    	{
       	 	printf("Successful !\n");
    	}
    	else
    	{
        	printf("Faild!\n");
    	}

    	fclose(outfile);
}


//List
void patient_list()
{
	char patient;
   	FILE *fptr;

   	if ((fptr = fopen("adatbazis.txt","r")) == NULL){
       		printf("Error! opening file");
       		exit(1);
   	}

    	while((patient = fgetc(fptr)) != EOF)
    		printf("%c", patient);
		
   	fclose(fptr);    
   	printf("\n");
}



//Delete
void patient_delete(unsigned int id, struct patient **deleted_patient, int msg)
{
	patient_list(NULL);

	 FILE *infile;
    FILE *outfile;

    struct patient *a;
    int visszajelzes_remove;
    int visszajelzes_rename;
    int flag = 0;

    if (deleted_patient != NULL)
    {
        *deleted_patient = NULL;
    }

    infile = fopen("adatbazis.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nHiba fajl megnyitasakor!\n");
        exit(1);
    }

    outfile = fopen("torles.txt", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nHiba fajl megnyitasakor!\n");
        exit(1);
    }

    a = file_read(infile);
    while (!feof(infile))
    {
        if (a->id != id)
        {
            fprintf(outfile, "%u\t%s\t%s\t%s\t%s\t%s\n", a->id, a->name, a->adress, a->taj, a->tests, a->express);
        }
        else
        {
            if (deleted_patient != NULL)
            {
                *deleted_patient = (struct patient *)malloc(sizeof(struct patient));
                memcpy(*deleted_patient, a, sizeof(struct patient));
            }
            flag = 1;
        }
        a = file_read(infile);
    }

    fclose(outfile);
    fclose(infile);
    visszajelzes_remove = remove("adatbazis.txt");
    visszajelzes_rename = rename("torles.txt", "adatbazis.txt");
    if (msg == 1)
    {
        if (visszajelzes_remove == 0 && visszajelzes_rename == 0 && flag == 1)
        {
            printf("Successful!\n");
        }
        else
        {
            printf("Failed!\n");
        }
    }
    id_setup();

}

//Modyfi
void  patient_changer(unsigned int id)
{
    struct patient *modositani_kivant = NULL;
    patient_delete(id, &modositani_kivant, 0);
    if (modositani_kivant == NULL)
    {
        printf("Dosn't exist!\n");
    }
    else
    {
        patient_creation(modositani_kivant);
    }
}

//beadando2
pid_t mainsvalue = 0;
int jelek = 0;
int mento1_pipes_in[2];
int mento1_pipes_out[2];
int mento2_pipes_in[2];
int mento2_pipes_out[2];

void varakozas(int sig)
{
	if (sig == SIGUSR1)
	{
		jelek++;
	}
}
void sikeres(int sig)
{
	if (sig == SIGUSR2)
	{
		printf("All done for the day");
	}
}
//gyerek1
pid_t mento_1(int pipe_id_rec, int pipe_id_send){

	char inbuf[50];
	int tests = 0;
	int number_of_tests = 0;

	pid_t szal = fork();
	if (szal == -1)
	{
		exit(-1);
	}
	if (szal > 0)
	{
		return szal;
	}
	kill(mainsvalue, SIGUSR1);
	read(pipe_id_rec, &number_of_tests, sizeof(int)); 
	
	while (tests < number_of_tests)
	{
	 	read(pipe_id_rec, inbuf, 50); 
        	printf("% s  ", inbuf); 
		read(pipe_id_rec, inbuf, 50); 
        	printf("% s\n", inbuf); 
		tests++;
		
	}
	
	exit(0);
}
//gyerek2
pid_t mento_2(int pipe_id_rec, int pipe_id_send){

	
	char inbuf[50];
	int number_of_tests = 0;
	int addressnumber= 0;

	pid_t szal = fork();
	if (szal == -1)
	{
		exit(-1);
	}
	if (szal > 0)
	{
		return szal;
	}
	kill(mainsvalue, SIGUSR1);
	read(pipe_id_rec, &number_of_tests, sizeof(int));

	if(number_of_tests > 6)
	{
		number_of_tests = 6;
	}

	addressnumber = 0;
	while (addressnumber < number_of_tests)
	{
		if(addressnumber%2 == 0)
		{
			printf("mento1: ");
		}else
		{
			printf("mento2: ");
		}
		
		read(pipe_id_rec, inbuf, 50); 
        printf("% s\n", inbuf); 
		addressnumber++;
		
	}


	exit(0);
}
void go_to_patient(){
	
	int i = 0;
	int number_of_tests = 0;
	FILE *infile;
	struct patient *a;
	
	signal(SIGUSR1, varakozas);
	signal(SIGUSR2, sikeres);
	mainsvalue = getpid();

	
	int succ = pipe(mento1_pipes_in);
	if (succ == -1)
	{
		exit(-1);
	}
	int succ1 = pipe(mento1_pipes_out);
	if (succ1 == -1)
	{
		exit(-1);
	}
	int succ2 = pipe(mento2_pipes_out);
	if (succ2 == -1)
	{
		exit(-1);
	}
	int succ3 = pipe(mento2_pipes_in);
	if (succ3 == -1)
	{
		exit(-1);
	}
	
	wait(NULL);

	mento_1(mento1_pipes_out[0],mento1_pipes_in[1]);
	mento_2(mento2_pipes_out[0],mento2_pipes_in[1]);
	while (jelek < 1);
	puts("First Ambulance is ready.");
	while (jelek < 2);
	puts("Second Ambulance is ready.\n");

	infile = fopen("adatbazis.txt", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nHiba fajl megnyitasakor!\n");
        exit(1);
    }

	a = file_read(infile);
	while(!feof(infile)){

		if(!strcmp(a->express, "Y"))
		{
			number_of_tests++;
		}
		a = file_read(infile);
	}
	
	write(mento1_pipes_out[1],&number_of_tests, sizeof(int));
	write(mento2_pipes_out[1],&number_of_tests, sizeof(int));

	rewind(infile);

	a = file_read(infile);
	while(!feof(infile)){

		if(!strcmp(a->express, "Y"))
		{
			write(mento1_pipes_out[1],a->name, 50);
			write(mento1_pipes_out[1],a->tests, 50);
		}
		a = file_read(infile);
	}
	

	wait(NULL);

	printf("Number of tests: %i\n", number_of_tests);
	if(number_of_tests > 6){
		printf("Not enough capacity\n");
	}

	rewind(infile);

	char array[number_of_tests][50];
	bool hasbeen = false;

	a = file_read(infile);
	while(!feof(infile)){

		hasbeen = false;

		if(!strcmp(a->express, "Y")){

			i++;
			for(int y = 1; y <= i; y++)
			 {
				 if(!strcmp(array[y], a->adress))
				 {
					 hasbeen = true;
					 i--;
				 }
			 }	
			if(!hasbeen)
			 {
				 strcpy(array[i], a->adress);
			 }
		}
		a = file_read(infile);
	}

	int y = 0;

	if(number_of_tests > 6)
	{
		y = 6;
	}
	else{
		y = number_of_tests;
	}
	
	for(i=1; i<=y; i++)
	{
			write(mento2_pipes_out[1],array[i], 50);
	}	

	wait(NULL);
	fclose(infile);
	kill(mainsvalue, SIGUSR2);


}

int main()
{
    int command;
	
    file_creation();
    id_setup();
	
	printf("\n\n\nWelcome to Express kft\nChoose from the menu options by typing in the number next to them\n");    

    do
    {
	
        printf("\n-----MENU-----\n");
        printf("1) New Patient\n");
		printf("2) Patient list\n");
		printf("3) Patient modify\n");
	 	printf("4) Patient delete\n");
		printf("5) Go to Patients\n"); 
        printf("6) Exit\n\n");
        switch (command)
        {
        case '1':
            patient_creation(NULL);
            break;
	  	case '2':
		   	patient_list(NULL);
            break;
	  	case '3':
		  	patient_list(NULL);
            printf("Id:\n");
            scanf("%u", &id);
            patient_changer(id);
            break;
	  	case '4':
		  	patient_list(NULL);
		  	printf("Id:\n");
            scanf("%u", &id);
            patient_delete(id, NULL, 1);
            break;
		case '5':
			go_to_patient();
			break;
        case '6':
            printf("Exit\n");
            exit(0);
            break;
        default:
            break;
        }
    } while ((command = getchar()) != EOF);
    return 0;
}