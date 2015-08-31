package Tree;
use base qw'Listable Bio::Phylo::Forest::Tree';
use Inline C => './tree.c';
__PACKAGE__;