package Bio::PhyloXS::Forest::Node;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Forest::Node';
use Inline C => 'src/Node.c';

our $AUTOLOAD;
sub AUTOLOAD {
	my $self = shift;
	my $method = $AUTOLOAD;
	$method =~ s/.+:/Bio::Phylo::Forest::Node::/;
	$self->$method(@_);
}

__PACKAGE__;
