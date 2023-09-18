#include <stdio.h>
#include <math.h>

void convert(long long int n, int s, int t){
	if(!(t >= 2 || t <= 10) || !(s >= 2 || s <= 10)){
		printf("cannot convert!\n");
		return;
	}

	int power = 0;
	long long int decimal = 0;
	int reminder = 0;

	while(n){
		reminder = (n % 10);
		if(reminder >= s){
			printf("cannot convert!\n");
			return;
		}
		n = n / 10;
		decimal = decimal + reminder * pow(s, power);
		power++;
	}

	if(t == 10){
		printf("%lld\n", decimal);
		return;
	}

	long long int result = 0;
	power = 0;

	while(decimal){
		reminder = decimal % t;
		decimal = decimal / t;
		result = result + reminder * pow(10, power);
		power++;
	}

	printf("%lld\n", result);
	return;
}


int main(){
	long long int n;
	int s, t;

	scanf("%lld %d %d", &n, &s, &t);
	convert(n, s, t);

	return 0;
}
