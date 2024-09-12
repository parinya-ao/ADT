#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct student {
    char name[35];
    int score; 
} student_t;

double miu = 0.00;
double sigma = 0.00;

void inputStudent(student_t *students, int n)
{
    miu = 0.00;
    sigma = 0.00;
    for (int i = 0; i < n; i++)
    {
        scanf("%s %i", students[i].name, &students[i].score);
        miu += students[i].score;
    } 
    miu /= n;
    for (int i = 0; i < n; i++)
    {
        sigma += pow((students[i].score - miu), 2);
    }
    sigma /= (n-1);
    sigma = sqrt(sigma);
}

void grade(int x)
{
    if (x >= miu + 1.5 * sigma)
    {
        printf("A");
    }
    else if (x >= miu + sigma)
    {
        printf("B");
    }
    else if (x >= miu - sigma)
    {
        printf("C");
    }
    else if (x >= miu - 1.5 * sigma)
    {
        printf("D");
    }
    else
    {
        printf("F");
    }
}

void showStudentGrade(student_t *students, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s ", students[i].name);
        grade(students[i].score);
        printf("\n");
    }
}

int main()
{
    student_t students[1001];
    int n;
    scanf("%i", &n);

    inputStudent(students, n); 
    showStudentGrade(students, n);

    return 0;
}
