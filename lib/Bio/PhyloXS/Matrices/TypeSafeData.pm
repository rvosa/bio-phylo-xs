package Bio::PhyloXS::Matrices::TypeSafeData;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Matrices::TypeSafeData';
use Inline C => 'src/TypeSafeData.c';
__PACKAGE__;