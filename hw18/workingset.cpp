#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
/*
 n is the array size, w is the window size and pages is the list
 of pages.
*/

void workingset(int n, int w, int pages[])
{
  /* DUMMY SAMPLE CODE, REMOVE! */
  /* This print shows how to compute the loop bounds. */
  //printf("Do from %d to %d\n",w-1,n-1);

  /* This print confirms the parameter pass, it shows you how to line
    things up with the headers.*/
    /* This is the header line as shown in the homework assignment */
  printf("Time \t Size \t Set\n");

  for (int time=w-1;time<n-1;time++)
  {
    vector<int> set;
    printf("%d \t %d \t ",time,w);
    for (int time2 = time - w + 1; time2 < time; time2++)
	{
    		if (std::count(set.begin(), set.end(), pages[time2]))
        	{
			//int i;
		}
		else{set.push_back(pages[time2]);
			}
    	}

    for(int i=0; i<set.size(); ++i)
    std::cout << set[i] << ' ';
	printf("\n");
  }
};

int main()
{
  int list1[] = {1,2,3,3,2,3,2,1,2,1,2,1,3,1,3,1,2,3,1};
  int list2[] = {1,2,3,3,4,4,5,3,3,2,1,2,1,2,3,4,5,3,2,4,2,4,2,2};
  /* notice the tricky way of getting the number of integers in the array */
  workingset(sizeof(list1)/sizeof(int),3,list1);
  workingset(sizeof(list2)/sizeof(int),4,list2);
  return 0;
};
