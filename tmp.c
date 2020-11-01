#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Bad number of arguments. Given %d. Required 3\n", argc - 1);
        return 1;
    }
    FILE *Afile, *xfile, *bfile; // declaration of file pointer
    float** A;
    float* x;
    float* b;
    int Ma, Na, Mx, Nx, Mb, Nb, i, j;
    Afile = fopen(argv[1], "r"); // opening of file
    if (!Afile)
    {
        return 1;
    }
    fscanf(Afile, "%d", &Na);
    fscanf(Afile, "%d", &Ma);
    printf("%d, %d\n", Ma, Na);
    A = (float **)malloc(Ma * sizeof(float));
    for (i = 0; i < Na; ++i)
    {
        A[i] = (float *)malloc(Na * sizeof(float));
    }
    for (i = 0; i < Na; ++i)
    {
        for (j = 0; j < Ma; ++j)
        {
            float tmp;
            if (!Afile)
            {
                printf("Bad file %s", argv[1]); 
                return 1;
            }
            fscanf(Afile, "%f", &tmp);
            A[j][i] = tmp;
        }
    }
    fclose(Afile);
    xfile = fopen(argv[2], "r"); // opening of file
    if (!xfile)
    {
        return 1;
    }
    fscanf(xfile, "%d", &Mx);
    fscanf(xfile, "%d", &Nx);
    printf("%d, %d\n", Mx, Nx);
    if (Na != Mx)
    {
        printf("Bad dims width of A (%d) not equal height of x (%d)", Na, Mx);
        return 0;
    }
    if (Nx != 1)
    {
        printf("Bad dims width of x (%d). Should be 1", Nx);
        return 0;
    }
    x = (float *)malloc(Mx * sizeof(float));
    for (i = 0; i < Mx; ++i)
    {
        float tmp;
        if (!xfile)
        {
            printf("Bad file %s", argv[2]);
            return 1;
        }
        fscanf(xfile, "%f", &tmp);
        x[i] = tmp;
    }
    fclose(xfile);
    Mb = Ma;
    Nb = 1;
    b = (float *)malloc(Mb * sizeof(float));
    for (i = 0; i < Mb; ++i)
    {
        b[i] = 0;
    }
    printf("(%d) [", Mb);
    for (i = 0; i < Ma; ++i)
    {
        for (j = 0; j < Mb; ++j)
        {
            b[i] += A[i][j] * x[j];
        }
        printf("%f ", b[i]);
    }
    printf("]\n");
    for (i = 0; i < Ma; ++i)
    {
        free(A[i]);
    }
    free(A);
    free(x);
    free(b);
    return 0;
}
