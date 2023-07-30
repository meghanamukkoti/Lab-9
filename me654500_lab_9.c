#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct RecordType record;
    char status;
};

struct LinkedList
{
    struct HashType hash;
    struct LinkedList *next;
};

// Compute the hash function
int hash(int x)
{
    return x % (31/2);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

    printf("Hash Table Records:\n");
	for (i=0;i<hashSz;i++)
	{
        struct LinkedList *temp = pHashArray + i;
        if (temp->hash.status == 'f')
        {
            printf("Index %d: \n", i);
            while (temp != NULL)
            {
                printf("\tID: %d \tName: %c \tOrder: %d\n", temp->hash.record.id, temp->hash.record.name, temp->hash.record.order);
                temp = temp->next;
            }
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

    struct LinkedList *arr = malloc(sizeof(struct LinkedList) * recordSz);
    int index;

    for (int i=0; i<recordSz; i++)
    {
        index = hash(pRecords[i].id);

        if (arr[index].hash.status != 'f')
        {
            arr[index].hash.record = pRecords[i];
            arr[index].hash.status = 'f';
            arr[index].next = NULL;
        }

        else
        {
            struct LinkedList *newNode = malloc(sizeof(struct LinkedList));

            newNode->hash.record = pRecords[i];
            newNode->hash.status = 'f';

            newNode->next = arr[index].next;
            arr[index].next = newNode;
        }
    }

    displayRecordsInHash(arr, recordSz);
}