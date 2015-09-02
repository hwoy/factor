#include "factor.h"

unsigned int
getFactor (unsigned int num, unsigned int bnum, unsigned int *buff,
	   unsigned int size)
{
  unsigned int i, j, count;

  if (num <= 1)
    {
      buff[0] = num;
      return 1;
    }


  for (i = 2 - (bnum % 2), j = num, count = 0; (i <= j) && (count < size);
       i++)
    {
      if (i == j)
	{
	  buff[count++] = i;
	}
      else if ((isPrime (i) && !(j % i)))
	{
	  j /= i;
	  buff[count++] = i;
	  i = 1;

	}

    }

  return count;
}


int
isPrime (unsigned int i)
{
  unsigned j;

  if (i >= 0 && i <= 2)
    return 1;

  for (j = 2; j < i; j++)
    {
      if (!(i % j))
	return 0;
    }

  return 1;
}

int
isUint (const char *ch)
{
  unsigned int i;
  if (!sLen (ch))
    return 0;
  for (i = 0; ch[i]; i++)
    {
      if (ch[i] < '0' || ch[i] > '9')
	{
	  return 0;
	}
    }
  return 1;
}

unsigned int
pow2ui (unsigned int base, unsigned int pow)
{
  unsigned int i, j;
  if (!base)
    return 0;
  if (!pow)
    return 1;
  for (i = 1, j = base; i < pow; i++)
    {
      j = j * base;
    }
  return j;
}

unsigned int
s2ui (const char *ch)
{
  unsigned int i, j, k;
  j = 0;
  k = 0;
  i = sLen (ch) - 1;
  do
    {
      j += (ch[i] - '0') * pow2ui (10, k++);
    }
  while (i-- != 0);

  return j;
}

unsigned int
sLen (const char *ch)
{
  unsigned int i;

  for (i = 0; ch[i]; i++)
    {
    }
  return i;
}
