#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina; //typedef in loc masina cu struct structura masina- e un fel de alias ca sa nu mai scriu cu stuct

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("\n ID Masina: %d", masina.id);
	printf("\n nr usi Masina: %d", masina.nrUsi);
	printf("\n pret Masina: %f", masina.pret);
	printf("\n model Masina: %s", masina.model);
	printf("\n nume sofer Masina: %s", masina.numeSofer);
	printf("\n serie Masina: %c\n", masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0;i < nrMasini;i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	
	(*nrMasini)++; //creste nr si trb trimis prin adresa! deaia avem pointer
	Masina* aux = malloc(sizeof(Masina) * (*nrMasini));
	for (int i = 0;i < (*nrMasini)-1;i++) {
		//pasii: dereferentiere, [deplasare, dereferentiere]-asta face operatorul index
		//aux[i] = *(masini)[i]; gresit!, mai intai facem indexare
		aux[i] = (*masini)[i];// shallow copy - asta vrem
	}
	aux[(*nrMasini) - 1] = masinaNoua;
	free(*masini); //trebuie dereferentiat! pt ca am fct shallow copy
	*masini = aux;

}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;

	char linie[50];
	fgets(linie, 50, file);
	char delimitator[3] = ",\n";
	Masina masina;
	masina.id = atoi(strtok(linie,delimitator));
	masina.nrUsi= atoi(strtok(NULL, delimitator));
	masina.pret = atof(strtok(NULL, delimitator));
	//model e de tip pointer deci trb alocat loc
	char* model = strtok(NULL, delimitator);
	masina.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);
	//free(model); gresit pt ca sirul pt model e pe stiva, stegem cu free doar elem pt care noi am dat malloc!

	char* numeSofer = strtok(NULL, delimitator);
	masina.numeSofer = malloc((strlen(numeSofer) + 1) * sizeof(char));
	strcpy(masina.numeSofer, numeSofer);

	char* serie = strtok(NULL, delimitator);
	masina.serie = serie[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide 
	// si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file= fopen(numeFisier, "r");
	*nrMasiniCitite = 0; //dereferentiem ca este primit prin adresa
	Masina* masini = NULL;
	while (!feof(file)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));//apelez functia, deci folosim &
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	/*for (int i = 0;i< nrMasini;i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
		free(*vector);
	}*/
}

int main() {

	//FILE* file = fopen("masini.txt.txt", "r"); //read-only
	//Masina masina = citireMasinaFisier(file);
	//afisareMasina(masina);
	Masina*  masini;
	int nr = 0;
	masini = citireVectorMasiniFisier("masini.txt.txt", &nr);
	afisareVectorMasini(masini, nr);

	return 0;
}