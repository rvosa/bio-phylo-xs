package Bio::PhyloXS::Forest::Tree;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Forest::Tree';
use Inline C => 'src/tree.c';
__PACKAGE__;