#!/usr/bin/perl
use strict;
use warnings;
use Bio::PhyloXS::Matrices::Character;
use Bio::PhyloXS::Matrices::Characters;
use Bio::PhyloXS::Matrices::Datatype;
use Bio::PhyloXS::Matrices::Datum;
use Bio::PhyloXS::Matrices::Matrix;
use Test::More 'no_plan';

for ( qw(Character Characters Datatype Datum Matrix) ) {
	my $c1 = new_ok('Bio::PhyloXS::Matrices::' . $_);
	if ( $c1->isa('Bio::PhyloXS::Matrices::TypeSafeData') ) {
		my $to = $c1->get_type_object;
		isa_ok( $to, 'Bio::PhyloXS::Matrices::Datatype' );
	}
	ok( $c1->get_tag, ref($c1) . ' => ' . $c1->get_tag );
}