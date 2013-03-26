#!/usr/bin/perl
# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/usr/targeting/common/genNodeMrwXml.pl $
#
# IBM CONFIDENTIAL
#
# COPYRIGHT International Business Machines Corp. 2013
#
# p1
#
# Object Code Only (OCO) source materials
# Licensed Internal Code Source Materials
# IBM HostBoot Licensed Internal Code
#
# The source code for this program is not published or otherwise
# divested of its trade secrets, irrespective of what has been
# deposited with the U.S. Copyright Office.
#
# Origin: 30
#
# IBM_PROLOG_END_TAG
#
# Usage:
#
# genNodeMrwXml.pl --system=systemname --mrwdir=pathname
#                  --build=hb/fsp --nodeCount=nodeCount
#                  [--help]
#                  
#        --system=systemname
#              Specify which system MRW XML to be generated. 
#              The file name will be set as uppercase 
#        --mrwdir=pathname
#              Specify the complete dir pathname of the MRW.
#        --build=hb/fsp
#              Specify if HostBoot build (hb) or FSP build (fsp)
#        --nodeCount
#              Specify the max number of nodes for the system
#        --help 
#             displays usage
#
# Purpose:
#
#   This perl script processes the various xml files of the Tuleta MRW to
#   extract the needed information for generating the final xml file.
#

use strict;
use XML::Simple;
use Data::Dumper;

################################################################################
# Set PREFERRED_PARSER to XML::Parser. Otherwise it uses XML::SAX which contains
# bugs that result in XML parse errors that can be fixed by adjusting white-
# space (i.e. parse errors that do not make sense).
################################################################################
$XML::Simple::PREFERRED_PARSER = 'XML::Parser';

################################################################################
#main
################################################################################
my $mrwdir = "";
my $sysname = "";
my $usage = 0;
my $nodeCount = 0;
my $build = "fsp";
use Getopt::Long;

GetOptions( "mrwdir:s"  => \$mrwdir,
            "system:s"  => \$sysname,
            "nodeCount:i" => \$nodeCount,
            "build:s"   => \$build,
            "help"      => \$usage, );


if ($usage || ($mrwdir eq "") || ($sysname eq ""))
{
    display_help();
    exit 0;
}

if ($nodeCount ==0)
{
    #no nodes so don't need to create node xml files
    exit 0;
}

#subtract one from the node count because want to start at zero to keep in sync
#with node numbering convention
$nodeCount--;

my $SYSNAME = uc($sysname);

my $outFile = "";
my @nodeOutFiles;

my $sysInfo;
my $fileSuffix;

if ($build eq "fsp")
{
    $fileSuffix="fsp";
}
elsif ($build eq "hb")
{
    $fileSuffix="hb";
}
else
{
    die "ERROR: $build is not valid. Valid values are fsp or hb\n";
}


#create files
open (FH, "<$mrwdir/${SYSNAME}_${fileSuffix}.mrw.xml") ||
        die "ERROR: unable to open $mrwdir/${SYSNAME}_${fileSuffix}.mrw.xml\n";
close (FH);

$sysInfo = XMLin("$mrwdir/${SYSNAME}_${fileSuffix}.mrw.xml",
                ForceArray=>1);
#print Dumper($sysInfo);
for my $j(0..($nodeCount))
{
    $outFile = "$mrwdir/${SYSNAME}_node_$j"."_${fileSuffix}.mrw.xml";
    push @nodeOutFiles, [$outFile];
}

#create file discriptor array
my @nodeFD;

for my $k(0..$#nodeOutFiles)
{
    my $filename= sprintf("%s",@{$nodeOutFiles[$k]});

    open $nodeFD[$k], '>', $filename ||
        die "ERROR: unable to create $filename\n";
}

#read in the targeting data from system xml files
foreach my $targetInstance (@{$sysInfo->{targetInstance}})
{
    my $Id = $targetInstance->{'id'};
    my $targetId = sprintf("%s",@{$Id});
    #print("targetId =", $targetId, "\n");
    my $xmlData= XMLout($targetInstance,RootName => "targetInstance");  
    #print Dumper($xmlData);
    if ($targetId eq "sys0")
    {
        for my $node(0..$nodeCount)
        {
            print {$nodeFD[$node]} $xmlData;
        }
    }
    else 
    {
        my $nodeValue = $targetId;
        $nodeValue =~ s/.*node(\d?).*/$1/;
        #print("nodeValue = ",$nodeValue,"\n");

        if ($nodeValue < $#nodeFD) 
        {
            print {$nodeFD[$nodeValue]} $xmlData;
        }
        else
        {
            die "ERROR: node value($nodeValue) is not in the range of possible nodes\n";
        }
    }

}

#close file descriptors
for my $k(0..$#nodeOutFiles)
{
    my $filename= sprintf("%s",@{$nodeOutFiles[$k]});

    close $nodeFD[$k] ||
        die "ERROR: unable to close $filename\n";
}

exit 0;

################################################################################
#subroutines below
################################################################################
#subroutines below

sub display_help
{
    use File::Basename;
    my $scriptname = basename($0);
    print STDERR "
Usage:
    $scriptname --help
        --help
             displays usage


    $scriptname --system=sysname --mrwdir=pathname
                     --build=hb --nodeCount=nodeCount
        --system=systemname
              Specify which system MRW XML to be generated
               The system name will be set as uppercase
        --mrwdir=pathname
              Specify the complete dir pathname of the MRW.
        --build=hb/fsp
              Specify if HostBoot build (hb) or FSP build (fsp)
        --nodeCount
              Specify the max number of nodes for the system

\n";
}
