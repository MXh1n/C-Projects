#include <stdio.h>

//Function for dot product
void dot_product(int dimension){
    int coordinate;
    int vector1[dimension], vector2[dimension];
    char ch;
    double result = 0.00;

    printf("\n");
    for (coordinate = 0, ch = 'x'; coordinate < dimension; coordinate++, ch++){
        printf("Enter %c-coordinate of vector1: ", ch);
        scanf("%d", &vector1[coordinate]);
    }

    printf("\n");
    for (coordinate = 0, ch = 'x'; coordinate < dimension; coordinate++, ch++){
        printf("Enter %c-coordinate of vector2: ", ch);
        scanf("%d", &vector2[coordinate]);
    }

    for (coordinate = 0; coordinate < dimension; coordinate++){
        result += (double) vector1[coordinate] * vector2[coordinate];
    }

    printf("\nDot product of vector1 and vector2: %.2lf\n\n", result);
}

//function handles cross product
void cross_product (void){
    int dimension = 3, coordinate;
    char ch;
    int vector1[dimension], vector2[dimension], result[dimension];

    printf("\n");
    for (coordinate = 0, ch = 'x'; coordinate < dimension; coordinate++, ch++){
        printf("Enter %c-coordinate of vector1: ", ch);
        scanf("%d", &vector1[coordinate]);
    }

    printf("\n");
    for (coordinate = 0, ch = 'x'; coordinate < dimension; coordinate++, ch++){
        printf("Enter %c-coordinate of vector2: ", ch);
        scanf("%d", &vector2[coordinate]);
    }

    result[0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
    result[1] = -((vector1[0] * vector2[2]) - (vector1[2] * vector2[0]));
    result[2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);

    printf("                         x   y   z\n");
    printf("Perpendicular vector: ");
    for (coordinate = 0; coordinate < dimension; coordinate++){
        printf("%4d", result[coordinate]);
    }
    printf("\n\n");
}

//Main function
int main(void){

    int choice;
    int operation;

    while (1){
        printf("Vector Calculator\n");
        printf("----------------------\n");
        printf("1. Two-dimensional vector\n");
        printf("2. Three-dimensional vector\n");
        printf("3. Exit\n");
        printf("Enter an option (1 - 3): ");
        scanf("%d", &choice);

        if (choice == 1){
            while (1){
                printf("\nOperation:\n");
                printf("1. Dot product\n");
                printf("2. Return\n");
                printf("Enter (1-2): ");
                scanf("%d", &operation);

                if (operation == 1) {
                    dot_product(2);
                    break;
                }
                else if (operation == 2) break;
                else printf("\nInvalid input\n");
            }

        }

        else if (choice == 2){

            while (1){
                printf("\nOperation:\n");
                printf("1. Dot product\n");
                printf("2. Cross product\n");
                printf("3. Return\n");
                printf("Enter (1-3): ");
                scanf("%d", &operation);

                if (operation == 1) {
                    dot_product(3);
                    break;
                }
                else if (operation == 2){
                    cross_product();
                    break;
                }
                else if (operation == 3) break;
                else printf("\nInvalid input\n");
            }

        }

        else if (choice == 3) break;

        else printf("Invalid option\n\n");
    }

    return 0;
}
