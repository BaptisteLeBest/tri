#include <stdio.h>

#define MAX_STR_SIZE 20

#define INPUT_FILE "evacuation_plan0.txt"
#define OUTPUT_FILE "better_evacuation_plan0.txt"

enum zipcode {
	GUADELOUPE = 971,
	STBARTH = 977,
	STMARTIN
};

struct inhabitant {
	int distance;
	char prenom[MAX_STR_SIZE];
	char nom[MAX_STR_SIZE];
	enum zipcode zip;
};

int nb_h;

// Retourner un message d'erreur et faire pause
void report_error(char *msg)
{
	fprintf(stderr, msg);
	system("pause");
	exit(-1);
}

// Lire un fichier et stocker ses valeurs dans un tableau de structures
void read(struct inhabitant **h, int *nb_habs) {
	int i, first_line, line;
	struct inhabitant *tmph;

	// On ouvre le fichier d'entree
	FILE *data_file;
	data_file = fopen(INPUT_FILE, "r");

	if (data_file == NULL) {
		report_error("Impossible d'ouvrir le fichier.\n");
	}

	/*
	Premiere ligne du fichier = nombre d'habitants
	first_line = 1 si il y a du contenu dans le fichier
	first_line = -1 si il n'y a pas de contenu
	*/
	first_line = fscanf(data_file, "%d", nb_habs);

	if (first_line != 1 || *nb_habs < 0) {
		report_error("Impossible de lire le fichier.\n");
	}

	if (*nb_habs < 0) {
		report_error("Le nombre d'habitants est incorrect.\n");
	}

	if ((*h = (struct inhabitant *)malloc(sizeof(struct inhabitant) * (*nb_habs))) == NULL) {
		report_error("Impossible d'allouer assez de place pour les habitants.\n");
	}

	tmph = *h;
	for (i = 0; i < (*nb_habs); ++i) {
		line = fscanf(data_file, "%d %s %s %d", &(tmph[i].distance), (char *)&(tmph[i].prenom), (char *)&(tmph[i].nom), (int *)&(tmph[i].zip));
		if (line != 4) {
			report_error("Le fichier n'est pas bien formatte.\n");
		}
	}

	fclose(data_file);
}

// Ecrire dans un fichier
void printout(int n, struct inhabitant *h) {
	// On ouvre le fichier de sortie
	FILE *sorted_file;
	sorted_file = fopen(OUTPUT_FILE, "w+");

	if (sorted_file == NULL) {
		report_error("Impossible d'ouvrir le fichier.\n");
	}

	for (int i = 0; i < n; i++) {
		fprintf(sorted_file, "%d %s %s %d\n", h[i].distance, h[i].prenom, h[i].nom, h[i].zip);
	}

	fclose(sorted_file);
}

void swap(struct inhabitant **A, struct inhabitant **B) {
	struct inhabitant *temp = *A;
	*A = *B;
	*B = temp;
}

void tri_bulles(struct inhabitant *h, int n) {
	int tab_en_ordre = 0;
	int taille = n;
	while (tab_en_ordre == 0)
	{
		tab_en_ordre = 1;
		for (int i = 0; i < taille - 1; i++)
		{
			if (h[i].distance > h[i + 1].distance)
			{
				swap(&h[i], &h[i + 1]);
				tab_en_ordre = 0;
			}
		}
		if (taille % 1000 == 0) {
			printf("%d sur %d (%f%%)\n", n - taille, n, (((float)n - (float)taille) / (float)taille) * 100);
		}
		taille--;
	}
}

int partition(struct inhabitant *h, int start, int end)
{
	int state = start;
	// On definit le pivot
	int pivot = h[start].distance;

	for (int i = start + 1; i <= end; i++)
	{
		// Si l'element est plus petit que le pivot, on place le place dans la premiere partie du tableau
		if (h[i].distance < pivot)
		{
			state++;
			swap(&h[state], &h[i]);
		}
	}
	swap(&h[state], &h[start]);

	if (state % 1000 == 0) {
		printf("%d sur %d (%f%%)\n", state, nb_h, ((float)state / (float)nb_h) * 100);
	}

	return(state);
}

void tri_rapide(struct inhabitant *h, int start, int end)
{
	if (start < end - 1)
	{
		int pivot = partition(h, start, end);
		tri_rapide(h, start, pivot);
		tri_rapide(h, pivot + 1, end);
	}
}

int main()
{
	printf("Licorne");
	
	return 0;
}