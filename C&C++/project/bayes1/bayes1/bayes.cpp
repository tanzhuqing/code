//与其他文件无关


#include<stdio.h>
#include<math.h>

#define pi 3.14159
#define p(x,t) exp(-(x-t)*(x-t)/20)/sqrt(20*pi)


void decision(){
  int i,j,type,m,n,flag,state[5],index;
  float xx,a[5][5],p[5],e[5],sum,decision;

  printf("####  Welcome to the Decision_System  ####"\n);
  printf("type of the problem,max(key ?0?) or min(key ?1?)  ");
  scanf("%d ",&type);
  printf("type of the decision,without data(key ?0?) or with data(key?1?)  ");
  scanf("%d", &flag);
  printf("number of the actions ");
  scanf("%d",&m);
  printf("number of the nature states   ");
  scanf("%d",&n);
  for(j=0;j<n;j++){
	printf("t%d",j+1);
  }	
  printf(" ");
  for(i=0;i<m;i++){
	printf("A%d ",i+1);
	for(j=0;j<n;j++){
	scanf("%f",&a[i][j]);
	}
  }

  printf("probability of the natural states = ?");
  for(j=0;j<n;j++){
	scanf("%f",&p[j]);
  }
  if(flag)
  {
		printf("given data = ?  ");
		scanf("%f",&xx);
		printf("states of nature = ?");
		for(j=0;j<n;j++){
		  scanf("%d",&state[j]);
		}
		sum = 0;
		for(j=0;j<n;j++){
			sum += p[j]*p(xx,state[j]);
		}
		for(j=0;j<n;j++){
			p[j] = p[j]*p(xx,state[j])/sum;
		}
  }
		for(i=0;i<m;i++)
		{
			sum = 0;
			for(j=0;j<n;j++)
			{
				sum+=p[j]*a[i][j];	
			}
			e[i] = sum;
		}

		decision = e[0];
		index = 1;
		if(type == 0){
			for(i=1;i<m;i++){
				if(decision<e[i]){
					decision = e[i];
					index = i+1;
				}
		
			}
		}
		else{
			for(i=0;i<m;i++){
				if(decision >e[i]){
					decision = e[i];
					index = i+1;
				}
			}
	      }
  
  printf("***********************");
  printf("Results:");
  printf("******************");
  printf("expexted loss for each course of action based on prior distribution ");
  for(i=0;i<m;i++){
	printf("%f",e[i]);
  }
  printf("The optimum expected loss is %f   ",decision);
  printf("choose action A(%d)",index);


  return;

}


void main(){

clrscr();
decision();
getch();
}