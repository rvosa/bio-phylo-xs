#!/usr/bin/perl
use strict;
use warnings;
use Bio::PhyloXS::Forest::Node;
use Bio::PhyloXS::Forest::Tree;
use Benchmark qw(:all);

sub run {

	# establish package names to call constructors on
	my $prefix = shift || '';
	my $tree_package = $prefix . 'Tree';
	my $node_package = $prefix . 'Node';

	# instantiate basal node in tree
	my $tree = $tree_package->new;
	my $root = $node_package->new( 
		'-rank'          => 'genus', 
		'-branch_length' => 0.342, 
		'-tree'          => $tree,
		'-name'          => 'root',
	);
	$tree->insert($root);

	# create two child nodes
	for ( 1 .. 2 ) {
		my $c = $node_package->new( 
			'-rank'          => 'species', 
			'-branch_length' => 0.789, 
			'-tree'          => $tree,
			'-name'          => "node$_",
		);
		$root->set_raw_child( $c );
		$c->set_raw_parent( $root );
		$tree->insert($c);
	}

	# do some lookups	
	$_->get_rank, for @{ $root->get_children };
	$tree->get_root->get_rank;
	$tree->to_newick;
}

timethese(10000, {
   'C'    => sub { run('Bio::PhyloXS::Forest::') },
   'Perl' => sub { run('Bio::Phylo::Forest::') },
});