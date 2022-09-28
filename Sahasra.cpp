//Sameer Mahajan
//101903686
//support for big Int in C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sahasra.h"

static void sahasra_adder(const char* sahasra1, const char* sahasra2, char* res);
static char* sahasra_differ(const char* sahasra1, const char* sahasra2);
static void sahasra_multy(const char* sahasra1, const char* sahasra2, char* res);
static char* max(char* sum, char* curr);
//static char* sahasra_multiply_by10(const char* sahasra2, int diff);
static void merge(char **arr, int l, int m, int r);
static int isZero(const char* sahasra);
static char* removeLeadZero(char* sahasra);	
//1725
static char* removeLeadZero(char* res){

	int nonz = 0, newlen =0,i = 0;
	for(nonz = 0; nonz < strlen(res); nonz++){
		if(res[nonz] != 48)
			break;	
	}
	//printf("NONZ == %d\n",nonz);
	if(nonz == 0)
		return res;
	newlen = strlen(res) - nonz;
	for(i = 0; i < newlen; i++)
		res[i] = res[i+nonz];
	//res = (char*)realloc(res,sizeof(char)*(newlen+1)); //6474
	res[i] = '\0';
	if(res[0] == '\0'){
		free(res);
		res = (char*)calloc(2,sizeof(char));
		res[0] = 48;
		res[1] = '\0';	
	}
	return res;

}
//8379746
static void sahasra_adder(const char* sahasra1, const char* sahasra2, char* res){
	//printf("Reached sahasra_adder\n");
	int l1 = strlen(sahasra1)-1;
	int l2 = strlen(sahasra2)-1;
	int sum = 0, carry = 0,k = l1+1;
	//printf("%d %d %d\n",l1,l2,k);
	for(int i = 0; i <= k;i++)
		res[i] = '0';
	while(l2>=0){
		sum = sahasra1[l1] + sahasra2[l2] + carry - 96;
		res[k] = 48 + sum%10;
		carry = sum/10;
		--l1;--l2;--k;		
	}
	while(l1>=0){
		sum = sahasra1[l1]+carry-48;
		res[k] = 48 + sum%10;
		carry = sum/10;
		--l1;--k;		
	}
	if(carry){
		res[k] = 48 + carry;
	}
	
}
char* sahasra_add(const char* sahasra1, const char* sahasra2){
	int bigger = sahasra_compare(sahasra1,sahasra2);
	//printf("Found biggger\n");
	if(bigger == -1){
		char* res = (char*)calloc(strlen(sahasra2)+2,sizeof(char));
		sahasra_adder(sahasra2, sahasra1, res);
		return removeLeadZero(res);
	}
	char* res = (char*)calloc(strlen(sahasra1)+2,sizeof(char));
	sahasra_adder(sahasra1, sahasra2, res);
	return removeLeadZero(res);
}
int sahasra_compare(const char* sahasra1, const char* sahasra2){
	int p1 = strlen(sahasra1)-1;
	int p2 = strlen(sahasra2)-1;
	int diff = 0, bigger = 0;
	int i =0;
	if(p1 < p2)
		return -1;
	if(p1 == p2){
		bigger = 0;
		do{
			diff = sahasra1[i] - sahasra2[i];
			if(diff > 0){
				bigger = 1;
			}else if(diff < 0){
				bigger = -1;
			}++i;
		}while(diff == 0 && i<=p1 && i <= p2);
		return bigger;
	}
	//printf("p1 %d p2 %d\n",p1,p2);
	return 1;	
}
static char* sahasra_differ(const char* sahasra1, const char* sahasra2){
	int l1 = strlen(sahasra1)-1;
	int l2 = strlen(sahasra2)-1;
	int top = 0,bottom = 0,k = l1,i;
	int taken = 0;
	char* res = (char*)calloc(k+2,sizeof(char));
	for(i = 0; i <= k;i++)
		res[i] = 48;
	res[i] = '\0';
	while(l2>= 0){
		top = sahasra1[l1]-48;
		bottom = sahasra2[l2]-48;
		if(taken > 0){
			if(taken == 1){
				//printf("if %c\n",sahasra1[l1]);
				top -=1;
			}else{	
				//printf("else %c\n",sahasra1[l1]);
				top = 9 + sahasra1[l1]-48 ;
			}
			//printf("updated top in if taken >0\n");
			--taken;		
		}
		//printf("%d %d %d\n",top, bottom, (top-bottom));
		if(top < bottom){
			//int look = 0;
			do{
				++taken;
			}while(sahasra1[l1-taken] == 48 && (l1-taken) > 0);
			top +=10;		
		}
		
		//printf("%d %d %d %d\n",top, bottom, (top-bottom), taken);
		res[k] = 48+ top - bottom;
		--l1;--l2;--k;
	}
	//printf("taken = %d\n",taken);
	while(l1>=0){
		if(taken >  0){
			res[k] = sahasra1[l1]-1; 
			if(sahasra1[l1] == 48)
				res[k] = 57;
			--taken;
		}else{
			res[k] = sahasra1[l1];		
		}
		--l1;--k;		
	}
	return res;
}
char* sahasra_diff(const char* sahasra1, const char* sahasra2){
	int bigger = sahasra_compare(sahasra1,sahasra2);
	//int i;
	//printf("bigger = %d\n",bigger);
	if(bigger == -1){
		//char* res = (char*)calloc(strlen(sahasra2)+1,sizeof(char));
		char* res = sahasra_differ(sahasra2, sahasra1);
		return removeLeadZero(res);
	}
	//char* res = (char*)calloc(strlen(sahasra1)+1,sizeof(char));
	char* res = sahasra_differ(sahasra1, sahasra2);
	return removeLeadZero(res);
}
static int isZero(const char* sahasra){
	int i =0, len = strlen(sahasra);
	while(i<len){
		if(sahasra[i] == 48)
			++i;
		else
			break;		
	}
	//printf("values of i%d, strlen = %d\n",i,len);
	if(sahasra[i] == '\0')
		return 1;
	//printf("Returning zero\n");
	return 0;
}
static void sahasra_multy(const char* sahasra1, const char* sahasra2, char* res){
	int l1 = strlen(sahasra1);
	int l2 = strlen(sahasra2);
	int sum = 0, carry = 0;
	int l3 = l1+l2;
	int ptr1 = 1;
	int ptr2;
	int i;
	//res = (char*)realloc(res,l3*sizeof(char));
	//printf("strlen before%d\n",strlen(res));
	for(i = 0; i < l3; i++){
		res[i] = '0';		
	}
	for(i = l2-1; i >= 0; i--){
		sum = 0;
		carry = 0;
		ptr2 = l3-ptr1;
		for(int j = l1-1; j >=0; j--){
			//printf("%c %c\n",sahasra1[j], sahasra2[i]);
			sum = (sahasra1[j]-'0')*(sahasra2[i]-'0') + (res[ptr2]-'0')+carry;
			//printf("%c %c %d\n",sahasra1[j], sahasra2[i],sum);
			res[ptr2] = 48+sum%10;
			carry = sum/10;
			--ptr2;	
			//printf("%d %d\n",ptr1,ptr2);	
		}
		if(carry){
			res[ptr2] += carry;		
		}
		++ptr1;		
	}
}
char* sahasra_multiply(const char* sahasra1, const char* sahasra2){
	//printf("%d %d\n",isZero(sahasra1),isZero(sahasra2));
			
	if(!isZero(sahasra1) && !isZero(sahasra2)){
		int bigger = sahasra_compare(sahasra1,sahasra2);
		//int i;
		char* res = (char*)calloc(strlen(sahasra1)+strlen(sahasra2)+1,sizeof(char));
		if(bigger>=0){
			sahasra_multy(sahasra1, sahasra2, res);
		}else{
			sahasra_multy(sahasra2, sahasra1, res);
		}
		return removeLeadZero(res);
	}
	char* res = (char*)malloc(2*sizeof(char));
	strcpy(res,"0");
	return res;
}
/*
static char* sahasra_multiply_by10(const char* sahasra2, int diff){
	int l = strlen(sahasra2)+diff;
	char* res = (char*)calloc(l+2,sizeof(char));
	int i = 0;
	for(i = 0; i < strlen(sahasra2);i++)
		res[i] = sahasra2[i];
	for(i =l-diff; i < l;i++)
		res[i] = 48;
	res[i] = '\0';
	return res;
}
static void sahasra_divide_by10(char* sahasra){
	int len = strlen(sahasra);
	//printf("LEN = %d\n",len);
	if(len > 1){
		sahasra = (char*)realloc(sahasra,sizeof(char)*(len));
		sahasra[len-1] = '\0';
	}
}
static void sahasra_modder(char* ni1, char* ni2){
	char* temp;
	//printf("Inside modder\n");
	while(sahasra_compare(ni1,ni2) == 1){
		printf("Going again in modder\n");
		temp = sahasra_diff(ni1,ni2);
		free(ni1);
		ni1 = temp;
		printf("%s %s\n",ni1,ni2);	
	}
	//printf("strlen NI1 after modder = %d\n",strlen(ni1));
	display(ni1);
}
static char* iter_mod(const char* sahasra1, const char* sahasra2){
	int comp = sahasra_compare(sahasra1,sahasra2);
	int l1 = strlen(sahasra1);
	int l2 = strlen(sahasra2);
	char* res;
	//printf("Compare = %d\n",comp);
	if(isZero(sahasra1) || comp == 0){
		res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		return res;
	}
	if(comp == -1){	
		//printf("sahasra2 is bigger\n");
		res = (char*)calloc(l1+1,sizeof(char));
		strcpy(res,sahasra1);
		return res;
	}
	int diff = l1-l2;;
	if(sahasra1[0] <= sahasra2[0])
		--diff;
	char* temp;
	char* ni2 = sahasra_multiply_by10(sahasra2,diff);
	char* ni1 = sahasra_diff(sahasra1,ni2);
	comp = sahasra_compare(ni1,sahasra2);
	//printf("%s %s %d\n",ni1,ni2,comp);
	while(comp> 0){
		//printf("going again\n");
		while(sahasra_compare(ni1,ni2) == 1){
			//printf("Going again in modder\n");
			temp = sahasra_diff(ni1,ni2);
			char* t2 = ni1;
			ni1 = temp;
			free(t2);
			//printf("%s %s\n",ni1,ni2);	
		}
		comp = sahasra_compare(ni1, sahasra2);
		free(ni2);
		diff = strlen(ni1) - l2;
		if(ni1[0] <= sahasra2[0])
			--diff;
		ni2 = sahasra_multiply_by10(sahasra2,diff);
		//free(t3);
		//printf("%s %s %d\n",ni1,ni2,comp);
	}
	free(ni2);
	if(comp == 0){
		res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		free(ni1);
		return res;
	}
	//printf("Strlen of ni1=%d\n",strlen(ni1));
	return ni1;
}
static char* recur_mod(const char* sahasra1, const char* sahasra2){
	int comp = sahasra_compare(sahasra1,sahasra2);
	int l1 = strlen(sahasra1);
	int l2 = strlen(sahasra2);
	int i;	
	//char* res;
	//printf("Compare = %d\n",comp);
	if(isZero(sahasra1) || comp == 0){
		char* res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		return res;
	}
	if(comp == -1){	
		//printf("sahasra2 is bigger\n");
		char* res = (char*)calloc(l1+1,sizeof(char));
		strcpy(res,sahasra1);
		return res;
	}
	int diff = l1-l2;
	if(sahasra1[0] <= sahasra2[0])
		--diff;
	if(diff > 0){
		char* ni2 = (char*)malloc(sizeof(char)*(l2+diff+1));	
		for(i = 0; i < l2; i++)
			ni2[i] = sahasra2[i];
		for(i = 0; i < diff; i++)
			ni2[l2+i] = 48;
		ni2[l2+i] = '\0';
		char* temp = sahasra_diff(sahasra1, ni2);
		char* t2 = ni2;
		ni2 = temp;
		free(t2);
		return sahasra_mod(ni2, sahasra2);	
	}
	char* temp = sahasra_diff(sahasra1,sahasra2);
	char* t2 = temp;
	char* res = sahasra_mod(temp, sahasra2);
	free(t2);
	return res;
}
*/
char* sahasra_mod(const char* sahasra1, const char* sahasra2){
	//return iter_mod(sahasra1,sahasra2);
	int comp = sahasra_compare(sahasra1,sahasra2);
	int l1 = strlen(sahasra1);
	int l2 = strlen(sahasra2);
	int i;	
	//char* res;
	//printf("Compare = %d\n",comp);
	if(isZero(sahasra1) || comp == 0){
		char* res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		return res;
	}
	if(comp == -1){	
		//printf("sahasra2 is bigger\n");
		char* res = (char*)calloc(l1+1,sizeof(char));
		strcpy(res,sahasra1);
		return res;
	}
	int diff = l1-l2;
	if(sahasra1[0] <= sahasra2[0])
		--diff;
	if(diff == 0){
		char* temp = sahasra_diff(sahasra1,sahasra2);
		char* t2 = temp;
		char* res = sahasra_mod(temp, sahasra2);
		free(t2);
		return res;
	}
	char* ni1 = (char*)malloc(sizeof(char)*(l1+1));
	strcpy(ni1, sahasra1);
	char* ni2 = (char*)malloc(sizeof(char)*(l2+diff+2));
	for(i = 0; i < l2; i++)
		ni2[i] = sahasra2[i];
	for(i = 0; i < diff; i++)
		ni2[l2+i] = 48;
	ni2[l2+i] = '\0';
	while(sahasra_compare(ni1,ni2) >0){
		char* temp = sahasra_diff(ni1,ni2);
		char* t2 = ni1;
		ni1 = temp;
		free(t2);
	}
	free(ni2);
	if(sahasra_compare(ni1,sahasra2) <= 0)
		return ni1;
	char* temp = ni1;
	char* res = sahasra_mod(ni1,sahasra2);
	free(temp);
	return res;
}

char* sahasra_pow(const char* sahasra1, unsigned int n){
	if(isZero(sahasra1)){
		char* res = (char*)malloc(sizeof(char)*2);
		strcpy(res,"0");
		return res;	
	}
	char* res = (char*)malloc(sizeof(char)*2);
	strcpy(res,"1");
	char* x = (char*)malloc(sizeof(char)*(strlen(sahasra1)+1));
	strcpy(x,sahasra1);
	char* temp;
	while(n > 0){
		if(n & 1){
			temp = sahasra_multiply(res,x);
			free(res);
			res = temp;		
		}	
		n = n >> 1;
		temp = sahasra_multiply(x,x);
		free(x);
		x = temp;
	}
	free(x);
	return res;
}

char* sahasra_gcd(const char* sahasra1, const char* sahasra2){
	if(strcmp(sahasra1,"0")==0 && strcmp(sahasra2,"0")==0){
		char* res = (char*)calloc(2,sizeof(char));
		res[0] = '0';
		res[1] = '\0';	
		return res;
	}
	if(strcmp(sahasra1,"0")==0){
		char* res = (char*)calloc(strlen(sahasra2)+1,sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(sahasra2);i++)
			res[i] = sahasra2[i];
		res[i] = '\0';	
		return res;
	}
	if(strcmp(sahasra2,"0") == 0){
		char* res = (char*)calloc(strlen(sahasra1)+1,sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(sahasra1);i++)
			res[i] = sahasra1[i];
		res[i] = '\0';	
		return res;	
	}
	char* temp = sahasra_mod(sahasra1, sahasra2);
	char* res =  sahasra_gcd(sahasra2, temp);
	free(temp);
	return res;	
}

char* sahasra_fibonacci(unsigned int n){
	unsigned int i;	
	//char **res = (char**)malloc(2 * sizeof(char*));
	char *res1 = (char*)malloc(2 * sizeof(char));
	strcpy(res1,"0");
	if(n==0)
		return res1;
	char *res2 = (char*)malloc(2 * sizeof(char));

	strcpy(res2,"1");
	//printf("%s %s\n",res[0],res[1]);
	char* temp = NULL;
	for(i = 2; i <= n; i++){
		temp = sahasra_add(res1,res2);
		free(res1);
		res1 = res2;
		res2 = temp;
		//printf("%s %s\n",res[0],res[1]);	
	}
	free(res1);
	return res2;
}
char* sahasra_factorial(unsigned int n){
	char* res = (char*)calloc(2,sizeof(char));
	strcpy(res,"1");	
	if(n == 0 || n== 1){
		return res;
	}
	char* num = (char*)calloc(2,sizeof(char));
	char* copy = NULL;
	strcpy(num,"1");
	unsigned int i = 2;
	while(i <= n){
		copy = sahasra_add(num,"1");
		free(num);
		num = copy;
		//printf("%s %s\n",num,res);
		copy = sahasra_multiply(num,res);
		free(res);
		res = copy;
		++i;	
	}
	//free(copy);
	free(num);
	return removeLeadZero(res);
}
/*
static unsigned int min(unsigned int i, unsigned int k){
	return (i > k)?k:i;
}
*/
char* sahasra_bincoeff(unsigned int n, unsigned int k){
	unsigned int i = 0;
	unsigned int j = 0;
	if(k > (n-k))
		k = n-k;
	char** dp = (char**)malloc(sizeof(char*)*(k+1));
	dp[0] = (char*)malloc(2*sizeof(char));

	strcpy(dp[0],"1");
	
	for(i = 1; i <= k; i++){
		dp[i] = (char*)malloc(2*sizeof(char));
		strcpy(dp[i],"0");	
	}
	char* temp;
	for(i = 1; i <= n;i++){
		for(j = (i > k)?k:i; j > 0; j--){
			temp = sahasra_add(dp[j],dp[j-1]);
			free(dp[j]);
			dp[j] = temp;	
		}	
	}
	char* res = (char*)malloc(sizeof(char)*(strlen(dp[k])+1));
	strcpy(res,dp[k]);
	for(i = 0; i <= k; i++){
	//	printf("%s ",dp[i]);
		free(dp[i]);
	}
	free(dp);
	return res;	
	
}

int sahasra_max(char **arr, int n){
	//char* max = arr[0];
	int min = 0,i;
	for(i = 1; i < n;i++){
		//printf("%s %s\n",arr[i],max);
		if(sahasra_compare(arr[min],arr[i]) < 0){
			//max = arr[i];
			min = i;		
		}		
	}
	//free(max);
	return min;
}
int sahasra_min(char **arr, int n){
	//char* mini = arr[0];
	int min = 0,i;
	for(i = 1; i < n; i++){
		if(sahasra_compare(arr[min],arr[i]) > 0){
			//mini = arr[i];	
			min = i;	
		}		
	}
	//free(mini);
	return min;
}
int sahasra_search(char **arr, int n, const char* key){
	int index =-1;	
	for(int i = 0; i< n; i++){
		if(sahasra_compare(arr[i],key) == 0){
			index = i;
			break;		
		}	
	}
	return index;
}
int sahasra_binsearch(char **arr, int n, const char* key){
	int lo = 0, hi = n-1;
	int mid = -1, comp = 0;
	while(lo <= hi){
		mid =lo + (hi - lo)/2; 
		comp = sahasra_compare(arr[mid],key);
		if(comp == 0){
			return mid;		
		}
		if(comp == 1){
			hi = mid-1;		
		}
		else{
			lo = mid+1;				
		}
	}
	return -1;
}
/*
static void swapPointers(char* a, char* b){
}
*/

static void merge(char **arr, int l, int m, int r){ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 
	char** left = (char**)malloc(sizeof(char*)*n1);
	char** right = (char**)malloc(sizeof(char*)*n2);
	for (i = 0; i < n1; i++){
		left[i] = (char*)malloc(sizeof(char)*(strlen(arr[l+i])+1)); 
		strcpy(left[i],arr[l+i]);
	} 
	for (j = 0; j < n2; j++){ 
		right[j] = (char*)malloc(sizeof(char)*(strlen(arr[m + 1+ j])+1)); 
		strcpy(right[j],arr[m + 1+ j]);
	} 
	i = 0;j = 0;k = l; 
	while (i < n1 && j < n2){ 
		if(sahasra_compare(left[i],right[j]) <= 0){ 
			strcpy(arr[k],left[i]); 
			i++; 
        	}else{ 
            		strcpy(arr[k],right[j]); 
            		j++; 
        	} 
        	k++; 
    	} 
	while (i < n1){ 
        	strcpy(arr[k],left[i]); 
       		i++; 
        	k++; 
    	} 
	while (j < n2){
		strcpy(arr[k],right[j]); 
        	j++; 
        	k++; 
    	}
	for(i = 0; i < n1; i++)
		free(left[i]);
	free(left);
	for(i = 0; i < n2; i++)
		free(right[i]);
	free(right); 
} 
void sahasra_sort(char **arr, int n){
	int curr_size;
	int left_start;
	for(curr_size=1; curr_size<=n-1; curr_size = 2*curr_size){ 
		for (left_start=0; left_start<n-1; left_start += 2*curr_size){ 
			int mid = ((left_start + curr_size - 1) > n-1)?(n-1):(left_start + curr_size - 1); 
			int right_end = ((left_start + 2*curr_size - 1) > n-1)?(n-1):(left_start + 2*curr_size - 1); 
  			merge(arr, left_start, mid, right_end); 
		} 
	} 
}
static char* max(char* sum, char* curr){
	int comp = sahasra_compare(sum,curr);
	if(comp >=0){
		return sum;
	}
	free(sum);
	return curr;
}
char* coin_row_problem(char **arr, int n){
	if(n == 0){
		char* res = (char*)malloc(sizeof(char)*2);
		strcpy(res,"0");
		return res;
	}
	char* prev = (char*)malloc(sizeof(char)*2);
	strcpy(prev,"0");
	char* curr = (char*)malloc(sizeof(char)*(strlen(arr[0])+1));
	strcpy(curr,arr[0]);
	char* next;
	//printf("0 %s %s \n",prev,curr);
	for(int i = 1; i < n;i++){
		next = max(sahasra_add(prev,arr[i]),curr);
		if(sahasra_compare(prev,curr) != 0){
			free(prev);
			prev = curr;
		}		
		curr = next;
		//printf("%s %s %s\n",next,prev,curr);
	}
	if(sahasra_compare(prev,curr) != 0)
		free(prev);
	return curr;	
}