#!/usr/bin/perl
use strict;
use warnings;
use Node;
use Bio::Phylo::Forest::Node;
use Benchmark qw(:all);

# C nodes
my $child = Node->new;
$child->set_raw_parent(Node->new);
$child->get_parent->set_raw_child($child);