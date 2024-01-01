#include "Projsetup.h"



 void mkdir_cd(const char* name) 
{
       mkdir(name,0777);
       chdir(name);
}
void filecreate(char* filename,const char* filecontent)
{
    FILE *fp;
    fp = fopen(filename,"w");
    fprintf(fp, "%s",filecontent);
    fclose(fp);
}

char* projmake(char* projname,char lang)
{
    mkdir_cd(projname,0777); // Make the root dir of the project
    // Determine the lengths of the strings
    char makefile[50];
    size_t filenameLength = strlen(projname);
    size_t extensionLength = 4;  // Assuming ".cpp" or ".h" can be expanded later if i add more langs other than those 2.
    char *cmainFilename = (char *)malloc(filenameLength + extensionLength + 1);  // +1 for the null terminator otherwise we get cut off names and we dont want that.
    char *hFilename = (char *)malloc(filenameLength + extensionLength + 1);
    // Check if memory allocation is successful
    if (cmainFilename == NULL || hFilename == NULL) {
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
    snprintf(makefile,sizeof(makefile),"%sgcc %s -o %s\n%s",makeftop,cmainFilename,projname,makefbot); // idk what a better way to implement this but rn this should do.
    filecreate("Makefile",makefile);
    filecreate("README.md",readme);
    filecreate(".gitignore",gitignore);
    mkdir("build",0777);
    mkdir_cd("src");
    if (lang == 'c')
    {
        filecreate(cmainFilename,cfile);
    }
    else if (lang == 'a')
    {
        filecreate(cmainFilename,cppfile);
    }

    filecreate(hFilename,header);
    free(cmainFilename);
    free(hFilename);
    
    
}


int main(int argc, char *argv[]){
    char projectname[NAMELEN];
    printf("Enter name of project:!\n");
    fgets(projectname, sizeof(projectname), stdin);
    if (projectname[strlen(projectname) - 1] == '\n') {
        projectname[strlen(projectname) - 1] = '\0';
    }
    projmake(projectname,'c');
    



    return 0;
}