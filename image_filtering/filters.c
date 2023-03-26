#include "filters.h"
#include <math.h>

//FILTRE contours
int contours (unsigned char * imgValues)
{
    unsigned char imgH[270054]={'0'};
    unsigned char imgV[270054]={'0'};
    unsigned int matriceH[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1}};
    unsigned int matriceV[3][3] = {{-1,-1,-1},{0,0,0},{1,1,1}};
    unsigned int matricePixel[3][3];
    int resultH;
    int resultV;

    gris(imgValues);

    //Definition Matrice
    for (int a=54;a<270054;a+=3)
    {
        resultH=0;
        resultV=0;

        matricePixel[0][0]=imgValues[a];
        matricePixel[0][1]=imgValues[a];
        matricePixel[0][2]=imgValues[a];
        matricePixel[1][0]=imgValues[a];
        matricePixel[1][1]=imgValues[a];
        matricePixel[1][2]=imgValues[a];
        matricePixel[2][0]=imgValues[a];
        matricePixel[2][1]=imgValues[a];
        matricePixel[2][2]=imgValues[a];

        matricePixel[1][1]=imgValues[a];
        if(a>900)
        {
            matricePixel[0][1]=imgValues[a-900];
            if((a-54)%900!=0)
            {
                matricePixel[0][0]=imgValues[a-909];
            }
            if((a-54)%900!=897)
            {
                matricePixel[0][2]=imgValues[a-891];
            }
        }
        if((a-54)%900!=0)
        {
            matricePixel[1][0]=imgValues[a-3];
        }
        if((a-54)%900!=897)
        {
            matricePixel[1][2]=imgValues[a+3];
        }
        if(a>954)
        {
            matricePixel[2][1]=imgValues[a+900];
            if((a-54)%900!=0)
            {
                matricePixel[2][0]=imgValues[a+891];
            }
            if((a-54)%900!=897)
            {
                matricePixel[2][2]=imgValues[a+909];
            }
        }

        for (int i=0;i<=2;i++)
        {
            for (int j=0;j<=2;j++)
            {
                resultH+=(matriceH[i][j]*matricePixel[i][j])/3;
                resultV+=(matriceV[i][j]*matricePixel[i][j])/3;
            }
        }
        imgH[a]=resultH;
        imgV[a]=resultV;
    }

    for (int a=54;a<270054;a+=3)
    {
        imgValues[a]=(char)sqrt((pow((int)imgH[a],2))+(pow((int)imgV[a],2)));
        imgValues[a]=imgV[a];
        imgValues[a+1]=imgValues[a];
        imgValues[a+2]=imgValues[a];
    }

    //Monochrome Modifié
//    int luminance;
//    for (int a=54;a<270054;a+=3)
//    {
//        luminance = (imgValues[a]+imgValues[a+1]+imgValues[a+2])/3;
//        if (luminance > 200)
//        {                               //Mettre le pixel en noir
//            imgValues[a]=255;
//            imgValues[a+1]=255;
//            imgValues[a+2]=255;
//        }
//        else                            //Mettre le pixel en blanc
//        {
//            imgValues[a]=0;
//            imgValues[a+1]=0;
//            imgValues[a+2]=0;
//        }
//    }
    inversion(imgValues);

    return 0;
}





//FILTRE inversement des couleurs
int inversion (unsigned char * imgValues)
{
    for (int a=54;a<270054;a++)
    {
        imgValues[a]=255-imgValues[a];
    }
    return 0;
}






//FILTRE monochrome
int monochrome (unsigned char * imgValues)
{
    int luminance;
    for (int a=54;a<270054;a+=3)
    {
        luminance = (imgValues[a]+imgValues[a+1]+imgValues[a+2])/3;
        if (luminance > 255/2)
        {                               //Mettre le pixel en noir
            imgValues[a]=255;
            imgValues[a+1]=255;
            imgValues[a+2]=255;
        }
        else                            //Mettre le pixel en blanc
        {
            imgValues[a]=0;
            imgValues[a+1]=0;
            imgValues[a+2]=0;
        }
    }
    return 0;
}






//FILTRE gris
int gris (unsigned char * imgValues)
{
    int luminance;
    for (int a=54;a<270054;a+=3)
    {
        luminance = (imgValues[a]+imgValues[a+1]+imgValues[a+2])/3;

        imgValues[a]=luminance;
        imgValues[a+1]=luminance;
        imgValues[a+2]=luminance;
    }
    return 0;
}






int superposition (unsigned char * imgValues, unsigned char * img2Values)
{
    for (int a=54;a<270054;a++)
    {
        imgValues[a]=(imgValues[a]+img2Values[a])/2;
    }
    return 0;
}
