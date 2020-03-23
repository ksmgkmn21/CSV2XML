#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAXCHAR 1000
char title[300][300]; // title array for dinamic program
int title_count = 0; // count for title
int id = 0; // row id 
/////////////////////////////////////////////////////////////////////////////////////////
void ToLower(char *str) /// lower function
{
    while(*str != '\0')
    {
        if(*str >=65 && *str<=90)
        {
            *str = *str + 32; // It fails in the below assignment
        }
        str++;
    }
}
////////////////////////////////////////////////////////////////////////////////////
char *replaceWord(char *orig, char *rep, char *with) {
    char *result;  //// the return string
    char *ins;    ////the next insert point
    char *tmp;    //// varies
    int len_rep;                              //length of rep (the string to remove)
    int len_with; ////length of with (the string to replace rep with)
    int len_front; //// distance between rep and end of last rep
    int count;    //// number of replacements

    // sanity checks and initialization///
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed ////
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc,  char *argv[]) {
    
 
  // error checks
    if(argc <= 6){ // missing input control

        printf("-You have entered the missing entry\n");
        return 0;
    }
    else if(argc > 8){

        printf("-More entries entered\n");
        return 0;
    }
    else{

        if(!(strstr(argv[1],".csv"))) //extension control
        {
            printf("-Enter the input extension correctly\n");
            return 5;
        }else if (!(strstr(argv[2],".xml")))
        {
            printf("-Enter the output extension correctly\n");
            return 5;
        }

        if(strcmp(argv[1],replaceWord(argv[2],".xml",".csv"))) //input and output file name kontrol.
        {  
            printf("-Please enter input and output file same.Should xml and csv file name be same \n");
            return 0;
        }

        if(atoi(argv[4]) > 3 || strcmp(argv[3],"separator") != 0) // true separator control
        {
            printf("-Wrong separator please enter true.\n  >separator 1 : comma \n  >separator 2 : tab\n  >separator 3 : semicolon\n");
            return 0;
        }
        else if(atoi(argv[6]) > 3 || strcmp(argv[5],"opsys") != 0) // true opsys control
        {
            printf("-Wrong opsys please enter true.\n  >opsys 1 : wındows\n  >opsys 2 : lınux\n  >opsys 3 : macos\n");
            return 0;
        }
    }
    ///fnısh error control
    if(argc == 8){
        if(strcmp(argv[7],"-h") == 0){
             printf("  **Separator**\n   >separator 1 : comma \n   >separator 2 : tab\n   >separator 3 : semicolon\n");
             printf("  **Opsys**\n   >opsys 1 : wındows\n   >opsys 2 : lınux\n   >opsys 3 : macos\n");
        }
        else{
            printf("-Please enter true --> -h \n");
            return 0;
        }
    }

    
    FILE *fb = fopen(argv[2],"w"); // create a XML file
    FILE *fp; // for read csv file
    char str[MAXCHAR];
    fp = fopen(argv[1], "r");
    if (fp == NULL){ // file exist control
        printf("Could not open file %s",argv[1]);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL){ // line-by-line reading process
        
        char *separator  = malloc(10);
        char *result     = malloc(50);
        char *opsys      = malloc(10);
        if(*argv[4] == *("1")) //the process of assigning separators according to the arguments entered by the user
            { 
                
                result = replaceWord(str,",,",",*,");
                strcpy(separator,  ",");
            }
         else if(*argv[4] == *("2"))
            {
                result = replaceWord(str,"\t\t","\t*\t");
                strcpy(separator,  " ");
            }
         else 
            {
                
                result = replaceWord(str,";;",";*;");
                strcpy(separator,  ";");
            }

        if(*argv[6] == *("1")) //the process of assigning opsys according to the arguments entered by the user
            {
               strcpy(opsys,  "\r\n");
            }
        else if(*argv[6] == *("2"))
            {  
               strcpy(opsys,  "\n");
            }
        else 
            {
                strcpy(separator,  "\r");
            }
        if(id == 1){
                fprintf ( fb,"<?xml version=\"1.0\" encoding=\"utf-8\"?>%s",opsys);
                fprintf (fb,"<");fprintf (fb,"%s",strtok(argv[2],"."));fprintf (fb,">%s",opsys);
            }
        if(id == 0 ) // I assign headers to an array to be dynamic, then I return the header array when I print to the xml file with for
            {   
                
                char *title_ptr = strtok(str,",");
                while(title_ptr != NULL){
                    
                    strcpy(title[title_count],title_ptr);
                    title_ptr = strtok(NULL,",");
                    ToLower(title[title_count]);
                    strcpy(title[title_count],replaceWord(title[title_count]," ","_"));
                    strcpy(title[title_count],replaceWord(title[title_count],opsys,""));
                    title_count++;
                }
            }
        else{
             
             
            fprintf (fb,"   <");fprintf (fb,"row id=\"%d\"",id);fprintf (fb,">%s",opsys);
            char *ptr = strtok(result,separator);
            for(int i = 0; i < title_count; i++){ // returning title sequence
                
                
                if(*ptr != *("*") && *ptr != *opsys){ // checking which label is empty
                    ptr = replaceWord(ptr,opsys,"");
                    fprintf (fb,"     <");fprintf (fb,"%s",title[i]);fprintf (fb,">"); //print portion to xml file
                    fprintf (fb,"%s",ptr);fprintf (fb,"</");fprintf (fb,"%s",title[i]);fprintf (fb,">%s",opsys);
                }else
                {
                    fprintf (fb,"     <");fprintf (fb,"%s/",title[i]);fprintf (fb,">%s",opsys);
                     
                }
                ptr = strtok(NULL,separator);
               
            }
            
            fprintf (fb,"   </row>%s",opsys);
        }
         id++;
    }
    fclose(fp);
    fprintf (fb,"</");fprintf (fb,"%s",strtok(argv[2],"."));fprintf (fb,">"); //where Root tag is finished
    printf("      **** File have been translated into an xml file ****\n");
    return 0;
}
