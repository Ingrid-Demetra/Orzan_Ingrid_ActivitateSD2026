//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////graf conex=am drum catre orice nod
//
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
//	m1.pret = atof(strtok(NULL, sep));
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
////1. 
//// structuri necesare
////dorim stocarea unui graf intr-o lista de liste
////astfel avem nod ListaPrincipala si NodListaSecundara
//
//typedef struct NodPrincipal NodPrincipal;
//typedef struct NodSecundar NodSecundar;
//
//struct NodPrincipal {
//	Masina info;
//	NodPrincipal* next;
//	NodPrincipal* vecini;
//};
//
//struct NodSecundar {
//	NodPrincipal* info;
//	NodSecundar* next;
//};
////2.
////functii de inserare in liste
////si in principala si in secundara
//
//void inserareListaP(NodPrincipal**graf, Masina masinaNoua) { //inserare clasica in lista cred
//	NodPrincipal* nou = malloc(sizeof(NodPrincipal)); 
//	//mereu cand crez ceva nou initializez atriutele
//	nou->info= masinaNoua;
//	nou->next = NULL;
//	nou->vecini = NULL;
//	if (*graf) {
//		NodPrincipal* aux = *graf;
//		while (aux->next) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//
//	}
//	else { //daca nu avem nmc in graf
//		*graf = nou;
//	}
//}
//void inserareListaS(NodSecundar** listaS, NodPrincipal* info) {
//	NodSecundar* nou = malloc(sizeof(NodSecundar));
//	nou->info = info;
//	nou->next = NULL;
//	if (*listaS) {
//		NodSecundar* aux = (*listaS);
//		while (aux->next)
//		{
//			aux = aux->next;
//		}
//		aux->next = nou;
//	}
//	else {
//		*listaS = nou;
//	}
//
//}
////3.
////functie de cautarea in lista principala dupa ID
//NodPrincipal* cautaNodDupaID(NodPrincipal* listaPrincipala, int id) {
//	
//		while ((listaPrincipala)&&listaPrincipala->info.id != id) {
//			listaPrincipala = listaPrincipala->next;
//		}
//		return listaPrincipala;
//}
//
////4.
////inserare muchie
//void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop) {
//	if (listaPrincipala) {
//		NodPrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
//		NodPrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStop);
//		if (nodStart && nodStop) {
//			inserareListaS(&(nodStart)->vecini, nodStop);
//			inserareListaS(&(nodStop)->vecini, nodStart);
//		}
//	}
//}
//
//
//NodPrincipal* citireNoduriMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	NodPrincipal* listaPrincipala = NULL;
//	if (f) {
//		while (!feof(f)) {
//
//			inserareListaP(&listaPrincipala, citireMasinaDinFisier(f));
//		}
//	}
//	fclose(f);
//	return listaPrincipala;
//}
//
//void citireMuchiiDinFisier(NodPrincipal *listaPrincipala, const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste 
//	//toate id-urile de start si stop pentru fiecare much
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file)) {
//		int idStart;
//		int idStop;
//		fscanf(file, "%d %d",&idStart,&idStop ); //cu & pt ca modific
//		inserareMuchie(listaPrincipala, idStart, idStop);
//	}
//}
//
//void dezalocareNoduriGraf(void* listaPrincipala) {
//	//sunt dezalocate toate masinile din graf 
//	//si toate nodurile celor doua liste
//}
//
//int main() {
//	NodPrincipal* graf = NULL;
//	graf = citireNoduriMasiniDinFisier("masini.tx");
//	citireMuchiiDinFisier(graf, "muchii.txt");
//
//	return 0;
//}