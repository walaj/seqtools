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
rgtools $OBAM $NBAM sample_name > mynewbam.bam
```

If need to parse the RG from the read names, then old and new are same:
```
OBAM=<original_bam_with_readgroups>
rgtools $OBAM $OBAM sample_name > mynewbam.bam
```

## Acknowledgments
-- Noah Greenwald for finding the problem :)
