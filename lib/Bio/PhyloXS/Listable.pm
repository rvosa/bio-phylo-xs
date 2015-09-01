package Bio::PhyloXS::Listable;
use base 'Bio::PhyloXS::Identifiable';
use Inline C => 'src/listable.c';
__PACKAGE__;