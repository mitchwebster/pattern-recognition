/*    Match Puzzle

This program finds the reference pattern in the candidates which might be
rotated or flipped.
 .
<10/6/14>                  <Mitch Webster>   */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int  Reference;
  int  Candidates[8];
  int  NumCandidates;
  int  Position = 0; //temporary initial value
  int  Load_Reference(char *);
  int  Load_Mem(char *, int *);

  if (argc != 2) {
    printf("usage: ./P1-1 testfile\n");
    exit(1);
  }
  Reference = Load_Reference(argv[1]);
  if (Reference == 0) {
    printf("Invalid Reference pattern.\n");
    exit(1);
   }
  NumCandidates = Load_Mem(argv[1], Candidates);
   if (NumCandidates != 8) {
      printf("testfiles must contain 8 candidates\n");
      exit(1);
   }

   int i;
   int r = Reference; //c1 = ref //76543210
   int c2 = (((r << 4) & 0xFFF0) + ((r >> 12) & 0x000F));
   int c3 = ((r >> 4) & 0x0FFF) + ((r & 0x000F) << 12);
   int c4 = ((r >> 8) & 0x00FF) + ((r << 8) & 0xFF00);

   int r2 = (r & 3) << 14; //r2 = 01234567
   r2 += ((r >> 2) & 3) << 12;
   r2 += ((r >> 4) & 3) << 10;
   r2 += ((r >> 6) & 3) << 8;
   r2 += ((r >> 8) & 3) << 6;
   r2 += ((r >> 10) & 3) << 4;
   r2 += ((r >> 12) & 3) << 2;
   r2 += ((r >> 14) & 3);

   int c5 = ((r2 >> 2) & 0x3FFF) + ((r2 & 3) << 14);
   int c6 = ((r2 >> 10) & 0x3F) + ((r2 << 6) & 0xFFC0);
   int c7 = ((r2 >> 6) & 0x3FF) + ((r2 & 0x3F) << 10);
   int c8 = ((r2 >> 14) & 3) + ((r2 << 2) & 0xFFFC);

   printf("%d\n",r);
   printf("%d\n",c2);
   printf("%d\n",c3);
   printf("%d\n",c4);
 
   printf("Inversed\n%d\n",r2);
   printf("%d\n",c5);
   printf("%d\n",c6);
   printf("%d\n",c7);
   printf("%d\n",c8);

   for (i=0; i < 8; i++) {
       //get the current candidate
       if (Candidates[i] == r){Position = i;break;}
       if (Candidates[i] == c2){Position = i;break;}
       if (Candidates[i] == c3){Position = i;break;}
       if (Candidates[i] == c4){Position = i;break;}
       if (Candidates[i] == c5){Position = i;break;}
       if (Candidates[i] == c6){Position = i;break;}
       if (Candidates[i] == c7){Position = i;break;}
       if (Candidates[i] == c8){Position = i;break;}
   }
   printf("The matching pattern is at position [0-7] %d\n", Position);
   exit(0);
}

/* This routine reads in one integer value from the first line of a named file in the local directory (each line of the file is in the form Addr: integer). The integer is returned. */

int Load_Reference(char *InputFileName) {
  int   Reference, NumVals, Addr, Value;
  FILE  *FP;

  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
    if (NumVals == 2)
      Reference = Value;
    else {
      printf("test file must contain Addr: Value pairs on each line.\n");
      Reference = 0;
    }
    fclose(FP);
    return Reference;
   }
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int  N, Addr, Value, NumVals;
   FILE *FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     fscanf(FP, "%d: %d", &Addr, &Value); // ignore first line
     for (N=0; N < 8; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
     IntArray[N] = Value;
       else
     break;
     }
     fclose(FP);
     return N;
   }
}
