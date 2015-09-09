package Bio::PhyloXS::Matrices::Datum;
use base qw'Bio::PhyloXS::Matrices::TypeSafeData Bio::Phylo::Matrices::Datum';
use Inline C => 'src/Datum.c';
__PACKAGE__;