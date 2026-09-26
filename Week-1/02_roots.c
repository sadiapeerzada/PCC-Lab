#include <math.h>
#include <stdio.h>

int main()
{
    float a, b, c, root1, root2, real, image;
    printf("Enter coefficient a, b and c: ");
    scanf("%f %f %f", &a, &b, &c);

    float disc = (b * b) - (4 * a * c);

    //Roots are real
    if (disc > 0) { 
        root1 = (-b + sqrt(disc)) / (2 * a);
        root2 = (-b - sqrt(disc)) / (2 * a);
        printf("Root 1 = %.2f & Root 2 = %.2f", root1, root2);
    }

    //Roots are equal
    else if (disc == 0) {
        root1 = root2 = - b / (2 * a);
        printf("Root 1 = Root 2 = %.2f", root1);
    }

    //Roots are imaginary
    else {
        real = - b / (2 * a);
        image = sqrt(- disc) / (2 * a);
        printf("Root 1 = %.2f + i%.2f & Root 2 = %.2f - i%.2f", real, image, real, image);
    }

    return 0;
}