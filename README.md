Bio::PhyloXS
==============

Drop-in replacement of core Bio::Phylo modules implemented using Inline::C

Inline::C is really nice because it allows most of the code to be written in C, in 
separate files, without having to worry too much about the glue language XS, typemapping,
etc. However, a downside is that this doesn't distribute all that well on CPAN. We have
to pre-process the code to make it so that it becomes a package that can be installed 
with recent versions of ExtUtils::MakeMaker (the "standard" build/install system) and
without Inline::C. For this to work, the following needs to happen:

1. make sure you have InlineX::C2XS installed.
2. run the script `package_maker.pl` (possibly with the `--version x.x` flag)
3. step into the directory Bio-PhyloXS-x.x and do the usual `perl Makefile.PL && make dist`


