#!/usr/bin/perl
use warnings;
use strict;
use File::Find;
use File::Copy;
use File::Spec;
use File::Path 'make_path';
use Getopt::Long;
use InlineX::C2XS qw(c2xs);

# process command line arguments
my $lib     = './lib'; # root of the pure perl modules
my $build   = './Bio-PhyloXS'; # distribution name
my $version = '0.01'; # distribution version number
my $t       = '../bio-phylo/t'; # location of bio::phylo unit tests
my $src     = './src'; # location of header files
my $package = 'Bio::PhyloXS'; # package/release name
GetOptions(
	'lib=s'     => \$lib,
	'build=s'   => \$build,
	'version=f' => \$version,
	't=s'       => \$t,
	'package=s' => \$package,
);

# prepare build folder and src folder inside it
$build .= '-' . $version;
mkdir $build if not -d $build;
my $buildsrc = File::Spec->catdir( $build, 'src' );
mkdir $buildsrc if not -d $buildsrc;

# look for all *.h files in $src and copy them
find({
	'no_chdir' => 1,
	'wanted'   => sub {
		my $name = $File::Find::name;
		if ( $name =~ /\.h$/ ) {
			my ( $volume, $dir, $localfile ) = File::Spec->splitpath( $name );
			copy( $name, "$buildsrc/$localfile" );
		} 
	},
},$src);

# look for all *.pm files in $lib and process them
find({
	'no_chdir' => 1,
	'wanted'   => sub {
		my $name = $File::Find::name;
		process_module($name) if $name =~ /\.pm$/;
	},	
},$lib);

# copy typemap to build
copy( 'typemap', "$build/typemap" );

# copy unit tests to build
if ( -d 't' ) {
	opendir my $dh, 't';
	make_path( "$build/t" );
	while( my $entry = readdir $dh ) {
		copy( "t/$entry", "$build/t/$entry" ) if $entry =~ /\.t$/;
	}
}

# write Makefile.PL
open my $fh, '>', "$build/Makefile.PL";
print $fh <<"MAKEFILE_PL";
use ExtUtils::MakeMaker 7.24;

my \%parms = (
	'NAME'      => '$package',
	'INC'       => '-Isrc -I.',
	'VERSION'   => '$version',
	'AUTHOR'    => 'Rutger Vos',
	'LICENSE'   => 'perl',  
	'XSMULTI'   => 1,
	'ABSTRACT'  => 'Core modules for Bio::Phylo, re-implemented using C',
	'PREREQ_PM' => { 'Bio::Phylo' => '0.58' },  
);

if ( \$ExtUtils::MakeMaker::VERSION ge '6.46' ) {
    \$parms{META_MERGE} = {
        resources => {
            homepage    => 'http://biophylo.blogspot.com/',
            bugtracker  => 'https://github.com/rvosa/bio-phylo-xs/issues',
            repository  => 'git://github.com/rvosa/bio-phylo-xs.git',
            license     => 'http://dev.perl.org/licenses/',
            MailingList => 'mailto:bio-phylo\@googlegroups.com',
        },
    };
}

WriteMakefile( \%parms );

# Remove the Makefile dependency. Causes problems on a few systems.
sub MY::makefile { '' }

MAKEFILE_PL


# given the location of a perl module (.pm extension), 
# composes and executes the commands to run InlineX::C2XS::c2xs
# on the module. See perldoc InlineX::C2XS
sub process_module {
	my $file = shift;
	my ( $mod, $src, $pkg, @lines );
	
	# parse package name and C source location out of file, store other
	# lines to append them to the generated code
	{
		open my $fh, '<', $file or die "Can't open $file: $!";
		while(<$fh>) {		
			if ( /^package (\S+);/ ) {
				$mod = $1;
				$pkg = $mod; # in our case that's always the same
			}
			elsif ( /^use Inline C => '(\S+)';/ ) {
				$src = $1;
			}
			else {
				push @lines, $_;
			}	
		}
	}
	
	# some modules might be pure perl, skip processing if no $src
	if ( $mod and $src ) {
	
		# generate the XS code and the module
		my $hashref = {
			'VERSION'      => $version,
			'WRITE_PM'     => 1,
			'SRC_LOCATION' => $src,
		};
		c2xs($mod, $pkg, $build, $hashref);
		
		# append pure perl lines to the generated PM code
		$file =~ s/.+\//$build\//;
		my @generated;
		{
			open my $fh, '<', $file;
			@generated = <$fh>;
			pop @generated;
			pop @generated;
			push @generated, @lines;
		}
		
		# write the module, which is now a mixture of generated and
		# perl perl code, as well as the generated XS code, to the
		# lib/* subfolder structure inside $build. 
		{
			
			# make a new directory, e.g. Bio::PhyloXS => $build/lib/Bio/
			my @path = split /::/, $pkg;
			pop @path;
			my $newdir = File::Spec->catdir( $build, 'lib', @path );
			make_path($newdir) if not -d $newdir;
			
			# write modified module to $build/lib/Bio/PhyloXS.pm, remove old version
			my ( $volume, $dir, $localfile ) = File::Spec->splitpath($file);
			open my $fh, '>', "$newdir/$localfile";
			print $fh @generated;			
			unlink $file;			
			
			# write PhyloXS.xs to $build/lib/Bio/PhyloXS.xs
			$localfile =~ s/\.pm$/.xs/;
			move( "$build/$localfile", "$newdir/$localfile" );
		}
	}
	else {
		
		# copy verbatim
		my ( $volume, $dir, $localfile ) = File::Spec->splitpath($file);
		my $newdir = File::Spec->catdir( $build, $dir );
		make_path( $newdir ) if not -d $newdir;
		copy( $file, "$newdir/$localfile" );		
	}
}
