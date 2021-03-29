#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#define SID_LEN	12
#define SR_NUM  10

using namespace std;

typedef struct student
{	char	sid[SID_LEN];
	int		score;
}	studentType;


void saveFile(FILE* , studentType[], int);

int main(void)
{   FILE        *outfile = NULL;
	string      fileName = "DSsample1.dat";
	studentType allS[SR_NUM] = {{"10027113", 60}, {"10127102", 70}, {"10027213", 90}, {"10127256", 80}, {"10227108", 100},
                                {"10227143", 95}, {"10227115", 75}, {"10220107", 88}, {"10227201", 64}, {"10227236", 85}};

    outfile = fopen(fileName.c_str(), "a");
    if (outfile != NULL)
        saveFile(outfile, allS, SR_NUM);
    system("pause");
    return 0;
}	// end main

void saveFile(FILE *fp, studentType dA[], int no)
{   for (int i = 0; i < no; i++)
    {   fwrite(&dA[i], sizeof(dA[i]), 1, fp);
        cout << dA[i].sid << ", " << dA[i].score << endl;
    }
    fclose(fp);
}
