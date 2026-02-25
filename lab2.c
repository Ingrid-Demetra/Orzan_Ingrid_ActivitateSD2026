#include<stdio.h>
#include<malloc.h>
#include<string.h>


struct Film {
	int id;
	int durata ;
	char* denumire ;
	float buget ;
	char varstaMinima ;
};
struct Film initializare(int _id, int _durata, const char * _denumire, float _buget, char _varstaMinima) {
	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((strlen(_denumire) + 1) * sizeof(char));
	//(s.denumire, _denumire); dc nu merge?? cum fac
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	
	return s;
}
struct Film copyFilm(struct Film s) {
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}
void afisare(struct Film s) {
	//afisarea tuturor atributelor.
	printf("\nNume: %s", s.denumire);
	printf("\nDurata in minute: %d", s.durata);
	printf("\nbuget: %f", s.buget);
	printf("\nvasrta minima: %c", s.varstaMinima);

}

void afisareVector(struct Film * vector, int nrFilme) {
	for (int i = 0;i < nrFilme;i++)
	{
		afisare(vector[i]);
		printf("\n");
	}

}

struct Film* copiazaPrimeleNElemente(struct Film * vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Film* vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0;i < nrElementeCopiate;++i) {
		vectorNou[i] = copyFilm(vector[i]);
	}


	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {   //mai recapitulez acasa
	for (int i = 0;i < * nrElemente;i++) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}


//char simplu merge pana la 127 primul bit e bit de semn
void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditied
	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].buget < bugetMaxim) {
			(*dimensiune)++;
		}
	}
	*vectorNou = malloc((*dimensiune) * sizeof(struct Film));
	int k = 0;
	for (int i = 0;i <nrElemente;i++) {
		if (vector[i].buget < bugetMaxim) {
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}
}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* numeCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Film s;
	s.id = -1;
	s.denumire = NULL;
	for (int i= 0;i < nrElemente;i++) {
		if (strcmp(vector[i].denumire, numeCautat))
			return vector[i];
	}

	return s;
}
	
int main() {
	struct Film f1 = initializare(1, 60, "narnia", 130000, '8');
	int nrFilme = 3;
	int nrFilmeCopiate = 2;

	struct Film* filme = malloc(nrFilme * sizeof(struct Film));
	filme[0] = f1;
	//*(filme+1) = initializare(2, 360, "james bond", 16, '8'); //dereferentiere daca nu vrem sa folosim index
	filme[1] = initializare(2, 340, "fight club", 50.6, '9');
	filme[2] = initializare(2, 340, "fight club", 50.6, '9');


	afisareVector(filme, nrFilme);
	//dezalocare(vectorNou, &nrFilmecopiate); de ce nu merge??
	struct Film * vectorNou;
	vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	afisareVector(vectorNou, nrFilmeCopiate);
	struct Film* vectorIeftin;
	float prag = 20;
	//de completat
	afisare(getPrimulElementConditionat(filme, nrFilme, "Dune"));

	return 0;
}