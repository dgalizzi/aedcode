// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: huffman.h,v 1.3 2004/05/05 02:32:24 mstorti Exp $
#ifndef AED_HUFFMAN_H
#define AED_HUFFMAN_H

double
huff_stat(aed::btree<int> &T,aed::btree<int>::iterator node,
	  const std::vector<double> &prob,int level,
	  std::vector<int> &codigo,std::vector< vector<int> > &codigos);

void 
huffman(const std::vector<double> &prob,aed::btree<int> &T);

void hufzip(char *file,char *zipped);

void hufunzip(char *zipped,char *unzipped);

extern int verbosity;

void 
huffman_exh(const std::vector<double> &prob,aed::btree<int> &T);

double codelen(aed::btree<int> &T,
	       const std::vector<double> &prob);

#endif
