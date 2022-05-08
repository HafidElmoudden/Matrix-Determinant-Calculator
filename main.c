#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float ** comCalc( int ln, int cn,float ** matrice, int lp, int cp)
{
    int i,j,b=0,c=0;
    float **res;
    // Allocation de 2D matrice
    res=(float**)malloc((ln-1)*sizeof(float*));
    for(i=0; i<ln-1; i++)
    {
        res[i]=(float*)malloc((cn-1)*sizeof(float));
    }
    if( res == NULL)
    {
        printf("Error d'allocation !");
        exit(22);
    }

    for(i=0; i<ln; i++)
    {
        for(j=0; j<cn; j++)
        {
            if(i == lp || j == cp)
                continue;
            if(b==cn-1)
            {
                c++;
                b=0;
            }
            res[c][b]=matrice[i][j];
            b++;
        }
    }
    return res;
}
float detCalc(int noL, int noC, float ** matrice)
{
    int i=0,j,colCounter[noC],lnCounter[noL],colPos=0,colPosZeros=0,lnPos=0,lnPosZeros=0;
    float res=0;
    if(noL == 1 && noC == 1)
    {
        res+=(matrice[0][0]);
    }
    if(noL == 2 && noC == 2)
    {
        res+=(matrice[0][0]*matrice[1][1])-(matrice[1][0]*matrice[0][1]);
        return res;
    }
    // Column zeros counter
    for(i=0; i<noC; i++)
    {
        colCounter[i]=0;
        for(j=0; j<noL; j++)
        {
            if(matrice[j][i]==0)
                colCounter[i]++;
        }
    }
    // Ligne zeros counter
    for(i=0; i<noL; i++)
    {
        lnCounter[i]=0;
        for(j=0; j<noC; j++)
        {
            if(matrice[i][j]==0)
                lnCounter[i]++;
        }
    }
    // Best ligne selection
    for(i=1; i<noL; i++)
    {
        if(lnCounter[i]>lnPos)
        {
            lnPos=i;
            lnPosZeros=lnCounter[i];
        }
    }
    // Best colonne selection
    for(i=0; i<noC; i++)
    {
        if(colCounter[i]>colPos)
        {
            colPos=i;
            colPosZeros=colCounter[i];
        }
    }
    if(lnPosZeros>=colPosZeros)
    {
        i=lnPos;
        for(j=0; j<noC; j++)
        {
            res+=matrice[i][j]*pow(-1,i+j)*detCalc(noL-1,noC-1,comCalc(noL,noC,matrice,i,j));
        }
    }
    if(colPosZeros>lnPosZeros)
    {
        j=colPos;
        for(j=0; j<noC; j++)
        {
            res+=matrice[i][j]*pow(-1,i+j)*detCalc(noL-1,noC-1,comCalc(noL,noC,matrice,i,j));
        }
    }
    return res;
}


int main()
{
    int i,j,noL,noC;
    float ** table;
    printf("Entrez le nombre de Lignes x Colonnes: ");
    scanf("%d",&noL);
    noC=noL;

    table=(float**)malloc(noL*sizeof(float*));
    if( table == NULL)
    {
        printf("Error d'allocation !");
        exit(22);
    }
    for(i=0; i<noL; i++)
    {
        table[i]=(float*)malloc(noC*sizeof(float));
        if( table[i] == NULL)
        {
        printf("Error d'allocation !");
        exit(22);
        }
    }

    for(i=0; i<noL; i++)
    {
        for(j=0; j<noC; j++)
        {
            printf("Entrez la valeur de table[%d][%d]: ", i, j);
            scanf("%f", &table[i][j]);
        }
    }
    printf("\n\n");
    for(i=0; i<noL; i++)
    {
        printf("\t\t|");
        for(j=0; j<noC; j++)
        {
            printf(" %.2f ",table[i][j]);
        }
        printf("|\n");
    }
    printf("\t    Determinant est = %.2f\n",detCalc(noL,noC,table));

    return 0;
}
