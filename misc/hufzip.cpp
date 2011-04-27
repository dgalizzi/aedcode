//__INSERT_LICENSE__
// $Id: hufzip.cpp,v 1.1 2004/05/01 16:09:16 mstorti Exp $

#include <vector>
#include <aedsrc/btree.h>
#include <cstdio>
#include <unistd.h>
#include <aedsrc/huffman.h>

using namespace std;
using namespace aed;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main(int argc,char **argv) {
  int c, unzip=0;
  char *infile=NULL, *outfile=NULL;
  while ((c = getopt (argc, argv, "vi:o:hu")) != -1) {
    switch (c) {
    case 'h':
      printf(" usage: $ hufzip [OPTIONS]\n\n"
	     "options: -h    give help\n"
	     "         -u    unzip input file into output file\n"
	     "         -i    input file (default = standard input)\n"
	     "         -o    output file (defualt = standard output)\n"
	     "         -v    increase verbosity\n"
	     "# sets number of rows sent to processors\n\n"
	     "examples: $ hufzip -i a.txt -o a.hzip\n"
	     "          $ hufzip -u -i a.hzip -o a.txt\n"
	     "          $ hufzip < a.txt > a.hzip\n"
	     "          $ hufzip -u < a.hzip > a.txt\n"
	     );
      exit(0);
    case 'v':
      verbosity=1;
      break;
    case 'u':
      unzip=1;
      break;
    case 'i':
      infile = optarg;
      break;
    case 'o':
      outfile = optarg;
      break;
    case '?':
      if (isprint (optopt))
	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
	fprintf (stderr,
		 "Unknown option character `\\x%x'.\n",
		 optopt);
      return 1;
    default:
      abort ();
    }
  }
  
  if (unzip) hufunzip(infile,outfile);
  else hufzip(infile,outfile);
  exit(0);
}
