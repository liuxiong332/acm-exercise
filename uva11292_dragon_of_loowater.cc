#include <stdio.h>
#include <algorithm>
/*
	first, sort the headers of dragon
	then, sort the ability value of knight
	the last, iterate over the headers and get the first ability value that greater than or equal the header value. 
*/
const int kMaxValue = 20000;
int header[kMaxValue];
int knight[kMaxValue];


int main()
{
	int n,m;
	while( scanf("%d %d",&n,&m)!=EOF ) {
		if(n==0 && m==0)	break;
		for(int i=0;i<n;++i) {
			scanf("%d",&header[i]);
		}
		for(int i=0;i<m;++i) {
			scanf("%d",&knight[i]);
		}
		std::sort(header,header+n);
		int *  knight_end = knight+m;
		std::sort(knight,knight_end);
		int *  knight_ptr = knight;
		
		int spend = 0;
		int count ;
		for(count=0; count<n && knight_ptr<knight_end; ++count) {
			knight_ptr = std::lower_bound(knight_ptr,knight_end,header[count]);
			if(knight_ptr == knight_end)
				break;		//not found the element greater than or equal the header, break
			spend += *knight_ptr++;
		}
		if(count>=n) {
			printf("%d\n",spend);
		} else {
			printf("Loowater is doomed!\n");
		}
	}
}