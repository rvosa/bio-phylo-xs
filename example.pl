#!/usr/bin/perl
use strict;
use warnings;
use Cat;

# amazingly, this all works
my $cat = Cat->new( '-name' => 'Rutger', '-legs' => 2 );
$cat->set_owner('Alva');
print $cat->get_owner, "\n";
