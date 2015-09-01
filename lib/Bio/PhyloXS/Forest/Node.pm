package Bio::PhyloXS::Forest::Node;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Forest::Node';
use Inline C => 'src/Node.c';
__PACKAGE__;
