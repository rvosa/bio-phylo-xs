package Bio::PhyloXS::Matrices::Matrix;
use base qw'Bio::PhyloXS::Matrices::TypeSafeData Bio::Phylo::Matrices::Matrix';
use Inline C => 'src/Matrix.c';
__PACKAGE__;