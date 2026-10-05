#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list
typedef struct node
{
    char *key;
    char *value;
    struct node *next;
} node;

node *head = NULL;

// copy and store
char *copy(char *user)
{
    char *p = malloc(strlen(user) + 1);
    strcpy(p, user);
    return p;
}

// find key
node *find(char *key)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->key, key) == 0)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

void db_set(char *key, char *value)
{
    node *n = find(key);
    if (n != NULL)
    {
        free(n->value);
        n->value = copy(value);
        return;
    }
    n = malloc(sizeof(node));
    n->key = copy(key);
    n->value = copy(value);
    n->next = head;
    head = n;
}

//*************SET************

void set_cmd(void)
{
    char *key = strtok(NULL, " ");
    char *value = strtok(NULL, "");

    if (key == NULL || value == NULL)
        printf("ERROR: usage: SET <key> <value>\n");
    else
    {
        db_set(key, value);
        printf("OK\n");
    }
}

//*************GET************
void get_cmd(void)
{
    char *key = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    if (key == NULL || extra != NULL)
        printf("ERROR: usage: GET <key> \n");
    else
    {
        node *a = find(key);
        if (a == NULL)
            printf("ERROR: key '%s' not found\n", key);
        else
            printf("%s\n", a->value);
    }
}

//*************EXISTS************
void exists_cmd(void)
{
    char *key = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    if (extra != NULL || key == NULL)
        printf("ERROR: usage: EXISTS <key> \n");
    else if (find(key) != NULL)
        printf("True\n");
    else
        printf("False\n");
}

//*************DEL************
void del_cmd(void)
{
    char *key = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    if (extra != NULL || key == NULL)
        printf("ERROR: usage: DEL <key> \n");
    else
    {
        if (find(key) == NULL)
            printf("ERROR: key '%s' not found\n", key);
        else
        {
            node *ptr = head;
            node *pptr = NULL;
            while (ptr != NULL)
            {
                if (strcmp(ptr->key, key) == 0)
                    break;
                else
                {
                    pptr = ptr;
                    ptr = ptr->next;
                }
            }
            if (strcmp(ptr->key, key) == 0 && pptr == NULL)
                head = ptr->next;
            else
                pptr->next = ptr->next;
            free(ptr->key);
            free(ptr->value);
            free(ptr);
            printf("ok\n");
        }
    }
}

//*************SAVE************
void save_cmd(void)
{
    char *filename = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    if (filename == NULL || extra != NULL)
        printf("ERROR: usage: SAVE <filename> \n");
    else
    {
        FILE *f = fopen(filename, "w");
        if (f == NULL)
            printf("ERROR: cannot open '%s'\n", filename);
        else
        {
            node *ptr = head;
            while (ptr != NULL)
            {
                fprintf(f, "%s %s\n", ptr->key, ptr->value);
                ptr = ptr->next;
            }
            fclose(f);
            printf("SAVED\n");
        }
    }
}

//*************LOAD************
void load_cmd(void)
{
    char *filename = strtok(NULL, " ");
    char *extra = strtok(NULL, "");
    if (filename == NULL || extra != NULL)
        printf("ERROR: usage: LOAD <filename> \n");
    else
    {
        FILE *f = fopen(filename, "r");
        if (f == NULL)
            printf("ERROR: cannot open '%s'\n", filename);
        else
        {
            char line[100];
            while (fgets(line, sizeof(line), f) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                char *key = strtok(line, " ");
                char *value = strtok(NULL, "");
                db_set(key, value);
            }
            fclose(f);
            printf("DONE\n");
        }
    }
}
//*************AUTO LOAD************
void aload_cmd(void)
{

    FILE *f = fopen("auto.txt", "r");
    if (f == NULL)
        printf("ERROR: cannot open '%s'\nStarting empty\n", "auto.txt");
    else
    {
        char line[100];
        while (fgets(line, sizeof(line), f) != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
            char *key = strtok(line, " ");
            char *value = strtok(NULL, "");
            db_set(key, value);
        }
        fclose(f);
        printf("LOADED PREVIOUS DATA\n");
    }
}

//*************AUTO SAVE************
void asave_cmd(void)
{

    FILE *f = fopen("auto.txt", "w");
    if (f == NULL)
        printf("ERROR: cannot open '%s'\n", "auto.txt");
    else
    {
        node *ptr = head;
        while (ptr != NULL)
        {
            fprintf(f, "%s %s\n", ptr->key, ptr->value);
            ptr = ptr->next;
        }
        fclose(f);
        printf("SAVED THIS DATA\n");
    }
}

//*************PRINT ALL************
void print_all(void)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        printf("%s = %s\n", ptr->key, ptr->value);
        ptr = ptr->next;
    }
}

//*************FREE ALL************
void free_all(void)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr->key);
        free(ptr->value);
        free(ptr);
        ptr = next;
    }
    head = NULL;
}

int main()
{
    char user[100];
    aload_cmd();
    while (1)
    {
        printf(">>>>> ");
        if (fgets(user, sizeof(user), stdin) == NULL)
            break;
        user[strcspn(user, "\n")] = '\0';
        if (strcmp(user, "EXIT") == 0)
        {
            asave_cmd();
            break;
        }

        char *cmd = strtok(user, " ");
        if (cmd == NULL)
            continue;
        if (strcmp(cmd, "EXIT") == 0)
            printf("if you want to exit just type \"EXIT\"\n");
        else if (strcmp(cmd, "SET") == 0)
        {
            set_cmd();
        }
        else if (strcmp(cmd, "GET") == 0)
        {
            get_cmd();
        }
        else if (strcmp(cmd, "EXISTS") == 0)
        {
            exists_cmd();
        }
        else if (strcmp(cmd, "DEL") == 0)
        {
            del_cmd();
        }
        else if (strcmp(cmd, "SAVE") == 0)
        {
            save_cmd();
        }
        else if (strcmp(cmd, "LOAD") == 0)
        {
            load_cmd();
        }
        else if (strcmp(cmd, "PRINT") == 0)
        {
            print_all();
        }
        else if (strcmp(cmd, "DEL_ALL") == 0)
        {
            free_all();
            PRINTF("ALL DATA DELETED\n");
        }
        else
        {
            printf("Enter a valid command\n");
        }
    }
    free_all();
    return 0;
}