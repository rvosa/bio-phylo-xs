package Bio::PhyloXS::Identifiable;
use Inline C => 'src/Identifiable.c';
use Carp;

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

sub DESTROY {
	my $self = shift;
	carp "destroying $self";
	my $class = ref $self;
	$class =~ s/.+://;
	my $destructor = 'destroy_' . lc $class;
	$self->$destructor;
}

__PACKAGE__;