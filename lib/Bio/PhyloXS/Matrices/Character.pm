package Bio::PhyloXS::Matrices::Character;
use base qw'Bio::PhyloXS::Matrices::TypeSafeData Bio::Phylo::Matrices::Character';
use Inline C => 'src/Character.c';
__PACKAGE__;