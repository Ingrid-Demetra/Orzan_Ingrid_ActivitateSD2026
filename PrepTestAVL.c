//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct FootballPlayer {
//	unsigned int PlayerID;
//	char* Name;
//	char* Position;
//	float marketValue;
//};
//typedef struct FootballPlayer FootballPlayer;
//typedef struct Nod Nod;
//
//struct Nod {
//	FootballPlayer info;
//	Nod* stanga;
//	Nod* dreapta;
//};
//
//FootballPlayer citirePlayerDinFisier(FILE * f) {
//	FootballPlayer  fb;
//	char  buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, f);
//
//	char* aux;
//	fb.PlayerID = atoi(strtok(buffer, sep));
//	aux = (strtok(NULL, sep));
//	fb.Name = malloc(strlen(aux) + 1);
//	strcpy_s(fb.Name, strlen(aux) + 1, aux);
//
//	aux = (strtok(NULL, sep));
//	fb.Position = malloc(strlen(aux) + 1);
//	strcpy_s(fb.Position, strlen(aux) + 1, aux);
//
//	fb.marketValue = atof(strtok(NULL, sep));
//
//	return fb;
//}
//void afisareFootballPlayer(FootballPlayer fb) {
//	printf("\nid: %d", fb.PlayerID);
//	printf("\nname: %s", fb.Name);
//	printf("\nposition: %s", fb.Position);
//	printf("\nmarket value: %f", fb.marketValue);
//
//}
//int calculeazaInaltimeArbore(Nod * radacina) {
//	if (radacina) { //max intre functia recursiva de staga, functia rec d e dreapta +1
//		return max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta)) + 1;
//	}
//	return 0;
//}
//char calculGE(Nod* radacina) {
//	if (radacina) {
//		return(calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta));
//	}
//	return 0;
//}
//void rotireStanga(Nod**radacina) { //daca rotesc la stanga urca nodul din dreapta
//	Nod* aux = (*radacina)->dreapta; 
//	(*radacina)->dreapta = aux->stanga; //de fosta radacina la dreapta se agata ce era in stanga lui aux(noii rsdacini)
//	aux->stanga = *radacina;
//	*radacina = aux;
//
//}
//void rotireDreapta(Nod** radacina) {
//	Nod* aux = (*radacina)->stanga;
//	(*radacina)->stanga = aux->dreapta;
//	aux->dreapta = *radacina;
//	*radacina = aux;
//}
//void inserarePlayerInAVL(Nod** radacina, FootballPlayer PlayerNou) {
//	//1)inserare ca la bst
//	//2)functie de calculInaltine
//	//3)functie de calculGradDeEchilobru
//	//4)functie de rotireStanga
//	//5)functie de rotireDreapta
//
//	if (*radacina == NULL) {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->dreapta = NULL;
//		nou->stanga = NULL;
//		nou->info = PlayerNou;
//
//		*radacina = nou;
//	}
//	else {
//		if (PlayerNou.PlayerID < (*radacina)->info.PlayerID) {
//			inserarePlayerInAVL(&(*radacina)->stanga, PlayerNou);
//		}
//		else {
//			inserarePlayerInAVL(&(*radacina)->dreapta, PlayerNou);
//		}
//	}
//	//verificare grad de echilibru:
//
//	int grad = calculGE(*radacina);
//		if (grad == 2) { //dezechilobru stanga
//			if (calculGE((*radacina)->stanga)==-1) {
//				//rotire dubla:
//				rotireStanga(&(*radacina)->stanga);
//			}
//			rotireDreapta(&(*radacina)); //daca am dez normal in partea stanga rotesc la dreapta o data
//			
//		}
//		else if (grad == -2) { //dezechilobru in dreapta
//			if (calculGE((*radacina)->dreapta)==1) { //dez dublu
//				rotireDreapta((*radacina)->dreapta);
//			}
//			rotireStanga(&(*radacina)); //daca am dez in partea dreapta rotesc la stanga o data
//		}
//}
//void afisarePlayeriDinArbore(Nod* radacina) {
//	if (radacina) {
//	
//	afisarePlayeriDinArbore(radacina->stanga);
//	afisareFootballPlayer(radacina->info);
//	afisarePlayeriDinArbore(radacina->dreapta);
//	}
//}
//void dezalocareArbore(Nod** radacina) {
//	if (radacina) {
//		dezalocareArbore(&(*radacina)->stanga);
//		dezalocareArbore(&(*radacina)->dreapta);
//
//		free((*radacina)->info.Name);
//		free((*radacina)->info.Position);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Nod * citirePlayeriDinFisier(char * numeFisier) {
//	Nod* radacina=NULL;
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		while (!feof(f)) {
//			inserarePlayerInAVL(&radacina, citirePlayerDinFisier(f));
//		}
//		fclose(f);
//	}
//	return radacina;
//}
//int numarareJucatoriPozitie(Nod * arbore, char * poz) {
//	int nr = 0;
//	if (arbore == NULL) {
//		return 0;
//	}
//	if (strcmp(arbore->info.Position, poz) == 0) {
//		nr = 1;
//	}
//	return nr+numarareJucatoriPozitie(arbore->stanga,poz)+numarareJucatoriPozitie(arbore->dreapta,poz);
//}
//Nod* gasireMinim(Nod * radacina) {
//	while (radacina->stanga != NULL) 
//		radacina = radacina->stanga;
//	return radacina;
//}
//void stergereDupaMarketValue(Nod** radacina, int prag) {
//	if (radacina) {
//		if ((*radacina)->info.marketValue < prag) {
//			if ((*radacina)->dreapta == NULL && (*radacina)->stanga == NULL) { //nod frunza
//				free((*radacina)->info.Name);
//				free((*radacina)->info.Position);
//				free(*radacina);
//				*radacina = NULL;
//			}
//			else if ((*radacina)->stanga == NULL) { //doar copil la dreapta
//				Nod* aux = (*radacina)->dreapta;
//				free((*radacina)->info.Name);
//				free((*radacina)->info.Position);
//				free(*radacina);
//				*radacina = aux;
//			}
//			else if ((*radacina)->dreapta == NULL) { //doar copil la stanga
//				Nod* aux = (*radacina)->stanga;
//				free((*radacina)->info.Name);
//				free((*radacina)->info.Position);
//				free(*radacina);
//				*radacina = aux;
//			}
//			else { //daca are 2 copii
//				Nod* succesor = gasireMinim((*radacina)->dreapta);
//				free((*radacina)->info.Name); //free doar pe astea dinamica ca nodul ramane doar is scimba datele!!!!
//				free((*radacina)->info.Position);
//				//realoc radacina cu datele succesorului:
//				(*radacina)->info.marketValue = succesor->info.marketValue;
//				(*radacina)->info.PlayerID = succesor->info.PlayerID;
//				(*radacina)->info.Name = malloc(strlen(succesor->info.Name) + 1);
//				strcpy_s((*radacina)->info.Name, strlen(succesor->info.Name) + 1, succesor->info.Name);
//				(*radacina)->info.Position = malloc(strlen(succesor->info.Position) + 1);
//				strcpy_s((*radacina)->info.Position, strlen(succesor->info.Position) + 1, succesor->info.Position);
//
//				// sterge succesorul din subarborele drept
//				stergereDupaMarketValue(&(*radacina)->dreapta, succesor->info.marketValue + 1);
//
//			}
//		}
//	}
//}
//typedef struct NodLS NodLS ;
//
//struct NodLS {
//	FootballPlayer info;
//	Nod* next;
//};
//
//void inserareLS( NodLS ** ls,FootballPlayer f) {
//	NodLS* nou = malloc(sizeof(NodLS));
//	nou->info = f;
//	nou->next = NULL;
//	if (*ls == NULL) {
//		*ls = nou;
//	}
//	else {
//		NodLS* aux = (*ls);
//		while (aux->next) {
//			aux = aux->next;
//		}
//		aux = nou;
//	}
//}
//void LSPlayeri(Nod* arbore, char* poz, NodLS** lista) {
//	if (arbore) {
//		LSPlayeri(arbore->stanga, poz, lista);
//		
//		if (strcmp(arbore->info.Position, poz) == 0) {
//			inserareLS(&lista, arbore->info);
//		}
//		LSPlayeri(arbore->dreapta, poz, lista);
//	}
//}
////Nod* LSPlayeri(Nod* arbore, char * poz) { gresit
////	Nod* ls = malloc(sizeof(Nod));
////	ls->dreapta = NULL;
////
////	if (arbore) {
////		
////		if (strcmp(arbore->info.Position, poz) == 0) {
////			if (ls == NULL) {
////				ls = arbore;
////			}
////			else {
////				Nod* aux = ls;
////				while (aux->dreapta != NULL) {
////					aux = arbore;
////				}
////			}
////		}
////		LSPlayeri(arbore, poz);
////	}
////	return ls;
////
////}
//int main() {
//	printf("test");
//	Nod* arbore = citirePlayeriDinFisier("Playeri.txt");
//	afisarePlayeriDinArbore(arbore);
//
//	
//	return 0;
//}