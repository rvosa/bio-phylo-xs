# The release version number. 
# TODO: convert to semantic versioning
VERSION=0.01

# Base package name, which also becomes
# the base name of the release
PACKAGE=Bio::PhyloXS

# Test folder. The ambition is that we can
# simply re-use the unit tests for Bio::Phylo,
# although these tests fail right now
TESTS=../bio-phylo/t

# Distribution name, i.e. the name stem
# of the release
BUILD=./Bio-PhyloXS

rm -rf ${BUILD}-${VERSION}

perl package_maker.pl \
	--version=$VERSION \
	--package=$PACKAGE \
	--t=$TESTS

cd ${BUILD}-${VERSION}
perl Makefile.PL
make

