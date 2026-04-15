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
//typedef struct Nod Nod;
//typedef struct ListaDubla ListaDubla;
//
//struct Nod {
//	Masina info;
//	Nod* next;
//	Nod* prev;
//};
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
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
//void afisareListaMasini(ListaDubla  lista) { //trimit prin val  ca nu modific, ar fi dif de memorie de doar un pointer
//	Nod* p = lista.prim;
//	while (p) {
//		afisareMasina(p->info);
//		p = p ->next;
//	}
//}
//void afisareInversaListaMasini(ListaDubla  lista) { 
//	Nod* p = lista.ultim;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//void adaugaMasinaInLista(ListaDubla *ld, Masina masinaNoua) {
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = ld->ultim;
//	if (ld->ultim != NULL) {
//		ld->ultim->next = nou;
//	}
//	else {
//		//cazul in care nu avem noduri la imceput in lista
//		ld->prim = nou;
//	}
//	ld->ultim = nou;
//
//}
//
//void adaugaLaInceputInLista(ListaDubla* ld, Masina masinaNoua) {
//	Nod* nou = malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = ld->prim;
//	nou->prev =NULL;
//	if (ld->ultim != NULL) {
//		ld->prim->prev = nou;
//	}
//	else {
//	
//		ld->ultim = nou;
//	}
//	ld->prim = nou;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		ListaDubla ld;
//		ld.prim = ld.ultim = NULL;
//		while (!feof(f)) {
//			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
//		}
//		fclose(f);
//		return ld; //sa nu se returneze ca adresa pt  a e in stiva functiei
//	}
//}
//
//void dezalocareLDMasini(ListaDubla * ld) {
//	
//	while (ld->prim&&ld->prim->next) {
//		free(ld->prim->info.numeSofer);
//		free(ld->prim->info.model);
//		ld ->prim = ld ->prim->next;
//		free(ld->prim);
//	}
//	//stergem ultimul nod:
//	if (ld->prim) {
//		free(ld->prim->info.numeSofer);
//		free(ld->prim->info.model);
//		free(ld->prim);
//	}
//	ld->prim = ld->ultim = NULL;
//}
//
//float calculeazaPretMediu(ListaDubla ld) {
//	//calculeaza pretul mediu al masinilor din lista.
//	float suma=0;
//	int cnt = 0;
//
//	Nod* p = ld.prim;
//	while (p) {
//		suma=p->info.pret+suma;
//		cnt++;
//		p = p->next;
//	}
//	return suma/cnt;
//}
////observatie:
//// daca nu modificam primul sau ultimul nod nu trb sa trimitem prin adresa!
//
//void stergeMasinaDupaID(ListaDubla * ld, int id) {
//
//	//daca e pe primul nod:
//	if (ld->prim && ld->prim->info.id == id) {
//		free(ld->prim->info.model);
//		free(ld->prim->info.numeSofer);
//		ld->prim = ld->prim->next;
//		if (ld->prim) {//verific iar daca exista pt ca m am deplasat
//			free(ld->prim->prev);
//		}
//		else {
//			free(ld->ultim);
//			ld->ultim = NULL;
//			//pe ld de prim l am fct null prin deplasare
//		}
//		return;
//	}
//	//altfel:
//	Nod* p = ld->prim;
//	while (p && p->info.id != id) {
//		p = p->next;
//	}
//	if (p) {
//		if (p->prev) {
//			p->prev->next = p->next;
//		}
//		if (p->next) {
//			p->next->prev = p->prev;
//		}
//		else {
//			p->prev->next = NULL;
//			ld->ultim = p->prev;
//		}
//		free(p->info.model);
//		free(p->info.numeSofer);
//		free(p);
//	}
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla ld) {
//	//cauta masina cea mai scumpa si 
//	//returneaza numele soferului acestei maasini.
//}
//
//int main() {
//
//	/*ListaDubla lista;
//	lista.prim = NULL;
//	lista.ultim = NULL;*/
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	stergeMasinaDupaID(&lista, 6);
//	printf("\npret masini: %f", calculeazaPretMediu(lista));
//	afisareListaMasini(lista);
//	return 0;
//}