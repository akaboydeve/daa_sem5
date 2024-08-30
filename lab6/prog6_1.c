/*Define a struct person as follows:
struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
Write a menu driven program to read the data of ‘n’ students from a file and store them in a dynamically allocated array of struct person.
Implement the min-heap or max-heap and its operations based on the menu options.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person heap[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].age < heap[smallest].age)
    {
        smallest = left;
    }
    if (right < n && heap[right].age < heap[smallest].age)
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void maxHeapify(struct person heap[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].weight > heap[largest].weight)
    {
        largest = left;
    }
    if (right < n && heap[right].weight > heap[largest].weight)
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

void createMinHeap(struct person heap[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        minHeapify(heap, n, i);
    }
}

void createMaxHeap(struct person heap[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(heap, n, i);
    }
}

void insertPerson(struct person heap[], int *n, struct person newPerson)
{
    heap[*n] = newPerson;
    int i = (*n)++;
    while (i != 0 && heap[(i - 1) / 2].age > heap[i].age)
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteOldestPerson(struct person heap[], int *n)
{
    if (*n <= 0)
    {
        printf("Heap is empty.\n");
        return;
    }
    heap[0] = heap[--(*n)];
    minHeapify(heap, *n, 0);
}

void displayWeightOfYoungestPerson(struct person heap[])
{
    printf("Weight of youngest student: %.2f kg\n", heap[0].weight * 0.453592);
}

void readData(struct person **persons, int *n)
{
    FILE *file = fopen("students.txt", "r");
    if (!file)
    {
        printf("File not found.\n");
        exit(1);
    }

    fscanf(file, "%d", n);
    *persons = (struct person *)malloc(*n * sizeof(struct person));
    for (int i = 0; i < *n; i++)
    {
        (*persons)[i].name = (char *)malloc(50 * sizeof(char));
        fscanf(file, "%d %s %d %d %d", &(*persons)[i].id, (*persons)[i].name, &(*persons)[i].age, &(*persons)[i].height, &(*persons)[i].weight);
    }

    fclose(file);
}

void displayData(struct person persons[], int n)
{
    printf("Id Name Age Height Weight(pound)\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d %s %d %d %d\n", persons[i].id, persons[i].name, persons[i].age, persons[i].height, persons[i].weight);
    }
}

int main()
{
    struct person *persons = NULL;
    int n = 0;
    int option;

    while (1)
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            readData(&persons, &n);
            displayData(persons, n);
            break;
        case 2:
            createMinHeap(persons, n);
            printf("Min-heap created based on age.\n");

            break;
        case 3:
            createMaxHeap(persons, n);
            printf("Max-heap created based on weight.\n");
            break;
        case 4:
            displayWeightOfYoungestPerson(persons);
            break;
        case 5:
        {
            struct person newPerson;
            newPerson.name = (char *)malloc(50 * sizeof(char));
            printf("Enter new person's data (id name age height weight): ");
            scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);
            insertPerson(persons, &n, newPerson);
            printf("Person inserted into the Min-heap.\n");
            break;
        }
        case 6:
            deleteOldestPerson(persons, &n);
            printf("Oldest person deleted from the Min-heap.\n");
            break;
        case 7:
            free(persons);
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}