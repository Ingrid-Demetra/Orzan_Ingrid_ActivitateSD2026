//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
////creare structura pentru Heap
////un vector de elemente, lungimea vectorului si numarul de elemente din vector
//struct Heap {
//	int lungime;
//	int nrMasini;
//	Masina* masini; //vector alocat dinamic de masini
//};
//typedef struct Heap Heap;
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
//Heap initializareHeap(int lungime) {
//	//initializeaza heap-ul cu 0 elemente 
//	//dar cu o lungime primita ca parametru
//	
//	//initializez toate atributele:
//	Heap heap;
//	heap.lungime = lungime;
//	heap.masini = malloc(lungime * sizeof(Masina)); //ii aloc spatiu vectorului de masini
//	heap.masini = NULL; //adresa de inceput a vectorului de elemente
//	heap.nrMasini = 0;
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
//	if (pozitieNod >= 0 && pozitieNod < heap.nrMasini) {
//		int pozitieStanga = pozitieNod * 2 + 1;
//		int pozitieDreapta = pozitieNod * 2 + 2;
//		int pMax = pozitieNod;
//		if (pozitieStanga < heap.lungime && heap.masini[pMax].pret< heap.masini[pozitieStanga].pret) {
//			pMax = pozitieStanga;
//		}
//		if (pozitieDreapta < heap.lungime && heap.masini[pMax].pret < heap.masini[pozitieDreapta].pret) {
//			pMax = pozitieDreapta;
//		}
//
//		if (pMax != pozitieNod) { //daca nu am gasit nodul maxim inca
//			Masina aux = heap.masini[pMax];
//			heap.masini[pMax] = heap.masini[pozitieNod];
//			heap.masini[pozitieNod] = aux;
//			if (pMax < (heap.nrMasini - 2) / 2) { //daca nu e nod frunza mai apelam interschimbarea-dc avem nevoie de conditia asta?
//				filtreazaHeap(heap, pMax);
//			}
//		}
//	}
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	//citim toate masinile din fisier si le stocam intr-un heap 
//	// pe care trebuie sa il filtram astfel incat sa respecte 
//	// principiul de MAX-HEAP sau MIN-HEAP dupa un anumit criteriu
//	// sunt citite toate elementele si abia apoi este filtrat vectorul
//
//	FILE* f = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(12);
//	heap.nrMasini = 0;
//	while (!feof(f)) {
//	//	Masina m = citireMasinaDinFisier(f);
//		heap.masini[heap.nrMasini++] = citireMasinaDinFisier(f); 
//		fclose(f);
//	}
//	//filtrare:
//	for (int i = (heap.nrMasini - 2) / 2; i >= 0;i--) {
//		filtreazaHeap(heap,i);
//	}
//
//}
//
//void afisareHeap(Heap heap) {
//	//afiseaza elementele vizibile din heap
//	for (int i = 0;i, heap.nrMasini;i++) {
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	//afiseaza elementele ascunse din heap
//
//}
//
//Masina extrageMasina(void* heap) {
//	//extrage si returneaza masina de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
//}
//
//
//void dezalocareHeap(Heap* heap) {
//	//sterge toate elementele din Heap
//}
//
//int main() {
//
//
//	return 0;
//}