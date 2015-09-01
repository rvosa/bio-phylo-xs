package Bio::PhyloXS::Listable;
use base 'Bio::PhyloXS::Identifiable';
use Inline C => 'src/Listable.c';
__PACKAGE__;