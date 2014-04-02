#include <stdio.h>
#include <algorithm>
#include <iostream>
/* 
	there are n people, every people has some wealth, and they want to give some wealth to others to make 
	every people have the same wealth. Your task is to find a method to spread the wealth and make the count 
	of wealth spread least .  

	Analysis: 
		First, I set the wealth of i-th people is Xi, the spread wealth of the i-th people to the (i+1)-th
	people is Yi, set the wealth after every people spread is P, Obviously, P = (X1+X2+...Xn)/n.
		Then, for every i-th people, Xi+Y(i-1)-Yi = P, namely Y(i-1)-Yi = P-Xi. If I can know the value Of Yn, 
	then all the Yi is known, Yi = Yn - i*n + X1+X2+...Xi
		 The task is make the G=|Y1|+|Y2|+...+|Yn| least, on the base of above analysis we can get 
	G= |Yn-n+X1| + |Yn-2n+X1+X2|+...+|Yn|, next, we can get the least value by the math method.
		For |X-a1|+|X-a2|+...|X-an|, when X = a(n+1/2 can get the least value.
*/

int main()
{
	int n;
	long long * p;
	long long sum;
	while( scanf("%d",&n)!=EOF ) {
		p = new long long[n];
		int d;
		sum = 0;
		for(int i=0;i<n;++i) {
			scanf("%d",&d);
			sum += d;
			p[i] = sum;
		}
		sum /= n;
		for(int i=0;i<n;++i) {
			p[i] = (i+1)*sum - p[i];		//Yi = Yn - (i+1)*n + X1+X2+...Xi
		}
		std::nth_element(p,p+n/2,p+n);
		long long Y = p[n/2];
		long long val;
		sum = 0;
		for(int i=0;i<n;++i) {
			val = Y-p[i];
			val = val>0?val:-val;
			sum += val;
		}
//		printf("%d\n",sum);
		std::cout<<sum<<std::endl;
		delete p;
	}
}
