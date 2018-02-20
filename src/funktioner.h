#define MAX_SIZE 100
typedef struct item {
    int varunummer;
    char namn[100];
    float pris;
    float volym;
    char stil[100];
    char typ[100];
    char forpackning[20];
    char land[20];
    char producent[50];
    float alkoholhalt;
} item;

int read_file(item **ptr, int count);
void list_products(item* ptr, int size);
void details(item *ptr, int index);
void str_scan(char *dest, int max_length);
int compare_int(int a, int b);
int compare_str(char a[], char b[]);
void swap(item *a, item *b);
void sort_by_number(item *ptr, int size);
void sort_by_price(item *ptr, int size);
void sort_by_name(item *ptr, int size);
int add_article(item **ptr, int size);
void search_article(item *ptr, int size);
void save_to_file(item *ptr, char *filename, int size);
