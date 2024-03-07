#include <stdio.h>

int main() {
    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1, 1.2, 1.3};
    FILE* fp;
    int arr_read_a[3];
    char arr_read_b[4];
    float arr_read_c[3];
    
    fp = fopen("a.bin", "wb+");

    fwrite(a, sizeof(int), 3, fp);
    fwrite(b, sizeof(char), 4, fp);
    fwrite(c, sizeof(float), 3, fp);

    fseek(fp, 0, SEEK_SET);

    fread(arr_read_a, sizeof(int), 3, fp);
    printf("%d, %d, %d\n", arr_read_a[0], arr_read_a[1], arr_read_a[2]);

    fread(arr_read_b, sizeof(char), 4, fp);
    printf("%s\n", arr_read_b);

    fread(arr_read_c, sizeof(float), 3, fp);
    printf("%f, %f, %f\n", arr_read_c[0], arr_read_c[1], arr_read_c[2]);

    fclose(fp);
    
    return 0;
}
