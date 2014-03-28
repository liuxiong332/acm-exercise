#include <stdio.h>
#include <algorithm>

/* 
	There are n troops, for i troop, it need Bi minutes to  arrange its work and it will take Ji minutes
   to finish the work. The arrangement of work cannot do synchronously, but the completion of work can do 
   synchronously. The problem is how to arrange the troops to make the time least.
*/

struct SoldierTime
{
	int  b;
	int  j;
};

SoldierTime  soldier_time[1000];

bool  SoldierTimeLess(const SoldierTime& v1, const SoldierTime& v2)
{
	return v1.j >  v2.j;
}

int main()
{
	int N;
	int case_count = 0;
	while( scanf("%d",&N)!=EOF ) {
		if(N == 0) break;
		++case_count;
		for(int i=0;i<N;++i) {
			scanf("%d %d",&soldier_time[i].b, &soldier_time[i].j);
		}
		std::sort(soldier_time,soldier_time+N,SoldierTimeLess);
		int max_time = 0;
		int current_time = 0;
		for(int i=0;i<N;++i) {
			current_time += soldier_time[i].b;
			max_time = std::max( current_time+soldier_time[i].j, max_time);
		}
		printf("Case %d: %d\n",case_count,max_time);
	}
}