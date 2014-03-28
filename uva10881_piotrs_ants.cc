#include <stdio.h>
#include <algorithm>


/* First, we consider the turning, when the ants collide, they will turn their direction and the speed 
   is not changed,  so if we don't make a difference with each ants, their collision will not take effect,
   so we can get the position of all the ants.
   Second, the relative position of the ants is not change. you can see, if the ant trying to get forward to 
   exceed its front ant, he will collide and go back to the origin position. So we can get the relation position.
*/
enum { LEFT, RIGHT };
struct Ant
{
	enum State { LEFT,	RIGHT,	TURNING,	LEFT_FELL_OFF,	RIGHT_FELL_OFF};
	int pos;
	State  state;
	int	  relative_pos;
};

int AntCompare(const void* first, const void* second)
{
	Ant* ant1 = *(Ant**)first;
	Ant* ant2 = *(Ant**)second;
	return ant1->pos-ant2->pos;
}

int AntStateCompare(const void* first, const void* second)
{
	Ant* ant1 = *(Ant**)first;
	Ant* ant2 = *(Ant**)second;
// 	if(ant1->state == Ant::LEFT_FELL_OFF || ant2->state == Ant::RIGHT_FELL_OFF)	return -1;
// 	if(ant1->state == Ant::RIGHT_FELL_OFF || ant2->state == Ant::LEFT_FELL_OFF)	return 1;
	int  diff = ant1->pos - ant2->pos;
	if( diff == 0 ) {
		ant1->state = ant2->state = Ant::TURNING;
		return 0;
	}
	return diff;
}

int main()
{
#ifdef LOCAL
	freopen("data.in","r",stdin);
#endif
	typedef Ant*  PAnt;
	int N,L,T,n;
	Ant*  ants;
	char   ch_state;
	scanf("%d",&N);
	Ant* * sort_ptr;			//this array for sort
	for(int i=1;i<=N;++i) {
		scanf("%d %d %d",&L,&T,&n);
		ants = new Ant[n];
		sort_ptr = new PAnt[n];
		for(int j=0;j<n;++j) {
			scanf("%d %c",&ants[j].pos,&ch_state);
			if(ch_state == 'L')		ants[j].state = Ant::LEFT;
			else  ants[j].state = Ant::RIGHT;
			sort_ptr[j] = &ants[j];
		}
		qsort(sort_ptr,n,sizeof(PAnt),AntCompare);
		for(int i=0;i<n;++i) {
			sort_ptr[i]->relative_pos = i;		//set the relative pos for every ant
			if(ants[i].state == LEFT) {
				if( (ants[i].pos -= T) < 0)
					ants[i].state = Ant::LEFT_FELL_OFF;
			} else {
				if( (ants[i].pos += T) > L) 
					ants[i].state = Ant::RIGHT_FELL_OFF;	//compute the ant's position after T second
			}
		}
		qsort(sort_ptr,n,sizeof(PAnt),AntStateCompare);
		printf("Case #%d:\n",i);
		Ant* ant_ite;
		for(int i=0;i<n;++i) {
			ant_ite = sort_ptr[ ants[i].relative_pos ];
			switch(ant_ite->state) {
			case Ant::LEFT:		printf("%d L\n",ant_ite->pos);	break;
			case Ant::RIGHT:	printf("%d R\n",ant_ite->pos);	break;
			case Ant::TURNING:	printf("%d Turning\n",ant_ite->pos);	break;
			case Ant::LEFT_FELL_OFF:
			case Ant::RIGHT_FELL_OFF:	printf("Fell off\n");	break;
			}
		}
		printf("\n");
		delete  ants;
		delete sort_ptr;
	}
}