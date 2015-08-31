package Node;
use base qw'Listable Bio::Phylo::Forest::Node';
use Inline C => './node.c';
__PACKAGE__;
