#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_ROWS 5
#define MAX_COLS 7

typedef struct {
    time_t timestamp;
    int counter;
    int numbers[MAX_ROWS][MAX_COLS];
} Record;

int getRecordCount() {
    FILE *recordFile = fopen("record.bin", "rb");
    int recordCount = 0;

    if (recordFile != NULL) {
        fseek(recordFile, 0, SEEK_END);
        long fileSize = ftell(recordFile);
        recordCount = fileSize / (sizeof(time_t) + sizeof(int) + sizeof(int) * MAX_ROWS * MAX_COLS);
        fclose(recordFile);
    }

    return recordCount;
}

Record* readRecords() {
    int recordCount = getRecordCount();
    FILE *recordFile = fopen("record.bin", "rb");

    Record* records = (Record*)malloc(recordCount * sizeof(Record));

    if (recordFile != NULL) {
        for (int i = 0; i < recordCount; i++) {
            fread(&records[i].timestamp, sizeof(time_t), 1, recordFile);
            fread(&records[i].counter, sizeof(int), 1, recordFile);
            for (int j = 0; j < MAX_ROWS; j++) {
                fread(&records[i].numbers[j], sizeof(int), MAX_COLS, recordFile);
            }
        }
        fclose(recordFile);
    }

    return records;
}

void freeRecords(Record* records) {
    free(records);
}

void checkWinning(int lottoNumbers[MAX_ROWS][MAX_COLS], int winningNumbers[3], time_t saleTime) {
    

    for (int i = 0; i < MAX_ROWS; i++) {
        int winningCount = 0; 

        for (int j = 0; j < MAX_COLS; j++) {
            for (int k = 0; k < 3; k++) {
                if (lottoNumbers[i][j] == winningNumbers[k]) {
                    winningCount++; 
                    break; 
                }
            }
        }

        if (winningCount > 0) {
            printf("彩卷 No. %d\n", i + 1);
            printf("售出時間： %s", ctime(&saleTime)); 
            printf("號碼：");
            for (int m = 0; m < MAX_COLS; m++) {
                printf("%d ", lottoNumbers[i][m]);
            }
            printf("\n");
        }
    }
}

void writeRecord(int out[MAX_ROWS][MAX_COLS], int counter) {
    char filename[20];
    sprintf(filename, "lotto[%05d].txt", counter);

    FILE *fptr;
    fptr = fopen(filename, "w");

    if (fptr != NULL) {
        FILE *recordFile = fopen("record.bin", "ab");
        time_t now = time(NULL);

        if (recordFile != NULL) {
            time_t currentTime;
            time(&currentTime);
            fwrite(&currentTime, sizeof(time_t), 1, recordFile);
            fwrite(&counter, sizeof(int), 1, recordFile);

            for (int i = 0; i < MAX_ROWS; i++) {
                for (int j = 0; j < MAX_COLS; j++) {
                    fwrite(&out[i][j], sizeof(int), 1, recordFile);
                }
            }

            fclose(recordFile);

            fprintf(fptr, "========= lotto649 =========\n");
            fprintf(fptr, "========+ No.%05d +========\n", counter);
            fprintf(fptr, "= %s", ctime(&now)); 
            fseek(fptr, -1, SEEK_END); 
            fprintf(fptr, " =\n");

            for (int x = 0; x < MAX_ROWS; x++) {
                fprintf(fptr, "[%1d]:", x + 1);

                for (int y = 0; y < MAX_COLS; y++) {
                    if (out[x][y] > 0) {
                        fprintf(fptr, " %02d", out[x][y]);
                    } else {
                        fprintf(fptr, " __");
                    }
                }

                fprintf(fptr, "\n");
            }
            fprintf(fptr, "========= csie@CGU =========\n");
            fclose(fptr);
            
        } 
    } 
}

void arrayRand(int v[MAX_ROWS][MAX_COLS], int k) {
    srand((unsigned int)time(NULL));

    for (int myRow = 0; myRow < k; myRow++) {
        for (int myColumn = 0; myColumn < MAX_COLS; myColumn++) {
            v[myRow][myColumn] = rand() % 69 + 1;

            for (int idx = 0; idx < myColumn; idx++) {
                if (v[myRow][idx] == v[myRow][myColumn]) {
                    myColumn--; 
                    break;
                }
            }
        }
    }
}

int main() {
    int input;
    int winningNumbers[3]; 

    setenv("TZ", "Asia/Taipei", 1);
    tzset();

    printf("請問您要買幾組樂透彩： ");
    scanf("%d", &input);

    if (input == 0) {
        printf("請輸入中獎號碼(最多三個)： ");
        scanf("%d %d %d", &winningNumbers[0], &winningNumbers[1], &winningNumbers[2]);
        printf("輸入中獎號碼為：%02d %02d %02d\n",winningNumbers[0], winningNumbers[1], winningNumbers[2]);
        printf("以下為中獎彩卷：\n");
        Record* records = readRecords();
        for (int i = 0; i < getRecordCount(); i++) {
            checkWinning(records[i].numbers, winningNumbers, records[i].timestamp); 
        }
        freeRecords(records);
        
    } else if (input >= 1 && input <= 5) {
        
        int target[MAX_ROWS][MAX_COLS] = {0};
        arrayRand(target, input);

        int counter = getRecordCount() + 1;
        writeRecord(target, counter);
    } 

    return 0;
}
