/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2009  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>

igraph_bool_t bfs_callback(const igraph_t *graph,
			   igraph_integer_t vid, 
			   igraph_integer_t pred, 
			   igraph_integer_t succ,
			   igraph_integer_t rank,
			   igraph_integer_t dist,
			   void *extra) {
  printf(" %li", (long int) vid);
  return 0;
}		   

int main() {
  
  igraph_t graph, ring;
  igraph_vector_t order, rank, father, pred, succ, dist;
  
  igraph_ring(&ring, 10, /*directed=*/ 0, /*mutual=*/ 0, /*circular=*/ 1);
  igraph_disjoint_union(&graph, &ring, &ring);
  igraph_destroy(&ring);
  
  igraph_vector_init(&order, 0);
  igraph_vector_init(&rank, 0);
  igraph_vector_init(&father, 0);
  igraph_vector_init(&pred, 0);
  igraph_vector_init(&succ, 0);
  igraph_vector_init(&dist, 0);
  
  igraph_bfs(&graph, /*root=*/0, /*neimode=*/ IGRAPH_OUT, 
	     &order, &rank, &father, &pred, &succ, &dist, 
	     /*callback=*/ 0, /*extra=*/ 0);
  
  igraph_vector_print(&order, stdout);
  igraph_vector_print(&rank, stdout);
  igraph_vector_print(&father, stdout);
  igraph_vector_print(&pred, stdout);
  igraph_vector_print(&succ, stdout);
  igraph_vector_print(&dist, stdout);

  igraph_vector_destroy(&order);
  igraph_vector_destroy(&rank);
  igraph_vector_destroy(&father);
  igraph_vector_destroy(&pred);
  igraph_vector_destroy(&succ);
  igraph_vector_destroy(&dist);

  /* Test the callback */

  igraph_bfs(&graph, /*root=*/ 0, /*neimode=*/ IGRAPH_OUT, 
	     0, 0, 0, 0, 0, 0, &bfs_callback, 0);
  printf("\n");
  
  igraph_destroy(&graph);
  
  return 0;
}
