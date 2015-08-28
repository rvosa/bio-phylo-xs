#!/usr/bin/perl
use strict;
use warnings;
use Node;
use Devel::Peek;

# amazingly, this all works
my $child = Node->new( '-branch_length' => 0.2342 );
print $child->get_id, "\n";
print $child->get_branch_length, "\n";

my $parent = Node->new( '-branch_length' => 0.7346 );
print $parent->get_id, "\n";
print $parent->get_branch_length, "\n";

$child->set_parent($parent);

print $child->get_parent->get_branch_length, "\n";

