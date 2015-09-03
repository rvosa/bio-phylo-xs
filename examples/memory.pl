#!/usr/bin/perl
use strict;
use warnings;
use Devel::Peek;
use Devel::Refcount qw(refcount);
use Data::Dumper;
use Test::More 'no_plan';
use Bio::PhyloXS::Forest::Node;
use Bio::PhyloXS::Forest::Tree;

my $root;
{

	# instantiate an object. refcount should now be 1
	my $tree = Bio::PhyloXS::Forest::Tree->new;
	ok( refcount($tree) == 1, 'tree refcount expected: 1, observed: '.refcount($tree) );

	# instantiate an object. refcount should now be 1
	$root = Bio::PhyloXS::Forest::Node->new;
	ok( refcount($root) == 1, 'root refcount expected: 1, observed: '.refcount($root) );

	# instantiate an object. refcount should now be 1	
	my $c1 = Bio::PhyloXS::Forest::Node->new;
	ok( refcount($c1) == 1, 'c1 refcount expected: 1, observed: '.refcount($c1) );

	# insert object in other object. API increments refcount.
	$root->set_raw_child($c1);
	ok( refcount($c1) == 2, 'c1 refcount expected: 2, observed: '.refcount($c1) );

	# instantiate an object. refcount should now be 1	
	my $c2 = Bio::PhyloXS::Forest::Node->new;
	ok( refcount($c2) == 1, 'c2 refcount expected: 1, observed: '.refcount($c2) );

	# insert object in other object. API increments refcount.
	$root->set_raw_child($c2);
	ok( refcount($c2) == 2, 'c2 refcount expected: 2, observed: '.refcount($c2) );

	# container still has same refcount
	ok( refcount($root) == 1, 'root refcount expected: 1, observed: '.refcount($root) );

	# not an insertion, refcount unchanged
	$c1->set_raw_parent($root);
	ok( refcount($c1) == 2, 'c1 refcount expected: 2, observed: '.refcount($c1) );
	ok( refcount($root) == 1, 'root refcount expected: 1, observed: '.refcount($root) );
	
	# not an insertion, refcount unchanged
	$c2->set_raw_parent($root);
	ok( refcount($c2) == 2, 'c2 refcount expected: 2, observed: '.refcount($c2) );
	ok( refcount($root) == 1, 'root refcount expected: 1, observed: '.refcount($root) );

	# insert object in other object. API increments refcount.	
	$tree->insert($root);
	$tree->insert($c1);
	$tree->insert($c2);
	ok( refcount($root) == 2, 'root refcount expected: 2, observed: '.refcount($root) );
	ok( refcount($c1) == 3, 'c1 refcount expected: 3, observed: '.refcount($c1) );
	ok( refcount($c2) == 3, 'c2 refcount expected: 3, observed: '.refcount($c2) );
}

# tree destructor called, API decrements refcount.
ok( refcount($root) == 1, 'root refcount expected: 1, observed: '.refcount($root) );

# local symbols for children went out of scope, they're gone
print Dumper( $root->get_children );

