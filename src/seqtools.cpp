/* Seqtools - Jeremiah's collection of useful command line tools
 * that don't seem to already exist
 * Copyright 2014 Jeremiah Wala 
 * Written by Jeremiah Wala (jeremiah.wala@gmail.com)
 * Released under the MIT license
 */

#include <iostream>

#include "rgtools.h"
#include "kmerize.h"

#define AUTHOR "Jeremiah Wala <jeremiah.wala@gmail.com>"

static const char *SEQTOOLS_USAGE_MESSAGE =
"----------------------------------------------------------------------\n"
"--- Seqtools - Useful (or not) command line tools for seq analysis ---\n"
"----------------------------------------------------------------------\n"
"Program: Seqtools \n"
"Contact: Jeremiah Wala [ jeremiah.wala@gmail.com ]\n"
"Usage: seqtools <command> [options]\n\n"
"Commands:\n"
"           rgtools        Move read groups from one BAM to another BAM, matching qname\n"
"           kmerize        Make kmers from a FASTA file\n"
"\nReport bugs on https://github.com/walaj/seqtools \n\n";

int main(int argc, char** argv) {

  if (argc <= 1) {
    std::cerr << SEQTOOLS_USAGE_MESSAGE;
    return 0;
  } else {
    std::string command(argv[1]);
    if (command == "help" || command == "--help") {
      std::cerr << SEQTOOLS_USAGE_MESSAGE;
      return 0;
    } else if (command == "rgtools") {
      runRGTools(argc -1, argv + 1);
    } else if (command == "kmerize") {
      runKmerize(argc-1, argv+1);
    }
    else {
      std::cerr << SEQTOOLS_USAGE_MESSAGE;
      return 0;
    }
  } 
  return 0;
}
