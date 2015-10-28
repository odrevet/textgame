#!/usr/bin/perl -w
use strict;
use GraphViz;
use File::Basename;

my $g = GraphViz->new();
my %graph;					# %graph => {$file => ref %{$funct_name => @returns}}

sub set_graph
{
	my($file, %graph) = @_;
	open(INPUT, "<$file"); 		# open lua script
	my(@lines) = <INPUT>; 		# read
	my $i=0;
	my $cur_funct;
	
	do{		
		if($lines[$i] =~ /^dofile ?\(['"](.+)['"]\)/){
			my $script_path = File::Spec->rel2abs($1);
			print "from $file, file $script_path to check ? \n";
			if(!grep $script_path ~~ $_, keys(%graph)){
				$graph{$script_path} = {};
				%graph = set_graph($script_path, %graph);
			}else{
				print "\t$script_path is alderly checked... skip\n";
			}
		}
		
		if($lines[$i] =~ /^function ([\w]+)/){
			$cur_funct = $1;
		}
		
		if($lines[$i] =~ /return ['"]([\w]+)['"]/){
			push @{$graph{$file}->{$cur_funct}}, $1;
		}
		
		$i++;
	}while($lines[$i]);
	close(INPUT);	
	
	return %graph;
}

my $script_path = File::Spec->rel2abs($ARGV[0]);
$graph{$script_path} = {};
%graph = set_graph($script_path, %graph);

#build the graph
foreach my $file(keys(%graph)){
	print $file."\n";
	foreach my $funct_name (keys(%{$graph{$file}})){
		$g->add_node($funct_name, cluster => basename($file));
		foreach my $link (@{$graph{$file}->{$funct_name}}){
			if($link ne 'stay' && $link ne 'unknow'){
				$g->add_edge($funct_name => $link);
			}
		}
	}
}

$g->as_png("$ARGV[0].png"); # save image

1;