#include <stdio.h>
#include <string.h>
#include "factor.h"

#define BEGIN_NUM 1		/* must be set to 1 or 2 */
#define BSIZE (sizeof(unsigned int)*8+1)
#define DEFAULT_PRINTFACTOR printFactorNor


#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_SUBMINOR 0


static const char _VERSION_STR[] = "1.0.0";


static int showHelp (const char *ch, int ret);
static unsigned int cropPath (const char *ch);
static void printErr (const char *str[], int i);
static void printFactorNor (unsigned int *buff, unsigned int size);
static void printFactorPow (unsigned int *buff, unsigned int size);

static const char *errStr[] = { "Parameter is not match.",
  "Min > Max.",
  "One of parameter is not an unsigned number."
};

enum
{
  e_parNmatch, e_mOm, e_parNnum
};



int
main (int argc, const char *argv[])
{
  unsigned int min, max, i, j, bnum, buff[BSIZE];
  void (*printFactor) (unsigned int *, unsigned int);


/*********	Paramer management	***********/
  bnum = BEGIN_NUM;
  printFactor = DEFAULT_PRINTFACTOR;

  switch (argc)
    {
    case 2:


      if (!isUint (argv[1]))
	{
	  printErr (errStr, e_parNnum);
	  return showHelp (argv[0], 1);
	}
      min = max = s2ui (argv[1]);

      break;
    case 4:

      if (!strcmp (argv[3], "1") || !strcmp (argv[3], "2")
	  || !strcmp (argv[3], "1p") || !strcmp (argv[3], "2p"))
	{
	  bnum = argv[3][0] - '0';
	  if (sLen (argv[3]) == 2)
	    {
	      printFactor = printFactorPow;
	    }
	}
      else
	{
	  printErr (errStr, e_parNnum);
	  return showHelp (argv[0], 1);
	}
    case 3:

      if (!isUint (argv[1]) || !isUint (argv[2]))
	{
	  printErr (errStr, e_parNnum);
	  return showHelp (argv[0], 1);
	}
      min = s2ui (argv[1]);
      max = s2ui (argv[2]);

      break;



    default:
      printErr (errStr, e_parNmatch);
      return showHelp (argv[0], 1);
    }

  if (min > max)
    {
      printErr (errStr, e_mOm);
      return showHelp (argv[0], 1);
    }
/*********	Paramer management	***********/




  for (i = min; i <= max; i++)
    {

      j = getFactor (i, bnum, buff, BSIZE);
      printf ("%u [%u] = ", i, j);
      printFactor (buff, j);
      putchar ('\n');
    }
  return 0;
}

static void
printFactorNor (unsigned int *buff, unsigned int size)
{
  unsigned int i;
  for (i = 0; i < size; i++)
    printf ((i != size - 1) ? "%u x " : "%u", buff[i]);

}

static void
printFactorPow (unsigned int *buff, unsigned int size)
{
  unsigned int i, j, k;
  for (i = 0; i < size; i++)
    {
      for (j = 1, k = i; (k < size - 1) && (buff[k] == buff[k + 1]); i = ++k)
	{
	  j++;
	}

      if (j > 1)
	{
	  printf ((i == size - 1) ? "(%u)^%u" : "(%u)^%u x ", buff[i], j);
	}

      else
	{
	  printf ((i == size - 1) ? "%u" : "%u x ", buff[i]);
	}

    }

}

static int
showHelp (const char *ch, int ret)
{
  unsigned int i;
  i = cropPath (ch);
  fprintf
    (stderr,
     "\n%s version %s is an utility that help you answer factor of numbers.\n\n",
     (char *) ch + i, _VERSION_STR);
  fprintf (stderr, "USAGE:\t%s number\nProgram shows a factor of numbers.\n",
	   (char *) ch + i);
  fprintf (stderr,
	   "USAGE:\t%s min max\nProgram shows factors of numbers between min to max.\n",
	   (char *) ch + i);
  fprintf (stderr,
	   "USAGE:\t%s min max bnum{p}\nProgram shows factors of numbers between min to max and start with bnum and p suffic means that power number format.\n\n",
	   (char *) ch + i);
  return ret;
}

static unsigned int
cropPath (const char *ch)
{
  unsigned int i, j;
  for (i = 0, j = 0; ch[i]; i++)
    {
      if (ch[i] == '\\' || ch[i] == '/')
	{
	  j = i;
	}
    }
  return (j == 0) ? 0 : j + 1;
}

static void
printErr (const char *str[], int i)
{
  fprintf (stderr, "** Error number %d : %s **\n", i, ((char *) str[i]));
}