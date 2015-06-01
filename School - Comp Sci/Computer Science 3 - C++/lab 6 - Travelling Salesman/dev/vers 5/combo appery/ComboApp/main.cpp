//#include <stdio.h>
//#include <stdlib.h>
//#include <fstream>
//
//#define ARRSIZE(arr)   (sizeof(arr)/sizeof(*(arr)))
//
//using namespace std;
//
//int main()
//{
//    // const char values[]= {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
//	const char values[]= {'a','b','c','d','e','f','g','h','i','j','k','l'};
//    char * buffer=NULL;
//    int * stack=NULL;
//    int combinationLength=-1;
//    int valuesNumber=-1;
//    int curPos=0;
//	fstream myFile;
//
//	myFile.open ("9.txt", ios_base::out);
//
//    fprintf(stderr, "%s", "Length of a combination: ");
//    if(scanf("%d", &combinationLength)!=1 || combinationLength<1)
//    {
//        fputs("Invalid value.\n",stderr);
//        return 1;
//    }
//    fprintf(stderr, "%s (%lu max): ", "Possible digit values",(long unsigned)ARRSIZE(values));
//    if(scanf("%d", &valuesNumber)!=1 || valuesNumber<1 || (size_t)valuesNumber>ARRSIZE(values))
//    {
//        fputs("Invalid value.\n", stderr);
//        return 1;
//    }
//    buffer=(char *)calloc(combinationLength + 1, sizeof(char));
//	//buffer=(char *)malloc(combinationLength);
//    stack=(int *)calloc(combinationLength*sizeof(*stack), sizeof(int));
//	//stack=(int *)malloc(combinationLength*sizeof(*stack));
//    if(buffer==NULL || stack==NULL)
//    {
//        fputs("Cannot allocate memory.\n", stderr);
//        free(buffer);
//        free(stack);
//        return 2;
//    }
//    /* Combinations generator */
//    for(;;)
//    {
//        if(stack[curPos]==valuesNumber) //this if takes us back to the beginning so we can start a new combination
//        {
//            /* ...get back to the previous position, if we finished exit */
//            if(--curPos==-1)
//                break;
//            /* Repeat this check */
//            continue;
//        }
//        buffer[curPos]=values[stack[curPos]]; 
//		//buffer[curPos]=values[curPos]; 
//
//        /* If we are in the most inner fake-cycle write the combination */
//        if(curPos==combinationLength-1)
//			{
//				buffer[curPos + 1] = '\0';
//			    puts(buffer);
//				buffer[curPos + 1] = '\n';
//				myFile.write(buffer, curPos + 2);
//			}
//        
//        stack[curPos]++;
//        /* If we aren't on the last position, start working on the next one */
//        if(curPos<combinationLength-1)
//        {
//            curPos++;
//            stack[curPos]=0;
//        }
//    }
//    /* Cleanup */
//    free(buffer);
//    free(stack);
//    return 0;    
//}