#include "pig_latin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *translate(const char *phrase){
    int num_words = count_words(phrase);

    char *final = calloc(strlen(phrase)+3*num_words, sizeof(char));
    char **words = malloc(strlen(phrase)*sizeof(*words)*num_words);
    for(int i=0; i < num_words; i++){
        words[i] = malloc(strlen(phrase)+1);
    }

    word_copy(words, phrase);

    char *temp = malloc(strlen(phrase)+3);

    for(int i=0; i < num_words; i++){
        translate_word(temp, words[i]);
        
        if(i != num_words-1){
            int len = strlen(final);
            sprintf(final+len, "%s ", temp);
        }else{
            strcat(final, temp);
        }
    }

    free(temp);
    for(int i=0; i < num_words; i++){
        free(words[i]);
    }
    free(words);
    return final;
}

void word_copy(char **w, const char *p){
    int p_index = 0;
    int curr_word = 0;

    while(p[p_index]){
        int index = 0;
        if(p_index != 0) p_index++;
        while(p[p_index] && p[p_index] != ' '){
            w[curr_word][index] = p[p_index];
            index++; p_index++;
        }
        w[curr_word][index] = '\0';
        curr_word++;
    }
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

int count_words(const char *p){
    int word_count = 0;

    while(*p){
        if(*p == ' ') word_count++;
        p++;
    }
    return word_count + 1;
}



