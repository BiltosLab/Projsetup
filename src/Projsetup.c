#include "Projsetup.h"

void mkdir_cd(const char *name)
{
    mkdir(name, 0777);
    chdir(name);
}
void filecreate(char *filename, const char *filecontent)
{
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, "%s", filecontent);
    fclose(fp);
}

char *projmake(char *projname, char lang)
{   char makefbot[50]; 
    mkdir_cd(projname); // Make the root dir of the project
    int result = system("git init");
    sprintf(makefbot,"clean:\n\trm -rf ./build/*\n\ttouch ./build/.keep\n"); // Unfortunetly i had to do this instead of making it a const char like the rest due to TAB character werid issues casuing the makefile to fail for whatever reason.
    // Determine the lengths of the strings
    //int sizeofmake = sizeof(makeftop)+sizeof(makefbot);
    char makefile[300];
    size_t filenameLength = strlen(projname);
    size_t extensionLength = 4;                                                 // Assuming ".cpp" or ".h" can be expanded later if i add more langs other than those 2.
    char *cmainFilename = (char *)malloc(filenameLength + extensionLength + 1); // +1 for the null terminator otherwise we get cut off names and we dont want that.
    char *hFilename = (char *)malloc(filenameLength + extensionLength + 1);
    // Check if memory allocation is successful
    if (cmainFilename == NULL || hFilename == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }

    strcpy(cmainFilename, projname);
    // prob need a string here to represent language choice but since we're on 2 rn it should be fine
    if (lang == 'c') // self explanatory (if u choose c we will use c extension and so on :D)
    {
        strcat(cmainFilename, cext);
    }
    else if (lang == 'a')
    {
        strcat(cmainFilename, cppext);
    }

    strcpy(hFilename, projname);
    strcat(hFilename, headerext);
    if (lang == 'c')
    {
        snprintf(makefile, sizeof(makefile), "%s\n\t$(CC) ./src/%s -o ./build/%s\n%s", makeftopc, cmainFilename, projname, makefbot); // idk what a better way to implement this but rn this should do.
    }
    else if (lang == 'a')
    {
        snprintf(makefile, sizeof(makefile), "%s\n\t$(CC) ./src/%s -o ./build/%s\n", makeftopcpp, cmainFilename, projname, makefbot); // idk what a better way to implement this but rn this should do.
    }
    filecreate("Makefile", makefile);
    filecreate("README.md", readme);
    filecreate(".gitignore", gitignore);
    mkdir_cd("build");
    filecreate(".keep","");
    chdir("..");
    mkdir_cd("src");
    if (lang == 'c')
    {
        filecreate(cmainFilename, cfile);
    }
    else if (lang == 'a')
    {
        filecreate(cmainFilename, cppfile);
    }

    filecreate(hFilename, header);
    free(cmainFilename);
    free(hFilename);

    if (result == 0) {
        printf("Success! everything should be setup now\n");
    } else {
        printf("Git init failed make sure you have git installed (command exit code %d).\n", result);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage Projsetup <lang choice> eg Projsetup c | Projsetup cpp | -v for version");
        return 0;
    }
    if (argc == 2 && strcmp("-v",argv[1]) ==0)
        {
            printf("Projsetup Version %f\n",VERSION);
            return 0;
        }
    char projectname[NAMELEN];
    printf("Enter name of project:!\n");
    fgets(projectname, sizeof(projectname), stdin);
    if (projectname[strlen(projectname) - 1] == '\n')
    {
        projectname[strlen(projectname) - 1] = '\0';
    }
       if (argc == 2){
        if (strcmp("c",argv[1]) ==0)
        {
            projmake(projectname, 'c');
        }
        else if (strcmp("cpp",argv[1]) ==0)
        {
            projmake(projectname, 'a');
        }
        else
        {
            printf("Error,Usage Projsetup <lang choice> eg Projsetup c | Projsetup cpp | -v for version");
        }
        
        
    }

    return 0;
}