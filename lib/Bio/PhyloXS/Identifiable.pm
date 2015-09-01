package Bio::PhyloXS::Identifiable;
use Inline C => 'src/Identifiable.c';

sub new {
	my $class = shift;	
	my $self = $class->create;
	my %args = @_;
	for my $key ( keys %args ) {
		my $method = $key;
		$method =~ s/^-/set_/;
		$self->$method($args{$key});
	}
	return $self;
}

__PACKAGE__;