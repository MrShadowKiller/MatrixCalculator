#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#define MAX_SIZE 20

void print_menu();

struct Matrix readMatrix();
void f_writeMatrix(struct Matrix,struct Matrix);
struct Matrix f_readMatrix(char);
void PrintMatrix(struct Matrix);
int addMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c);
int subMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c);
int mulMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c);
struct Matrix transposeMatrix(struct Matrix *a);
float determinantMatrix(struct Matrix);
float calc_determinantMatrix(struct Matrix,int,float*,float*);
void swap(float *a,float *b);
struct Matrix invertibleMatrix(struct Matrix);



struct Matrix {
float array[MAX_SIZE][MAX_SIZE];
int m,n;
};


int main() {
 struct Matrix a,b,c;
 int inp_num;
 char inp_char;
 while(1){
    print_menu();
    scanf("%d",&inp_num);
    switch(inp_num) {
        case 1: // Read matrix
            printf("Which matrix do you want to write ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char=='A')
                a = readMatrix();
            else if (inp_char=='B')
                b = readMatrix();
            else {
                printf("ERROR : Invalid Character!\n");
                break;
            }
            
            printf("Done.\n");
        break;


        case 2 : // Save the matrix in file
            f_writeMatrix(a,b);
            break;

        case 3 : // Print the Matrix

            printf("Which matrix do you want to print ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char=='A')
                PrintMatrix(a);
            else if (inp_char=='B')
                PrintMatrix(b);
            else
            printf("ERROR : Invalid Character!\n");
            break;

        case 4 : // Read the matrix from file
            printf("Which matrix do you want to read ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char == 'A')
                a = f_readMatrix(inp_char);
            else if (inp_char=='B')
                b = f_readMatrix(inp_char);
            else
            printf("ERROR : Invalid Character!\n");

            break;

        case 5 : // Add matrix A and B
            if(addMatrix(&a,&b,&c)==0)
                printf("ERROR : The matrices are not square.\n");
            else{
                printf("The result is : \n");
                PrintMatrix(c);
                a = c;
                printf("Saved to matrix A !\n");
            }
            break;

        case 6 : // Substraction Matrix A and B
            if(subMatrix(&a,&b,&c)==0)
                printf("ERROR : The matrices are not square.\n");
            else{
                printf("The result is : \n");
                PrintMatrix(c);
                a = c;
                printf("Saved to matrix A !");
            }
            break;

        case 7 : // Multiplication Matrix A and B
            if(mulMatrix(&a,&b,&c)==0)
                    printf("ERROR : These matrices are not allowed.\n");
            else{
                printf("The result is : \n");
                PrintMatrix(c);
                a = c;
                printf("Saved to matrix A !\n");
            }
            break;

        case 8 : // Transpose
            printf("Which matrix do you want to transpose ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char == 'A'){
                if (a.m != a.n){
                    printf("ERROR : Matrix is not square!\n");
                    break;
                }      
                a = transposeMatrix(&a);
                printf("The result is : \n");
                PrintMatrix(a);
            }
            else if (inp_char=='B'){
                if (b.m != b.n){
                    printf("ERROR : Matrix is not square!\n");
                    break;
                }      
                b = transposeMatrix(&b);
                printf("The result is : \n");
                PrintMatrix(b);
            }

            else {
                printf("ERROR : Invalid Character!\n");
                break;
            }
            printf("Saved to Matrix %c!\n",inp_char);
            break;

        case 9 : //Determinant
            printf("Which matrix do you want to calculate its determinant ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char == 'A')
                printf("The determinant of Matrix A is : %.6f\n",determinantMatrix(a));
            else if (inp_char=='B')
                printf("The determinant of Matrix B is : %.6f\n",determinantMatrix(b));
            else
            printf("ERROR : Invalid Character!\n");

            break;

        case 10 : // Inverse
            printf("Which matrix do you want to inverse ? (A,B) : ");
            scanf(" %c",&inp_char);
            inp_char = toupper(inp_char);
            if (inp_char == 'A') {
                if (a.m != a.n){
                    printf("ERROR : Matrix is not square!\n");
                    break;
                }      
                a = invertibleMatrix(a);
                printf("The result is :\n");
                PrintMatrix(a);
            }
            else if (inp_char=='B'){
                if (b.m != b.n){
                    printf("ERROR : Matrix is not square!\n");
                    break;
                }      
                b = invertibleMatrix(b);
                printf("The result is :\n");
                PrintMatrix(b);
            }
            else 
                printf("ERROR : Invalid Character!\n");
            
            break;

        case 11 :
            return 0;
    }
    sleep(2);
 }


 return 0;
}

void print_menu(){
    puts("____________________________________");
    puts("       * Matrix Calculator *\n ");
    puts("1.Enter a matrix");
    puts("2.Save the matrix in a file");
    puts("3.Print a matrix");
    puts("4.Read the matrix from the file");
    puts("5.Add the matrices");
    puts("6.Subtraction the matrices");
    puts("7.Multiplication the matrices");
    puts("8.Transpose the matrix");
    puts("9.Calculate the determinant of the matrix");
    puts("10.Inverse the matrix");
    puts("11.Exit");
    puts("____________________________________");
    printf("Please select an option : ");
}

struct Matrix readMatrix(){
    struct Matrix matrix;
    printf("Pleas enter the row and column of the matrix : ");
    scanf("%d %d",&matrix.m,&matrix.n);
    printf("Please enter the values of matrix (left to right) :\n");
    for (int i=0;i<matrix.m;i++)
        for (int j=0;j<matrix.n;j++)
            scanf("%f",&matrix.array[i][j]);
    return matrix;
}

void PrintMatrix(struct Matrix a){
    for (int i=0;i<a.m;i++){
        for (int j=0;j<a.n;j++){
            printf("%.3f ",a.array[i][j]);
        }
        printf("\n");
    }
}

int addMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c){
    if (a->m != b->m || a->n != b->n)
        return 0;
    for (int i=0;i<a->m;i++){
        for (int j=0;j<a->n;j++){
            c->array[i][j] = a->array[i][j] + b->array[i][j];
        }
    }
    c->m = a->m;
    c->n = a->n;
    return 1;
}

int subMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c){
    if (a->m != b->m || a->n != b->n)
        return 0;
    for (int i=0;i<a->m;i++){
        for (int j=0;j<a->n;j++){
            c->array[i][j] = a->array[i][j] - b->array[i][j];
        }
    }
    c->m = a->m;
    c->n = a->n;
    return 1;
}

int mulMatrix(struct Matrix *a,struct Matrix *b,struct Matrix *c){
    if (a->n != b->m)
        return 0;
    int sum =0;
    for (int i=0;i<a->m;i++){
        for (int j=0;j<b->n;j++){
            for (int f=0;f<a->n;f++){
                sum += a->array[i][f] * b->array[f][j];
            }
            c->array[i][j] = sum;
            sum =0;
        }
    }
    c->m = a->m;
    c->n = b->n;
    return 1;
}

struct Matrix transposeMatrix(struct Matrix *a){
    struct Matrix temp;
    temp.m = a->n;
    temp.n = a->m;
    for (int i=0;i<a->m;i++){
        for (int j=0;j<a->n;j++){
            temp.array[j][i] = a->array[i][j];
        }
    }
    return temp;
}

float determinantMatrix(struct Matrix a){
    float negative_int = 1;
    float mp_determinant = 1;
    return (negative_int * calc_determinantMatrix(a,0,&mp_determinant,&negative_int))/mp_determinant;
}

float calc_determinantMatrix(struct Matrix a,int b,float* mp_determinant,float* negative_int){
     if (a.m == 1)
         return a.array[0][0];

     if (a.m - b == 2){
        return a.array[0+b][0+b]* a.array[1+b][1+b] - a.array[1+b][0+b]*a.array[0+b][1+b];
    }

    // Check kon age sotoon aval satr shoroo 0 hast ya na
    int i=1;
    while(a.array[0+b][0+b]==0){ 
        if (i>a.m)
            return 0;
        for(int j=0+b;j<a.n;j++){
            swap(&a.array[0+b][j],&a.array[i+b][j]);
        }
        *negative_int *= -1;
        i+=1;
    }

    float soorat;
    float makhraj;

    //Mazrab makhraj ha ke biroon mire :
    //Khat be khat shoroo mikone va arraye aval ra sefr mikone
    //Az tarafi vaghti ba kasr mikhad jam beshe soorat ro jam va makhraj ro biroon mibare

    for (int i=1+b;i<a.m;i++){
        if (a.array[i][0+b] == 0)
            continue;
        soorat = -a.array[i][0+b];
        makhraj = a.array[0+b][0+b];
        a.array[i][0+b] = 0;
            for(int j=1+b;j<a.n;j++){
                a.array[i][j] =a.array[i][j]*makhraj + soorat*a.array[0+b][j];
            }
        *mp_determinant *= makhraj;
    }
   
     return (a.array[0+b][0+b]*calc_determinantMatrix(a,++b,mp_determinant,negative_int));
}

void swap(float *a,float *b){
    float temp;
    temp=*a, *a=*b,*b=temp;
}

struct Matrix invertibleMatrix(struct Matrix a){
    struct Matrix c,d;
    float det_matrix_a = determinantMatrix(a);
    if (det_matrix_a==0){
        printf("ERROR : The matrix is singular.\n");
        return a;
    }
    c.m = a.m-1;
    c.n = a.n-1;
    d = a;

    // 1) Calc Matrix Kahad
    for (int i=0;i<a.m;i++){
        for (int j=0;j<a.n;j++){
            for (int f=0,m=0;f<a.m-1 && m<a.m;f++,m++){
                for (int g=0,n=0;g<a.n-1 && n<a.n;g++,n++){
                    if (m==i)
                        m++;
                    if (n==j)
                        n++;
                    if (m==a.m || n==a.n)
                        break;
                    c.array[f][g] = a.array[m][n];
                }
            }
            d.array[i][j] = determinantMatrix(c);
        }
    }
    // 2 ) Matrix Hamsaze (manfi kardan) + 3) Zarb har deraye dar determinan

    for (int i=0;i<d.m;i++){
        for (int j=0;j<d.n;j++){
            if (d.array[i][j] !=0){
                if ((i+j)%2==1 && d.array[i][j]!=0)
                    d.array[i][j] *= -1;
                d.array[i][j] /= det_matrix_a;
            }
        }
    }

    //4 ) Matrix Transpose
    d = transposeMatrix(&d);
    return d;
}

void f_writeMatrix(struct Matrix a,struct Matrix b){
    char inp;
    char m,n;
    printf("Do you want to save Matrix A or B ? (A,B)\n");
    scanf(" %c",&inp);
    inp = toupper(inp);
    if (inp=='A'){
        FILE *stream = fopen("Matrix_A","w");
        fprintf(stream,"%d ",a.m);
        fprintf(stream,"%d ",a.n);
        fputc('\n',stream);

        for (int i=0;i<a.m;i++){
            for (int j=0;j<a.n;j++)
                fprintf(stream,"%.3f ",a.array[i][j]);
            fputc('\n',stream);
        }
        fclose(stream);
    }

    else if (inp=='B'){
        FILE *stream = fopen("Matrix_B","w");
        fprintf(stream,"%d ",b.m);
        fprintf(stream,"%d ",b.n);
        fputc('\n',stream);

        for (int i=0;i<b.m;i++){
            for (int j=0;j<b.n;j++)
                fprintf(stream,"%.3f ",b.array[i][j]);

            fputc('\n',stream);
        }
        fclose(stream);
    }
    printf("Done. \n");
}

struct Matrix f_readMatrix(char inp){
    int m,n;
    struct Matrix a;
    if (inp=='A'){
        FILE *stream = fopen("Matrix_A","r");

        fscanf(stream,"%d",&m);
        fscanf(stream,"%d",&n);

        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                fscanf(stream,"%f",&a.array[i][j]);
    }

    else {
        FILE *stream = fopen("Matrix_B","r");

        fscanf(stream,"%d",&m);
        fscanf(stream,"%d",&n);

        for (int i=0;i<m;i++)
            for (int j=0;j<n;j++)
                fscanf(stream,"%f",&a.array[i][j]);
    }

    a.m = m;
    a.n = n;

    printf("Matrix %c was received.\n",inp);
    return a;
}
