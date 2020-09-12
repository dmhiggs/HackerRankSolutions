#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return *(*(*(document + n - 1) + m - 1) + k - 1);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return *(*(document + m - 1) + k - 1);
}

char*** kth_paragraph(char**** document, int k) {
    return *(document + k - 1);
}

char**** get_document(char* text) {
    // char         letter                      'L'
    // char *       word[]-arr char             "Learning"
    // char **      sentence[][]-arr word       {"Learning", "C", "is", "fun"}
    // char ***     paragraph[][][]-arr sent    {{"Learning", "C", "is", "fun"}}
    // char ****    document[][][][]-arr para   {{{"Learning", "C", "is", "fun"}}, {{"Learning", "pointers", "is", "more", "fun"}, {"It", "is", "good", "to", "have", "pointers"}}};

    // words separated by " "
        // last word in sent does not end with " "
    // sents separated by "."
    // paras separated by "\n"
        // last para does not end with "\n"
    // only [a-z][A-Z] in words
    // max 1000 chars in document
    // max 5 paras in document

    char**** doc;
    int paras = 0;
    int sents = 0;
    int words = 0;

    //allocate?
    doc = malloc(5 * sizeof(char***)); //5 max paras
    for (int i = 0; i < 5; i++) {
        doc[i] = malloc(1 * sizeof (char **)); //1 sentence in para
        doc[i][0] = malloc(1 * sizeof(char *)); //1 word in sentence
        doc[i][0][0] = malloc(1000 * sizeof(char)); //1000 chars in word
    }
    

    // tokenize into words based on non letter words -- ' ', '.', '\n'
        //assuming that Every sentence ends with '.'
    int letters = 0;
    char *c = text;
    while (*c != '\0') {
        switch (*c) {
        case '\n':
            //new paragraph
            paras++;
            sents = 0;
            words=0;
            letters=0;
            break;
        case '.':
            //new sentence
            //new word
            doc[paras][sents][words] = realloc(doc[paras][sents][words], strlen(doc[paras][sents][words]) * sizeof(char) + 1);
            sents++;
            words=0;
            doc[paras] = realloc(doc[paras], (sents + 1) * sizeof(char **) + 1);
            doc[paras][sents] = malloc(1 * sizeof(char *));// realloc(doc[paras][sents], (words + 1) * sizeof(char *));
            doc[paras][sents][words] = malloc(1000 * sizeof(char));
            letters=0;
            break;
        case ' ':
            if (letters == 0 && words == 0) { //space after period
                break;
            }
            //new word
            doc[paras][sents][words] = realloc(doc[paras][sents][words], strlen(doc[paras][sents][words]) * sizeof(char) + 1);
            words++;
            doc[paras][sents] = realloc(doc[paras][sents], (words + 1) * sizeof(char *) + 1);
            doc[paras][sents][words] = malloc(1000 * sizeof(char));
            letters=0;
            break;
        default:
            if ((*c > 'Z' && *c < 'a') || *c > 'z' || *c < 'A') {
                break;
            }
            //add letter to word...
            // printf("%c", *c);
            *(*(*(*(doc + paras) + sents) + words) + letters) = *c;
            letters++;
            break;
        }
        c++;
    }

    return doc;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}