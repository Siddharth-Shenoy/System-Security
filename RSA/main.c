#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct KEYS
{
	int key[2];
}
KEYS;

int strval(char *str);
int getTotalLength(int k);
int generateKey(int k, int tn);
int getMod(int val, int pow, int mod);
char toupper(char c);
int main()
{
	int p, q, tn, n, len;
	char ch;
	KEYS m_keys;
	char m_input[128];
	char m_inputcpy[128];
	int m_enc[128];
	int m_dec[128];
	char encrypt[2048] = "";
	char decryptx[128][12];
	char decrypt[2048] = "";
	int i, k, l;
	int m_len, comb = 0, rem;
	printf("Enter two prime numbers:\n");
	scanf("%d%d", &p, &q);
	n = p * q;
	tn = (p - 1) * (q - 1);
	printf("Enter your key:\n");
	scanf("%d", &m_keys.key[0]);
	m_keys.key[1] = generateKey(m_keys.key[0], tn);
	printf("Key pair generated: %d %d\n", m_keys.key[0], m_keys.key[1]);
	while ((ch = getchar()) != '\n');
	fflush(stdin);
	
	printf("Enter a string(128 characters):\n");
	fgets(m_inputcpy, sizeof(m_inputcpy), stdin);
	k = 0;
	for (i = 0; i < strlen(m_inputcpy); i++)
	{
		if (m_inputcpy[i] == ' ' || m_inputcpy[i] == ',' || m_inputcpy[i] == '?' || m_inputcpy[i] == ';') continue;
		m_input[k] = toupper(m_inputcpy[i]);

		k++;
	}
	m_input[k] = '\0';

	printf("Entered string: %s\n", m_input);
	for (i = 0; i < strlen(m_input); i++)
	{
		m_enc[i] = getMod((int)m_input[i], m_keys.key[0], n);
		m_len = getTotalLength(m_enc[i]);

		sprintf(encrypt, "%s%d",encrypt, m_enc[i]);
	}
	printf("Encrypted String: %s\n", encrypt);
	len = getTotalLength(getMod((int)'A', m_keys.key[0], n));


	k = 0;
	for (i = 0; i < strlen(encrypt); i += len)
	{
		for (l = 0; l < len; l++)
		{
			decryptx[k][l] = encrypt[i + l];
		}
		decryptx[k][len] = '\0';
		//printf("%s\n", decryptx[k]);
		k++;
	}

	for (i = 0; i < k; i++)
	{
		m_dec[i] = strval(decryptx[i]);
		decrypt[i] = (char)getMod(m_dec[i], m_keys.key[1], n);
	}
		
	printf("Decrypted String: %s\n", decrypt);
	_getch();
	return 0;
}

int getMod(int val, int pow, int mod)
{
	int x = 1;
	for (int i = 0; i < pow; i++)
	{
		x = (x*val) % mod;
	}
	return x;
}
int generateKey(int k, int tn)
{
	int ret = 1;
	for (int i = 1; i < tn; i++)
	{
		if ((i*k) % tn == 1)
		{
			ret = i;
			break;
		}
	}
	return ret;
}
int getTotalLength(int k)
{
	int x = 0;
	while (k != 0)
	{
		k /= 10;
		x++;
	}
	return x;
}
int strval(char *str)
{
	int result = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		result = result * 10 + ((int)str[i] - (int)'0');
	}
	return result;
}
char toupper(char c)
{
	if (c == '\0') return c;
	int val = (int)'a' - (int)'A';
	int ret = c;
	if (c >= 'a' && c <= 'z')
	{
		ret = c - val;
	}
	return (char)ret;
}
