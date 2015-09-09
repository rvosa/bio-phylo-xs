package Bio::PhyloXS::Matrices::Datatype;
use base qw'Bio::PhyloXS::NeXML::Writable Bio::Phylo::Matrices::Datatype';
use Inline C => 'src/Datatype.c';
__PACKAGE__;