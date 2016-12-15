package Bio::PhyloXS::Util::Exceptions;
use base 'Bio::Phylo::Util::Exceptions';
use Inline C => 'src/Exceptions.c';

sub Bio::Phylo::Util::Exceptions::error {
	Bio::PhyloXS::Util::Exceptions::error(shift);
}

sub Bio::Phylo::Util::Exceptions::trace {
	Bio::Phylo::Util::StackTrace->new;
}

__PACKAGE__