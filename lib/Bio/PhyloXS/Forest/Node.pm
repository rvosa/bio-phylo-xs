package Bio::PhyloXS::Forest::Node;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Forest::Node';
use Inline C => 'src/node.c';
__PACKAGE__;
