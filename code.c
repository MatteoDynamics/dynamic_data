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
    FILE *file = fopen("prosta_lista (1).csv", "r");
    if(file == NULL)
    {
        printf("Error: Could not open file\n");
        return;
    }

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

void search_contacts(node *lista, char search[20])
{
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
        
        if (strstr(name_temp, search) != NULL || strstr(surname_temp, search) != NULL)
        {
            
            printf("name: %-20s surname: %-20s\n", current->data.name, current->data.surname);
        }
        current = current->next;
    }
}

void search_group(node *lista, char group[20])
{
    
    node *current = get_first(lista);
    
    for(int i = 0; i < strlen(group); i++) {
            group[i] = tolower(group[i]);
        }
    
    while (current != NULL)
    {
       
        char group_temp[20];
        strcpy(group_temp,current->data.group);
        for(int i = 0; i < strlen(group_temp); i++) {
            group_temp[i] = tolower(group_temp[i]);
        }
        if (strstr(group_temp, group) != 0)
        {
            
            printf("\ found:    name: %-20s surname: %-20s number: %-20s\n", current->data.name, current->data.surname, current->data.number);
        }
        current = current->next;
    }
}

void delete_contact(node **lista, char name[20], char surname[20]) {
    node *current = get_first(*lista); // get the first node in the list
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0 && strcmp(current->data.surname, surname) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            printf("\nContact %s %s deleted\n", name, surname);
            return;
        }
        current = current->next;
    }
    printf("Error: \nContact %s %s not found\n", name, surname);
}

kontakt create_contact() {
    kontakt new_contact;

    printf("Enter name: ");
    scanf("%s", new_contact.name);
    printf("Enter surname: ");
    scanf("%s", new_contact.surname);
    printf("Enter phone number: ");
    scanf("%s", new_contact.number);
    printf("Enter group: ");
    scanf("%s", new_contact.group);

    return new_contact;
}


void add_sorted(node **lista, kontakt dane, char field[20]) {
    if (*lista == NULL) {
        *lista = malloc(sizeof(node));
        if (lista == NULL) 
        {
        free_list(*lista);
        exit(1);
        }
        (*lista)->data = dane;
        (*lista)->prev = NULL;
        (*lista)->next = NULL;
        return;
    }
    node *current = get_first(*lista);
    if(strcmp(field, "name") == 0) {
        while (current->next != NULL && strcmp(current->next->data.name, dane.name) < 0) {
            current = current->next;
        }
    } else if(strcmp(field, "surname") == 0) {
        while (current->next != NULL && strcmp(current->next->data.surname, dane.surname) < 0) {
            current = current->next;
        }
    }
    node *new = malloc(sizeof(node));
    if (new == NULL) 
        {
        free_list(*lista);
        exit(1);
        }
    new->data = dane;
    new->prev = current;
    new->next = current->next;
    if (current->next != NULL) {
        current->next->prev = new;
    }
    current->next = new;
}

void menu_option(int * menu1)
{
    printf("Type what you want to do?\n");
    printf("\n1)sort by name\n2)sort by surname\n3)sort by group\n");
    while (1) {
    printf("type probability to noise: ");
    if (scanf("%d", &*menu1) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
}

void menu_option3(int * menu3)
{
    printf("Type what you want to do?\n");
    printf("\n1)find by name and surname\n2)find by group\n");
    while (1) {
    printf("type probability to noise: ");
    if (scanf("%d", &*menu3) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
}

void main_menu(int * menu)
{
    printf("Type what you want to do?\n");
    printf("\n1)sort\n2)add\n3)searsch\n4)delete\n5)quit\n");
    while (1) {
    printf("type probability to noise: ");
    if (scanf("%d", &*menu) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
}

int main()
{node *lista = NULL;kontakt dane;int menu1;int menu;int menu3;char name_delete[20], surname_d[20];
    char name[20];
    char surname[20];
    read_from_csv(&lista);
    print_list(lista);
    do
    {
        main_menu(&menu);
        switch(menu)
        {
            //SORT
            case 1:
            {

    menu_option(&menu1);
    switch(menu1)
    {
        case 1:
        {
            sort_list(&lista, "name");
            print_list(lista);
        }break;
        case 2:
        {
            sort_list(&lista, "surname");
            print_list(lista);
        }break;
        case 3:
        {
            sort_list(&lista, "group");
            print_list(lista);
        }break;

    }
    
            }break;
            //ADD
            case 2:
            {
                kontakt new_contact = create_contact();
                add_sorted(&lista, new_contact, "surname");
                print_list(lista);
            }break;
            //FIND
            case 3:
            {
                menu_option3(&menu3);
                switch(menu3)
                {
                    case 1:
                    {
                        printf("Enter name to search: \n");
                scanf("%s", name);
                        search_contacts(lista, name);
                    }break;

                    case 2:
                    {
                        printf("Enter surname to search: \n");
                scanf("%s", name);
                        search_contacts(lista, name);
                    }break;
                    case 3:
                    {
                        printf("Enter group to search: \n");
                scanf("%s", name);
                        search_group(lista, name);
                    }
                }
                
                
            }break;
            //DELETE
            case 4:
            {
                printf("\nEnter the name of the contact to be deleted: ");
                scanf("%s", name_delete);
                printf("Enter the surname of the contact to be deleted: ");
                scanf("%s", surname_d);
                delete_contact(&lista, name_delete, surname_d);
            }break;
            //Quitting;
            case 5:
            {
                printf("QUITTING!");
                clear_list(&lista);
                printf("Free memory!");
                exit(0);
            }
        }
    } while (menu<=5&&menu>=1);

    return 0;
}