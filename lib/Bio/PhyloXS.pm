package Bio::PhyloXS;
use Inline C => 'src/PhyloXS.c';
BEGIN {
	use Bio::Phylo::Factory;
	my $fac = Bio::Phylo::Factory->new;
	$fac->register_class('Bio::PhyloXS::Forest::Node');
	$fac->register_class('Bio::PhyloXS::Forest::Tree');
}
use version 0.77; our $VERSION = qv("v0.1.0");
__PACKAGE__