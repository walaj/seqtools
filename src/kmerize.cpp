#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>

#include "kmerize.h"

#include <SeqLib/BWAWrapper.h>
#include <SeqLib/FastqReader.h>

static const char* shortopts = "hvk:s:";
static const struct option longopts[] = {
  { "help",                    no_argument, NULL, 'h' },
  { "verbose",                 no_argument, NULL, 'v' },
  { NULL, 0, NULL, 0 }
};

static const char *KMER_USAGE_MESSAGE =
  "Usage: seqtools kmer <fasta> -G <reference> -k <kmer_size> \n\n"
  "\n"
  "  General options\n"
  "  -v, --verbose                        Select verbose output\n"
  "  -h, --help                           Display this help and exit\n"
  "  -k, --kmer                           Size of the kmer to produce\n"
  "  -s, --seed                           Set the seed for the random number generator [0]\n"
  "\n";

namespace opt {
  static std::string fasta_file;
  static int seed = 0;
  static int kmer = -1;
  static bool verbose = false;
}

void runKmerize(int argc, char** argv) {
  
  parseKmerOptions(argc, argv);
  
  // setup the fasta/fastq reader
  SeqLib::FastqReader fr;
  fr.Open(std::string(opt::fasta_file));
  
  srand(opt::seed);

  // read the fasta/fastq file
  SeqLib::UnalignedSequence s;
  int count = 0;
  while (fr.GetNextSequence(s)) {
    if (s.Seq.length() > opt::kmer) {
      int r = rand() % (s.Seq.length() - opt::kmer);
      std::string ss = s.Seq.substr(r,opt::kmer);
      std::cout << ">seq" << count << std::endl << ss << std::endl;
    } 
    ++count;
  }
  
  return;
}

// do the matching
/*  std::string ref = std::string(argv[2]);
  if (opt::verbose)
    std::cerr << "Matching kmers against " << ref << std::endl;

  SeqLib::BWAWrapper bwa;
  std::cerr << "...loading the reference genome" << std::endl;
  bwa.LoadIndex(ref);

  const bool hardclip = false;
  const double secondary_cutoff = 0.90;
  const int secondary_cap = 100;
  const int kmer = 100;
  const int kmer_advance = 100;

  const std::string sep = "\t";
  for (auto& q : queries) {

    if (opt::verbose)
      std::cerr << "...doing the mapping for " << q.Name << " which is length " << q.Seq.length() << " or " << ((int)(q.Seq.length() / kmer_advance)) << " kmers" << std::endl;
    
    // kmer-ize
    for (size_t i = 0; i + kmer < q.Seq.length(); i += kmer_advance) {
      SeqLib::BamRecordVector results;
      bwa.AlignSequence(q.Seq.substr(i, i + kmer), q.Name, results, hardclip, secondary_cutoff, secondary_cap);
      std::cout << q.Name << sep << i << sep << results.size() << std::endl;
    }
  }

  return;
}
*/

void parseKmerOptions(int argc, char** argv) {

  bool die = false;

  if (argc <= 2) 
    die = true;

  bool help = false;
  std::stringstream ss;

  char c;
  while (optind < argc) {
    opt::fasta_file = std::string(argv[optind]);
    //optind++;
    if ((c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
      switch (c) {
      case 'h': help = true; break;
      case 'v': opt::verbose = true; break;
      case 'f': opt::fasta_file = std::string(optarg); break;
      case 'k': opt::kmer = atoi(optarg); break;
      case 's': opt::seed = atoi(optarg); break;
      default: break;
      }
    } else {
      ++optind;
    }
  }

  std::cerr << " FASTA " << opt::fasta_file << std::endl;
  if (opt::fasta_file.empty()) {
    std::cerr << "Must input a fasta/fastq file" << std::endl;
    std::cerr << KMER_USAGE_MESSAGE;
    exit(EXIT_FAILURE);
  }

  if (opt::kmer <= 0) {
    std::cerr << "Must input a kmer size > 0 (with -k flag)" << std::endl;
    std::cerr << KMER_USAGE_MESSAGE;
    exit(EXIT_FAILURE);
  }

  if (die || help) {
    std::cerr << "\n" << KMER_USAGE_MESSAGE;
    if (die)
      exit(EXIT_FAILURE);
    else 
      exit(EXIT_SUCCESS);	
  }
  
}
