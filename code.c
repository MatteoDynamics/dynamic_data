#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct kontakt
{
    char name[20];
    char surname[20];
    char number[20];
    char group[20];
    
}kontakt;

typedef struct node
{
    struct node *next;
    struct node *prev; 
    kontakt data;
}node;



void add(node **koniec, kontakt dane)
{   
    if (*koniec == NULL) {
        *koniec = malloc(sizeof(node));
        (*koniec)->data = dane;
        (*koniec)->prev = NULL;
        (*koniec)->next = NULL;
    } else {
        node *new = malloc(sizeof(node));
        new->data = dane;
        new->prev = *koniec;
        new->next = NULL;
        (*koniec)->next = new;
        *koniec = new;
    }
}
node *get_first(node *koniec) {
  while (koniec->prev != NULL) {
    koniec = koniec->prev;
  }
  return koniec;
}

void print_list(node *koniec) {
  while (koniec->prev != NULL) {
    koniec = koniec->prev;
  }
  while (koniec != NULL) {
    printf("name: %-20s surname: %-20s number: %-20s group: %-20s\n", koniec->data.name, koniec->data.surname, koniec->data.number, koniec->data.group);
    koniec = koniec->next;
  }
}



void clear_list(node** koniec) {
  node* current = *koniec;

  while (current != NULL) {
    node* next = current->prev;
    free(current);
    current = next;
  }

  *koniec = NULL;
}

void read_from_csv(node **koniec)
{
    // Open the CSV file
    FILE *file = fopen("kontakty (1).csv", "r");
    if(file == NULL)
    {
        printf("Error: Could not open file\n");
        return;
    }

    // Read each line of the file
    char line[1024];
    while (fgets(line, 1024, file))
    {
        // Split the line into fields
        char *field = strtok(line, ";");
        int i = 0;
        kontakt dane;
        while (field)
        {
            // Convert the field from a string to the appropriate data type
            // and store it in the 'dane' struct
            if (i == 0) strcpy(dane.name, field);
            else if (i == 1) strcpy(dane.surname, field);
            else if (i == 2) strcpy(dane.number, field);
            else if (i == 3) strcpy(dane.group, field);

            field = strtok(NULL, ";");
            i++;
        }

        // Add the 'dane' struct to the linked list
        add(koniec, dane);
    }

    // Close the file
    fclose(file);
}


int main()
{
    node *koniec = NULL;
    kontakt dane;
    read_from_csv(&koniec);
    //add(&koniec,dane);
    //add(&koniec,dane);
    print_list(koniec);
    clear_list(&koniec);
}