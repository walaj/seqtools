```
git clone --recursive https://github.com/walaj/rgtools 
cd rgtools/SeqLib 
./configure ## configure SeqLib and build
make CXXFLAGS=-std=c++14
cd ..
make ## build rgtools
```

```
OBAM=<original_bam_with_readgroups>
NBAM=<new_bam_without_readgroup>
rgtools $OBAM $NBAM > mynewbam.bam
```

## Acknowledgments
-- Noah Greenwald for generating the problem :)
