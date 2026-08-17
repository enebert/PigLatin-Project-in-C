#include "pig_latin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *translate(const char *phrase){
    size_t allocated = 10;
    size_t used = 0;
    
    char *result = calloc(allocated, sizeof(char));
    char *result_start = result;
    char *temp = calloc(strlen(phrase)+3, sizeof(char));
    char *temp_start = temp;
    char *transform = calloc(strlen(phrase)+3, sizeof(char));


    while(*phrase){
        int num_letters = 1;
        
        while(*phrase != ' ' && *phrase){
            *temp = *phrase;
            temp++; phrase++; num_letters++;
        }

        *temp = '\0';

        translate_word(transform, temp_start);

        if(allocated < used + num_letters + 3){
            char *p = realloc(result_start, (allocated+num_letters+5)*sizeof(char));
            if(p!=NULL){
                result_start = p;
                result = result_start + used;
                allocated += num_letters + 5;
            }
        }

        if(*phrase){
            sprintf(result, "%s ", transform);
            result += num_letters + 3;
            temp = temp_start;
            phrase++;
        }else{
            sprintf(result, "%s", transform);
        }

        used += num_letters + 2;
    }

    free(temp_start); free(transform);
    return result_start;
}

void translate_word(char *buffer, const char* src){
    switch(*src){
        case 'x':
            if(src[1]=='r'){
                sprintf(buffer, "%say", src);
            }else{
                cons_segment(buffer, src);
            }

            break;
            
        case 'y':
            if(src[1]=='t'){
                sprintf(buffer, "%say", src);
            }else{
                sprintf(buffer, "%syay", src+1);
            }

            break;
            
        default:
            if(is_vowel(src)){
                sprintf(buffer, "%say", src);
            }else{
                cons_segment(buffer, src);
            }
    }
}

bool is_vowel(const char *s){
    if(*s && (*s=='a' || *s=='e' || *s=='i' || *s=='o' || *s=='u')) return true;
    return false;
}

void cons_segment(char *buffer, const char* p){
    char *prefix = calloc(strlen(p), sizeof(char));
    int count = 0;
 
    while(!is_vowel(p) && *p!='y'){
        prefix[count] = *p;
        if(*p=='q' && p[1]=='u'){
            count++; p++;
            prefix[count] = *p;
         }
         count++; p++;
      }
 
      prefix[count] = '\0';
 
      sprintf(buffer, "%s%say", p, prefix);
      free(prefix);
}


