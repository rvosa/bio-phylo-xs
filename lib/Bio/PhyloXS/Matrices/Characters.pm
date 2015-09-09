package Bio::PhyloXS::Matrices::Characters;
use base qw'Bio::PhyloXS::Matrices::TypeSafeData Bio::Phylo::Matrices::Characters';
use Inline C => 'src/Characters.c';
__PACKAGE__;