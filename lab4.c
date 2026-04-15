//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret= atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//
//void adaugaMasinaInLista(Nod ** lista, Masina masinaNoua) {
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = masinaNoua; //shallow copy
//	nou->next = NULL;
//	Nod* aux = *lista;
//	if ((*lista) != NULL) {
//		while (aux->next != NULL) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//	}
//	else {
//		*lista = nou;
//	}
//}
//void afisareListaMasini(Nod * cap) {
//	while (cap != NULL) {
//		afisareMasina(cap -> info);
//		cap = cap->next;
//	}
//}
//void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//}
//
////void * este ponier la orice- 4/8 octeti orice pointer
////tot trb sa returneze un pointer !! doar ca poate fi de orice tip 
////puteam sa punem Nod*
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* lista=NULL;
//	while (!feof(file)) {
//		Masina masina = citireMasinaDinFisier(file);
//		adaugaMasinaInLista(&lista, masina);
//	}
//	fclose(file);
//	return lista;
//}
//
//void dezalocareListaMasini(/*lista de masini*/ Nod**lista) {
//	Nod* head = *lista;
//	Nod* next = NULL;
//	while (head != NULL) {
//		next = head->next;
//		free(head->info.model);
//		free(head->info.numeSofer);
//		free(head);
//		head = next;
//	}
//	*lista = NULL;
//}
//
//float calculeazaPretMediu(Nod * lista) { //doar o * ca nu modificam, asa e lista pointer
//	float suma = 0;
//	int nrMasini = 0;
//	while (lista != NULL) {
//		suma += lista->info.pret;
//		nrMasini++;
//		lista = lista->next;
//	}
//	if(nrMasini!=0)
//	return suma / nrMasini; //daca unul dintre operanzi e real, rez e tot real
//	return 0;
//}
//
//void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() {
//
//	//Nod* lista = NULL;
//	Nod* lista = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	float pretMediu = calculeazaPretMediu(lista);
//	printf("\npret mediu= %f", pretMediu);
//	dezalocareListaMasini(&lista);
//	afisareListaMasini(lista);
//	
//	
//	return 0;
//}