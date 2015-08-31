#!/usr/bin/perl
use strict;
use warnings;
use Node;
use Tree;
use Data::Dumper;
use Benchmark qw(:all);
use Bio::Phylo::Util::CONSTANT qw(:objecttypes);
use Devel::Peek;

sub run {
	my $prefix = shift || '';
	my $tree_package = $prefix . 'Tree';
	my $node_package = $prefix . 'Node';

	my $tree = $tree_package->new;
	my $root = $node_package->new( 
		'-rank'          => 'genus', 
		'-branch_length' => 0.342, 
		'-tree'          => $tree,
		'-name'          => 'root',
	);
	$tree->insert($root);

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

	$_->get_rank, for @{ $root->get_children };
	$tree->get_root->get_rank;
	$tree->to_newick;
}

timethese(1000, {
   'C'    => sub { run() },
   'Perl' => sub { run('Bio::Phylo::Forest::') },
});