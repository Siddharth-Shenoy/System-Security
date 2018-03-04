#include <stdio.h>
#include <string.h>

struct RSA
{
  	long primes[2];
	long keys[2];
  	int totient;
  	int bigN;
  	char string[256];
  	char sstring[256];
  	char encstring[1024];
  	char decstring[1024];
};
typedef struct RSA RSA;

int getMod(int key,int pow,int mod);
int getKey(int key,int totient);
void sanitizeString(char *string,char *newstring);
char ctoupper(char s);
int getDigitCount(int number);
void useRSA(char *string,char *encstring,RSA rsa);
void decrypt(char *string,char *decstring,RSA rsa);
int strtodig(char *string);
int getmax(int x,int y);
int getMaxDC(int key,int n);

int main(int argc,char **argv)
{
  	RSA mRSA;

	memset(mRSA.encstring,0,sizeof(mRSA.encstring));
  	memset(mRSA.decstring,0,sizeof(mRSA.decstring));
  	printf("Enter two prime numbers:\n");
  	scanf("%ld%ld",&mRSA.primes[0],&mRSA.primes[1]);
  	mRSA.bigN = mRSA.primes[0] * mRSA.primes[1];
  	mRSA.totient = (mRSA.primes[0] - 1) * (mRSA.primes[1] - 1);
	printf("Enter first key:\n");
  	scanf("%ld",&mRSA.keys[0]);
  	mRSA.keys[1] = getKey(mRSA.keys[0],mRSA.totient);
	printf("Key pair: %ld %ld\n",mRSA.keys[0],mRSA.keys[1]);
 	printf("Enter a string\n");
	fflush(stdin);
  	while((getchar() != '\n'));
  	fgets (mRSA.string,sizeof(mRSA.string),stdin);
	sanitizeString(mRSA.string,mRSA.sstring);
	useRSA(mRSA.sstring,mRSA.encstring,mRSA);
  	printf("%s\n",mRSA.encstring);
	printf("Decrypting the above string..\n");
  	decrypt(mRSA.encstring,mRSA.decstring,mRSA);
  	printf("%s\n",mRSA.decstring);
 	return 0;
}
int getKey(int key,int totient)
{
  	int res = 1;
	for(int i = 1; i < totient; i++)
    	{
		if((i*key)%totient == 1)
		{
			res = i;
		  	break;
		}
	}
  	return res;
}
void sanitizeString(char *string,char *newstring)
{
  	int k = 0;
  	for(int i = 0; i < strlen(string); i++)
	{
		if(string[i] == ' ' || string[i] == ',' || string[i] == ':' || string[i] == ';')
	    	{
			continue;
	    	}
	  	else
		{
			newstring[k] = string[i];
		  	k++;
		}
	}
  	newstring[k] = '\0';
  	for(int i = 0; i < strlen(newstring); i++)
	{
		newstring[i] = ctoupper(newstring[i]);
	}
}

char ctoupper(char s)
{
	return (s >= 'a' && s <= 'z') ? (char)((int)s - 32) : s;
}
int getMod(int key,int pow,int mod)
{
  	int res = 1;
  	for(int i = 0; i < pow; i++)
    	{
		res = (res*key)%mod;
	}
  	return res;
}

int getDigitCount(int number)
{
  	if(number == 0) return 1;
 	int res = 0;
  	while(number != 0)
    	{
		number /= 10;
	    	res++;
	}
  	return res;
}
void useRSA(char *string,char *encstring,RSA rsa)
{
	char teststring[128];
  	int digits[2];
  	int dc = getMaxDC(rsa.keys[0],rsa.bigN);
  	for(int i = 0; i < strlen(string)-1; i++)
	{
		digits[0] = (int)((int)string[i] / 10);
	  	digits[1] = (int)((int)string[i] % 10);
	  	digits[0] = getMod(digits[0],rsa.keys[0],rsa.bigN);
	  	digits[1] = getMod(digits[1],rsa.keys[0],rsa.bigN);

	  	if(getDigitCount(digits[0]) < dc)
	    	{
			for(int k = 0; k < dc - getDigitCount(digits[0]); k++)
				sprintf(encstring,"%s%d",encstring,0);
		    	sprintf(encstring,"%s%d",encstring,digits[0]);
		}
	  	else sprintf(encstring,"%s%d",encstring,digits[0]);
	  	if(getDigitCount(digits[1]) < dc)
	    	{
			for(int k = 0; k < dc - getDigitCount(digits[1]); k++)
				sprintf(encstring,"%s%d",encstring,0);
		    	sprintf(encstring,"%s%d",encstring,digits[1]);

		}
	  	else sprintf(encstring,"%s%d",encstring,digits[1]);
	}
}
void decrypt(char *string,char *decstring,RSA rsa)
{
  	int digits[2];
  	char tempdigits[2][10];
  	int finaldig;
  	memset(tempdigits[0],0,sizeof(tempdigits[0]));
  	memset(tempdigits[1],0,sizeof(tempdigits[1]));
  	int dc = getMaxDC (rsa.keys[1],rsa.bigN);
  	int k = 0;
  	for(int i = 0; i < strlen(string); i++)
    	{
		for( k = i; k < i+dc; k++)
	    	{
			tempdigits[0][k-i] = string[k];
		}
	    	i += dc;
	    	for( k = i; k < i+dc; k++)
	    	{
			tempdigits[1][k-i] = string[k];
		}
	    	i += dc - 1;
	    	digits[0] = strtodig(tempdigits[0]);
	    	digits[1] = strtodig(tempdigits[1]);
		digits[0] = getMod(digits[0],rsa.keys[1],rsa.bigN);
	    	digits[1] = getMod(digits[1],rsa.keys[1],rsa.bigN);
	    	finaldig = digits[0]*10 + digits[1];
	    	sprintf(decstring,"%s%c",decstring,(char)finaldig);
	}
}

int strtodig(char *string)
{
  	int number = 0;
  	for(int i = 0; i < strlen(string); i++)
    	{
		number = number*10 + ((int)string[i] - (int)'0');
	}
  	return number;
}
int getmax(int x,int y)
{
  	return x > y ? x : y;
}
int getMaxDC(int key,int n)
{
  	int dc = -1;
  	int digits[2];
	for(char c = 'A'; c <= 'Z'; c++)
    	{
		digits[0] = (int)((int)c / 10);
	    	digits[1] = (int)((int)c % 10);
	    	digits[0] = getMod(digits[0],key,n);
	    	digits[1] = getMod(digits[1],key,n);
	    	digits[0] = getDigitCount (digits[0]);
	    	digits[1] = getDigitCount (digits[1]);
		dc = getmax(dc,digits[0]);
	    	dc = getmax(dc,digits[1]);
	}
  	return dc;
}
