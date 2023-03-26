#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "filters.h"

int main(int argc, char *argv[])
{
    unsigned char imgValues[270054];
    unsigned char img2Values[270054];


    FILE *img;
    FILE *img2;
    FILE *newi;
    char *dir = malloc(sizeof(char) * 100);
    char *file = malloc(sizeof(char) * 100);
    char *file2 = malloc(sizeof(char) * 100);
    char *dirfile = malloc(sizeof(char) * 200);
    char *dirfile2 = malloc(sizeof(char) * 200);
    char *dirresult = malloc(sizeof(char) * 120);
    char *endchar;
    long choice = 0;

    if(argc>=4)
    {

        strcpy(dir,argv[1]);
        fputs(dir,stdout);
        printf("\n");

        choice = strtol(argv[2],&endchar,10);
        if(*endchar!='\0'){printf("meh");return -1;}
        printf("\n");

        strcpy(file,argv[3]);
        fputs(file,stdout);
        printf("\n");

        if(choice==5)
        {
            if(argc<4){return "Image 2 missing";}
            strcpy(file2,argv[4]);
            fputs(file2,stdout);
        }
    }
    else
    {
        printf("Chemin vers le repertoire / Path to the directory : ");
        fflush(stdin);
        fgets(dir,100,stdin);
        dir[strlen(dir) - 1] = '\0';
        fputs(dir,stdout);
        printf("\n");

        printf("Chemin vers l'image/ Path to the image : ");
        fflush(stdin);
        fgets(file,100,stdin);
        file[strlen(file) - 1] = '\0';
        fputs(file,stdout);
        printf("\n");

        printf("Choix :\n1 : Contours \n2 : Couleurs inversees \n3 : Monochrome \n4 : Niveaux de gris \n5 : Superposition \nVotre choix (1-5) : ");
        scanf("%d",&choice);
        printf("\n");

        if(choice==5)
        {
            fgets(file2,100,stdin);
            if(argc==1)
            {
                printf("Chemin vers l'image a superposer / Path to the image to overlay : ");
                fflush(stdin);
                fgets(file2,100,stdin);
            }
        }
    }


    strcpy(dirfile,dir);
    strcat(dirfile,"/");
    strcat(dirfile,file);
    fputs(dirfile,stdout);
        printf("\n");

    strcpy(dirresult,dir);
    strcat(dirresult,"/result.bmp");
    fputs(dirresult,stdout);
        printf("\n");

    strcpy(dirfile2,dir);
    strcat(dirfile2,"/");
    strcat(dirfile2,file2);
    fputs(dirfile2,stdout);
        printf("\n");

    //recupération de l'image
    img=fopen(dirfile,"rb"); //Lisez le fichier .bmp image dans le même répertoire.
    newi=fopen(dirresult,"wb"); //Lis et créer le fichier si inexistant
    if(img == NULL)
    {
        printf("Echec de l'ouverture de l'image / Can't open the image \n");
        return -1;
    }
    fread(imgValues, sizeof(unsigned char), 270054, img);

    switch (choice)
    {
        case 1:
            contours(imgValues);
            break;
        case 2:
            inversion(imgValues);
            break;
        case 3:
            monochrome(imgValues);
            break;
        case 4:
            gris(imgValues);
            break;
        case 5:
            img2=fopen(dirfile2,"rb");
            fread(img2Values, sizeof(unsigned char), 270054, img2);

            superposition(imgValues,img2Values);
            break;
        default:
            printf("Wrong choice");
            return -1;

    }

    printf("\nFini");

   //ecriture de l'image
    fwrite(imgValues, sizeof(unsigned char), 270054, newi);


    fclose(newi);
    fclose(img);

    free(dir);
    free(file);
    free(file2);
    free(dirfile);
    free(dirfile2);
    free(dirresult);

    return 0;
}
