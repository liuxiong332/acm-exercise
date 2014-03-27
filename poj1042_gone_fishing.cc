#include <stdio.h>
#include <algorithm>
/*
  the origin problem link is http://poj.org/problem?id=1042
  we first image that the trip is stop in the k lake, then the fishing count is f(k)
  then the all max fishing count is max(f(0),f(1),...,f(n-1)
  
  so we can get the f(k). from lake 0 to lake k-1, the time spent in the road is t0+t1+...+t(k-1), so we first 
  strip that time, the remaining time(hour-t(i)) is all apply to fishing. 
  Now I should not consider the trip time, I only need to pay attention to which lake to fish.
  Obviously, we should choose the max number form the k lakes in the every 5-minute intervals. 
  That is the greedy algorithm. 
  In order to get the max number from the k lakes, we can use the heap structure to get the maximum number.
*/

struct LakeInfo
{
	int fish_count;
	int lake_id;
//	LakeInfo(int count,int id):fish_count(count),lake_id(id)	{}
};
 
typedef bool(*FiSetLessFunctor)(const LakeInfo& first, const LakeInfo& second) ;
bool  FiSetLessThan(const LakeInfo& first, const LakeInfo& second) 
{
	return first.fish_count>second.fish_count || 
		(first.fish_count==second.fish_count&&first.lake_id<second.lake_id);
}

inline int GetLeftChildIndex(int index) 
{
	return 2*index+1;
}
inline int GetRightChildIndex(int index)
{
	return 2*index+2;
}

inline void  MaxHeapify(LakeInfo* info_array, int begin_index, int end_index) 
{
	if(begin_index>=end_index) 
		return ;
	int left_index = GetLeftChildIndex(begin_index);
	int right_index = GetRightChildIndex(begin_index);
	int max_index = begin_index;
	if(left_index<end_index && FiSetLessThan(info_array[left_index],info_array[max_index])) {
		max_index = left_index;
	}
	if(right_index<end_index && FiSetLessThan(info_array[right_index],info_array[max_index])) {
		max_index = right_index;
	}
	if(max_index>begin_index) {
		std::swap( info_array[begin_index], info_array[max_index]);
		MaxHeapify(info_array,max_index, end_index);
	}
}

inline void  MakeHeap(LakeInfo* lake_array,int size)
{
	for(int i=size/2;i>=1;--i) {
		MaxHeapify(lake_array,i-1,size);
	}
}

inline LakeInfo*	GetMaxElement(LakeInfo* lake_array)
{
	return &lake_array[0];
}
inline  void  HeapifyRoot(LakeInfo* lake_array,int size)
{
	MaxHeapify(lake_array,0,size);
}

const static int kMaxLakeCount = 25;
int  kStopTime[kMaxLakeCount];
int  kMaxStopTime[kMaxLakeCount];
int  kTripTime[kMaxLakeCount];

int  kFi[kMaxLakeCount];
int  kDi[kMaxLakeCount];
int  kTi[kMaxLakeCount];

LakeInfo  kHeap[kMaxLakeCount];

int  GetMaxFishInKLake(int lake_count,int time ,int* stop_time)
{
// 	for(int i=0;i<lake_count-1;++i) {
// 		time -= kTi[i]*5;
// 	}
	if(lake_count>=2)
		time -= kTripTime[lake_count-2]*5;
// 	typedef std::set< LakeInfo, FiSetLessFunctor> LakeSet;
// 	typedef LakeSet::iterator	LakeSetIterator;
// 	LakeSet		lake_fi_set(FiSetLessThan);
	int fishing_count = time/5;

	for(int i=0;i<lake_count;++i) {
		kHeap[i].fish_count = kFi[i];
		kHeap[i].lake_id = i;
	}
	MakeHeap(kHeap,lake_count);
// 	for(int i=0;i<lake_count;++i) {
// 		lake_fi_set.insert( LakeInfo(kFi[i],i) );
// 	}
	int fish_num = 0;
// 	for(int i=0;i<lake_count;++i) {
// 		stop_time[i] = 0;
// 	}
	memset(stop_time,0,lake_count*sizeof(int));
	int  current_fish_num, current_lake_id;
	for(int i=0;i<fishing_count;++i) {
//		LakeSetIterator iter = lake_fi_set.begin();
//		current_fish_num = iter->fish_count;
		LakeInfo* max_info = GetMaxElement(kHeap);
		current_fish_num = max_info->fish_count;
		if(current_fish_num<=0) {
			stop_time[0] += (fishing_count-i)*5;
			break;
		}
		current_lake_id = max_info->lake_id;	//iter->lake_id;
		fish_num += current_fish_num;
		stop_time[current_lake_id] += 5;
		int  decrease_num = current_fish_num-kDi[current_lake_id];

		if(decrease_num <= 0) {
			decrease_num = 0;
		}
// 		LakeInfo new_node(decrease_num,iter->lake_id);
// 		lake_fi_set.erase(iter);
// 		lake_fi_set.insert(new_node);
		max_info->fish_count = decrease_num;
		HeapifyRoot(kHeap,lake_count);
	}
	return fish_num;
}

void  GetMaxFish(int n,int hour)
{
	int time = hour*60;
	int fish_num = -1;
	int lake_num = 0;
	int* stop_time = kStopTime;
	int* max_stop_time = kMaxStopTime;
	for(int i=1;i<=n;++i) {
		int current_num = GetMaxFishInKLake(i,time, stop_time);
		if( fish_num<current_num ) {
			lake_num = i;
			fish_num = current_num;
			std::swap(stop_time,max_stop_time);
		}
	}
// 	for(int i=lake_num;i<n;++i) {
// 		max_stop_time[i] = 0;
// 	}
	memset(max_stop_time+lake_num,0, (n-lake_num)*sizeof(int) );
	for(int i=0;i<n-1;++i) {
		printf("%d, ",max_stop_time[i]);
	}
	printf("%d \nNumber of fish expected: %d \n\n",max_stop_time[n-1],fish_num);
}

int main()
{
#ifdef LOCAL
	freopen("data.in","r",stdin);
#endif
	int n;
	while(true) {
		scanf("%d",&n);
		if(n<=0)
			break;
		int hour;
		scanf("%d",&hour);
		for(int i=0;i<n;++i) {
			scanf("%d",&kFi[i]);
		}
		for(int i=0;i<n;++i) {
			scanf("%d",&kDi[i]);
		}
		int trip_time = 0;
		for(int i=0;i<n-1;++i) {
			scanf("%d",&kTi[i]);
			trip_time += kTi[i];
			kTripTime[i] = trip_time;
		}
		GetMaxFish(n,hour);
	}
}