#!/usr/bin/perl
use strict;
use warnings;
use Devel::Peek;
use Data::Dumper;
use Bio::PhyloXS::Forest::Node;
use Bio::PhyloXS::Forest::Tree;

my ( $node, $count );
{
	$node = Bio::PhyloXS::Forest::Node->new;
	$node->set_raw_child(Bio::PhyloXS::Forest::Node->new);
	print Dumper($node->get_children);
	$node->DESTROY;	
}
print Dumper($node->get_children);
print $node->get_id, "\n";