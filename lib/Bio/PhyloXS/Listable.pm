package Bio::PhyloXS::Listable;
use base 'Bio::PhyloXS::NeXML::Writable';
use Inline C => 'src/Listable.c';
__PACKAGE__;