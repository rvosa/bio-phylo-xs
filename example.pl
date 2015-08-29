#!/usr/bin/perl
use strict;
use warnings;
use Node;
use Data::Dumper;
use Benchmark qw(:all);
use Bio::Phylo::Util::CONSTANT qw(:objecttypes);
use Devel::Peek;

# C nodes
my $child = Node->new;
my $parent = Node->new;
$child->set_raw_parent($parent);
$parent->set_raw_child($child);
$parent->set_raw_child( Node->new => 1 );
print Dumper($parent->get_children);

Dump($child);

if ( $child->_type == _NODE_ ) {
	print "It's a node\n";
}