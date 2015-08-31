package Identifiable;
use Inline C => './identifiable.c';
#use Bio::Phylo::Util::MOP;

sub new {
	my $class = shift;	
	my $self = $class->create;
#	my $init = Bio::Phylo::Util::MOP->get_implementations( 'initialize', $class );
#	$_->{code}->($self) for @$init;
	my %args = @_;
	for my $key ( keys %args ) {
		my $method = $key;
		$method =~ s/^-/set_/;
		$self->$method($args{$key});
	}
	return $self;
}

__PACKAGE__;