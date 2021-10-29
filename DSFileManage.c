#include <conio.h>
#include <string.h>
#define USER_MAX 20
// This system can store up to number of users
typedef struct
{
    char name[15];
    char password[30];
} User;
// definition of the structure of a user storing

User list[USER_MAX];
// define a global array, type User, size is USER_MAX

char *filename = "user.txt";
// user.txt need to create a file in your application directory
// Log function
User login()
{
    char name[15];
    char password[30];
    User lg;
    printf("\n\n__ USER LOGIN __ \n\n");
    printf("Name(Enter without space): ");
    scanf("%s", name);
    strcpy(lg.name, name);
    printf("Password: ");
    int p = 0;
    do
    {
        password[p] = getch();
        if (password[p] != '\r')
        {
            printf("*");
        }
        p++;
    } while (password[p - 1] != '\r');
    password[p - 1] = '\0';
    // scanf("%s", password);
    strcpy(lg.password, password);
    return lg;
}

// write txt file, there is a row for each user
void writeToFile(User u)
{
    FILE *fw = fopen(filename, "a+");
    fprintf(fw, u.name);
    fprintf(fw, "\t");
    fprintf(fw, u.password);
    fprintf(fw, "\n");
}

// determine whether the user exists
int exist(User u)
{
    int i;
    for (i = 0; i < USER_MAX; i++)
    {
        if (0 == strcmp(list[i].name, u.name) && 0 == strcmp(list[i].password, u.password))
        {
            return 1;
        }
    }
    return -1;
}

//registered user
void registerUser()
{
    char name[15];
    char password[30];
    User user;
    int i;

    printf("\n\n__ NEW USER REGISTRATION __\n\n");
    printf("Enter name(without space):  ");
    scanf("%s", name);
    strcpy(user.name, name);

    // determine whether there has been a registered user
    for (i = 0; i < USER_MAX; i++)
    {
        if (0 == strcmp(list[i].name, name))
        {
            printf("USER ALREADY EXIST");
            return;
        }
    }

    printf("Create password:  ");
    scanf("%s", password);
    strcpy(user.password, password);
    writeToFile(user);
    exit(0);
}
int menu()
{
    int choice;
    printf("\n----WELCOME TO X----\n\n");
    printf("* Enter '1' to login\n");
    printf("* New User? Enter '2' to register\n");
    printf("* Enter '3' to Exit\n\n");
    printf("Enter your choice:");
    scanf("%d", &choice);
    return choice;
}
int main()
{
    User test[USER_MAX];
    FILE *fp = fopen(filename, "r");
    int i;
    User u;
    if (NULL == fp)
    {
        printf("FILE NOT FOUND");
        return -1;
    }
    for (i = 0; i < USER_MAX; i++)
    {
        char uname[15];
        char upassword[30];
        fscanf(fp, "%s%s", uname, upassword);

        strcpy(list[i].name, uname);
        strcpy(list[i].password, upassword);
    }

    while (1)
    {
        int choice = menu();
        switch (choice)
        {
        case 1:
            system("cls");
            u = login();
            if (1 == exist(u))
            {
                printf("\n\nLOGIN SUCCESSFUL! \n");
                exit(0);
            }
            else
            {
                printf("\nINVALID USERNAME OR PASSWORD!");
            }
            break;

        case 2: system("cls");
            registerUser();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("\n--INVALID INPUT!--\n");
            exit(0);
            break;
        }
    }
}
