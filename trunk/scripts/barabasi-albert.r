#! /usr/bin/R
library(igraph)
g <- barabasi.game(10000,directed=FALSE);
g

#average.path.length(g)
#shortest.paths(g)
#get.shortest.paths(g, 5)
#get.all.shortest.paths(g, 0, 5:7)
#average.path.length(g)

#degree.distribution(g)
