package Bio::PhyloXS::Forest::Node;
use base qw'Bio::PhyloXS::Listable Bio::Phylo::Forest::Node';
use Inline C => 'src/Node.c';
use Scalar::Util 'looks_like_number';
use Bio::Phylo::Util::Exceptions 'throw';

our $AUTOLOAD;
sub AUTOLOAD {
	my $self = shift;
	my $method = $AUTOLOAD;
	$method =~ s/.+:/Bio::Phylo::Forest::Node::/;
	$self->$method(@_);
}

sub set_branch_length {
	my ( $self, $bl ) = @_;
	my $id = $self->get_id;
	if ( defined $bl && looks_like_number $bl && !ref $bl ) {
		$self->set_raw_branch_length($bl);
	}
	elsif ( defined $bl && ( !looks_like_number $bl || ref $bl ) ) {
		throw 'BadNumber' => "Branch length \"$bl\" is a bad number";
	}
	elsif ( !defined $bl ) {
		$self->set_raw_branch_length();
	}
	return $self;
}


__PACKAGE__;
