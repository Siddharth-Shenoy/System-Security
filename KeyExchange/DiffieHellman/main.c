#include <stdio.h>
#include <conio.h>

int getMod(int value, int power,int mod);

int main2()
{
	int key = -1;
	int genkeys[2];
	int temp;
	int p, q, g, n;
	printf("Enter P , Q , G, N\n");
	scanf("%d%d%d%d", &p, &q, &g,&n);
	printf("Calculating A's partial symmetric key:\n");
	genkeys[0] = getMod(g, p, n);
	printf("%d\n", genkeys[0]);
	printf("Calculating B's partial symmetric key:\n");
	genkeys[1] = getMod(g, q, n);
	printf("%d\n", genkeys[1]);
	temp = genkeys[0];
	genkeys[0] = genkeys[1];
	genkeys[1] = temp;
	printf("Exchanged Keys: %d , %d\n", genkeys[0], genkeys[1]);
	printf("Calculating A's symmetric key:\n");
	genkeys[0] = getMod(genkeys[0], p, n);
	printf("%d\n", genkeys[0]);
	printf("Calculating B's symmetric key:\n");
	genkeys[1] = getMod(genkeys[1], q, n);
	printf("%d\n", genkeys[1]);
	if (genkeys[1] == genkeys[0]) printf("Keys match!\n");
	else printf("Keys donot match!\n");
	_getch();
	return 0;
}
int getMod(int value, int power, int mod)
{
	int x = 1;
	for (int i = 0; i < power; i++)
	{
		x = (x * value) % mod;
	}
	return x;
}
