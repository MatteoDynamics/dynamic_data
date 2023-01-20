#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void free_list(node *lista) {
    if (lista == NULL) {
        return;
    }
    free_list(lista->next);
    free(lista);
}

void add(node **lista, kontakt dane)
{   
    if (*lista == NULL) {
        *lista = malloc(sizeof(node));
        (*lista)->data = dane;
        (*lista)->prev = NULL;
        (*lista)->next = NULL;
    } else {
        node *new = malloc(sizeof(node));
        if (new == NULL) 
        {
        free_list(*lista);
        exit(1);
        }
        new->data = dane;
        new->prev = *lista;
        new->next = NULL;
        (*lista)->next = new;
        *lista = new;
    }
}
node *get_first(node *lista) {
  while (lista->prev != NULL) {
    lista = lista->prev;
  }
  return lista;
}

void print_list(node *lista) {
  while (lista->prev != NULL) {
    lista = lista->prev;
  }
  while (lista != NULL) {
    printf("name: %-20s surname: %-20s number: %-20s group: %-20s\n", lista->data.name, lista->data.surname, lista->data.number, lista->data.group);
    lista = lista->next;
  }
}



void clear_list(node** lista) {
  node* current = *lista;

  while (current != NULL) {
    node* next = current->prev;
    free(current);
    current = next;
  }

  *lista = NULL;
}

void read_from_csv(node **lista)
{
    // Open the CSV file
    FILE *file = fopen("prosta_lista (1).csv", "r");
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
        add(lista, dane);
    }

    // Close the file
    fclose(file);
}

void swap(node *a, node *b)
{
    kontakt temp = a->data;
    a->data = b->data;
    b->data = temp;
}


void sort_list(node **lista, char field[20]) {
  if(strcmp(field, "name") != 0 && strcmp(field, "surname") != 0 && strcmp(field, "group") != 0) {
        printf("Error: Invalid field.\n");
        return;
  }

  node *current = *lista;

  while (current->prev != NULL) {
    current = current->prev;
  }

  int swapped;
  node *ptr1;
  node *lptr = NULL;

  if (current == NULL)
    return;

  do
  {
    swapped = 0;
    ptr1 = current;

    while (ptr1->next != lptr)
    {
        if (strcmp(field, "name") == 0) {
            char name1[20], name2[20];
            if(strlen(ptr1->data.name)>=19) 
                strncpy(name1, ptr1->data.name,19);
            else
                strcpy(name1, ptr1->data.name);
            if(strlen(ptr1->next->data.name)>=19) 
                strncpy(name2, ptr1->next->data.name,19);
            else
                strcpy(name2, ptr1->next->data.name);
            for(int i = 0; name1[i]; i++){
              name1[i] = tolower(name1[i]);
            }
            for(int i = 0; name2[i]; i++){
              name2[i] = tolower(name2[i]);
            }
            if (strcmp(name1, name2) > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
        } else if (strcmp(field, "surname") == 0) {
            char surname1[20], surname2[20];
            if(strlen(ptr1->data.surname)>=19) 
                strncpy(surname1, ptr1->data.surname,19);
            else
                strcpy(surname1, ptr1->data.surname);
            if(strlen(ptr1->next->data.surname)>=19) 
                strncpy(surname2, ptr1->next->data.surname,19);
            else
                strcpy(surname2, ptr1->next->data.surname);
            for(int i = 0; surname1[i]; i++){
              surname1[i] = tolower(surname1[i]);
            }
            for(int i = 0; surname2[i]; i++){
              surname2[i] = tolower(surname2[i]);
            }
            if (strcmp(surname1, surname2) > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
        } else if (strcmp(field, "group") == 0) {
char group1[20], group2[20];
            if(strlen(ptr1->data.group)>=19) 
                strncpy(group1, ptr1->data.group,19);
            else
                strcpy(group1, ptr1->data.group);
            if(strlen(ptr1->next->data.group)>=19) 
                strncpy(group2, ptr1->next->data.group,19);
            else
                strcpy(group2, ptr1->next->data.group);
            for(int i = 0; group1[i]; i++){
              group1[i] = tolower(group1[i]);
            }
            for(int i = 0; group2[i]; i++){
              group2[i] = tolower(group2[i]);
            }
            if (strcmp(group1, group2) > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
        }

        ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void add_sorted_input(node **lista, char field[20]) {
    if(strcmp(field, "name") != 0 && strcmp(field, "surname") != 0 && strcmp(field, "group") != 0) {
        printf("Error: Invalid field.\n");
        return;
    }
    *lista = get_first(*lista);

    kontakt dane;

    printf("Enter contact name: ");
    scanf("%s", dane.name);

    printf("Enter contact surname: ");
    scanf("%s", dane.surname);

    printf("Enter contact number: ");
    scanf("%s", dane.number);

    printf("Enter contact group: ");
    scanf("%s", dane.group);

    node *new = malloc(sizeof(node));
    new->data = dane;
    new->prev = NULL;
    new->next = NULL;

    node *current = *lista;
    node *prev = NULL;
    
    // change the while loop to traverse the list until it reaches the correct position to insert the new contact
    while (current != NULL) {
        int comparison;
        if(strcmp(field, "name") == 0) {comparison = strcmp(dane.name, current->data.name);} else if (strcmp(field, "surname") == 0) {comparison = strcmp(dane.surname, current->data.surname);} else if (strcmp(field, "group") == 0) {comparison = strcmp(dane.group, current->data.group);}
if(comparison < 0) {
break;
}
prev = current;
current = current->next;
}
// check if the new contact should be inserted at the beginning of the list
if (prev == NULL && *lista != NULL) {
    new->next = *lista;
    (*lista)->prev = new;
    *lista = new;
}
// check if the new contact should be inserted at the end of the list
else if (current == NULL) {
    if(prev != NULL) {
        new->prev = prev;
        prev->next = new;
    } else {
        *lista = new;
    }
}
// insert the new contact in the middle of the list
else {
    new->prev = prev;
    new->next = current;
    prev->next = new;
    current->prev = new;
}
}

void search_contacts(node *lista, char search[20])
{
    // get the first element of the linked list
    node *current = get_first(lista);
    int i;
    // convert the search query to lowercase
    for(i = 0; i < strlen(search); i++) {
        search[i] = tolower(search[i]);
    }
    // iterate through the linked list
    while (current != NULL)
    {
        char name_temp[20],surname_temp[20];
        strcpy(name_temp,current->data.name);
        strcpy(surname_temp,current->data.surname);
        for(i = 0; i < strlen(name_temp); i++) {
            name_temp[i] = tolower(name_temp[i]);
        }
        for(i = 0; i < strlen(surname_temp); i++) {
            surname_temp[i] = tolower(surname_temp[i]);
        }
        // check if the name or surname field contains the search query
        if (strstr(name_temp, search) != NULL || strstr(surname_temp, search) != NULL)
        {
            // print out the name and surname fields of the contact
            printf("name: %-20s surname: %-20s\n", current->data.name, current->data.surname);
        }
        current = current->next;
    }
}

void search_group(node *lista, char group[20])
{
    // get the first element of the linked list
    node *current = get_first(lista);
    
    for(int i = 0; i < strlen(group); i++) {
            group[i] = tolower(group[i]);
        }
    // iterate through the linked list
    while (current != NULL)
    {
        // check if the group field matches the search query
        char group_temp[20];
        strcpy(group_temp,current->data.group);
        for(int i = 0; i < strlen(group_temp); i++) {
            group_temp[i] = tolower(group_temp[i]);
        }
        if (strstr(group_temp, group) != 0)
        {
            // print out the name, surname and number fields of the contact
            printf("\ found:    name: %-20s surname: %-20s number: %-20s\n", current->data.name, current->data.surname, current->data.number);
        }
        current = current->next;
    }
}

void remove_contact(node **lista, char name[20], char surname[20]) {
    node *current = get_first(*lista);
    while (current != NULL) {
        char current_name[20], current_surname[20];
        strcpy(current_name, current->data.name);
        strcpy(current_surname, current->data.surname);
        for(int i = 0; current_name[i]; i++){
            current_name[i] = tolower(current_name[i]);
        }
        for(int i = 0; current_surname[i]; i++){
            current_surname[i] = tolower(current_surname[i]);
        }
        if (strcmp(current_name, name) == 0 && strcmp(current_surname, surname) == 0) {
            // Contact found, remove it from the list
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            if (current == *lista) {
                *lista = current->next;
            }
            free(current);
            return;
        }
        current = current->next;
    }
    // Contact not found
    printf("Error: Contact not found.\n");
}



int main()
{node *lista = NULL;kontakt dane;char name_delete[20]; char surname_delete[20];
    char name[20];
    char surname[20];
    //printf("Enter name to search: ");
    //scanf("%s", name);


    read_from_csv(&lista);
    //search_contacts(lista, name);
    printf("Enter group to search: \n");
    scanf("%s", name);
    search_group(lista, name);
    //add(&lista,dane);
    //add(&lista,dane);
    sort_list(&lista, "surname");
    print_list(lista);
//add_sorted_input(&lista, "surname");
//print_list(lista);
    printf("type name and surname to delete contact");
    scanf("%s",&name_delete);
    scanf("%s",&surname_delete);
    remove_contact(&lista, name_delete,surname_delete);
    print_list(lista);
    clear_list(&lista);
}