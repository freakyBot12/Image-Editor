//312CA_Selea_Tudor_Octavian_Tema3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char rotunjire(double nr_virgula);

void LOAD(char fisier[], char format[], int *load, unsigned char ***img,
		  int *nc, int *nl, int *vmax, int *x1, int *y1, int *x2, int *y2);

void SELECT(int *load, int *x1, int *y1, int *x2, int *y2, int *nc, int *nl);

void GRAYSCALE(char format[], int *load, int *x1, int *y1,
			   unsigned char ***img, int *x2, int *y2);

void SEPIA(char format[], int *load, int *x1, int *y1,
		   unsigned char ***img, int *x2, int *y2, int *vmax);

void SAVE(char format[], int *load, int *vmax,
		  unsigned char ***img, int *nc, int *nl);

void EXIT(int *load, unsigned char ***img, int *nl, int *exit);

void CROP(char format[], int *load, unsigned char ***img, int *nc, int *nl,
		  unsigned char ***imgaux, int *x1, int *y1, int *x2, int *y2);

void UNGHI_LOAD_ROTATE(int *unghi, int *load, int *mv);

void ROTATE_90_FULL(unsigned char ***img, unsigned char ***imgaux,
					int *unghi, int *nc, int *nl, int *x2, int *y2);

void ROTATE_180_FULL(unsigned char ***img, unsigned char ***imgaux,
					 int *unghi, int *nc, int *nl);

void ROTATE_270_FULL(unsigned char ***img, unsigned char ***imgaux,
					 int *unghi, int *nc, int *nl, int *x2, int *y2);

void ROTATE_360(int *unghi);

void ROTATE_90_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						int *unghi, int *nc, int *nl, int *x2, int *y2);

void ROTATE_180_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						 int *unghi, int *nc, int *nl);

void ROTATE_270_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						 int *unghi, int *nc, int *nl, int *x2, int *y2);

void ROTATE_SQUARE(unsigned char ***img, unsigned char ***imgaux,
				   int *unghi, int *x1, int *y1, int *x2, int *y2);

void ROTATE_SQUARE_COL(unsigned char ***img, unsigned char ***imgaux,
					   int *unghi, int *x1, int *y1, int *x2, int *y2);

int main(void)
{
	int x1, x2, y1, y2, load = 0, nl = 0, nc = 0;
	int unghi, exit = 0, vmax, mv = 0;
	char format[5], comanda[100], fisier[100];
	unsigned char **img = NULL;
	unsigned char **imgaux = NULL;
	while (exit == 0) {
		mv = 0;
		scanf("%s", comanda);
		if (strcmp(comanda, "LOAD") == 0) {
			LOAD(fisier, format, &load, &img, &nc, &nl,
				 &vmax, &x1, &y1, &x2, &y2);
			continue;
		}
		if (strcmp(comanda, "SELECT") == 0) {
			SELECT(&load, &x1, &y1, &x2, &y2, &nc, &nl);
			continue;
		}
		if (strcmp(comanda, "GRAYSCALE") == 0) {
			GRAYSCALE(format, &load, &x1, &y1, &img, &x2, &y2);
			continue;
		}
		if (strcmp(comanda, "SEPIA") == 0) {
			SEPIA(format, &load, &x1, &y1, &img, &x2, &y2, &vmax);
			continue;
		}
		if (strcmp(comanda, "SAVE") == 0) {
			SAVE(format, &load, &vmax, &img, &nc, &nl);
			continue;
		}
		if (strcmp(comanda, "EXIT") == 0) {
			EXIT(&load, &img, &nl, &exit);
			continue;
		}
		if (strcmp(comanda, "CROP") == 0) {
			CROP(format, &load, &img, &nc, &nl, &imgaux, &x1, &y1, &x2, &y2);
			continue;
		}
		if (strcmp(comanda, "ROTATE") == 0) {
			UNGHI_LOAD_ROTATE(&unghi, &load, &mv);
			if (mv == 1)
				continue;
			if (x1 == 0 && x2 == nc && y1 == 0 && y2 == nl) {
				if (strcmp(format, "P2") == 0 || strcmp(format, "P5") == 0) {
					ROTATE_90_FULL(&img, &imgaux, &unghi, &nc, &nl, &x2, &y2);
					ROTATE_180_FULL(&img, &imgaux, &unghi, &nc, &nl);
					ROTATE_270_FULL(&img, &imgaux, &unghi, &nc, &nl, &x2, &y2);
					ROTATE_360(&unghi);
				}
				if (strcmp(format, "P3") == 0 || strcmp(format, "P6") == 0) {
					ROTATE_90_COL_FULL(&img, &imgaux, &unghi, &nc,
									   &nl, &x2, &y2);
					ROTATE_180_COL_FULL(&img, &imgaux, &unghi, &nc, &nl);
					ROTATE_270_COL_FULL(&img, &imgaux, &unghi, &nc,
										&nl, &x2, &y2);
					ROTATE_360(&unghi);
				}
				continue;
			}
			if ((x2 - x1) == (y2 - y1)) {
				if (strcmp(format, "P2") == 0 || strcmp(format, "P5") == 0)
					ROTATE_SQUARE(&img, &imgaux, &unghi, &x1, &y1, &x2, &y2);
				if (strcmp(format, "P3") == 0 || strcmp(format, "P6") == 0)
					ROTATE_SQUARE_COL(&img, &imgaux, &unghi, &x1, &y1,
									  &x2, &y2);
				continue;
			}
			printf("The selection must be square\n");
			continue;
		}
		printf("Invalid command\n");
		char caracter;
		scanf("%c", &caracter);
		while (caracter != '\n')
			scanf("%c", &caracter);
	}
}

//Functia de rotunjire a unui numar cu virgula la intregul cel mai apropiat
unsigned char rotunjire(double nr_virgula)
{
	if ((int)nr_virgula + 1 - nr_virgula < nr_virgula - (int)nr_virgula)
		return (int)nr_virgula + 1;
	else
		return (int)nr_virgula;
}

//Functia de incarcare a pozei in memoria programului
void LOAD(char fisier[], char format[], int *load, unsigned char ***img,
		  int *nc, int *nl, int *vmax, int *x1, int *y1, int *x2, int *y2)
{
	scanf("%s", fisier);
	if (*load == 1) {
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*load = 0;
	}
	FILE * f = fopen(fisier, "r");
	if (!f) {
		printf("Failed to load %s\n", fisier);
		return;
	}
	fscanf(f, "%s", format);

	//In functie de format, incarc imaginea in matricea img
	if (strcmp(format, "P2") == 0) {
		fscanf(f, "%d %d %d", nc, nl, vmax);
		*img = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*img + i) = calloc(*nc, sizeof(unsigned char));
		for (int i = 0; i < *nl; i++)
			for (int j = 0; j < *nc; j++)
				fscanf(f, "%hhu", &(*img)[i][j]);
		printf("Loaded %s\n", fisier);
		*load = 1;
		fclose(f);
	}
	if (strcmp(format, "P5") == 0) {
		char tmp;
		fscanf(f, "%d %d %d%c", nc, nl, vmax, &tmp);
		*img = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*img + i) = calloc(*nc, sizeof(unsigned char));
		for (int i = 0; i < *nl; i++)
			fread(*(*img + i), *nc, sizeof(unsigned char), f);
		printf("Loaded %s\n", fisier);
		*load = 1;
		fclose(f);
	}
	if (strcmp(format, "P3") == 0) {
		fscanf(f, "%d %d %d", nc, nl, vmax);
		*img = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*img + i) = calloc(*nc * 3, sizeof(unsigned char));
		for (int i = 0; i < *nl; i++)
			for (int j = 0; j < *nc * 3; j++)
				fscanf(f, "%hhu", &(*img)[i][j]);
		printf("Loaded %s\n", fisier);
		*load = 1;
		fclose(f);
	}
	if (strcmp(format, "P6") == 0) {
		char tmp;
		fscanf(f, "%d %d %d%c", nc, nl, vmax, &tmp);
		*img = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*img + i) = calloc(*nc * 3, sizeof(unsigned char));
		for (int i = 0; i < *nl; i++)
			fread(*(*img + i), *nc * 3, sizeof(unsigned char), f);
		printf("Loaded %s\n", fisier);
		*load = 1;
		fclose(f);
	}
	//Dupa incarcarea imaginii, selectez intreaga imagine pentru a o prelucra
	*x1 = 0;
	*x2 = *nc;
	*y1 = 0;
	*y2 = *nl;
}

//Functia de selectie a suprafetei pe care doresc sa lucrez
void SELECT(int *load, int *x1, int *y1, int *x2, int *y2, int *nc, int *nl)
{
	int varx1, varx2, vary1, vary2;
	char all[10];
	scanf("%s", all);
	char restall[40];
	fgets(restall, 40, stdin);
	if (*load == 0) {
		printf("No image loaded\n");
		return;
	}

	//Selectez toata imaginea
	if (strcmp(all, "ALL") == 0) {
		*x1 = 0;
		*x2 = *nc;
		*y1 = 0;
		*y2 = *nl;
		printf("Selected ALL\n");
		return;
	}
	int ctrl1, ctrl234;
	ctrl1 = sscanf(all, "%d", &varx1);
	if (ctrl1 != 1) {
		printf("Invalid command\n");
		return;
	}
	ctrl234 = sscanf(restall, "%d %d %d", &vary1, &varx2, &vary2);
	if (ctrl234 != 3) {
		printf("Invalid command\n");
		return;
	}

	//Verific daca coordonatele noi sunt date in ordine(x1 < x2 si y1 < y2)
	if (varx2 < varx1) {
		int tempx;
		tempx = varx1;
		varx1 = varx2;
		varx2 = tempx;
	}
	if (vary2 < vary1) {
		int tempy;
		tempy = vary1;
		vary1 = vary2;
		vary2 = tempy;
	}

	//Verific daca noua selectie nu depaseste dimensiunile imaginii
	if (varx1 < 0 || varx2 > *nc || vary1 < 0 || vary2 > *nl) {
		printf("Invalid set of coordinates\n");
		return;
	}

	//Verific daca noua selectie nu este unidimensionala (o linie sau
	//un punct)
	if (varx1 == varx2 || vary1 == vary2) {
		printf("Invalid set of coordinates\n");
		return;
	}
	*x1 = varx1;
	*x2 = varx2;
	*y1 = vary1;
	*y2 = vary2;
	printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
}

//Functia de aplicare a filtrului GRAYSCALE pe imaginea curenta
void GRAYSCALE(char format[], int *load, int *x1, int *y1,
			   unsigned char ***img, int *x2, int *y2)
{
	//Verific daca exista o imagine incarcata in memoria programului
	if (*load == 0) {
		printf("No image loaded\n");
		return;
	}

	//Verific daca imaginea incarcata nu este color
	if (strcmp(format, "P2") == 0 || strcmp(format, "P5") == 0) {
		printf("Grayscale filter not available\n");
		return;
	}
	double medie;
	int suma = 0;
	for (int i = *y1; i < *y2; i++)
		for (int j = 3 * (*x1); j < 3 * (*x2); j = j + 3) {
			suma = (*img)[i][j] + (*img)[i][j + 1] + (*img)[i][j + 2];
			medie = (double)suma / 3;
			(*img)[i][j] = rotunjire(medie);
			(*img)[i][j + 1] = rotunjire(medie);
			(*img)[i][j + 2] = rotunjire(medie);
			suma = 0;
		}
	printf("Grayscale filter applied\n");
}

//Functia de aplicare a filtrului SEPIA
void SEPIA(char format[], int *load, int *x1, int *y1,
		   unsigned char ***img, int *x2, int *y2, int *vmax)
{
	//Verific daca exista o imagine incarcata in memoria programului
	if (*load == 0) {
		printf("No image loaded\n");
		return;
	}

	//Verific daca imaginea nu este color
	if (strcmp(format, "P2") == 0 || strcmp(format, "P5") == 0) {
		printf("Sepia filter not available\n");
		return;
	}
	double sum1, sum2, sum3, R, G, B;
	for (int i = *y1; i < *y2; i++)
		for (int j = 3 * (*x1); j < 3 * (*x2); j = j + 3) {
			R = 0.393 * (*img)[i][j];
			G = 0.769 * (*img)[i][j + 1];
			B = 0.189 * (*img)[i][j + 2];
			sum1 = R + G + B;
			if (sum1 > *vmax)
				sum1 = *vmax;
			R = 0.349 * (*img)[i][j];
			G = 0.686 * (*img)[i][j + 1];
			B = 0.168 * (*img)[i][j + 2];
			sum2 = R + G + B;
			if (sum2 > *vmax)
				sum2 = *vmax;
			R = 0.272 * (*img)[i][j];
			G = 0.534 * (*img)[i][j + 1];
			B = 0.131 * (*img)[i][j + 2];
			sum3 = R + G + B;
			if (sum3 > *vmax)
				sum3 = *vmax;
			(*img)[i][j] = rotunjire(sum1);
			(*img)[i][j + 1] = rotunjire(sum2);
			(*img)[i][j + 2] = rotunjire(sum3);
			sum1 = 0;
			sum2 = 0;
			sum3 = 0;
		}
	printf("Sepia filter applied\n");
}

//Functia de salvare a pozei
void SAVE(char format[], int *load, int *vmax,
		  unsigned char ***img, int *nc, int *nl)
{
	char saved_file[100], nume_output[40], ascii[7];
	fgets(saved_file, 100, stdin);
	if (*load == 0) {
		printf("No image loaded\n");		//Verific daca exista o imagine
		return;								//incarcata in program
	}
	saved_file[strlen(saved_file) - 1] = 0;
	int verif = sscanf(saved_file, "%s %s", nume_output, ascii);
	if (verif == 2 && strcmp(ascii, "ascii") == 0) {
		FILE *g = fopen(nume_output, "wt");
		if (strcmp(format, "P2") == 0) {
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++) {
				for (int j = 0; j < *nc; j++)
					fprintf(g, "%d ", (*img)[i][j]);
				fprintf(g, "\n");
			}
		}
		if (strcmp(format, "P5") == 0) {
			strcpy(format, "P2");
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++) {
				for (int j = 0; j < *nc; j++)
					fprintf(g, "%d ", (*img)[i][j]);
				fprintf(g, "\n");
			}
		}
		if (strcmp(format, "P3") == 0) {
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++) {
				for (int j = 0; j < 3 * (*nc); j++)
					fprintf(g, "%d ", (*img)[i][j]);
				fprintf(g, "\n");
			}
		}
		if (strcmp(format, "P6") == 0) {
			strcpy(format, "P3");
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++) {
				for (int j = 0; j < 3 * (*nc); j++)
					fprintf(g, "%d ", (*img)[i][j]);
				fprintf(g, "\n");
			}
		}
		fclose(g);
		printf("Saved %s\n", nume_output);
	}
	if (verif == 2 && strcmp(ascii, "ascii") != 0)
		printf("Invalid command\n");
	if (verif == 1) {
		FILE *g = fopen(nume_output, "wb");
		if (strcmp(format, "P2") == 0) {
			strcpy(format, "P5");
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++)
				fwrite(*(*img + i), *nc, sizeof(unsigned char), g);
		}
		if (strcmp(format, "P5") == 0) {
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++)
				fwrite(*(*img + i), *nc, sizeof(unsigned char), g);
		}
		if (strcmp(format, "P3") == 0) {
			strcpy(format, "P6");
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++)
				fwrite(*(*img + i), 3 * (*nc), sizeof(unsigned char), g);
		}
		if (strcmp(format, "P6") == 0) {
			fprintf(g, "%s\n%d %d\n%d\n", format, *nc, *nl, *vmax);
			for (int i = 0; i < *nl; i++)
				fwrite(*(*img + i), 3 * (*nc), sizeof(unsigned char), g);
		}
		fclose(g);
		printf("Saved %s\n", nume_output);
	}
}

//Functia de inchidere a programului
void EXIT(int *load, unsigned char ***img, int *nl, int *exit)
{
	//Daca exista o imagine incarcata in memoria programului, eliberez memoria
	if (*load == 1) {
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*exit = 1;
	} else {
		printf("No image loaded\n");
		*exit = 1;
	}
}

//Functia de decupare a imaginii
void CROP(char format[], int *load, unsigned char ***img, int *nc, int *nl,
		  unsigned char ***imgaux, int *x1, int *y1, int *x2, int *y2)
{
	//Verific daca exista o imagine incarcata in memoria programului
	if (*load == 0) {
		printf("No image loaded\n");
		return;
	}
	if (strcmp(format, "P2") == 0 || strcmp(format, "P5") == 0) {
		int col = *x2 - *x1;
		int lin = *y2 - *y1;

		//Creez o copie a imaginii
		*imgaux = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*imgaux + i) = calloc(*nc, sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			for (int j = 0; j < *nc; j++)
				(*imgaux)[i][j] = (*img)[i][j];

		//Redimensionez imaginea initiala astfel incat sa aiba dimensiunile
		//suprafetei selectate
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*img = malloc(lin * sizeof(unsigned char *));
		for (int i = 0; i < lin; i++)
			*(*img + i) = calloc(col, sizeof(unsigned char));

		//Copiez subimaginea selectata (din copie) in imaginea redimensionata
		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				(*img)[i][j] = (*imgaux)[i + (*y1)][j + (*x1)];
		for (int i = 0; i < *nl; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Image cropped\n");

		//Selectez noua imagine
		*x1 = 0;
		*y1 = 0;
		*x2 = col;
		*y2 = lin;
		*nl = lin;
		*nc = col;
		return;
	}
	//Aplic acelasi procedeu si pentru imaginea color
	if (strcmp(format, "P3") == 0 || strcmp(format, "P6") == 0) {
		int col = 3 * ((*x2) - (*x1));
		int lin = *y2 - *y1;
		*imgaux = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*imgaux + i) = calloc(3 * (*nc), sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			for (int j = 0; j < 3 * (*nc); j++)
				(*imgaux)[i][j] = (*img)[i][j];
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*img = malloc(lin * sizeof(unsigned char *));
		for (int i = 0; i < lin; i++)
			*(*img + i) = calloc(col, sizeof(unsigned char));
		for (int i = 0; i < lin; i++)
			for (int j = 0; j < col; j++)
				(*img)[i][j] = (*imgaux)[i + (*y1)][j + 3 * (*x1)];
		for (int i = 0; i < *nl; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Image cropped\n");
		*x1 = 0;
		*y1 = 0;
		*x2 = col / 3;
		*y2 = lin;
		*nl = lin;
		*nc = col / 3;
		return;
	}
}

//Functia de rotire a intregii imagini (gri) cu 90 sau -270 de grade
void ROTATE_90_FULL(unsigned char ***img, unsigned char ***imgaux,
					int *unghi, int *nc, int *nl, int *x2, int *y2)
{
	if (*unghi == 90 || *unghi == -270) {
		//Stochez imaginea rotita intr-o copie
		*imgaux = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < (*nc); i++)
			*(*imgaux + i) = calloc((*nl), sizeof(unsigned char));
		for (int i = 0; i < (*nc); i++)
			for (int j = 0; j < (*nl); j++)
				(*imgaux)[i][j] = (*img)[(*nl) - 1 - j][i];

		//Redimensionez imaginea initiala
		for (int i = 0; i < (*nl); i++)
			free(*(*img + i));
		free(*img);
		*img = malloc((*nc) * sizeof(unsigned char *));
		for (int i = 0; i < (*nc); i++)
			*(*img + i) = calloc((*nl), sizeof(unsigned char *));

		//Transpun copia in imaginea redimensionata si eliberez memoria
		//alocata pentru copia imaginii
		for (int i = 0; i < (*nc); i++)
			for (int j = 0; j < (*nl); j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < (*nc); i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);

		//Selectez noua imagine
		int auxil;
		auxil = *nc;
		*nc = *nl;
		*nl = auxil;
		*x2 = *nc;
		*y2 = *nl;
	}
}

//Functia de rotire a intregii imagini (gri) cu 180 sau -180 de grade
void ROTATE_180_FULL(unsigned char ***img, unsigned char ***imgaux,
					 int *unghi, int *nc, int *nl)
{
	//Aplic procedeul de mai sus (cu exceptia redimensionarii, care nu este
	//necesara)
	if (*unghi == 180 || *unghi == -180) {
		*imgaux = malloc((*nl) * sizeof(unsigned char *));
		for (int i = 0; i < (*nl); i++)
			*(*imgaux + i) = calloc((*nc), sizeof(unsigned char));
		for (int i = 0; i < (*nl); i++)
			for (int j = 0; j < (*nc); j++)
				(*imgaux)[i][j] = (*img)[(*nl) - 1 - i][(*nc) - 1 - j];
		for (int i = 0; i < (*nl); i++)
			for (int j = 0; j < (*nc); j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < (*nl); i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
	}
}

//Functia de rotire a intregii imagini (gri) cu -90 sau 270 de grade
void ROTATE_270_FULL(unsigned char ***img, unsigned char ***imgaux,
					 int *unghi, int *nc, int *nl, int *x2, int *y2)
{
	//Aplic procedeul descris la ROTATE_90_FULL
	if (*unghi == -90 || *unghi == 270) {
		*imgaux = malloc((*nc) * sizeof(unsigned char *));
		for (int i = 0; i < (*nc); i++)
			*(*imgaux + i) = calloc((*nl), sizeof(unsigned char));
		for (int i = 0; i < (*nc); i++)
			for (int j = 0; j < (*nl); j++)
				(*imgaux)[i][j] = (*img)[j][(*nc) - 1 - i];
		for (int i = 0; i < (*nl); i++)
			free(*(*img + i));
		free(*img);
		*img = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			*(*img + i) = calloc(*nl, sizeof(unsigned char));
		for (int i = 0; i < *nc; i++)
			for (int j = 0; j < *nl; j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < *nc; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		int auxil;
		auxil = *nc;
		*nc = *nl;
		*nl = auxil;
		*x2 = *nc;
		*y2 = *nl;
	}
}

//Functia de rotire a intregii imagini cu 0, 360 sau -360 de grade
void ROTATE_360(int *unghi)
{
	if (*unghi == 0 || *unghi == 360 || *unghi == -360)
		printf("Rotated %d\n", *unghi);
}

//Functia de rotire a intregii imagini (color) cu 90 sau -270 de grade
void ROTATE_90_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						int *unghi, int *nc, int *nl, int *x2, int *y2)
{
	//Aplic procedeul descris la ROTATE_90_FULL
	if (*unghi == 90 || *unghi == -270) {
		int k = 0;
		*imgaux = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			*(*imgaux + i) = calloc(3 * (*nl), sizeof(unsigned char));
		for (int i = 0; i < *nc; i++) {
			for (int j = 0; j < 3 * (*nl); j++)
				(*imgaux)[i][j] = (*img)[*nl - 1 - j / 3][j % 3 + k];
			k = k + 3;
		}
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*img = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			*(*img + i) = calloc(3 * (*nl), sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			for (int j = 0; j < 3 * (*nl); j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < *nc; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		int auxil;
		auxil = *nc;
		*nc = *nl;
		*nl = auxil;
		*x2 = *nc;
		*y2 = *nl;
	}
}

//Functia de rotire a intregii imagini (color) cu 180 sau -180 de grade
void ROTATE_180_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						 int *unghi, int *nc, int *nl)
{
	//Aplic procedeul descris la ROTATE_90_FULL (cu exceptia redimensionarii,
	//care nu este necesara)
	if (*unghi == 180 || *unghi == -180) {
		int k = 0;
		int k_prim;
		*imgaux = malloc(*nl * sizeof(unsigned char *));
		for (int i = 0; i < *nl; i++)
			*(*imgaux + i) = calloc(3 * (*nc), sizeof(unsigned char));
		for (int i = 0; i < *nl; i++) {
			for (int j = 0; j < 3 * (*nc); j++) {
				k_prim = j % 3 + 3 * ((*nc) - j / 3 - 1);
				(*imgaux)[i][j] = (*img)[*nl - k - 1][k_prim];
			}
			k++;
		}
		for (int i = 0; i < *nl; i++)
			for (int j = 0; j < 3 * (*nc); j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < *nl; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
	}
}

//Functia de rotire a intregii imagini (color) cu -90 sau 270 de grade
void ROTATE_270_COL_FULL(unsigned char ***img, unsigned char ***imgaux,
						 int *unghi, int *nc, int *nl, int *x2, int *y2)
{
	//Aplic procedeul descris la ROTATE_90_FULL
	if (*unghi == -90 || *unghi == 270) {
		int k = 3 * (*nc);
		*imgaux = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			*(*imgaux + i) = calloc(3 * (*nl), sizeof(unsigned char));
		for (int i = 0; i < *nc; i++) {
			for (int j = 0; j < 3 * (*nl); j++)
				(*imgaux)[i][j] = (*img)[j / 3][j % 3 + k - 3];
			k = k - 3;
		}
		for (int i = 0; i < *nl; i++)
			free(*(*img + i));
		free(*img);
		*img = malloc(*nc * sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			*(*img + i) = calloc(3 * (*nl), sizeof(unsigned char *));
		for (int i = 0; i < *nc; i++)
			for (int j = 0; j < 3 * (*nl); j++)
				(*img)[i][j] = (*imgaux)[i][j];
		for (int i = 0; i < *nc; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		int auxil;
		auxil = *nc;
		*nc = *nl;
		*nl = auxil;
		*x2 = *nc;
		*y2 = *nl;
		printf("Rotated %d\n", *unghi);
	}
}

//Functia de rotire a subimaginii patratice (gri)
void ROTATE_SQUARE(unsigned char ***img, unsigned char ***imgaux,
				   int *unghi, int *x1, int *y1, int *x2, int *y2)
{
	int n = *x2 - *x1;
	//Rotirea subimaginii selectate cu 90 sau -270 de grade
	if (*unghi == 90 || *unghi == -270) {
		//Creez o matrice auxiliara, in care stochez subimaginea rotita
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(n, sizeof(unsigned char));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				(*imgaux)[i][j] = (*img)[*y1 + n - 1 - j][*x1 + i];

		//Transpun subimaginea rotita in imaginea initiala si eliberez memoria
		//alocata pentru matricea auxiliara
		for (int i = (*y1); i < (*y2); i++)
			for (int j = (*x1); j < (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu -90 sau 270 de grade
	if (*unghi == -90 || *unghi == 270) {
		//Repet procedeul descris la rotirea subimaginii cu 90 / -270 de grade
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(n, sizeof(unsigned char));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				(*imgaux)[i][j] = (*img)[(*y1) + j][(*x1) + n - 1 - i];
		for (int i = (*y1); i < (*y2); i++)
			for (int j = (*x1); j < (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu 180 sau -180 de grade
	if (*unghi == 180 || *unghi == -180) {
		//Repet procedeul descris la rotirea subimaginii cu 90 / -270 de grade
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(n, sizeof(unsigned char));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				(*imgaux)[i][j] = (*img)[(*y1) + n - 1 - i][(*x1) + n - 1 - j];
		for (int i = (*y1); i < (*y2); i++)
			for (int j = (*x1); j < (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu 0 / -360 / 360 de grade
	if (*unghi == 0 || *unghi == 360 || *unghi == -360) {
		printf("Rotated %d\n", *unghi);
		return;
	}
}

//Functia de rotire a subimaginii patratice (color)
void ROTATE_SQUARE_COL(unsigned char ***img, unsigned char ***imgaux,
					   int *unghi, int *x1, int *y1, int *x2, int *y2)
{
	//Repet procedeul descris la rotirea subimaginii gri
	// cu 90 sau -270 de grade pentru toate rotirile de mai jos
	int n = *x2 - *x1;
	//Rotirea subimaginii selectate cu 90 sau -270 de grade
	if (*unghi == 90 || *unghi == -270) {
		int k = 0, laux;
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(3 * n, sizeof(unsigned char));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3 * n; j++) {
				laux = (*y1) + n - 1 - j / 3;
				(*imgaux)[i][j] = (*img)[laux][3 * (*x1) + j % 3 + k];
			}
			k = k + 3;
		}
		for (int i = (*y1); i < (*y2); i++)
			for (int j = 3 * (*x1); j < 3 * (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - 3 * (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu -90 sau 270 de grade
	if (*unghi == -90 || *unghi == 270) {
		int k = 3 * n, caux;
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(3 * n, sizeof(unsigned char));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3 * n; j++) {
				caux = 3 * (*x1) + j % 3 + k - 3;
				(*imgaux)[i][j] = (*img)[(*y1) + j / 3][caux];
			}
			k = k - 3;
		}
		for (int i = (*y1); i < (*y2); i++)
			for (int j = 3 * (*x1); j < 3 * (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - 3 * (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu 180 sau -180 de grade
	if (*unghi == 180 || *unghi == -180) {
		int k = 0, cvar;
		*imgaux = malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			*(*imgaux + i) = calloc(3 * n, sizeof(unsigned char));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3 * n; j++) {
				cvar = 3 * (*x1) + j % 3 + 3 * (n - j / 3 - 1);
				(*imgaux)[i][j] = (*img)[(*y1) + n - k - 1][cvar];
			}
			k++;
		}
		for (int i = (*y1); i < (*y2); i++)
			for (int j = 3 * (*x1); j < 3 * (*x2); j++)
				(*img)[i][j] = (*imgaux)[i - (*y1)][j - 3 * (*x1)];
		for (int i = 0; i < n; i++)
			free(*(*imgaux + i));
		free(*imgaux);
		printf("Rotated %d\n", *unghi);
		return;
	}
	//Rotirea subimaginii selectate cu 0 / -360 / 360 de grade
	if (*unghi == 0 || *unghi == 360 || *unghi == -360) {
		printf("Rotated %d\n", *unghi);
		return;
	}
}

//Verific daca unghiul de rotatie este divizibil cu 90 si daca exista
//o imagine incarcata in memoria programului
void UNGHI_LOAD_ROTATE(int *unghi, int *load, int *mv)
{
	scanf("%d ", unghi);
	if (*unghi % 90 != 0) {
		printf("Unsupported rotation angle\n");
		*mv = 1;
		return;
	}
	if (*load == 0) {
		printf("No image loaded\n");
		*mv = 1;
		return;
	}
}
