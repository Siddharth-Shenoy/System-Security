#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int findkeypair(int key,int p0,int p1);
int RSAAlgoChar(char c,int power,int n);
int gettotaldigits(int k);
typedef struct RSAKeys
{
	long enckey;
	long deckey;
}
KEYS;

int main()
{
  	int i = 0;
  	int ei = 0;
  	int di = 0;
  	int k = 0;
	int enc[128];
  	int dec[128];
  	char mainstring[128];
	char newstr[128];
  	char transmission[2048] =  "";
	char declines[128];
	long prime0;
	long prime1;
  	long n;
	KEYS K;
	char string[128];
  	//char string[128] = "Hello world";
	int buffersize = 128;
	printf("Enter two prime numbers..\n");
	scanf("%ld%ld",&prime0,&prime1);
  	n = prime0 * prime1;
	printf("Entered prime numbers: ( %ld , %ld )\n",prime0,prime1);
	printf("Enter the encryption key:\n");
	scanf("%ld",&K.enckey);
	K.deckey = findkeypair(K.enckey,prime0,prime1);
	printf("Key pair: %ld , %ld\n",K.enckey,K.deckey);
  	printf("Enter a string to encrypt..\n");
  	while ((getchar()) != '\n');
	fgets(&mainstring,&buffersize,stdin);
  	printf("Entered string: %s\n",mainstring);
  	printf("String length: %d\n",strlen(mainstring));
	for(i = 0; i < strlen(mainstring); i++)
   	{
	   	if(mainstring[i] == ' ')
	    	{
			continue;
		}
	   	else
	    	{
			newstr[k] = mainstring[i];
		    	k++;
		}
	}
	printf("New string: %s\n",newstr);
	for(i = 0; i < strlen(newstr); i++)
    	{
		enc[ei] = RSAAlgoChar(newstr[i],K.enckey,n);
	    	printf("%d\n",enc[ei]);
	    	sprintf(transmission,"%s%d",transmission,enc[ei]);
	    	ei++;
	}
  	//sprintf(transmission,"%s00%d",transmission,ei);
  	printf("Transmission String:\n");
  	printf("%s\n",transmission);
  	printf("\n\n\nRECEPTION:\n");
  	printf("Test Decryption for the letter 'A'\n");
  	int testdec = RSAAlgoChar('A',K.deckey,n);
  	printf("Total digits: %d\n",gettotaldigits(testdec));
  	printf("Parsing transmission line..")
	return 0;
}

int findkeypair(int key,int p0,int p1)
{
	int keyret = -1;
	int totient = (p0-1)*(p1-1);
	for(int i = 1; i < totient; i++)
	{
		if((key*i)%totient == 1)
		{
			keyret = i;
			break;
		}
	}
	return keyret;
}

int RSAAlgoChar(char c,int power,int n)
{
	int value = (int)c;
  	for(int i = 0; i < power; i++)
    	{
		value = (value*(int)c)%n;
	}
  	value = (value*(int)c)%n;
	return value;
}
int gettotaldigits(int k)
{
  	int temp =  k;
  	int total = 0;
  	while(temp != 0)
    	{
		temp /= 10;
	    	total++;
	}
  	return total;
}
