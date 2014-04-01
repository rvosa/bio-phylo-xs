package Animal;
use Inline C => './animal.c';

sub new {
	my $class = shift;
	my %args = @_;
	my $self = $class->create;
	for my $key ( keys %args ) {
		my $method = $key;
		$method =~ s/^-/set_/;
		$self->$method($args{$key});
	}
	return $self;
}

__PACKAGE__;