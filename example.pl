#!/usr/bin/perl
use strict;
use warnings;
use Node;
use Tree;
use Data::Dumper;
use Benchmark qw(:all);
use Bio::Phylo::Util::CONSTANT qw(:objecttypes);
use Devel::Peek;

my $tree = Tree->new;
my $root = Node->new( 
	'-rank'          => 'genus', 
	'-branch_length' => 0.342, 
	'-tree'          => $tree,
	'-name'          => 'root',
);
$tree->insert($root);

for ( 1 .. 2 ) {
	my $c = Node->new( 
		'-rank'          => 'species', 
		'-branch_length' => 0.789, 
		'-tree'          => $tree,
		'-name'          => "node$_",
	);
	$root->set_raw_child( $c );
	$c->set_raw_parent( $root );
	$tree->insert($c);
}

print $_->get_rank, "\n" for @{ $root->get_children };
print $tree->get_root->get_rank, "\n";
print $tree->to_newick;